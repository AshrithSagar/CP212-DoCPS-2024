#include "radio.h"
#include <string.h>

#define GROUP 25
#define FREQ 7 /* Frequency 2407 MHz */
#define RADIO_PACKET 128

#define BIT(n) (1UL << (n))
typedef unsigned char byte;
static struct {
  byte length;             /* Packet length, including 3-byte prefix */
  byte version;            /* Version: always 1 */
  byte group;              /* Radio group */
  byte protocol;           /* Protocol identifier: always 1 */
  byte data[RADIO_PACKET]; /* Payload */
} packet_buffer;

static radio_callback_t rx_callback;

static volatile enum { MODE_RADIO_RX, MODE_RADIO_TX } mode;

static volatile unsigned long interrupt_flag;

/* wait for expected event and clear it */
static void radio_await(unsigned volatile long *event) {
  while (*event == 0)
    ;

  *event = 0;
}

/* initialise radio hardware */
void radio_init(radio_callback_t callback) {

  // We need external high-frequency crystal for radio
  CLK_HFCLKSTART = 1;
  while (CLK_HFCLKSTARTED == 0)
    ;

  RADIO_TXPOWER = 0;                 // Default transmit power
  RADIO_FREQUENCY = FREQ;            // Transmission frequency
  RADIO_MODE = RADIO_MODE_NRF_1Mbit; // 1Mbit/sec data rate
  RADIO_BASE0 = 0x75626974;          // That spells 'ubit'
  RADIO_TXADDRESS = 0;               // Use address 0 for transmit
  RADIO_RXADDRESSES = BIT(0);        //   and also (just one) for receive.

  // Basic configuration
  RADIO_PCNF0 = 8;          // One 8-bit length field
  RADIO_PCNF1 = 0x02040083; // matched microbian

  // CRC and whitening settings -- match micro_bit runtime
  RADIO_CRCCNF = 2; // CRC is 2 bytes
  RADIO_CRCINIT = 0xffff;
  RADIO_CRCPOLY = 0x11021;
  RADIO_DATAWHITEIV = 0x18;

  RADIO_PREFIX0 = GROUP;
  RADIO_PACKETPTR = (unsigned long)&packet_buffer;

  // Short READY and START to start rx/tx automatically when we enable.
  RADIO_SHORTS = BIT(0);

  rx_callback = callback;
  interrupt_flag = 0;
  mode = MODE_RADIO_RX;

  // Enable interrupt generation for Rx/Tx completion
  RADIO_INTENSET = BIT(RADIO_INT_END);

  // Enable interrupts in NVIC
  NVIC_ISER0 = BIT(RADIO_IRQ);

  // Enable radio and start rx
  RADIO_RXEN = 1;
}

void radio_send(void *buf, unsigned int n) {

  mode = MODE_RADIO_TX;

  // Disable continuous recpetion
  RADIO_DISABLE = 1;
  radio_await(&RADIO_DISABLED);

  // Assemble the packet
  packet_buffer.length = (byte)n + 3;
  packet_buffer.version = 1;
  packet_buffer.group = GROUP;
  packet_buffer.protocol = 1;
  memcpy(packet_buffer.data, buf, n);

  // Enable and start Tx
  RADIO_TXEN = 1;
  radio_await(&interrupt_flag);

  // Disable the transmitter -- otherwise it jams the airwaves
  RADIO_DISABLE = 1;
  radio_await(&RADIO_DISABLED);

  // Enable and start Rx
  mode = MODE_RADIO_RX;
  RADIO_RXEN = 1;
}

void RADIO_IRQHandler(void) {

  static char buf[RADIO_PACKET]; // static, not on stack
  int n;

  RADIO_END = 0;

  if (mode == MODE_RADIO_TX) {
    interrupt_flag = 1;
    return;
  }

  // Copy only if CRC and groups are okay
  if (RADIO_CRCSTATUS && packet_buffer.group == GROUP) {
    // Copy the received packet
    n = packet_buffer.length - 3;
    memcpy(buf, packet_buffer.data, n);

    // Call the application callback
    rx_callback(buf, n);
  }

  // Restart reception
  mode = MODE_RADIO_RX;
  RADIO_START = 1;

  return;
}
