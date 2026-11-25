// F-006 — Save Document (testes de unidade)
// Cobre os cenários T1-T15 do design doc docs/architecture/F-006-SaveDocument.md
// (e as regras R1-R4, E1-E7 da spec docs/features/F-006.md).
// Inclui E10 + needBackupOnSave (rollback do backup não-incremental) com injeção
// determinística de falha do serializer — ver testE10* abaixo.
#include <QtTest/QtTest>
#include <QTemporaryDir>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QJsonDocument>
#include <QCryptographicHash>
#include <cstdlib>
#include <iostream>

#include "../../src/document/document_model.h"
#include "../../src/document/document_save_manager.h"
#include "../../src/document/document_serializer.h"

using namespace ArtPlus;

class TestSaveDocument : public QObject {
    Q_OBJECT
private:
    Document makeDoc() {
        Document d;
        d.setModified(true);
        return d;
    }

    WriteOptions baseOpts() {
        WriteOptions o;
        o.isSaveAs = false;
        o.isSaveAsCopy = false;
        o.isSaveUnmodified = false;
        o.needBackupOnSave = false;
        o.isIncrementalSave = false;
        o.noOptimizedSave = false;
        o.flavour = SaveFlavour::NormalPdf;
        o.encryption.encryptionLevel = 0;
        return o;
    }

    // Bytes crus do arquivo (vazio se não existir).
    static QByteArray fileBytes(const QString& path) {
        QFile f(path);
        if (!f.open(QIODevice::ReadOnly))
            return QByteArray();
        return f.readAll();
    }

    // SHA-256 em hex maiúsculo; vazio se o arquivo não existir.
    static QByteArray sha256File(const QString& path) {
        const QByteArray data = fileBytes(path);
        if (data.isEmpty() && !QFile::exists(path))
            return QByteArray();
        return QCryptographicHash::hash(data, QCryptographicHash::Sha256).toHex().toUpper();
    }

    // ---------------------------------------------------------------- E10 helper
    // Usuário no formato DOMINIO\usuario aceito por icacls.
    static QString currentUserForIclacls() {
        const QString user = qEnvironmentVariable("USERNAME");
        const QString domain = qEnvironmentVariable("USERDOMAIN");
        if (user.isEmpty())
            return QString();
        return domain.isEmpty() ? user : domain + "\\" + user;
    }

    // Nega FILE_WRITE_DATA (WD) ao usuário atual no arquivo indicado, mantendo
    // DELETE concedido. Depois verifica de fato que QFile::open(WriteOnly) falha.
    // Retorna false se o ACE não pôde ser aplicado OU se a escrita não foi
    // realmente bloqueada — nesse caso o teste é declarado condicional (QSKIP),
    // nunca um verde vazio.
    static bool denyWriteData(const QString& path) {
        const QString user = currentUserForIclacls();
        if (user.isEmpty())
            return false;
        // std::system evita depender de event loop (QTEST_APPLESS_MAIN não tem
        // QCoreApplication) e de QProcess.
        const QString cmd = QString("icacls \"%1\" /deny \"%2:(WD)\" >NUL 2>&1")
                                .arg(QDir::toNativeSeparators(path), user);
        const int rc = std::system(cmd.toLocal8Bit().constData());
        if (rc != 0)
            return false;
        QFile probe(path);
        const bool blocked = !probe.open(QIODevice::WriteOnly);
        if (!blocked)
            probe.close();
        return blocked;
    }

private slots:
    // ---------------------------------------------------------------- T1
    void testT1SaveValidPathCreatesFile() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("valid.artplus");

        Document doc = makeDoc();
        doc.setFilePath(path); // same path → isSaveAs stays false
        DocumentSaveManager mgr(doc);

        SaveResult r = mgr.save(path, baseOpts());

        QVERIFY2(r.ok, qPrintable("save failed: " + r.errorMessage));
        QCOMPARE(r.filePath, path);
        QCOMPARE(r.errorCode, 0);
        QVERIFY(r.errorMessage.isEmpty());
        QVERIFY(QFile::exists(path));

