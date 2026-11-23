@echo off
set JAVA_HOME=C:\Program Files\Eclipse Adoptium\jdk-25.0.5.8-hotspot
call "H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat" "H:\Desktop\ArtPlus\tools\ghidra_projects" ArtProPlus_Document -process Document.dll -noanalysis -readOnly -scriptPath "H:\Desktop\ArtPlus\tools\ghidra_analysis\scripts" -postScript DumpF005Vtable.java "H:\Desktop\ArtPlus\tools\ghidra_analysis\f005_vtables.txt" vt:0x1802e99a0:24 vt:0x1802fa418:8 vt:0x180405228:1
