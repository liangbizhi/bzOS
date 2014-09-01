/*=================================================================================================
		 	 printf.c			Bill Liang	2014-9-1
=================================================================================================*/
#include "type.h"
#include "const.h"
#include "protect.h"
#include "console.h"
#include "tty.h"
#include "proc.h"
#include "string.h"
#include "proto.h"
#include "global.h"

PUBLIC int vsprintf(char* buf, const char* fmt, va_list args){
	char* 	p = buf;
	char	tmp[256];
	char*	str;
	int	value;
	int 	i;

	for(; *fmt; fmt++){
		if(*fmt != '%'){
			*buf ++ = *fmt;
			continue;
		}
		fmt ++;
		switch(*fmt){
		case 's':
			str = (char*) *((int*)args);
			while(*str){
				*buf ++ = *str ++;
			}
			args += 4;
			break;
		case 'd':
			value = *((int*) args);
			if(value < 0){
				*buf ++ = '-';
				value = -value;
			}
			i = 0;
			tmp[i] = (value % 10) + '0';
			i ++;
			value /= 10;
			while(value){
				tmp[i] = (value % 10) + '0';
				i ++;
				value /= 10;
			}
			for(i=i-1; i>=0; i--){
				*buf ++ = tmp[i];
			}
			args += 4;
			break;
		case 'x':
			itoa(tmp, *((int*) args));
			strcpy(buf, tmp);
			buf += strlen(tmp);
			args += 4;
			break;
		default:
			break;
		}
	}

	return (buf - p);
}

PUBLIC int printf(const char* fmt, ...){
	int	i;
	char	buf[256];

	va_list arg = (va_list) ((char*)(&fmt) + 4);		/* 参数 */
	i = vsprintf(buf, fmt, arg);

	write(buf, i);

	return i;
}
