// F-006 — Save Document (testes de unidade)
// Cobre os cenários T1-T15 do design doc docs/architecture/F-006-SaveDocument.md
// (e as regras R1-R4, E1-E7 da spec docs/features/F-006.md).
#include <QtTest/QtTest>
#include <QTemporaryDir>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
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