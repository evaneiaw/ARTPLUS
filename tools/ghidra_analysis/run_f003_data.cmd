@echo off
set JAVA_HOME=C:\Program Files\Eclipse Adoptium\jdk-25.0.5.8-hotspot
call "H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat" "H:\Desktop\ArtPlus\tools\ghidra_projects" DocMarks_v240 -process DocumentMarks.dll -noanalysis -scriptPath "H:\Desktop\ArtPlus\tools\ghidra_analysis\ghidra_scripts" -postScript DumpData.java 0x1802fa2e8 0x1802fa2f0 0x1802fa2d8 0x1802fa2e0 0x1802fa130 0x1802fa140 0x1802fa1f8 0x1802fa208 0x18031ad78 0x180316468 0x180316280 0x180319f90 0x18032fda8 0x180330128 0x180330148 0x180330168 0x180330188 0x1803301a8 0x1803301c8
