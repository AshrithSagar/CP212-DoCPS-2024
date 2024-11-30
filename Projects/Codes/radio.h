#ifndef RADIO_H
#define RADIO_H

typedef void (*radio_callback_t)(const char buf[], unsigned int n);
void radio_init(radio_callback_t rx_callback);
void radio_send(void *buf, unsigned int n);

#define RADIO_BASE0 (*(volatile unsigned long *)0x4000151c)
#define RADIO_CRCCNF (*(volatile unsigned long *)0x40001534)
#define RADIO_CRCINIT (*(volatile unsigned long *)0x4000153c)
#define RADIO_CRCPOLY (*(volatile unsigned long *)0x40001538)
#define RADIO_CRCSTATUS (*(volatile unsigned long *)0x40001400)
#define RADIO_DATAWHITEIV (*(volatile unsigned long *)0x40001554)
#define RADIO_DISABLE (*(volatile unsigned long *)0x40001010)
#define RADIO_DISABLED (*(volatile unsigned long *)0x40001110)
#define RADIO_END (*(volatile unsigned long *)0x4000110c)
#define RADIO_FREQUENCY (*(volatile unsigned long *)0x40001508)
#define RADIO_INTENSET (*(volatile unsigned long *)0x40001304)
#define RADIO_INT_END 3
#define RADIO_IRQ 1
#define RADIO_MODE (*(volatile unsigned long *)0x40001510)
#define RADIO_MODE_NRF_1Mbit 0
#define RADIO_PACKETPTR (*(volatile unsigned long *)0x40001504)
#define RADIO_PCNF0 (*(volatile unsigned long *)0x40001514)
#define RADIO_PCNF0_LFLEN_8 8
#define RADIO_PCNF1 (*(volatile unsigned long *)0x40001518)
#define RADIO_PREFIX0 (*(volatile unsigned long *)0x40001524)
#define RADIO_RXADDRESSES (*(volatile unsigned long *)0x40001530)
#define RADIO_RXEN (*(volatile unsigned long *)0x40001004)
#define RADIO_SHORTS (*(volatile unsigned long *)0x40001200)
#define RADIO_START (*(volatile unsigned long *)0x40001008)
#define RADIO_TXADDRESS (*(volatile unsigned long *)0x4000152c)
#define RADIO_TXEN (*(volatile unsigned long *)0x40001000)
#define RADIO_TXPOWER (*(volatile unsigned long *)0x4000150c)

#define NVIC_ISER0 (*(volatile unsigned long *)0xe000e100)
#define NVIC_ICPR0 (*(volatile unsigned long *)0xe000e280)

#define CLK_HFCLKSTART (*(volatile unsigned long *)0x40000000)
#define CLK_HFCLKSTARTED (*(volatile unsigned long *)0x40000100)

#endif /* RADIO_H */
