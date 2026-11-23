// F-002 — Mark Set (DocumentMarks.dll, v24.03.10017).
// Testes unitários de MarkSetProcessor (src/prepress/markset_processor.h/.cpp).
//
// Evidência do contrato (rag/evidence/F-002/ghidra/):
//   R1 ReadMarkSetFile        GHIDRA-DocumentMarks-0x180248D30
//   R2 PrepareMarksCachePage  GHIDRA-DocumentMarks-0x180248720
//   R3 ApplyMarksFromSet      GHIDRA-DocumentMarks-0x180243EC0
//      CopyMarksToPageWithLog GHIDRA-DocumentMarks-0x180245380
//      CopyMarksToPage        GHIDRA-DocumentMarks-0x1800426F0
//   R4 ApplyRelevantMarkSets  GHIDRA-DocumentMarks-0x18024D460 (critério não derivado)
//
// Contrato REAL verificado aqui (lido de src/prepress/markset_processor.h/.cpp):
//   - Ordem obrigatória: setTargetDocument -> prepareMarksCachePage -> applyMarksFromSet.
//   - loadMarkSetFile(): arquivo inexistente -> "MarkSetFileDoesNotExist"; extensão fora de
//     .pdf/.artplus/.json -> "WrongMarkSet"; conteúdo inválido -> "MarkSetFileError".
//   - copyMarksToPage(): copia a PRIMEIRA página do mark set para a página alvo (que precisa
//     pertencer ao documento de destino), com ObjectIds novos, sem alterar a origem;
//     devolve a contagem em lastCopiedObjectCount(). Segunda chamada ANEXA.
//   - identifyRelevantSets(): vazio (TODO(F-002): critério de R4 não derivado; ids fixos
//     seriam simulação).
//
// Observação de modelo: Document::Document() nasce vazio (tests/unit/test_main.cpp:13);
// página/camada são criadas explicitamente, como em tests/unit/test_cut_mark.cpp:110.
//
// Não é usada fixture em disco para o caso de sucesso: o documento de mark set é montado em
// memória. O único arquivo escrito é um .artplus temporário (QTemporaryDir) para exercitar
// applyMarksFromSet ponta a ponta.

#include <QtTest/QTest>
#include <QFile>
#include <QRectF>
#include <QTemporaryDir>

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "../../src/prepress/markset_processor.h"
#include "../../src/document/document_model.h"
#include "../../src/document/document_serializer.h"

using namespace ArtPlus;

namespace {

struct DocFixture {
    PageId page = 0;
    LayerId layer = 0;
};

// Página + camada explícitas (o construtor de Document não cria nenhuma das duas).
DocFixture setupPage(Document& doc, const QString& layerName = QStringLiteral("Layer 1"))
{
    auto layer = std::make_shared<Layer>(layerName);
    doc.addLayer(layer);

    auto page = std::make_shared<Page>();
    page->addLayer(layer->id());
    doc.addPage(page);

    return DocFixture{page->id(), layer->id()};
}

std::shared_ptr<PathObject> addPath(Document& doc, LayerId layerId, const QString& name,
                                    bool inLayer = true)
{
    auto path = std::make_shared<PathObject>();
    path->setName(name);
    path->setLayerId(layerId);
    path->addMove(QPointF(0.0, 0.0));
    path->addLine(QPointF(20.0, 0.0));
    path->addLine(QPointF(20.0, 20.0));
    path->closePath();
    doc.addObject(path);
    if (inLayer) {
        if (auto layer = doc.layer(layerId)) layer->addObject(path->id());
    }
    return path;
}

std::shared_ptr<ClippingMaskObject> addClipMask(Document& doc, LayerId layerId)
{
    auto mask = std::make_shared<ClippingMaskObject>();
    mask->setName(QStringLiteral("clip"));
    mask->setLayerId(layerId);
    mask->addMove(QPointF(0.0, 0.0));
    mask->addLine(QPointF(5.0, 0.0));
    mask->addLine(QPointF(5.0, 5.0));
    doc.addObject(mask);
    // Não entra na camada: é alcançável apenas por clipMaskIds(), como num PDF real.
    return mask;
}

// Documento de mark set com grafo não trivial:
//   camada: path "p1", grupo "g" (filhos c1, c2 fora da camada), path "clipped"
//   "clipped" referencia um ClippingMaskObject fora da camada.
// Total de objetos alcançáveis a partir da página = 6.
std::vector<ObjectId> buildMarkSet(Document& source)
{
    const DocFixture f = setupPage(source, QStringLiteral("Mark Set"));

    auto p1 = addPath(source, f.layer, QStringLiteral("p1"));
    auto group = std::make_shared<GroupObject>();
    group->setName(QStringLiteral("g"));
    group->setLayerId(f.layer);
    source.addObject(group);
    source.layer(f.layer)->addObject(group->id());

    auto c1 = addPath(source, f.layer, QStringLiteral("c1"), false);
    auto c2 = addPath(source, f.layer, QStringLiteral("c2"), false);
    c1->setParentId(group->id());
    c2->setParentId(group->id());
    group->addChild(c1->id());
    group->addChild(c2->id());

    auto clipped = addPath(source, f.layer, QStringLiteral("clipped"));
    auto mask = addClipMask(source, f.layer);
    clipped->addClipMaskId(mask->id());

    return {p1->id(), group->id(), clipped->id(), c1->id(), c2->id(), mask->id()};
}

std::unordered_set<ObjectId> toSet(const std::vector<ObjectId>& ids)
{
    return std::unordered_set<ObjectId>(ids.begin(), ids.end());
}

} // namespace

