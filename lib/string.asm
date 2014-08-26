; ------------------------------------------------------------------------
;		string.asm		2014-8-21
; ------------------------------------------------------------------------
[section .text]

;导出函数
global	memcpy
global	memset

; ------------------------------------------------------------------------
; void* memcpy(void* pDest, void* pSrc, int iSize);
; ------------------------------------------------------------------------
memcpy:
	push	ebp
	mov	ebp, esp

	push	esi
	push	edi
	push	ecx

	mov	edi, [ebp + 8]	; Destination
	mov	esi, [ebp + 12]	; Source
	mov	ecx, [ebp + 16]	; Counter
.1:
	cmp	ecx, 0		; 判断计数器
	jz	.2		; 计数器为零时跳出

	mov	al, [ds:esi]		; ┓
	inc	esi			; ┃
					; ┣ 逐字节移动
	mov	byte [es:edi], al	; ┃
	inc	edi			; ┛

	dec	ecx		; 计数器减一
	jmp	.1		; 循环
.2:
	mov	eax, [ebp + 8]	; 返回值

	pop	ecx
	pop	edi
	pop	esi
	mov	esp, ebp
	pop	ebp

	ret			; 函数结束，返回
; memcpy 结束-------------------------------------------------------------

; ------------------------------------------------------------------------
; void* memset(void* s, int ch, int size);
; ------------------------------------------------------------------------
memset:
	push	ebp
	mov	ebp, esp

	push	esi
	push	edi
	push	ecx

	mov	edi, [ebp + 8]			;void *s
	mov	edx, [ebp + 12]			;int ch
	mov	ecx, [ebp + 16]			;int size
.1:
	cmp	ecx, 0
	jz	.2

	mov	byte [edi], dl
	inc	edi
	dec	ecx
	jmp	.1
.2
	pop	ecx
	pop	edi
	pop	esi
	mov	esp, ebp
	pop	ebp

	ret
;-------------------------------------------------------------------------
