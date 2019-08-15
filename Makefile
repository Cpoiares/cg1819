.PHONY: clean zip
src = $(wildcard src/*.cpp)
inc = include

CC = g++
CFLAGS = -g
LDFLAGS = -lGL -lglut -lGLU -I $(inc)

main.out: $(src)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

clean:
	rm -f main.out

run: main.out
	./main.out

zip:
	zip -r cg-projecto.zip *
