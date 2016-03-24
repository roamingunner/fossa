/*
 * Copyright (c) 2015 roamingunner
 * All rights reserved
 *
 * This program is an example of timeout
 */

#include "fossa.h"

#define TEST_LOOP 5

static void ns_timeout_handler(struct ns_timeout *to, struct ns_mgr *mgr, void *ctx) {
  static int loop = 0;
  loop++;
  printf("timeout handler invoked @ loop %d\n",loop);
  if (loop < TEST_LOOP){
    ns_register_timeout(0,500000,ns_timeout_handler,mgr,NULL);
  }else{
    ns_mgr_poll_loop_stop(mgr);
  }
  return;
}

int main(int argc, char* argv[]) {
  struct ns_mgr mgr;

  ns_mgr_init(&mgr, NULL);

  ns_register_timeout(0,500000,ns_timeout_handler, &mgr,NULL);

  ns_mgr_poll_loop(&mgr);

  ns_mgr_free(&mgr);

  return 0;
}
