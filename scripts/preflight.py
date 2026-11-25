#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""preflight.py — pré-voo de sessão do ArtPlus (AGENTS.md §10.5).

Prova, antes de qualquer despacho ou retomada, que esta sessão está na árvore
canônica e que o verificador de versão está verde. Imprime PASS/FAIL por item
e retorna 0 somente quando todos os itens obrigatórios passam.

Uso:
    python scripts/preflight.py

Itens verificados:
    1. `git rev-parse --show-toplevel` == H:/Desktop/ArtPlus (árvore canônica)
    2. branch atual == master (não HEAD destacado)
    3. contagem de entradas de `git status --short` (informativo: WIP de outras
       sessões não reprova o pré-voo)
    4. HEAD <sha> e data do último commit (informativo)
    5. `python scripts/check_version.py --strict` retorna 0

Códigos de saída:
    0  PASS (árvore canônica, branch master, versão aprovada)
    1  FAIL (divergência de árvore/branch ou versão reprovada)
"""

from __future__ import annotations

import os
import subprocess
import sys

CANON_ROOT = "H:/Desktop/ArtPlus"
CANON_BRANCH = "master"


def _utf8_stdout():
    try:
        sys.stdout.reconfigure(encoding="utf-8")
    except Exception:  # noqa: BLE001
        pass


def _run(cmd, timeout=600):
    """Executa cmd na árvore atual; retorna (exit, stdout, stderr)."""
    try:
        p = subprocess.run(cmd, cwd=os.getcwd(), stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE, timeout=timeout)
        out = (p.stdout or b"").decode("utf-8", "replace").strip()
        err = (p.stderr or b"").decode("utf-8", "replace").strip()
        return p.returncode, out, err
    except FileNotFoundError as e:  # noqa: BLE001
        return 127, "", f"comando não encontrado: {e}"
    except subprocess.TimeoutExpired:
        return 124, "", "timeout"


def _norm(path):
    return os.path.normcase(os.path.abspath(path.replace("/", os.sep)))


def main():
    _utf8_stdout()
    items = []  # (nome, ok, detalhe)
    print("preflight — árvore canônica do ArtPlus")
    print(f"esperado: {CANON_ROOT} (branch {CANON_BRANCH})")
    print("-" * 72)

    # 1. raiz canônica
    code, out, err = _run(["git", "rev-parse", "--show-toplevel"])
    if code != 0:
        items.append(("raiz", False, (err or "git falhou").splitlines()[0][:200]))
    else:
        actual = out.replace("\\", "/")
        ok = _norm(actual) == _norm(CANON_ROOT)
        items.append(("raiz", ok, actual if ok else
                      f"{actual} != {CANON_ROOT} (worktree/clone divergente)"))

    # 2. branch master (não HEAD destacado)
    code, out, err = _run(["git", "rev-parse", "--abbrev-ref", "HEAD"])
    if code != 0:
        items.append(("branch", False, (err or "git falhou").splitlines()[0][:200]))
    else:
        ok = out == CANON_BRANCH
        detail = out if ok else f"{out} != {CANON_BRANCH} (HEAD destacado ou branch divergente)"
        items.append(("branch", ok, detail))

    # 3. WIP (informativo — nunca reprova)
    code, out, _ = _run(["git", "status", "--short"])
    wip = len([ln for ln in out.splitlines() if ln.strip()]) if code == 0 else 0
    print(f"INFO  WIP: {wip} entrada(s) em git status --short (não reprova)")

    # 4. HEAD + data do último commit (informativo)
    code, out, _ = _run(["git", "log", "-1", "--format=%H|%ad", "--date=iso"])
    if code == 0 and "|" in out:
        sha, date = out.split("|", 1)
        print(f"INFO  HEAD {sha} ({date})")
    else:
        print("INFO  HEAD indisponível (git log falhou)")

    # 5. versão estrita
    script = os.path.join(CANON_ROOT.replace("/", os.sep), "scripts", "check_version.py")
    if not os.path.exists(script):
        items.append(("versão", False, "scripts/check_version.py ausente"))
    else:
        env = dict(os.environ, PYTHONIOENCODING="utf-8")
        try:
            p = subprocess.run([sys.executable, script, "--strict"],
                               cwd=os.path.dirname(script), env=env,
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               timeout=600)
            vcode = p.returncode
            vout = (p.stdout or b"").decode("utf-8", "replace")
        except subprocess.TimeoutExpired:
            vcode, vout = 124, "timeout"
        except FileNotFoundError as e:  # noqa: BLE001
            vcode, vout = 127, str(e)
        last = [ln.strip() for ln in vout.splitlines() if ln.strip()]
        detail = f"exit {vcode}" + (f" — {last[-1]}" if last else "")
        items.append(("versão", vcode == 0, detail))

    print("-" * 72)
    for name, ok, detail in items:
        print(f"{'PASS' if ok else 'FAIL'}  {name}: {detail}")
    passed = sum(1 for _, ok, _ in items if ok)
    total = len(items)
    ok_all = passed == total
    print("-" * 72)
    print(f"RESULTADO: {'PASS' if ok_all else 'FAIL'} ({passed}/{total} itens obrigatórios)")
    return 0 if ok_all else 1


if __name__ == "__main__":
    sys.exit(main())