class TestMarkSetProcessor : public QObject {
    Q_OBJECT

private slots:
    // F-002 / R4: enquanto o critério de "mark set relevante" não for derivado da
    // evidência (GHIDRA-DocumentMarks-0x18024D460), o contrato é lista vazia.
    void test_identifyRelevantSets_emptyUntilCriterionIsDerived()
    {
        MarkSetProcessor processor;

        const std::vector<std::string> sets = processor.identifyRelevantSets();
        QVERIFY2(sets.empty(), "ids fixos seriam simulação (TODO(F-002) em R4)");

        // Estável entre chamadas.
        QVERIFY(processor.identifyRelevantSets().empty());
    }

    // F-002 / R2 (GHIDRA-DocumentMarks-0x180248720): lê a geometria da página alvo.
    void test_prepareMarksCachePage_trueAndReadsPageBoxes()
    {
        MarkSetProcessor processor;
        Page page;

        // Page usa contador estático iniciado em 1: id sempre válido (> 0).
        QVERIFY(page.id() > 0u);

        // PageBoxes padrão declarado em document_model.h (595 x 842 pt).
        QVERIFY(qFuzzyCompare(page.boxes().cropBox.width(), 595.0));
        QVERIFY(qFuzzyCompare(page.boxes().cropBox.height(), 842.0));
        QVERIFY(qFuzzyCompare(page.pageRect().width(), page.boxes().cropBox.width()));

        QVERIFY(processor.prepareMarksCachePage(page));

        // Funciona igual com boxes alterados (o processor só lê a geometria).
        page.boxes().cropBox = QRectF(10.0, 20.0, 300.0, 400.0);
        QVERIFY(qFuzzyCompare(page.pageRect().width(), 300.0));
        QVERIFY(processor.prepareMarksCachePage(page));
    }

    // F-002 / R2: com documento de destino definido, a página alvo precisa pertencer a ele.
    void test_prepareMarksCachePage_rejectsPageOutsideTargetDocument()
    {
        Document target;
        const DocFixture t = setupPage(target);

        MarkSetProcessor processor;
        processor.setTargetDocument(target);

        Page foreign;
        QVERIFY(!processor.prepareMarksCachePage(foreign));
        QVERIFY2(processor.lastError().find("does not belong to the target document")
                     != std::string::npos,
                 processor.lastError().c_str());

        // Sem página válida preparada, applyMarksFromSet recusa (ordem obrigatória).
        QVERIFY(!processor.applyMarksFromSet("markset.pdf"));
        QVERIFY2(processor.lastError().find("no target page prepared") != std::string::npos,
                 processor.lastError().c_str());

        // A página correta continua aceita.
        QVERIFY(processor.prepareMarksCachePage(*target.page(t.page)));
    }

    // F-002 / R2: página sem geometria utilizável -> recusa (WrongMarkSet).
    void test_prepareMarksCachePage_rejectsPageWithoutGeometry()
    {
        MarkSetProcessor processor;
        Page page;
        page.boxes().cropBox = QRectF(); // largura/altura zero, rect inválido

        QVERIFY(!processor.prepareMarksCachePage(page));
        QVERIFY2(processor.lastError().find("no usable geometry") != std::string::npos,
                 processor.lastError().c_str());
    }

    // F-002 / R1: arquivo inexistente -> MarkSetFileDoesNotExist.
    void test_loadMarkSetFile_missingFile_reportsMarkSetFileDoesNotExist()
    {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());

