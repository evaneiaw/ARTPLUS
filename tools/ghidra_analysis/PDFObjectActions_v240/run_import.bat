@echo off
echo. | "H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat" "H:\Desktop\ArtPlus\tools\ghidra_projects" "ArtProPlus_v240" -import "C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\PDFObjectActions.dll" -overwrite
exit /b %ERRORLEVEL%