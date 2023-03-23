setlocal
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
MSBuild.exe .\windowsDesktop\OpenSiv3D.sln 
MSBuild.exe .\windowsDesktop\OpenSiv3D.sln /t:Build /p:Configuration=Release /p:Platform=x64
rem MSBuild.exe .\windowsDesktop\OpenSiv3D.sln /t:Build /p:Configuration=Debug /p:Platform=x64
endlocal