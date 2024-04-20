CC := gcc

main: build/main.o build/wav.o build/fft.o
	$(CC) -o $@ $^

build/%.o: src/%.c | mkdir
	$(CC) -c -o $@ $< -I`pwd`/include

.PHONY: clean run build

mkdir:
	mkdir -p build

build: clean main

run: main
	./main

clean:
	rm -rf main build
