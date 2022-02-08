@ECHO OFF
CD ..\
SET SolutionDir=%cd%\
MSBUILD Core\Core.vcxproj /property:Platform=x64 /property:Configuration=Debug -p:outputdir=%cd%\x64\Debug\Core
PAUSE