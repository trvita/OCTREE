.PHONY: clean bin/main bin/test result
CFLAGS = -Wall -Wextra
CPPFLAGS = -MMD

bin/main: obj/main.o obj/octree.o obj/func.o
	gcc $(CFLAGS) -g -o $@ $^

bin/test: obj/test/main.o obj/test/test.o obj/octree.o
	gcc $(CFLAGS) -o $@ $^

obj/main.o: src/main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -o $@ $<

obj/octree.o: src/octree.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -o $@ $<

obj/func.o: src/func.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -o $@ $<

obj/test/test.o: test/test.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -I thirdparty/ -o $@ $<

obj/test/main.o: test/main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -I thirdparty/ -o $@ $<

result:
	chmod +x bin/octree.gnuplot

run/main:
	./bin/main

run/result:
	./bin/octree.gnuplot

run/test:
	./bin/test

clean:
	rm obj/*.[od] && rm obj/test/*.[od]
