# -*- coding: utf-8 -*-
import json, os

out = r"H:\Desktop\ArtPlus\rag\evidence\F-001\manifest.json"
static = [
    "GHIDRA-DocumentMarks-0x1801344E0",
    "GHIDRA-DocumentMarks-0x180136190",
    "GHIDRA-DocumentMarks-0x180134B00",
    "GHIDRA-DocumentMarks-0x180172100",
    "GHIDRA-DocumentMarks-0x180135160",
    "GHIDRA-DocumentMarks-0x1800AA1B0",
    "GHIDRA-DocumentMarks-0x1800A9FB0",
    "GHIDRA-DocumentMarks-0x180134F60",
    "GHIDRA-DocumentMarks-0x180135670",
    "GHIDRA-DocumentMarks-0x180135660",
    "GHIDRA-DocumentMarks-0x18010E0F0",
    "GHIDRA-DocumentMarks-0x180051F90",
    "GHIDRA-DocumentMarks-0x180052950",
    "GHIDRA-DocumentMarks-0x180052470",
    "GHIDRA-DocumentMarks-0x180052700",
    "GHIDRA-DocumentMarks-0x180243EC0",
    "GHIDRA-DocumentMarks-0x180245380",
    "GHIDRA-DocumentMarks-0x180134880",
    "GHIDRA-DocumentMarks-0x180135930",
    "GHIDRA-DocumentMarks-0x180135CB0",
    "GHIDRA-DocumentMarks-0x180134830",
    "GHIDRA-DocumentMarks-0x18012A130",
    "GHIDRA-DocumentMarks-0x1801683E0",
    "GHIDRA-Document-0x1800FAE70",
]

doc = {
    "id": "F-001",
    "modulo": "DocumentMarks.dll",
    "versao_ref": "24.03.10017",
    "binario": r"C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll",
    "sha256": "E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102",
    "tamanho_bytes": 4841904,
    "programa_ghidra": {
        "projeto": "DocMarks_v240",
        "programa": "/DocumentMarks.dll",
        "ferramenta": "Ghidra 12.2 headless, JDK 25",
        "importado_em": "2026-11-21",
        "log_import": "tools/ghidra_analysis/f001_docmarks_v240_import.log",
        "log_extracao": "tools/ghidra_analysis/f001_v240_export2.log",
    },
    "estatico": static,
    "comportamental": ["CAP-20261119-01"],
    "bloqueios": [
        "GHIDRA-DocumentMarks-0x18013A8B0 e endereco da v25.03.116, nao da v24.03.10017; "
        "na v240 a funcao equivalente e DocumentMarks::PDFPlusCutMark::PDFPlusCutMark em 0x1801344E0 "
        "(ver DocumentMarks__0x18013A8B0.md e DocumentMarks__0x1801344E0.md).",
        "GHIDRA-DocumentMarks-0x18013EE90 e endereco da v25.03.116; na v240 a equivalente e "
        "DocumentMarks::PDFPlusCutMark::regenerateMarkImp em 0x180136190.",
        "GHIDRA-DocumentMarks-0x18013CB50 e endereco da v25.03.116; na v240 a equivalente e "
        "DocumentMarks::PDFPlusCutMark::GetReferenceBox em 0x180134B00.",
        "GHIDRA-DocumentMarks-0x18017C5D0 e endereco da v25.03.116; na v240 a equivalente e o parser "
        "PDF+ FUN_180172100 em 0x180172100.",
        "GHIDRA-DocumentMarks-0x180111410 e endereco da v25.03.116; na v240 a equivalente e o dispatch "
        "legado FUN_18010E0F0 em 0x18010E0F0.",
        "GHIDRA-DocumentMarks-0x180052CA0 e endereco da v25.03.116; na v240 a equivalente e "
        "DocumentMarks::CutMark::regenerateMarkImp em 0x180052950.",
        "Spec F-001 R2 cita Orientation=1, Repetition=2 e LineTypes=[0] no construtor; o construtor v240 "
        "(0x1801344E0) nao escreve esses campos e o layout usa +0x7C0/+0x838. A tabela de R2 precisa de "
        "revalidacao para a v240.",
        "Spec F-001 R11/E1/E2/E3 descrevem AllStructuralDesignStations, Orientation, Repetition e LineTypes "
        "no parser; esses literais nao existem no binario v240 e o parser v240 (0x180172100) le apenas "
        "Position, Reference, ReferenceID e Offset.",
        "Spec F-001 R7 espera 1 GroupObject com 8 PathObject; na v240 regenerateMarkImp (0x180136190) copia "
        "o conteudo do FormPaint de origem para um Group por posicao de dm::MarkPositionVector. A contagem "
        "de posicoes/caminhos nao foi medida nesta extracao.",
        "GetPageBox (Document.dll 0x1800FAE70) foi revalidado na v240; o conteudo da tabela de fallback "
        "DAT_1802EF6D8 (qual caixa substitui a ausente) nao foi decodificado.",
        "A evidencia identifica o binario por caminho e SHA-256; a versao 24.03.10017 vem da regra do "
        "projeto (docs/agents/REFERENCE_VERSION.md), pois o DLL nao carrega FileVersion.",
    ],
}

with open(out, "w", encoding="utf-8", newline="\n") as f:
    json.dump(doc, f, ensure_ascii=False, indent=2)
    f.write("\n")
print("wrote", out)
