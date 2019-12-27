/*
 * serial_printf.c
 *
 *  Created on: Dec 23, 2019
 *      Author: pavit
 */
#include "stdio.h"
#include "stdint.h"
#include "stdarg.h"

/* Depending on the library type */
#include "stm32f3xx_hal.h"

#ifdef __GNUC__
#define PUTCHAR_FUNCTION int __io_putchar(int put_data_s32)
#else
#define PUTCHAR_FUNCTION int fputc(int ch, FILE *f)
#endif

/* Extension for the address is required */
extern UART_HandleTypeDef huart1;

#define PUTCHAR_PORT_ADDR		(&huart1)
#define PUTCHAR_BLOCKING_TIME	(5U)

void serial_printf(const char *msg, ...);

/* Redefinition of the syscall write function */
PUTCHAR_FUNCTION
{
  uint8_t tx_data_u8 = (uint8_t)put_data_s32;

  if(HAL_UART_Transmit(PUTCHAR_PORT_ADDR, &tx_data_u8, 1, PUTCHAR_BLOCKING_TIME))
  {
	  /* Some Error */
	  UNUSED(0);
  }

  return put_data_s32;
}


void serial_printf(const char *msg, ...)
{
  va_list list;

  va_start(list,msg);
  vprintf(msg,list);
  va_end(list);

}

