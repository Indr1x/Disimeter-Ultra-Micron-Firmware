@Echo Off 

cd make_dfu
del ..\dfu\%~n1.dfu >nul
dfuse.exe %1 ..\dfu\%~n1.dfu >nul