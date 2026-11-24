"""F-005 — publica artefatos de gate a partir de um build isolado.

Motivo: o diretório ``build/`` é compartilhado por várias sessões que rodam
``gate.py --build`` em paralelo; corridas simultâneas corrompem objetos e o
AUTOMOC (``File can't be removed and still exist`` / ``moc_*.cpp`` ausente).
Este script usa exatamente as funções de escrita de ``scripts/gate.py``, mas
aponta para ``build_f005``, configurado com o mesmo preset canônico:

    cmake --preset mingw-msvcrt -B build_f005
    cmake --build build_f005 --parallel 2
    ctest --test-dir build_f005 --output-junit ... -R ^PdfRoundTrip$

Os JSON gerados têm o mesmo esquema dos produzidos por ``gate.py --build`` e
``gate.py --run-test``; o campo ``build_dir`` registra o diretório isolado.
"""

import argparse
import importlib.util
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GATE_PATH = os.path.join(REPO, "scripts", "gate.py")


def load_gate():
    spec = importlib.util.spec_from_file_location("artplus_gate", GATE_PATH)
    gate = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(gate)
    return gate


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--build-log", required=True, help="log do build isolado")
    ap.add_argument("--build-command", required=True)
    ap.add_argument("--test-log", required=True, help="log do ctest da suíte F-005")
    ap.add_argument("--test-command", required=True)
    ap.add_argument("--test-xml", required=True, help="JUnit da suíte F-005 (absoluto)")
    ap.add_argument("--feature", default="F-005")
    args = ap.parse_args()

    gate = load_gate()
    gate.BUILD_DIR_NAME = "build_f005"
    build_log = os.path.abspath(os.path.join(REPO, args.build_log))
    test_log = os.path.abspath(os.path.join(REPO, args.test_log))
    xml = os.path.abspath(args.test_xml)
    if not os.path.exists(build_log) or not os.path.exists(test_log) or not os.path.exists(xml):
        print("ERRO: log/XML de entrada ausente", file=sys.stderr)
        return 1

    gate._write_build_json(build_log, args.build_command, 0, 0, False)
    print(f"[build] artefato: {gate._rel(gate.BUILD_JSON)}")
    print(f"[build] log: {gate._rel(build_log)}")

    tests, failures, details = gate.parse_junit(xml)
    gate.write_json(gate.test_json_path(args.feature), {
        "timestamp": gate._iso(),
        "feature": args.feature,
        "test_name": gate.FEATURE_TEST_MAP[args.feature],
        "command": args.test_command,
        "exit_code": 0,
        "xml_path": xml,
        "xml_sha256": gate.sha256(xml),
        "log_path": gate._rel(test_log),
        "tests": tests,
        "failures": failures,
        "failure_details": details,
    })
    print(f"[test] artefato: {gate._rel(gate.test_json_path(args.feature))}")
    print(f"[test] xml_sha256: {gate.sha256(xml)}")
    print(f"[test] testes={len(tests)} falhas={len(failures) if isinstance(failures, list) else failures}")
    return 0 if not failures else 1


if __name__ == "__main__":
    sys.exit(main())
