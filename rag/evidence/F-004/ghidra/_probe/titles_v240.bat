@echo off
set JAVA_HOME=C:\Program Files\Eclipse Adoptium\jdk-25.0.5.8-hotspot
call "H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat" "H:\Desktop\ArtPlus\tools\ghidra_projects" PDFObjectActions_v240 -process PDFObjectActions.dll -noanalysis -scriptPath "H:\Desktop\ArtPlus\rag\evidence\F-004\ghidra\_scripts" -postScript F004Titles.java > "H:\Desktop\ArtPlus\rag\evidence\F-004\ghidra\_probe\titles_v240.log" 2>&1 < nul
echo EXITCODE=%ERRORLEVEL% >> "H:\Desktop\ArtPlus\rag\evidence\F-004\ghidra\_probe\titles_v240.log"
