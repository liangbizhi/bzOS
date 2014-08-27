/*=================================================================================================
  			i8259.c			Bill Liang	2014-8-22
=================================================================================================*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
/*=================================================================================================
					   初始化8259A中断控制器。
=================================================================================================*/
PUBLIC void init_8259A(){

	out_byte(INT_M_CTL, 0x11);

	out_byte(INT_S_CTL, 0x11);

	out_byte(INT_M_CTLMASK, INT_VECTOR_IRQ0);

	out_byte(INT_S_CTLMASK, INT_VECTOR_IRQ8);

	out_byte(INT_M_CTLMASK, 0x4);

	out_byte(INT_S_CTLMASK, 0x2);

	out_byte(INT_M_CTLMASK, 0x1);
	
	out_byte(INT_S_CTLMASK, 0x1);
	/*主8259A，OCW1 (Operatione Control World)*/
	out_byte(INT_M_CTLMASK, 0xfe);
	/*从8259A，OCW1 (Operatione Control World)*/
	out_byte(INT_S_CTLMASK, 0xff);
}

/*=================================================================================================
					   spurious_irq
=================================================================================================*/
PUBLIC void spurious_irq(int irq){
	disp_str("spurious irq: ");
	disp_int(irq);
	disp_str("\n");
}
