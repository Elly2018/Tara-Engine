@ECHO OFF
CD ..\
SET SolutionDir=%cd%\
MSBUILD Core\Core.vcxproj /property:Platform=x64 /property:Configuration=Debug -p:outputdir=%cd%\x64\Debug\Core
CD x64\Debug
XCOPY Core\Core.dll Demo /Y
CD ..\..\
MSBUILD Demo\Demo.vcxproj /property:Platform=x64 /property:Configuration=Debug -p:outputdir=%cd%\x64\Debug\Core
PAUSE