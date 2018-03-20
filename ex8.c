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

char s[5]__attribute__((aligned(4096))) = {'h','o','l','a','\0'};
void bucle(){
	printf("%s", s);
}


int stack[8192];
int main(){
	mach_port_t child, parent;
	struct i386_thread_state thread_state;
	mach_msg_type_number_t state_count = THREAD_STATE_MAX;
	parent = mach_task_self();
	kern_return_t ret = thread_create(parent, &child);
	if(ret != KERN_SUCCESS){
		printf("ERROR CREATING THREAD: %s\n", mach_error_string(ret));
		exit(1);
	}

	ret = thread_get_state(child, i386_THREAD_STATE, (thread_state_t)&thread_state, &state_count);
       if( ret != KERN_SUCCESS){
	       printf("ERROR GETTING STATE: 0x%x %s\n", ret, mach_error_string(ret));
	       exit(1);
       }

       thread_state.eip = (unsigned int) bucle;
       thread_state.uesp = (unsigned int) &stack[8188] ;
	ret = thread_set_state(child, i386_THREAD_STATE, (thread_state_t ) &thread_state, state_count); 
  	if(ret != KERN_SUCCESS){
		printf("ERROR SETTING STATE: %s\n", mach_error_string(ret));
		exit(1);
	}	

	ret = thread_resume(child);
	if(ret != KERN_SUCCESS){
		printf("ERROR STARTING THREAD: %s\n", mach_error_string(ret));
	}

	sleep(20);

	

}
