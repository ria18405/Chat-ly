all: client server

client: helloclient.c
	gcc -w -pthread -o client helloclient.c

server: helloserver.c
	gcc -w -pthread -o server helloserver.c

clean: 
	rm server client