        MarkSetProcessor processor;
        Document markSet;
        QVERIFY(!processor.loadMarkSetFile(dir.filePath("nao-existe.pdf").toStdString(), markSet));
        QVERIFY2(processor.lastError().find("MarkSetFileDoesNotExist") != std::string::npos,
                 processor.lastError().c_str());
    }

    // F-002 / R1: extensão fora de .pdf/.artplus/.json -> WrongMarkSet.
    void test_loadMarkSetFile_unknownExtension_reportsWrongMarkSet()
    {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        const QString path = dir.filePath("markset.xyz");
        {
            QFile file(path);
            QVERIFY(file.open(QIODevice::WriteOnly));
            file.write("nao e um mark set");
        }

        MarkSetProcessor processor;
        Document markSet;
        QVERIFY(!processor.loadMarkSetFile(path.toStdString(), markSet));
        QVERIFY2(processor.lastError().find("WrongMarkSet") != std::string::npos,
                 processor.lastError().c_str());
    }

    // F-002 / R1: .artplus inválido -> MarkSetFileError (não WrongMarkSet).
    void test_loadMarkSetFile_corruptArtplus_reportsMarkSetFileError()
    {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        const QString path = dir.filePath("quebrado.artplus");
        {
            QFile file(path);
            QVERIFY(file.open(QIODevice::WriteOnly));
            file.write("{ isto nao e json valido");
        }

        MarkSetProcessor processor;
        Document markSet;
        QVERIFY(!processor.loadMarkSetFile(path.toStdString(), markSet));
        QVERIFY2(processor.lastError().find("MarkSetFileError") != std::string::npos,
                 processor.lastError().c_str());
    }

    // F-002 / R3: sem documento de destino, a cópia é recusada.
    void test_copyMarksToPage_withoutTargetDocument_returnsFalse()
    {
        MarkSetProcessor processor;

        Document source;
        const DocFixture s = setupPage(source);
        addPath(source, s.layer, QStringLiteral("p1"));

        Document target;
        const DocFixture t = setupPage(target);

        QVERIFY(!processor.copyMarksToPage(source, *target.page(t.page)));
        QVERIFY2(processor.lastError().find("no target document") != std::string::npos,
                 processor.lastError().c_str());
        QCOMPARE(processor.lastCopiedObjectCount(), 0);
    }

    // F-002 / R3: página alvo que não pertence ao documento de destino.
    void test_copyMarksToPage_targetPageOutsideDocument_returnsFalse()
    {
        MarkSetProcessor processor;

        Document source;
        const DocFixture s = setupPage(source);
        addPath(source, s.layer, QStringLiteral("p1"));

        Document target;
        setupPage(target);
        processor.setTargetDocument(target);

        Page foreign;
        QVERIFY(!processor.copyMarksToPage(source, foreign));
        QVERIFY2(processor.lastError().find("does not belong to the target document")
                     != std::string::npos,
                 processor.lastError().c_str());
        QCOMPARE(processor.lastCopiedObjectCount(), 0);
    }

    // F-002 / R3: documento de mark set sem páginas.
    void test_copyMarksToPage_emptySourceDocument_returnsFalse()
    {
        MarkSetProcessor processor;

        Document source; // nasce vazio
        QVERIFY(source.pageOrder().empty());

        Document target;
        const DocFixture t = setupPage(target);
        processor.setTargetDocument(target);

        QVERIFY(!processor.copyMarksToPage(source, *target.page(t.page)));
        QVERIFY2(processor.lastError().find("source document has no pages") != std::string::npos,
                 processor.lastError().c_str());
        QCOMPARE(processor.lastCopiedObjectCount(), 0);
    }

    // F-002 / R3: primeira página do mark set sem nenhum objeto (WrongMarkSet).
    void test_copyMarksToPage_sourcePageWithoutObjects_returnsFalse()
    {
        MarkSetProcessor processor;

        Document source;
        setupPage(source); // página + camada, nenhum objeto
        QCOMPARE(source.objects().size(), 0u);

        Document target;
        const DocFixture t = setupPage(target);
        processor.setTargetDocument(target);

        QVERIFY(!processor.copyMarksToPage(source, *target.page(t.page)));
        QVERIFY2(processor.lastError().find("has no objects") != std::string::npos,
                 processor.lastError().c_str());
        QCOMPARE(processor.lastCopiedObjectCount(), 0);
    }

    // F-002 / R3 (GHIDRA-DocumentMarks-0x1800426F0): cópia do grafo da primeira página com
    // ids novos, preservando origem e conteúdo do destino; segunda aplicação ANEXA.
    void test_copyMarksToPage_copiesGraphWithNewIdsAndAppends()
    {
        MarkSetProcessor processor;

        Document source;
        const std::vector<ObjectId> sourceIds = buildMarkSet(source);
        QCOMPARE(sourceIds.size(), 6u);
        QCOMPARE(source.objects().size(), 6u);
        const std::vector<ObjectId> sourceIdsBefore = source.objectIds();
        const LayerId sourceLayerId = source.layerOrder().front();
        const std::vector<ObjectId> sourceLayerBefore = source.layer(sourceLayerId)->objects();
        QCOMPARE(static_cast<int>(sourceLayerBefore.size()), 3);

        Document target;
        const DocFixture t = setupPage(target);
        auto existing = addPath(target, t.layer, QStringLiteral("existente"));
        QCOMPARE(target.objects().size(), 1u);

        processor.setTargetDocument(target);
        QVERIFY2(processor.prepareMarksCachePage(*target.page(t.page)),
                 processor.lastError().c_str());

        QVERIFY2(processor.copyMarksToPage(source, *target.page(t.page)),
                 processor.lastError().c_str());
        QCOMPARE(processor.lastCopiedObjectCount(), 6);
        QCOMPARE(target.objects().size(), 7u);
        QVERIFY2(processor.lastError().empty(), processor.lastError().c_str());

        const std::unordered_set<ObjectId> sourceSet = toSet(sourceIds);

        // Nenhum id do mark set foi reaproveitado no destino.
        std::vector<ObjectId> copied;
        for (ObjectId id : target.objectIds()) {
            if (id == existing->id()) continue;
            QVERIFY2(sourceSet.count(id) == 0, "id do destino colide com id da origem");
            QVERIFY2(target.object(id) != nullptr, "objeto copiado ausente no destino");
            QVERIFY2(source.object(id) == nullptr, "objeto copiado existe na origem");
            copied.push_back(id);
        }
        QCOMPARE(static_cast<int>(copied.size()), 6);

        // Conteúdo anterior do destino preservado, na mesma camada.
        auto targetLayer = target.layer(t.layer);
        QVERIFY(targetLayer != nullptr);
        QCOMPARE(static_cast<int>(targetLayer->objects().size()), 7);
        QCOMPARE(targetLayer->objects().front(), existing->id());
        QCOMPARE(target.object(existing->id()), existing);

        // Filhos do grupo copiado são ids do destino, não da origem.
        bool sawGroup = false;
        bool sawClip = false;
        for (ObjectId id : copied) {
            auto object = target.object(id);
            if (object->type() == ObjectType::Group) {
                sawGroup = true;
                QCOMPARE(static_cast<int>(object->children().size()), 2);
                for (ObjectId child : object->children()) {
                    QVERIFY2(sourceSet.count(child) == 0, "filho aponta para id da origem");
                    QVERIFY2(target.object(child) != nullptr, "filho ausente no destino");
                }
            }
            for (ObjectId clip : object->clipMaskIds()) {
                sawClip = true;
                QVERIFY2(sourceSet.count(clip) == 0, "clipMask aponta para id da origem");
                QVERIFY2(target.object(clip) != nullptr, "clipMask ausente no destino");
            }
        }
        QVERIFY2(sawGroup, "grupo copiado não encontrado");
        QVERIFY2(sawClip, "objeto com clipMask copiado não encontrado");

        // Origem intacta: mesmos ids, mesma contagem, mesma camada.
        const std::vector<ObjectId> sourceIdsAfter = source.objectIds();
        QCOMPARE(static_cast<int>(sourceIdsAfter.size()), 6);
        QCOMPARE(toSet(sourceIdsAfter), toSet(sourceIdsBefore));
        QCOMPARE(static_cast<int>(source.pageOrder().size()), 1);
        QCOMPARE(static_cast<int>(source.objects().size()), 6);
        for (ObjectId id : sourceIds) {
            QVERIFY2(source.object(id) != nullptr, "origem perdeu objeto após a cópia");
        }
        QCOMPARE(static_cast<int>(source.layer(sourceLayerId)->objects().size()), 3);
        QVERIFY(source.layer(sourceLayerId)->objects() == sourceLayerBefore);

        // Segunda aplicação ANEXA (7 -> 13), não substitui.
        QVERIFY2(processor.copyMarksToPage(source, *target.page(t.page)),
                 processor.lastError().c_str());
        QCOMPARE(processor.lastCopiedObjectCount(), 6);
        QCOMPARE(target.objects().size(), 13u);
        QCOMPARE(static_cast<int>(targetLayer->objects().size()), 13);
        QCOMPARE(static_cast<int>(source.objects().size()), 6);
    }

    // F-002 / R3: ordem obrigatória setTargetDocument -> prepareMarksCachePage.
    void test_applyMarksFromSet_requiresTargetDocumentAndPreparedPage()
    {
        MarkSetProcessor processor;

        QVERIFY(!processor.applyMarksFromSet("markset.pdf"));
        QVERIFY2(processor.lastError().find("no target document") != std::string::npos,
                 processor.lastError().c_str());

        Document target;
        setupPage(target);
        processor.setTargetDocument(target);

        QVERIFY(!processor.applyMarksFromSet("markset.pdf"));
        QVERIFY2(processor.lastError().find("no target page prepared") != std::string::npos,
                 processor.lastError().c_str());
        QCOMPARE(processor.lastCopiedObjectCount(), 0);
        QCOMPARE(target.objects().size(), 0u);
    }

    // F-002 / R1+R3: caminho vazio é MarkSetFileDoesNotExist, não copy.
    void test_applyMarksFromSet_emptyPath_reportsMarkSetFileDoesNotExist()
    {
        Document target;
        const DocFixture t = setupPage(target);

        MarkSetProcessor processor;
        processor.setTargetDocument(target);
        QVERIFY(processor.prepareMarksCachePage(*target.page(t.page)));

        QVERIFY(!processor.applyMarksFromSet(std::string()));
        QVERIFY2(processor.lastError().find("MarkSetFileDoesNotExist") != std::string::npos,
                 processor.lastError().c_str());
        QCOMPARE(target.objects().size(), 0u);
    }

    // F-002 / R3: mark set válido mas sem páginas -> MarkSetFileError (nada escrito no destino).
    void test_applyMarksFromSet_emptyMarkSetFile_returnsFalse()
    {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());

        Document emptyMarkSet; // nasce sem páginas
        const QString path = dir.filePath("vazio.artplus");
        QVERIFY(DocumentSerializer::save(emptyMarkSet, path));

        Document target;
        const DocFixture t = setupPage(target);

        MarkSetProcessor processor;
        processor.setTargetDocument(target);
        QVERIFY(processor.prepareMarksCachePage(*target.page(t.page)));

        QVERIFY(!processor.applyMarksFromSet(path.toStdString()));
        QVERIFY2(processor.lastError().find("no pages") != std::string::npos,
                 processor.lastError().c_str());
        QCOMPARE(processor.lastCopiedObjectCount(), 0);
        QCOMPARE(target.objects().size(), 0u);
    }

    // F-002 / R1+R3 ponta a ponta: mark set .artplus real (escrito em QTemporaryDir) é
    // carregado e a primeira página é copiada para o destino preparado.
    void test_applyMarksFromSet_copiesFirstPageOfArtplusFile()
    {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());

        Document markSet;
        buildMarkSet(markSet);
        QCOMPARE(markSet.objects().size(), 6u);

        const QString path = dir.filePath("markset.artplus");
        QVERIFY2(DocumentSerializer::save(markSet, path), "não foi possível gravar a fixture");
        QVERIFY(QFile::exists(path));

        Document target;
        const DocFixture t = setupPage(target);

        MarkSetProcessor processor;
        processor.setTargetDocument(target);
        QVERIFY2(processor.prepareMarksCachePage(*target.page(t.page)),
                 processor.lastError().c_str());

        QVERIFY2(processor.applyMarksFromSet(path.toStdString()), processor.lastError().c_str());
        QCOMPARE(processor.lastCopiedObjectCount(), 6);
        QCOMPARE(target.objects().size(), 6u);
        QCOMPARE(static_cast<int>(target.objects().size()), 6);

        // A página de mark set não foi alterada no arquivo carregado (a cópia é no destino).
        Document reloaded;
        QVERIFY(DocumentSerializer::load(path, reloaded));
        QCOMPARE(static_cast<int>(reloaded.objects().size()), 6);
    }

    // Documenta por que o caso "targetPage.id() == 0" não é testado: a API pública de Page
    // atribui id a partir de Page::nextId (iniciado em 1) e não expõe setter.
    void test_pageApi_cannotBuildInvalidTarget()
    {
        Page a;
        Page b;
        QVERIFY(a.id() > 0u);
        QVERIFY(b.id() > 0u);
        QVERIFY(a.id() != b.id());
    }
};

QTEST_APPLESS_MAIN(TestMarkSetProcessor)
#include "test_markset_processor.moc"
