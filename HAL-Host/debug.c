/*
 * degub.c
 *
 *  Created on: 09.04.2014
 *      Author: netzwerg
 */


#include <stdio.h>
#include "../Application/debug.h"

void debug_string(const char * s){
	printf("%s",s);
}
void debug_int(uint8_t x){
	printf("%i",x);
}
