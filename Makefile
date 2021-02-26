all:
	$(CC) qe.c -static -O3 -flto -o qe 
install:
	cp qe /usr/local/bin/
