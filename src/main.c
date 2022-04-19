/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include<stdio.h>
#include<math.h>

#include <drivers/uart.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(uart_polling ,LOG_LEVEL_DBG);

/* change this to any other UART peripheral if desired */
#define UART_DEVICE_NODE DT_CHOSEN(zephyr_shell_uart)

#define MSG_SIZE 32

// /* queue to store up to 10 messages (aligned to 4-byte boundary) */
// K_MSGQ_DEFINE(uart_msgq, MSG_SIZE, 10, 4);

static const struct device *uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);

/* receive buffer rx used in UART */
static char rx_buf[MSG_SIZE] = "rx_buf_test\r\n";
// static int rx_buf_pos;

void print_uart(char *buf)
{	LOG_INF("print_uart(): Printing *buf ");
	int msg_len = strlen(buf);
	for (int i = 0; i < msg_len; i++) {
		uart_poll_out(uart_dev, buf[i]);
	}
}

void main(void) {
	LOG_INF("Starting UART Polling Sample");
	/*Transmitted buffer tx */
	char tx_buf[MSG_SIZE] = "tx_buf_test\r\n";

	LOG_INF("rx_buf contains: '%s", log_strdup(rx_buf));
	LOG_INF("tx_buf contains: '%s", log_strdup(tx_buf));

	if (!device_is_ready(uart_dev)) {
		LOG_WRN("UART device not found!");
		return;
	}	

	while (1){
		LOG_INF("Inside while loop");
		LOG_INF("Calling print_uart(rx_buf);");
		print_uart(rx_buf);
		LOG_INF("Calling print_uart(tx_buf);");
		print_uart(tx_buf);

		LOG_INF("Sleeping 5 sec");
		k_msleep(5000);
	}
}
