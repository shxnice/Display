/*
 * Simple program for FRDM-K64F with CAN loopback 
 *
 * Implemented using mbed OS 5 and threads scheduled according to RMS
 *
 * DK - 02-Feb-2019
 */


#include <stdbool.h>
#include <stdint.h>
#include <mbed.h>
#include <stdio.h>
#include <assert.h>
#include "can.h"

static DigitalOut red(LED_RED);
static Serial pc(USBTX, USBRX, 115200);
uint32_t txCount;
uint32_t rxCount;

Thread writer(osPriorityRealtime);
Thread reader(osPriorityRealtime1);

static void led1Toggle(void);
static void canWriteTask(void);
static void canReadTask(void);
static void canHandler(canISRData_t *);

int main () {
    osStatus status;

    red = 0;
    canInit(true);
    pc.printf("Display -- Loopback test\n");

    status = reader.start(canReadTask);
    assert(osOK == status);
    status = writer.start(canWriteTask);
    assert(osOK == status);

    while (true) {
      led1Toggle();
      wait_ms(500);
    }
}

static void led1Toggle(void) {
  red = 1 - red;
}

void canWriteTask(void) {
  
  static canMessage_t txMsg = {0x23, 8, 0, 0};
  bool txOk;
    
  while (true) {
      // Transmit message on CAN 
      txOk = canWrite(&txMsg);
      if (txOk) {
	txCount += 1;
	txMsg.dataA = txCount;
	txMsg.dataB = txCount;
      }
      wait_ms(250);
  }
}

void canReadTask(void) {

  static canMessage_t rxMsg;
  static canISRData_t canData;

  canData.message = &rxMsg; 
  canData.rxDone = false;
  canRxInterrupt(canHandler, &canData);

  while (true) {
      if (canData.rxDone) {
	  canData.rxDone = false;
	  pc.printf("ID: 0x%lx LEN: 0x%01lx DATA_A: 0x%08lx DATA_B: 0x%08lx\n", rxMsg.id, rxMsg.len, rxMsg.dataA, rxMsg.dataB); 
	  rxCount += 1;
      }
      wait_ms(150);
  }
}

void canHandler(canISRData_t *d) {
    d->rxDone = true;
}
    

