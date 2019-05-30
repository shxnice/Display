#include <FXOS8700Q.h">
#include <stdbool.h>
#include <stdint.h>
#include <mbed.h>
#include <stdio.h>
#include "can.h"
#include <assert.h>
#include "scheuler.h"
#include "counter.h"

static DigitalOut green (LED GREEN);
static Serial pc(USBTX, USBRX, 115200) ; // init s er ia l connection

I2C i2c (PTE25, PTE24) ;
FXOS8700QAccelerometer acc ( i2c , FXOS8700CQ SLAVE ADDR1) ; // K64F onboard accelerometer , used to gather readings to send over the CAN network

uint32 t timeElapsed = 0; // counts time task takes to complete 19 
uint32 t counterCompTime = 0; // find time it takes to start and stop the counter 20 
uint t min = 100000; // store shortest time to complete task , cant be zero because task cant be faster than zero 
uint32 t max = 0; // store longest time to complete task 22 uint32 t avg ; // store average time of all tests 
uint32 t testCounter ; // number of times test is ran

void tempT( void ) ;  
static void tachoT( void ) ;
int16_t raX , raY , raZ , rmX, rmY, rmZ, tmp int ; // Used to hold readings from accelerometer − Only ’raY ’ is used currently 

int main () { 
	counterInit () ; // turn counter on ready 
	counterStart () ; // start running counter 
	counterCompTime = counterStop () ; // find time it takes to turn counter on and off  
	pc . printf (”\ncounterCompTime : %020lu\n” , counterCompTime); 
	green = 0; //Turn red LED on to check program is running properly
	
canInit(BD125000, FALSE); // the can network is on
	pc(printf("EngineMonitor - loopback test"); // prints message to show success
	acc.enable(); // the accelorator is enabled
	schInit(); // the scheduler is initalised
	schAddTask(tachoT, 1, 20); // the tasks are added to the schedulers
	schAddTask(tachoT, 2, 500);
	schStart(); // scheduler starts
	
	while ( true ) { 
		schDispatch () ; //run scheduler forever
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		





