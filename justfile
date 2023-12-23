watch:
   watchexec -r -e.c -- just run

run: build
    ./main

build: clean
    gcc -o main -fopenmp main.c

clean:
    rm -f main
