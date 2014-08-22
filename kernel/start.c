/*=================================================================================================
  		Start.c			2014-8-21
 ================================================================================================*/

#include "type.h"
#include "const.h"
#include "protect.h"

PUBLIC	void*	memcpy(void* pDst, void* pSrc, int iSize);

PUBLIC	void	disp_str(char* info);


PUBLIC u8		gdt_ptr[6];				//0-15: Limit	16-47: Base
PUBLIC DESCRIPTOR	gdt[GDT_SIZE];				//新的GDT表，大小GDT_SIZE

PUBLIC	void	cstart(){
	
	disp_str("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n--------\"cstart\" begins-------\n");
	disp_str("--------\"cstart\" ends-------\n");

	//将LOADER中的GDT复制到新的GDT中
	memcpy(&gdt,
		(void*) (*((u32*)(&gdt_ptr[2]))),	
		*((u16*)(&gdt_ptr[0])) + 1);

	//把gdt_ptr中的内容换成新的GDT的基地址和界限
	u16* p_gdt_limit = (u16*)(&gdt_ptr[0]);
	u32* p_gdt_base = (u32*)(&gdt_ptr[2]);
	*p_gdt_limit = GDT_SIZE * sizeof(DESCRIPTOR) - 1;
	*p_gdt_base = (u32)(&gdt_ptr);
}
