//
//  main.c
//  dyld
//
//  Created by Misha Nya on 19.10.2023.
//

#include "main.h"
#include <mach/vm_map.h>
#include <mach/mach_init.h>

int main(int argc, const char * argv[]) {
    mach_port_t mach_task_self_ = task_self_trap();

    vm_address_t    r;
    int vmFlags = 1006632960;
    kern_return_t kr = vm_allocate(mach_task_self(), &r, 266240, VM_FLAGS_ANYWHERE | vmFlags);
    printf("");
}
