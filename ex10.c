#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <mach/processor_info.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>
#include <mach/machine/thread_status.h>
#include <unistd.h>

int main(){
	task_t child;
	char data[4096*4] __attribute__((aligned(4096))) = {1};
	task_t parent = mach_task_self();
	kern_return_t ret;
	ret = task_create(parent, 0, &child);
	if(ret != KERN_SUCCESS){
		printf("Error creating task: %s\n", mach_error_string(ret));
	}
	vm_address_t addr;
	addr = vm_allocate(child, &addr, 4096 * 4, 1);
       	if(addr != KERN_SUCCESS){
		printf("Error allocating memory: %s\n", mach_error_string(ret));
	}

	ret = vm_write(child, addr, (vm_offset_t)data, 4096*4);	
	if(ret != KERN_SUCCESS){
		printf("Error writing data: %s\n", mach_error_string(ret));
	}


	sleep(20);

	ret = task_terminate(child);
	if(ret != KERN_SUCCESS){
		printf("ERROR terminating task%s\n", mach_error_string(ret));
	}
	exit(0);

}
