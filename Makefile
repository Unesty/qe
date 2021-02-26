all:
	$(CC) qe.c -static -O3 -flto -o qe 
install:
	install -m 755 qe /usr/local/bin/
