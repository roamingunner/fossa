/*
 * Copyright (c) 2015 roamingunner
 * All rights reserved
 *
 * This program is an example of timeout
 */
#include "fossa.h"

#define TEST_LOOP 5

#define NS_DEV_TEST_MSG  "abcde12345"

static void ns_timeout_handler(struct ns_mgr *mgr, void *ctx) {
    static int loop = 0;
    loop++;
    if (loop < TEST_LOOP){
        printf("LOOP %d:write test msg\n",loop);
        /* WARNING: just for test, not recommend call block funcion !!*/
        system("echo abcde12345 > /tmp/read_fifo");
        ns_register_timeout(0,500000,ns_timeout_handler, mgr,NULL);
    }else{
        ns_mgr_poll_loop_stop(mgr);
    }
    return;
}

static void ns_dev_io_cb(struct ns_dev_io *nd, int ev, void *p)
{
    int *data = (int *)nd->ctx;
    struct mbuf *recv_mbuf = &nd->recv_mbuf;
    switch(ev){
        case NS_DEV_EV_READ:
            printf("==>\nrecv:%s private data:%d\n<==\n",recv_mbuf->buf,*data);
            mbuf_remove(recv_mbuf, recv_mbuf->len);
            break;
        default:
            break;
    }
}

int main(int argc, char* argv[]) {
    struct ns_mgr mgr;
    struct ns_dev_io *nd;
    int private_data = 9;

    unlink("/tmp/read_fifo");
    mkfifo("/tmp/read_fifo",0666);
    ns_mgr_init(&mgr, NULL);

    nd = ns_register_dev_io(&mgr, "/tmp/read_fifo", O_RDWR , ns_dev_io_cb, NS_DEV_EV_READ, &private_data);

    if (!nd){
        abort();
    }
    ns_register_timeout(0,500000,ns_timeout_handler, &mgr,NULL);

    ns_mgr_poll_loop(&mgr);

    ns_mgr_free(&mgr);

    unlink("/tmp/read_fifo");

    return 0;
}
