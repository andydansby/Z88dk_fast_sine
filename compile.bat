SET PATH=c:\z88dk199c;c:\z88dk199c\bin;c:\z88dk199c\lib\;c:\z88dk199c\lib\clibs;c:\z88dk199c\lib\config

del "main.tap"
cls

@rem zcc +zx -lp3 -lm -create-app -bn sin main.c

zcc +zx -vn -SO3 -m -lm -clib=new main.c -o main -startup=9 -create-app

rem  (generate sin.tap)

del "main_CODE.bin"
del "main_UNASSIGNED.bin"


