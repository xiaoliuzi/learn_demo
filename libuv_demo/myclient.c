#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#define STR_MAX_SIZE 1000
#define PORT 7000
uv_loop_t *loop = NULL;


void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
	buf->base = (char*)malloc(suggested_size);
	buf->len = suggested_size;
}
void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
	
	uv_write_t *req = (uv_write_t*)malloc(sizeof(uv_write_t));
	uv_buf_t wrbuf = uv_buf_init(buf->base, nread);
	
	printf("%s\n", buf->base);
}


void on_read(uv_write_t *req, int status) {
	if (status) {
		fprintf(stderr, "Write error %s\n", uv_strerror(status));
	}
	
	uv_stream_t *client = req->handle;//(uv_tcp_t*)malloc(sizeof(uv_tcp_t));

	uv_read_start((uv_stream_t*)client, alloc_buffer,echo_read );
	free(req);
	
}


void on_connect(uv_connect_t* req, int status)
{
	char str[STR_MAX_SIZE] = "hello";
	uv_write_t *req_write = (uv_write_t*)malloc(sizeof(uv_write_t));

	uv_buf_t wrbuf = uv_buf_init(str, strlen(str));
	uv_write(req_write, req->handle, &wrbuf, 1, on_read);
}


int main()
{
	loop = uv_default_loop();
	uv_tcp_t* socket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
	uv_tcp_init(loop, socket);
	
	uv_connect_t* connect = (uv_connect_t*)malloc(sizeof(uv_connect_t));
	
	struct sockaddr_in dest;
	uv_ip4_addr("127.0.0.1", PORT, &dest);
	uv_tcp_connect(connect, socket, (struct sockaddr*)&dest, on_connect);
 	uv_run(loop, UV_RUN_DEFAULT);
	return 0;
}
