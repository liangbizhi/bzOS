#ifndef _BZOS_CONST_H_
#define	_BZOS_CONST_H_

/* function type */
#define PUBLIC
#define PRIVATE	static

/* Boolean */
#define	TRUE		1
#define	FALSE		0

#define max(a,b)	((a) > (b) ? (a) : (b))
#define min(a,b)	((a) < (b) ? (a) : (b))

/* Color */
#define	BLACK		0x0
#define	WHITE		0x7
#define	RED		0x4
#define	GREEN		0x2
#define	BLUE		0x1
#define	FLASH		0x80
#define	BRIGHT		0x8
#define	MAKE_COLOR(X,Y)	(X | Y)


/* GDT和IDT中描述符的个数 */
#define	GDT_SIZE	128
#define	IDT_SIZE	256

/* privilege */
#define	PRIVILEGE_KRNL	0
#define	PRIVILEGE_TASK	1
#define	PRIVILEGE_USER	3
/* RPL */
#define	RPL_KRNL	SA_RPL0
#define	RPL_TASK	SA_RPL1
#define	RPL_USER	SA_RPL3

/* 8259A中断处理器的端口 */
#define INT_M_CTL		0x20			/* 中断命令寄存器I/O地址（主片） */
#define	INT_M_CTLMASK		0x21			/* 中断屏蔽寄存器I/O地址（主片） */
#define	INT_S_CTL		0xa0
#define	INT_S_CTLMASK		0xa1

#define	NR_IRQ			16
#define CLOCK_IRQ		0
#define	KEYBOARD_IRQ		1
#define	CASCADE_IRQ		2
#define	ETHER_IRQ		3
#define	SECONDARY_IRQ		3
#define	RS232_IRQ		4
#define	XT_WINT_IRQ		5
#define	FLOPPY_IRQ		6
#define	PRINTER_IRQ		7
#define	AT_WINT_IRQ		14

/* System call */
#define	NR_SYS_CALL		2

/* 8253/8254 PIT (Programmable Interval Timer)可编程间隔计时器 */
#define	TIMER0			0x40			/* I/O端口计时器 Counter 0 */
#define TIMER_MODE		0x43			/* 8253模式控制寄存器I/O地址 */
#define	RATE_GENERATOR		0x34			/* 输入到 Counter 0 的数据，00-11-010-0 */
#define	TIMER_FREQ		1193182L		/* 计时器时钟频率 */
#define	HZ			100			

/* Keyboard */
/* 8042键盘控制器端口 */
#define KB_DATA			0x60			/* 数据缓冲区，读/写 */
#define	KB_CMD			0x64			/* 读：状态	写：发送命令 */

#define	LED_CODE		0xed
#define	KB_ACK			0xfa

/* VGA */
#define	CRTC_ADDR_REG		0x3d4			/* CRT control registers 之 addr register */
#define	CRTC_DATA_REG		0x3d5			/* CRT control registers 之 data registers */
#define	START_ADDR_H		0xc			/* reg index of video mem start addr (MSB) */
#define	START_ADDR_L		0xd			/* reg index of video mem start addr (LSB) */
#define	CURSOR_H		0xe			/* reg index of cursor position (MSB) */
#define	CURSOR_L		0xf			/* reg index of cursor position (LSB) */
#define	V_MEM_BASE		0xb8000			/* base of color video memory */
#define	V_MEM_SIZE		0x8000			/* 32K: 0xb8000~0xbffff */
/* TTY */
#define	NR_CONSOLES		3			/* 控制台个数 */

/**************************************************************************************************
 * 					Message Mechanism
 *************************************************************************************************/
/* magic chars used by 'sys_printx' */
#define	MAG_CH_PANIC		'\002'
#define	MAG_CH_ASSERT		'\003'

/* process status */
#define	SENDING			0x02			/* set when proc trying to send message */
#define	RECEIVING		0x04			/* set when proc trying to receive message */
#define WAITING			0x08			/* set when proc waiting for the child to terminate */
#define HANGING			0x10			/* set when proc exits whithout being waited by parent */
#define FREE_SLOT		0x20			/* set when proc table entry is not used
							 * (ok to allocated to a new process)
							 */

/* system tasks */
#define INVALID_DRIVER		-20
#define INTERRUPT		-10
#define TASK_TTY		0			/* TASK_XXX must be corresponding with global.c  */
#define	TASK_SYS		1
#define TASK_HD			2
#define TASK_FS			3
#define TASK_MM			4
#define INIT			5

