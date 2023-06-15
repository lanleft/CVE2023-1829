#define _GNU_SOURCE
#include <stdint.h>
#include <stdlib.h>
#include <sched.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/resource.h>

#include "setup.h"
#include "log.h"

void assign_to_core(int core_id)
{
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(core_id, &mask);
    if (sched_setaffinity(getpid(), sizeof(mask), &mask) < 0)
    {
        errout("sched_setaffinity");
    }
}

int setup_sandbox(void)
{
    struct rlimit fdlim;
    cpu_set_t set;
    int pid;

    // assign_to_core(DEF_CORE);
    /*
       Execute ourselves in a new network namespace to
       be able to trigger and exploit the bug
    */

    /* For another user can communicate with netlink - somehow  */
    if (unshare(CLONE_NEWUSER) < 0)
    {
        errout("[-] unshare(CLONE_NEWUSER)");
        return -1;
    }

    /* Network namespaces provide isolation of the system resources */
    if (unshare(CLONE_NEWNET) < 0)
    {
        errout("[-] unshare(CLONE_NEWNET)");
        return -1;
    }

    return 0;
}


