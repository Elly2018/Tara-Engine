@echo off
SET n="engine.resource"
cd ../bin
del %n% /q
cd ../
del %n% /q
set PATH=%PATH%;%cd%
cd resources
set k=fonts icon image lang material mesh shader template Manifest.json
%k%
bsdtar -cf %n% %k%
move engine.resource ../bin
pause