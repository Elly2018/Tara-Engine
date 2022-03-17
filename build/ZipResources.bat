@echo off
SET n="engine.resource"
cd ../bin
del %n% /q
cd ../
del %n% /q
bsdtar -cf %n% resources
move %n% bin
pause