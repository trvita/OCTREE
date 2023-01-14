.PHONY: clean main 
CFLAGS = -Wall -Wextra
CPPFLAGS = -MMD

main : obj/main.o obj/octree.o obj/func.o
	gcc $(CFLAGS) -g -o $@ $^

obj/main.o: src/main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -o $@ src/main.c

obj/octree.o: src/octree.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -o $@ src/octree.c

obj/func.o: src/func.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -o $@ src/func.c
run/main:
	./main

result.png:
	chmod +x octree.gnuplot
run/result:
	./octree.gnuplot

clean:
	rm obj/*/*.[od]