#define	ANY			(NR_TASKS + NR_PROCS + 10)
#define	NO_TASK			(NR_TASKS + NR_PROCS + 20)

/* IPC */
#define	SEND			1
#define	RECEIVE			2
#define	BOTH			3			/* BOTH = (SEND | RECEIVE) */

#define FD			u.m3.m3i1		/* File descriptor */
#define PATHNAME		u.m3.m3p1
#define FLAGS			u.m3.m3i1
#define NAME_LEN		u.m3.m3i2

#define	RETVAL			u.m3.m3i1		/* return value */
#define CNT			u.m3.m3i2
#define REQUEST			u.m3.m3i2
#define PROC_NR			u.m3.m3i3
#define DEVICE			u.m3.m3i4
#define POSITION		u.m3.m3l1
#define BUF			u.m3.m3p2

#define OFFSET			u.m3.m3i2
#define WHENCE			u.m3.m3i3

#define PID			u.m3.m3i2
#define STATUS			u.m3.m3i1

#define DIOCTL_GET_GEO		1

enum	msgtype{
	HARD_INT	= 1,		/* when hard interrupt occurs, a msg with type == HARD_INT will be sent to some tasks */
	/* SYS task */
	GET_TICKS, GET_PID, GET_RTC_TIME,
	/* FS */
	OPEN, CLOSE, READ, WRITE, LSEEK, STAT, UNLINK,
	/* FS & TTY */
	SUSPEND_PROC, RESUME_PROC,
	/* MM */
	FORK, EXIT,
	/* TTY, SYS, FS, MM, etc */
	SYSCALL_RET,
	/* for drivers */
	DEV_OPEN	= 998,
	DEV_CLOSE,
	DEV_READ,
	DEV_WRITE,
	DEV_IOCTL
};




/* Hard Drive */
#define SECTOR_SIZE		512
#define SECTOR_BITS		(SECTOR_SIZE * 8)
#define SECTOR_SIZE_SHIFT	9

#define MAX_DRIVES		2
#define NR_PART_PER_DRIVE	4
#define NR_SUB_PER_PART		16
#define NR_SUB_PER_DRIVE	(NR_PART_PER_DRIVE * NR_SUB_PER_PART)
#define NR_PRIM_PER_DRIVE	(NR_PART_PER_DRIVE + 1)

/**
 * @def MAX_PRIM
 * Defines the max minor number of the primary partitions.
 * If there are 2 disks, prim_dev ranges in hd[0-9], this macro will
 * equal 9.
 */
#define MAX_PRIM		(MAX_DRIVES * NR_PRIM_PER_DRIVE - 1)
#define MAX_SUBPARTITIONS	(NR_SUB_PER_DRIVE * MAX_DRIVES)

/* 硬盘设备号 */
#define MINOR_hd1a		0x10
#define MINOR_hd2a		(MINOR_hd1a + NR_SUB_PER_PART)

#define P_PRIMARY		0
#define P_EXTENDED		1

#define BZOS_PART		0x99	/* bzOS partition */
#define NO_PART			0x00	/* unused entry */
#define EXT_PART		0x05	/* extended partition */

/* major device numbers (corresponding to kernel/global.c::dd_map[]) */
#define NO_DEV			0
#define DEV_FLOPPY		1
#define DEV_CDROM		2
#define DEV_HD			3
#define DEV_CHAR_TTY		4
#define DEV_SCSI		5

/* make device number from major and minor numbers */
#define MAJOR_SHIFT		8
#define MAKE_DEV(a,b)		((a << MAJOR_SHIFT) | b)

#define ROOT_DEV		MAKE_DEV(DEV_HD, MINOR_BOOT)

/* separate major and minor numbers from device number */
#define MAJOR(x)		((x >> MAJOR_SHIFT) & 0xff)
#define MINOR(x)		(x & 0xff)

#define INVALID_INODE		0
#define ROOT_INODE		1

/* INODE::i_mode (actually, lower 12 bits are reserved) */
#define I_TYPE_MASK		0170000
#define I_REGULAR		0100000
#define I_BLOCK_SPECIAL		0060000
#define I_DIRECTORY		0040000
#define I_CHAR_SPECIAL		0020000
#define I_NAMED_PIPE		0010000

#define NR_DEFAULT_FILE_SECTS	2048	/* 2048 * 512 = 1MB */
/* file manipulate scheme */
#define NR_FILES		64	/* the maximun num of files opened by one process. */
#define NR_FILE_DESC		64
#define NR_INODE		64
#define NR_SUPER_BLOCK		8

#endif
