@for /F "tokens=1,2 delims= " %%i in ("%~t1") do (
@rem echo строка "%%i"
@rem copy %1 "../%~n1 %2 %%i.exe"
copy %1 "../%~n1 %%i.exe"
)
@rem copy %1 "../%~n1 %2 %~t1.exe"

echo "%0 %*" > ../1.log 