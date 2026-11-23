---
modulo: Document.dll
versao: 24.03.10017
funcao: 0x180000000
nome: Document.dll v240 - identidade do programa analisado
endereco: 0x180000000
confianca: alta
xrefs: []
strings: []
---

# Identidade do binario analisado (Document.dll v240)

## Arquivo alvo
- Caminho: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\Document.dll`
- Tamanho: 4.421.040 bytes
- Ultima modificacao: 2024-03-12 18:41:10
- SHA-256 medido no arquivo real: `DA91E28574C877D392D3E6BEF9CCBB7C4DCF3117EBD03655DE89834FC8FA9E21`
  (conferido por `Get-FileHash` e pelo proprio Ghidra em
  `currentProgram.getExecutableSHA256()`)

## Programa no Ghidra
- Projeto: `H:\Desktop\ArtPlus\tools\ghidra_projects\ArtProPlus_Document`
  (import pre-existente; nao houve reimport nesta etapa)
- Programa: `Document.dll`
- `executablePath = /C:/Esko/bg_prog_artpro+_v240/ArtPro+.app/Contents/Windows/Document.dll`
- `executableMD5 = 22fd92f4e1bfc14456d342ee715479ef`
- `imageBase = 180000000`
- `language = x86:LE:64:default`
- Funcoes: 12.793
- Simbolos: 82.091

## Prova da execucao
Ghidra 12.2 headless, JDK 25, `-process Document.dll -noanalysis -readOnly`:
- `tools/ghidra_analysis/f005_probe.log` / `f005_probe.txt` (identidade + simbolos + strings)
- `tools/ghidra_analysis/f005_refs1.log` / `f005_refs1.txt`
- `tools/ghidra_analysis/f005_refs2.log` / `f005_refs2.txt`
- `tools/ghidra_analysis/f005_vtables.log` / `f005_vtables.txt`
- `tools/ghidra_analysis/f005_refs3.txt`, `f005_vtables2.txt`
- `tools/ghidra_analysis/f005_refs4.txt`, `f005_vtables3.txt`
- `tools/ghidra_analysis/f005_refs5.txt`, `f005_refs6.txt`
- Scripts: `tools/ghidra_analysis/scripts/DumpF005Symbols.java`,
  `DumpF005Refs.java`, `DumpF005Vtable.java`

## Rastreabilidade de versao
O mesmo projeto foi importado a partir do caminho v240 e o hash do programa confere com
o hash do arquivo v240 medido agora; nenhum endereco desta evidencia vem de
`rag/evidence/F-004` (ColorManipulationLayer) nem do binario v25.
