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

int main(int argc, char **argv){
	if(argc != 3){
		printf("Invalid number of arguments\n");
		exit(1);
	}

	int pid = atoi(argv[1]);
	unsigned int addr = atoi(argv[2]);
	printf("%d\n", pid);
	task_t task_to_read = pid2task((pid_t)pid);
	if((kern_return_t)task_to_read != KERN_SUCCESS){
		printf("Error getting task: %s\n", mach_error_string((kern_return_t)task_to_read));
		exit(1);
					
	}

	int p;

	int count = 4096;
	vm_offset_t *ret = vm_read(task_to_read, (vm_address_t) atoi(argv[2]), (vm_size_t )4096, (vm_offset_t *)&p, (mach_msg_type_number_t *)&count);
	if((kern_return_t)ret){
		printf("Error reading: %s\n", mach_error_string((kern_return_t)ret));
		exit(1);
	}
	exit(0);

}

