#include "bcos_sdk_c.h"
#include "bcos_sdk_c_amop.h"
#include "bcos_sdk_c_rpc.h"
#include "bcos_sdk_c_ws.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void usage()
{
    printf("Usage: pub <host> <port> <topic> <msg>\n");
    printf("Example:\n");
    printf("    ./pub 127.0.0.1 20200 topic aaaaaa\n");
    exit(0);
}

void callback(struct bcos_sdk_struct_response* resp)
{
    printf(" ==> receive response, status: %d, data: %s\n", resp->error, (char*)resp->data);
}

int main(int argc, char** argv)
{
    if (argc < 5)
    {
        usage();
    }

    char* host = argv[1];
    uint16_t port = atoi(argv[2]);
    char* topic = argv[3];
    char* msg = argv[4];

    // ini bcos_sdk_c_config
    struct bcos_sdk_c_config config;

    config.heartbeat_period_ms = 10000;
    config.reconnect_period_ms = 20000;
    config.message_timeout_ms = 20000;
    config.thread_pool_size = 4;

    struct bcos_sdk_c_endpoint ep;
    ep.host = host;
    ep.port = port;

    config.peers = &ep;
    config.peers_count = 1;

    void* sdk = bcos_sdk_create(&config);
    if (!sdk)
    {
        printf("bcos_sdk_create failed.\n");
        return 0;
    }

    printf("start sdk service.\n");
    bcos_sdk_start(sdk);

    void* amop = bcos_sdk_get_amop(sdk);
    if (!amop)
    {
        printf("bcos_sdk_get_amop failed.\n");
        return 0;
    }

    while (1)
    {
        sleep(5);
        printf("==> publish, topic: %s, message: %s\n", topic, msg);
        bcos_amop_publish(amop, topic, (void*)msg, strlen(msg), 0, callback, amop);
    }

    return 0;
}
