main:
	gcc -Wall -g -std=c99 src/linkedListADT.c -c -Iinclude -o bin/LLADT.o
	gcc -Wall -g -std=c99 src/queueADT.c -c -Iinclude -o bin/QADT.o
	gcc -Wall -g -std=c99 src/sorkinRyanA1.c -c -Iinclude -o bin/A1.o
	gcc -Wall -g -std=c99 src/sorkinRyanA1Libray.c -c -Iinclude -o bin/A1L.o
	gcc -Wall -g -std=c99 bin/LLADT.o bin/QADT.o bin/A1.o bin/A1L.o -Iinclude -o bin/runMe

test:
	gcc -Wall -g -std=c99 src/linkedListADT.c -c -Iinclude -o bin/LLADT.o
	gcc -Wall -g -std=c99 src/queueADT.c -c -Iinclude -o bin/QADT.o
	gcc -Wall -g -std=c99 src/testMain.c -c -Iinclude -o bin/TM.o
	gcc -Wall -g -std=c99 src/sorkinRyanA1Libray.c -c -Iinclude -o bin/A1L.o
	gcc -Wall -g -std=c99 bin/QADT.o bin/LLADT.o bin/TM.o bin/A1L.o -Iinclude -o bin/test

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*
