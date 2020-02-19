#/bin/sh
#ocamlbuild -cflags -I,/usr/local/lib/ocaml/sdl/ -lflags -I,/usr/local/lib/ocaml/sdl/ -libs bigarray,sdl main.native
ocamlbuild -cflags -I,/usr/local/lib/ocaml/lablGL/ -lflags -I,/usr/local/lib/ocaml/lablGL/ -libs lablGL,lablglut main.native
