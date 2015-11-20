/*
 * test.cc
 * empty msg loop
 * created on 2015-11-20
*/

#include <stdio.h>
#include <stdlib.h>
#include <node/uv.h>

int main()
{
        uv_loop_t *loop = uv_loop_new();
        uv_run(loop, UV_RUN_DEFAULT);
        printf("Hello World\n");

        return 0;
}

