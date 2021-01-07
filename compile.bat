SET PATH=c:\z88dk199c;c:\z88dk199c\bin;c:\z88dk199c\lib\;c:\z88dk199c\lib\clibs;c:\z88dk199c\lib\config

del "sine.tap"
cls

@rem zcc +zx -lp3 -lm -create-app -bn sin main.c

zcc +zx -vn -SO3 -m -lm -clib=new main.c -o sine -startup=9 -create-app

rem  (generate sin.tap)

del "sine_CODE.bin"
del "sine_UNASSIGNED.bin"

rem rename main.tap sine.tap
