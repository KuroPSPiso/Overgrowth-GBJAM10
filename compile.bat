CLS
@ECHO OFF

REM====================================================
REM rm previous compile, create backup

COPY /b/v/y overgrowth.gb overgrowth.old.gb
DEL overgrowth.gb 

RMDIR /S /Q compile

ECHO Removed previous compilation

REM====================================================
REM create compilation folders

MKDIR "compile"
MKDIR "compile/sprites"
MKDIR "compile/maps"
MKDIR "compile/sounds"

ECHO Created compile folders

REM====================================================
REM make objects

lcc -c -o compile/main.o main.c
lcc -c -o compile/FUNC.o FUNC.c
lcc -c -o compile/lvl.o lvl.c
lcc -c -o compile/controls.o controls.c
lcc -c -o compile/sprites/alpha.o sprites/alpha.c
lcc -c -o compile/maps/alpha.o maps/alpha.c
lcc -c -o compile/sprites/bg.o sprites/bg.c
lcc -c -o compile/sprites/bg_lvl.o sprites/bg_lvl.c
lcc -c -o compile/maps/bg.o maps/bg.c
lcc -c -o compile/sprites/doors.o sprites/doors.c
lcc -c -o compile/sounds/sfx.o sounds/sfx.c

ECHO Created objects

REM====================================================
REM compile gb rom

lcc  -o overgrowth.gb^
 compile/main.o^
 compile/FUNC.o^
 compile/lvl.o^
 compile/controls.o^
 compile/sprites/alpha.o^
 compile/maps/alpha.o^
 compile/sprites/bg.o^
 compile/sprites/bg_lvl.o^
 compile/maps/bg.o^
 compile/sounds/sfx.o

ECHO Created ROM

REM====================================================
REM playtest
ECHO Launching Playtest
bgb ./overgrowth.gb
EXIT