        // The file must be valid JSON .artplus
        QFile f(path);
        QVERIFY(f.open(QIODevice::ReadOnly));
        QJsonDocument jdoc = QJsonDocument::fromJson(f.readAll());
        f.close();
        QVERIFY(jdoc.isObject());
        QCOMPARE(jdoc.object().value("format").toString(), QString("artplus"));

        // Finalização: filePath e modified atualizados
        QCOMPARE(doc.filePath(), path);
        QVERIFY(!doc.modified());
    }

    // ---------------------------------------------------------------- T2
    void testT2SaveAsNewPath() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString newPath = dir.filePath("saveas.artplus");
        QString oldPath = dir.filePath("original.artplus");

        Document doc = makeDoc();
        doc.setFilePath(oldPath);
        WriteOptions opts = baseOpts();
        opts.isSaveAs = true;

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(newPath, opts);

        QVERIFY2(r.ok, qPrintable("save failed: " + r.errorMessage));
        QCOMPARE(r.filePath, newPath);
        QVERIFY(QFile::exists(newPath));
        // Save As (not copy) → caminho/título atualizados
        QCOMPARE(doc.filePath(), newPath);
        QVERIFY(!doc.modified());
    }

    // ---------------------------------------------------------------- T3
    void testT3SaveIncrementalWithNoOptimizedSave() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("incremental.artplus");

        // Base file first
        {
            Document base = makeDoc();
            base.setFilePath(path);
            DocumentSaveManager m(base);
            SaveResult r = m.save(path, baseOpts());
            QVERIFY(r.ok);
        }

        Document doc = makeDoc();
        doc.setFilePath(path);
        WriteOptions opts = baseOpts();
        opts.isIncrementalSave = true;
        opts.noOptimizedSave = true;

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(path, opts);

        QVERIFY2(r.ok, qPrintable("save failed: " + r.errorMessage));
        QVERIFY(QFile::exists(path));
        // Serializer always performs a full save in v1 (TODO(F-006)); the flag
        // is recorded but does not change the outcome. Verify the file is valid.
        QFile f(path);
        QVERIFY(f.open(QIODevice::ReadOnly));
        QVERIFY(QJsonDocument::fromJson(f.readAll()).isObject());
        f.close();
    }

    void testT3IncrementalNoBaseFallsBackToFullSave() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("incremental_nobase.artplus");
        // Ensure no base exists
        QFile::remove(path);

        Document doc = makeDoc();
        doc.setFilePath(path);
        WriteOptions opts = baseOpts();
        opts.isIncrementalSave = true;

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(path, opts);

        // Destination inexistente → flag forçada a false (R2/E5); save prossegue como completo
        QVERIFY2(r.ok, qPrintable("save failed: " + r.errorMessage));
        QVERIFY(QFile::exists(path));
    }

    // ---------------------------------------------------------------- T4
    void testT4FlavourPreflightReturnsExplicitError() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("preflight.artplus");

        Document doc = makeDoc();
        doc.setFilePath(path);
        WriteOptions opts = baseOpts();
        opts.flavour = SaveFlavour::Preflight;

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(path, opts);

        QVERIFY(!r.ok);
        QCOMPARE(r.errorCode, 8); // SaveException(8)
        QVERIFY(!r.errorMessage.isEmpty());
        // Nenhum arquivo gravado
        QVERIFY(!QFile::exists(path));
    }

    // ---------------------------------------------------------------- T5
    void testT5FlavourSeparationsReturnsExplicitError() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("separations.artplus");

        Document doc = makeDoc();
        doc.setFilePath(path);
        WriteOptions opts = baseOpts();
        opts.flavour = SaveFlavour::Separations;

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(path, opts);

        QVERIFY(!r.ok);
        QCOMPARE(r.errorCode, 8); // SaveException(8)
        QVERIFY(!r.errorMessage.isEmpty());
        QVERIFY(!QFile::exists(path));
    }

    // ---------------------------------------------------------------- T6
    void testT6EncryptionReturnsExplicitError() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("encrypted.artplus");

        Document doc = makeDoc();
        doc.setFilePath(path);
        WriteOptions opts = baseOpts();
        opts.encryption.encryptionLevel = 1;
        opts.encryption.ownerPassword = "owner";
        opts.encryption.userPassword = "user";

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(path, opts);

        QVERIFY(!r.ok);
        QVERIFY(!r.errorMessage.isEmpty());
        // Nenhum arquivo gravado
        QVERIFY(!QFile::exists(path));
    }

    // ---------------------------------------------------------------- T7 (design doc T5/T6): backup
    void testT7BackupRenameMovesOriginalToBak() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("backup.artplus");

        // Pre-create destination with marker content (original)
        {
            QFile f(path);
            QVERIFY(f.open(QIODevice::WriteOnly));
            f.write("ORIGINAL_CONTENT");
            f.close();
        }

        Document doc = makeDoc();
        doc.setFilePath(path);
        WriteOptions opts = baseOpts();
        opts.needBackupOnSave = true;
        opts.isIncrementalSave = false;

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(path, opts);

        QVERIFY2(r.ok, qPrintable("save failed: " + r.errorMessage));
        // Backup path derived as <dest>.bak
        QCOMPARE(r.backupPath, path + ".bak");
        QVERIFY(QFile::exists(path + ".bak"));

        // Backup contains the OLD content (rename moved original)
        QFile bak(path + ".bak");
        QVERIFY(bak.open(QIODevice::ReadOnly));
        QCOMPARE(bak.readAll(), QByteArray("ORIGINAL_CONTENT"));
        bak.close();
    }

    void testT7BackupIncrementalCopiesOriginalToBak() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("backup_inc.artplus");

        {
            QFile f(path);
            QVERIFY(f.open(QIODevice::WriteOnly));
            f.write("ORIGINAL_CONTENT");
            f.close();
        }

        Document doc = makeDoc();
        doc.setFilePath(path);
        WriteOptions opts = baseOpts();
        opts.needBackupOnSave = true;
        opts.isIncrementalSave = true;

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(path, opts);

        QVERIFY2(r.ok, qPrintable("save failed: " + r.errorMessage));
        QCOMPARE(r.backupPath, path + ".bak");
        QVERIFY(QFile::exists(path + ".bak"));
        // Both files exist (copy, not rename)
        QVERIFY(QFile::exists(path));

        QFile bak(path + ".bak");
        QVERIFY(bak.open(QIODevice::ReadOnly));
        QCOMPARE(bak.readAll(), QByteArray("ORIGINAL_CONTENT"));
        bak.close();
    }

    // ---------------------------------------------------------------- E10 (rollback)
    // F-006 / E10 + needBackupOnSave (backup não-incremental = rename).
    //
    // Como a falha do serializer é forçada DEPOIS do rename bem-sucedido:
    //   1. DocumentSaveManager::save emite progressStatus("STATUS_SAVE") de forma
    //      SÍNCRONA (mesma thread, antes de DocumentSerializer::save) logo após o
    //      bloco R3.4 que renomeia <dest> → <dest>.bak. O teste conecta um slot
    //      nesse sinal; logo não há corrida nem sleep.
    //   2. No slot o teste confirma que o destino NÃO existe mais e que <dest>.bak
    //      existe — prova de que o rename já ocorreu — e então cria um arquivo
    //      placeholder no destino e nega FILE_WRITE_DATA ("WD") ao usuário atual
    //      via `icacls <placeholder> /deny "<DOMINIO\usuario>:(WD)"`. DELETE
    //      permanece concedido.
    //   3. DocumentSerializer::save faz QFile::open(QIODevice::WriteOnly) nesse
    //      destino → access denied → retorna false (E10 real, sem mock).
    //   4. O rollback do manager remove o placeholder (DELETE permitido) e renomeia
    //      <dest>.bak de volta para <dest>.
    // O mecanismo foi verificado no ambiente (deny WD bloqueia open-for-write e
    // permite DeleteFile). Se o ACE não puder ser aplicado/verificado, o teste é
    // declarado condicional (QSKIP) com a limitação explícita — não passa vazio.
    void testE10NeedBackupRollbackRestoresOriginalOnSerializerFailure() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        const QString path = dir.filePath("e10_rollback.artplus");
        const QString bakPath = path + ".bak";
        const QByteArray original("ORIGINAL_CONTENT_E10_ROLLBACK\n");

        {
            QFile f(path);
            QVERIFY(f.open(QIODevice::WriteOnly));
            f.write(original);
            f.close();
        }
        const QByteArray shaBefore = sha256File(path);
        QVERIFY(!shaBefore.isEmpty());

        Document doc = makeDoc();
        doc.setFilePath(path); // mesmo caminho → IsSaveAs == false → backup elegível

        WriteOptions opts = baseOpts();
        opts.needBackupOnSave = true;
        opts.isIncrementalSave = false; // R3.4: rename

        DocumentSaveManager mgr(doc);

        bool injectionAttempted = false;
        bool destMissingAtInjection = false;
        bool bakPresentAtInjection = false;
        bool injectionArmed = false;
        QObject::connect(&mgr, &DocumentSaveManager::progressStatus,
                         [&](const QString& status) {
                             if (status != QLatin1String("STATUS_SAVE") || injectionAttempted)
                                 return;
                             injectionAttempted = true;
                             destMissingAtInjection = !QFileInfo::exists(path);
                             bakPresentAtInjection = QFileInfo::exists(bakPath);
                             if (!destMissingAtInjection || !bakPresentAtInjection)
                                 return; // não estamos no ponto esperado do R3.4
                             QFile placeholder(path);
                             if (!placeholder.open(QIODevice::WriteOnly))
                                 return;
                             placeholder.write("PARTIAL_WRITE_PLACEHOLDER");
                             placeholder.close();
                             injectionArmed = denyWriteData(path);
                         });

        SaveResult r = mgr.save(path, opts);

        QVERIFY2(injectionAttempted, "E10: progressStatus(STATUS_SAVE) não foi emitido");
        QVERIFY2(destMissingAtInjection,
                 "E10: o destino ainda existia no STATUS_SAVE — o rename R3.4 não ocorreu");
        QVERIFY2(bakPresentAtInjection,
                 "E10: <dest>.bak ausente no STATUS_SAVE — o backup R3.4 não ocorreu");
        if (!injectionArmed) {
            QSKIP("F-006 E10 condicional: não foi possível negar FILE_WRITE_DATA via icacls "
                  "neste ambiente; falha do serializer pós-rename não injetável. "
                  "Mecanismo e limitação registrados em docs/testing/gates/F-006-E10-rollback.md.");
        }

        // E10: falha declarada com SaveException(8)
        QVERIFY2(!r.ok, "E10: a falha injetada do serializer deve reprovar o save");
        QCOMPARE(r.errorCode, 8);
        QVERIFY2(!r.errorMessage.isEmpty(), "E10: mensagem de erro obrigatória");
        // Rollback bem-sucedido: o .bak foi consumido pelo rename de volta.
        QVERIFY2(r.backupPath.isEmpty(),
                 qPrintable("E10: rollback consumiu o .bak, backupPath deve ficar vazio, veio '"
                            + r.backupPath + "'"));
        QVERIFY2(r.errorMessage.contains(QStringLiteral("restaurado")),
                 qPrintable("E10: mensagem deve indicar restauração, veio: " + r.errorMessage));
        QVERIFY2(!r.errorMessage.contains(QStringLiteral("rollback do backup falhou")),
                 qPrintable("E10: não deveria cair no ramo de rollback falho: " + r.errorMessage));

        // Destino EXISTE com o conteúdo ORIGINAL (bytes e sha iguais)
        QVERIFY2(QFile::exists(path), "E10: o destino precisa existir após o rollback");
        QCOMPARE(fileBytes(path), original);
        QCOMPARE(sha256File(path), shaBefore);

        // Nenhum .bak remanescente e nenhum resíduo
        QVERIFY2(!QFile::exists(bakPath), "E10: nenhum .bak pode remanescer após o rollback");
        QCOMPARE(QDir(dir.path()).entryList(QStringList() << "*.bak", QDir::Files).size(), 0);

        // Documento não corrompido / sem estado de sucesso
        QCOMPARE(doc.filePath(), path);
        QVERIFY2(doc.modified(), "E10: save falho não pode limpar o dirty state");
    }

    // F-006 / E10 com backup INCREMENTAL (R3.3 = copy): não há rollback e o destino
    // NUNCA é apagado pelo caminho de falha. Mesmo ponto de injeção (STATUS_SAVE),
    // mas aqui o destino ainda existe e o backup é uma CÓPIA — o teste comprova a
    // diferença observável: .bak preserva o original e backupPath continua preenchido.
    void testE10IncrementalBackupDoesNotRollbackNorDeleteDestination() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        const QString path = dir.filePath("e10_incremental.artplus");
        const QString bakPath = path + ".bak";
        const QByteArray original("ORIGINAL_CONTENT_E10_INCREMENTAL\n");

        {
            QFile f(path);
            QVERIFY(f.open(QIODevice::WriteOnly));
            f.write(original);
            f.close();
        }
        const QByteArray shaBefore = sha256File(path);
        QVERIFY(!shaBefore.isEmpty());

        Document doc = makeDoc();
        doc.setFilePath(path);

        WriteOptions opts = baseOpts();
        opts.needBackupOnSave = true;
        opts.isIncrementalSave = true; // R3.3: copy

        DocumentSaveManager mgr(doc);

        bool injectionAttempted = false;
        bool destPresentAtInjection = false;
        bool bakPresentAtInjection = false;
        bool injectionArmed = false;
        QObject::connect(&mgr, &DocumentSaveManager::progressStatus,
                         [&](const QString& status) {
                             if (status != QLatin1String("STATUS_SAVE") || injectionAttempted)
                                 return;
                             injectionAttempted = true;
                             destPresentAtInjection = QFileInfo::exists(path);
                             bakPresentAtInjection = QFileInfo::exists(bakPath);
                             if (!destPresentAtInjection || !bakPresentAtInjection)
                                 return;
                             // Substitui o destino por um placeholder sem tocar no .bak.
                             QFile::remove(path);
                             QFile placeholder(path);
                             if (!placeholder.open(QIODevice::WriteOnly))
                                 return;
                             placeholder.write("PARTIAL_WRITE_PLACEHOLDER_INC");
                             placeholder.close();
                             injectionArmed = denyWriteData(path);
                         });

        SaveResult r = mgr.save(path, opts);

        QVERIFY2(injectionAttempted, "E10-inc: progressStatus(STATUS_SAVE) não foi emitido");
        QVERIFY2(destPresentAtInjection && bakPresentAtInjection,
                 "E10-inc: no backup incremental destino e .bak devem coexistir no STATUS_SAVE");
        if (!injectionArmed) {
            QSKIP("F-006 E10 condicional (backup incremental): não foi possível negar "
                  "FILE_WRITE_DATA via icacls neste ambiente. Ver "
                  "docs/testing/gates/F-006-E10-rollback.md.");
        }

        QVERIFY2(!r.ok, "E10-inc: a falha injetada do serializer deve reprovar o save");
        QCOMPARE(r.errorCode, 8);
        QVERIFY(!r.errorMessage.isEmpty());
        // Sem rollback: o backup não-incremental não foi usado; .bak continua no disco.
        QCOMPARE(r.backupPath, bakPath);
        QVERIFY2(QFile::exists(bakPath), "E10-inc: o .bak do backup incremental permanece");
        QCOMPARE(fileBytes(bakPath), original);
        QCOMPARE(sha256File(bakPath), shaBefore);
        // O destino nunca é apagado pelo caminho de falha (segue sendo o placeholder).
        QVERIFY2(QFile::exists(path), "E10-inc: o caminho de falha não pode apagar o destino");
        QCOMPARE(fileBytes(path), QByteArray("PARTIAL_WRITE_PLACEHOLDER_INC"));

        QCOMPARE(doc.filePath(), path);
        QVERIFY2(doc.modified(), "E10-inc: save falho não pode limpar o dirty state");
    }

    // ---------------------------------------------------------------- D1a
    // F-006 / regressão D1a (achado de auditoria 2026-11-24): o backup NÃO pode
    // ser executado antes do guard de criptografia. Destino existente com conteúdo
    // conhecido + encryptionLevel=1 + needBackupOnSave=true →
    //   ok == false, errorCode == 0 (E8), destino intacto, nenhum .bak criado.
    void testD1aEncryptionGuardRunsBeforeBackup() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("d1a_encrypted.artplus");
        const QByteArray original("ORIGINAL_CONTENT_D1A\n");

        {
            QFile f(path);
            QVERIFY(f.open(QIODevice::WriteOnly));
            f.write(original);
            f.close();
        }
        const QByteArray shaBefore = sha256File(path);
        QVERIFY(!shaBefore.isEmpty());

        Document doc = makeDoc();
        doc.setFilePath(path); // mesmo caminho → IsSaveAs == false (backup seria elegível)
        WriteOptions opts = baseOpts();
        opts.encryption.encryptionLevel = 1;
        opts.encryption.ownerPassword = "owner";
        opts.encryption.userPassword = "user";
        opts.needBackupOnSave = true;

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(path, opts);

        // E8: falha declarada, sem código de SaveException
        QVERIFY2(!r.ok, "save com criptografia deve falhar");
        QCOMPARE(r.errorCode, 0);
        QVERIFY(!r.errorMessage.isEmpty());
        QVERIFY(r.backupPath.isEmpty());

        // Nenhuma escrita: destino existe com os mesmos bytes e nenhum .bak
        QVERIFY(QFile::exists(path));
        QCOMPARE(sha256File(path), shaBefore);
        QCOMPARE(fileBytes(path), original);
        QVERIFY2(!QFile::exists(path + ".bak"), "D1a: backup não pode ser criado no caminho de erro");
        QCOMPARE(QDir(dir.path()).entryList(QStringList() << "*.bak", QDir::Files).size(), 0);

        // Estado do documento não muda
        QCOMPARE(doc.filePath(), path);
        QVERIFY(doc.modified());
    }

    // ---------------------------------------------------------------- D1b
    // F-006 / regressão D1b: o backup NÃO pode anteceder o guard de flavour.
    // Destino existente + flavour=Preflight + needBackupOnSave=true →
    //   ok == false, errorCode == 8, destino intacto, nenhum .bak.
    void testD1bFlavourGuardRunsBeforeBackup() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("d1b_preflight.artplus");
        const QByteArray original("ORIGINAL_CONTENT_D1B\n");

        {
            QFile f(path);
            QVERIFY(f.open(QIODevice::WriteOnly));
            f.write(original);
            f.close();
        }
        const QByteArray shaBefore = sha256File(path);
        QVERIFY(!shaBefore.isEmpty());

        Document doc = makeDoc();
        doc.setFilePath(path);
        WriteOptions opts = baseOpts();
        opts.flavour = SaveFlavour::Preflight;
        opts.needBackupOnSave = true;

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(path, opts);

        // E9: SaveException(8)
        QVERIFY2(!r.ok, "save com flavour Preflight deve falhar");
        QCOMPARE(r.errorCode, 8);
        QVERIFY(!r.errorMessage.isEmpty());
        QVERIFY(r.backupPath.isEmpty());

        QVERIFY(QFile::exists(path));
        QCOMPARE(sha256File(path), shaBefore);
        QCOMPARE(fileBytes(path), original);
        QVERIFY2(!QFile::exists(path + ".bak"), "D1b: backup não pode ser criado no caminho de erro");
        QCOMPARE(QDir(dir.path()).entryList(QStringList() << "*.bak", QDir::Files).size(), 0);

        QCOMPARE(doc.filePath(), path);
        QVERIFY(doc.modified());
    }

    // ---------------------------------------------------------------- E5
    // F-006 / regressão E5: Save para caminho INEXISTENTE em documento sem
    // filePath prévio → comportamento de Save As, arquivo criado e
    // doc.filePath() atualizado.
    void testE5SaveToNonExistentPathBehavesAsSaveAs() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("e5_brand_new.artplus");
        QVERIFY(!QFile::exists(path));

        Document doc = makeDoc(); // sem filePath prévio
        QVERIFY(doc.filePath().isEmpty());

        WriteOptions opts = baseOpts(); // isSaveAs == false na entrada
        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(path, opts);

        QVERIFY2(r.ok, qPrintable("save failed: " + r.errorMessage));
        QCOMPARE(r.errorCode, 0);
        QVERIFY(QFile::exists(path));
        // Save As: caminho adotado pelo documento e dirty limpo
        QCOMPARE(doc.filePath(), path);
        QVERIFY(!doc.modified());
        // Arquivo gravado é .artplus válido
        QFile f(path);
        QVERIFY(f.open(QIODevice::ReadOnly));
        QJsonDocument jdoc = QJsonDocument::fromJson(f.readAll());
        f.close();
        QVERIFY(jdoc.isObject());
        QCOMPARE(jdoc.object().value("format").toString(), QString("artplus"));
    }

    // E5 (variante discriminante): filePath do documento aponta para um arquivo
    // inexistente e o destino também não existe — os dois canonicalFilePath()
    // valem "" e sem a correção E5 IsSaveAs ficaria false. Com
    // needBackupOnSave=true, IsSaveAs=false entraria no bloco de backup e
    // preencheria backupPath; IsSaveAs forçado a true → nenhum backup.
    void testE5BothPathsNonExistentForcesSaveAsNoBackup() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString stale = dir.filePath("e5_stale_missing.artplus");
        QString path = dir.filePath("e5_target.artplus");
        QVERIFY(!QFile::exists(stale));
        QVERIFY(!QFile::exists(path));

        Document doc = makeDoc();
        doc.setFilePath(stale);
        WriteOptions opts = baseOpts();
        opts.needBackupOnSave = true; // sem E5, o bloco de backup seria alcançado
        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(path, opts);

        QVERIFY2(r.ok, qPrintable("save failed: " + r.errorMessage));
        QVERIFY(QFile::exists(path));
        QCOMPARE(doc.filePath(), path);
        QVERIFY(!doc.modified());
        // E5 → IsSaveAs == true (R3.5: nenhum backup em Save As)
        QVERIFY2(r.backupPath.isEmpty(), "E5: Save As forçado não pode derivar backup");
        QVERIFY2(!QFile::exists(path + ".bak"), "E5: nenhum .bak deve ser criado");
    }

    // ---------------------------------------------------------------- T8
    void testT8SaveUnmodifiedSkipsStateUpdate() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("unmodified.artplus");
        QString otherPath = dir.filePath("other.artplus");

        Document doc;
        doc.setFilePath(otherPath);
        doc.setModified(true);
        WriteOptions opts = baseOpts();
        opts.isSaveUnmodified = true;

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(path, opts);

        QVERIFY2(r.ok, qPrintable("save failed: " + r.errorMessage));
        QVERIFY(QFile::exists(path));
        // E6: isSaveUnmodified → pula setFilePath e setModified
        QCOMPARE(doc.filePath(), otherPath);
        QVERIFY(doc.modified());
    }

    // ---------------------------------------------------------------- T2/E7 Save As Copy
    void testT2SaveAsCopyKeepsOriginalPathAndModified() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString newPath = dir.filePath("copy.artplus");
        QString origPath = dir.filePath("original.artplus");

        Document doc;
        doc.setFilePath(origPath);
        doc.setModified(true);
        WriteOptions opts = baseOpts();
        opts.isSaveAs = true;
        opts.isSaveAsCopy = true;

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(newPath, opts);

        QVERIFY2(r.ok, qPrintable("save failed: " + r.errorMessage));
        QVERIFY(QFile::exists(newPath));
        // E7: Save As Copy → não atualiza caminho nem dirty
        QCOMPARE(doc.filePath(), origPath);
        QVERIFY(doc.modified());
    }

    // ---------------------------------------------------------------- T9
    void testT9SaveInvalidPathReturnsGenericError() {
        QString invalidPath = "Z:\\nonexistent_dir_xyz\\save_test.artplus";

        Document doc = makeDoc();
        doc.setFilePath(invalidPath);
        WriteOptions opts = baseOpts();

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(invalidPath, opts);

        QVERIFY(!r.ok);
        QCOMPARE(r.errorCode, 8); // generic SaveException(8)
        QVERIFY(!r.errorMessage.isEmpty());
    }

    // ---------------------------------------------------------------- T10
    void testT10WriteFailureReturnsGenericError() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        // Parent directory does not exist → serializer fails to open file
        QString badPath = dir.filePath("no_such_subdir/save.artplus");

        Document doc = makeDoc();
        doc.setFilePath(badPath);
        WriteOptions opts = baseOpts();

        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.save(badPath, opts);

        QVERIFY(!r.ok);
        QCOMPARE(r.errorCode, 8);
        QVERIFY(!r.errorMessage.isEmpty());
    }

    // ---------------------------------------------------------------- T11
    void testT11RevertToSavedReturnsFalse() {
        Document doc;
        DocumentSaveManager mgr(doc);
        QVERIFY(!mgr.revertToSaved());
    }

    // ---------------------------------------------------------------- T12 + T13
    void testT12ProgressStatusEmittedDuringSave() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("signals.artplus");

        Document doc = makeDoc();
        doc.setFilePath(path);
        WriteOptions opts = baseOpts();

        DocumentSaveManager mgr(doc);
        QSignalSpy progressSpy(&mgr, &DocumentSaveManager::progressStatus);

        mgr.save(path, opts);

        // STATUS_SAVE and STATUS_WRITING_TO_DISK are emitted on success
        QVERIFY(progressSpy.count() >= 1);
        QCOMPARE(progressSpy.at(0).at(0).toString(), QString("STATUS_SAVE"));
    }

    void testT13FinishedEmittedWithSaveResult() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("finished.artplus");

        Document doc = makeDoc();
        doc.setFilePath(path);
        WriteOptions opts = baseOpts();

        DocumentSaveManager mgr(doc);
        SaveResult captured;
        bool capturedFlag = false;
        QObject::connect(&mgr, &DocumentSaveManager::finished,
                         [&captured, &capturedFlag](const SaveResult& res) {
                             captured = res;
                             capturedFlag = true;
                         });

        QSignalSpy finishedSpy(&mgr, &DocumentSaveManager::finished);
        SaveResult r = mgr.save(path, opts);

        QCOMPARE(finishedSpy.count(), 1);
        QVERIFY(capturedFlag);
        QVERIFY(captured.ok);
        QCOMPARE(captured.filePath, path);
        QCOMPARE(r.ok, true);
    }

    void testT13FinishedEmittedOnError() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("finished_err.artplus");

        Document doc = makeDoc();
        doc.setFilePath(path);
        WriteOptions opts = baseOpts();
        opts.flavour = SaveFlavour::Preflight;

        DocumentSaveManager mgr(doc);
        QSignalSpy finishedSpy(&mgr, &DocumentSaveManager::finished);

        mgr.save(path, opts);

        QCOMPARE(finishedSpy.count(), 1);
    }

    // ---------------------------------------------------------------- T14 (cancelamento — não implementado)
    // Não há API de cancelamento em v1 (TODO(F-006)); nada a testar.
    // Reportado como "não implementado" na entrega.

    // ---------------------------------------------------------------- deriveBackupPath
    void testDeriveBackupPath() {
        QCOMPARE(DocumentSaveManager::deriveBackupPath("C:/x/y.artplus"),
                 QString("C:/x/y.artplus.bak"));
    }

    // ---------------------------------------------------------------- saveDocument
    void testSaveDocumentDelegatesToSave() {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        QString path = dir.filePath("savedoc.artplus");

        Document doc = makeDoc();
        doc.setFilePath(path);
        DocumentSaveManager mgr(doc);
        SaveResult r = mgr.saveDocument(path, baseOpts());

        QVERIFY2(r.ok, qPrintable("save failed: " + r.errorMessage));
        QVERIFY(QFile::exists(path));
    }

    // ---------------------------------------------------------------- fromSaveOptions (TODO)
    void testFromSaveOptionsDefault() {
        WriteOptions o = WriteOptions::fromSaveOptions("ignored");
        QVERIFY(!o.isSaveAs);
        QVERIFY(!o.isIncrementalSave);
        QCOMPARE(o.flavour, SaveFlavour::NormalPdf);
    }
};

QTEST_APPLESS_MAIN(TestSaveDocument)
#include "test_save_document.moc"