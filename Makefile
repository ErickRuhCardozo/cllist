CC=gcc
CFLAGS=-Wall

liblinkedlist.so: src/liblinkedlist.c
	if [ ! -d ./lib ] ; then mkdir ./lib ; fi
	$(CC) $(CFLAGS) -fPIC -shared -o lib/$@ $< -lc

example: example/main.c liblinkedlist.so
	if [ ! -d ./example/bin ] ; then mkdir ./example/bin; fi
	$(CC) $(CFLAGS) -o ./example/bin/$@ -L./lib -llinkedlist $<
	LD_LIBRARY_PATH=./lib ./example/bin/$@

clean:
	$(RM) -r ./lib/ ./example/bin/
