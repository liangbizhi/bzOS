/**************************************************************************************************
 * @file			main.c
 * @brief 			
 * @author			Bill Liang
 * @date			2014-10-5
 *************************************************************************************************/

#include "type.h"
#include "config.h"
#include "const.h"
#include "stdio.h"
#include "protect.h"
#include "fs.h"
#include "console.h"
#include "tty.h"
#include "proc.h"
#include "string.h"
#include "proto.h"
#include "global.h"

PRIVATE void init_mm();
/**************************************************************************************************
 * 					task_mm
 **************************************************************************************************
 * <Ring 1> The main loop of TASK_MM.
 *************************************************************************************************/
PUBLIC void task_mm(){
	init_mm();

	while(TRUE){
		send_recv(RECEIVE, ANY, &mm_msg);
		int src		= mm_msg.source;
		int msgtype	= mm_msg.type;
		int reply	= 1;

		switch(msgtype){
		case FORK:
			mm_msg.RETVAL = do_fork();
			break;
		/*case EXIT:
			do_exit(mm_msg.STATUS);
			reply = 0;
			break;
		case WAIT:
			do_wait();*/
		default:
			dump_msg("MM::unknown msg", &mm_msg);
			assert(0);
			break;
		}

		if(reply){
			mm_msg.type = SYSCALL_RET;
			send_recv(SEND, src, &mm_msg);
		}
	}

}
/**************************************************************************************************
 * 					init_mm
 **************************************************************************************************
 * Do some initialization work.
 *************************************************************************************************/
PRIVATE void init_mm(){
	struct boot_params bp;
	get_boot_params(&bp);

	memory_size = bp.mem_size;

	printl("{MM} memsize: %dMB\n", memory_size >> 20);
}
/**************************************************************************************************
 * 					alloc_mem
 **************************************************************************************************
 * Allocate a memory block for a proc.
 *
 * @param pid		Which proc the memory is for.
 * @param memsize	How many bytes is needed.
 *
 * @return		The base of the memory just allocated.
 *************************************************************************************************/
PUBLIC int alloc_mem(int pid, int memsize){
	assert(pid >= (NR_TASKS + NR_NATIVE_PROCS));

	if(memsize > PROC_IMAGE_SIZE_DEFAULT){
		panic("unsupported memory request: %d. "
			"(should be less than %d)", memsize, PROC_IMAGE_SIZE_DEFAULT);
	}

	int base = PROCS_BASE +
		(pid - (NR_TASKS + NR_NATIVE_PROCS)) * PROC_IMAGE_SIZE_DEFAULT;

	if(base + memsize >= memory_size){	/* the total memory is not enough */
		panic("memory allocation failed. pid: %d", pid);
	}

	return base;
}
