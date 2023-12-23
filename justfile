watch:
   watchexec -r -e.c -- just run

run: build
    ./main

build: clean
    gcc -o main -fopenmp ./src/main.c ./src/matrix.c

clean:
    rm -f main
