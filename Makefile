CC=gcc
CFLAGS=-Wall

example: example.c
	$(CC) $(CFLAGS) -o ./$@ $< && ./$@

clean:
	$(RM) -r example
