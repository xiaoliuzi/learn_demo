all:server client
client:echo_client.c
	gcc -luv -pthread -o client echo_client.c /usr/lib/libuv.a
server:echo_server.c
	gcc -luv -pthread -o server echo_server.c /usr/lib/libuv.a
clean:
	rm server client
