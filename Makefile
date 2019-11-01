
    

all :	#target name
	gcc -pthread helloserver.c -o server
	gcc -pthread helloclient.c -o client