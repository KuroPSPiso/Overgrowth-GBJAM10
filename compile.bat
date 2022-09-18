#rm previous compile
DEL *.gb

RMDIR /S compile

if not exist "compile/" (
  mkdir "compile"
)
if not exists "compile/sprites/" (
  mkdir "compile/sprites"
)

#make objects
lcc -c -o compile/main.o main.c
lcc -c -o compile/sprites/alpha.o sprites/alpha.c

#compile gb rom
lcc  -o overgrowth.gb compile/main.o compile/sprites/alpha.o

#playtest
bgb ./overgrowth.gb