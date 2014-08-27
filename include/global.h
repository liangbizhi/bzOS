/*除了在global.c 中，EXTERN被定义为extern*/
#ifdef	GLOBAL_VARIABLES_HERE
#undef	EXTERN
#define	EXTERN
#endif

EXTERN	int		disp_pos;
EXTERN	u8		gdt_ptr[6];				//0-15: Limit	16-47: Base
EXTERN	DESCRIPTOR	gdt[GDT_SIZE];				//新的GDT表，大小GDT_SIZE
EXTERN	u8		idt_ptr[6];				//0-15: Limit	16-47: Base
EXTERN	GATE		idt[IDT_SIZE];				//新的GDT表，大小GDT_SIZE

EXTERN	u32		k_reenter;

EXTERN	TSS		tss;
EXTERN	PROCESS*	p_proc_ready;

/* extern声明 */
extern	PROCESS		proc_table[];
extern	TASK		task_table[];

extern	char		task_stack[];
