all: build run

build: 
	gcc ./src/*.c -o main

run:
	./main

clean:
	rm main