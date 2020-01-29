all: svc clt

svc: server.c
	gcc  server.c -o svc

clt: client.c
	gcc client.c -o clt
	

		
