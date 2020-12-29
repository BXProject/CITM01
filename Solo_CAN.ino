// CAN In The Middle (CITM) 01 - BXProject 7th May 2018
// Based on the work of Cory J. Fowler, January 31st 2014
// Set to L320 (#15)

//--------------------------------------------- // Define function(s) to use, remove comments to enable function(s)
#define SerMon                                  // Turn on Serial functions (used to send data to PC)
//--------------------------------------------- // Setup libraries
#include <mcp_can_dfs.h>                        // Include the required libraries from the MCP_CAN Library Master
#include <mcp_can.h>
#include <SPI.h>                                // Include the SPI library so the CANBus shield is accessible
//--------------------------------------------- // Setup some parameters 
unsigned long rxId;                             
unsigned long rxId_Filter;
unsigned char flagRecv = 0;
unsigned char buf[8];
char str[20];

byte len;
byte rxBuf[8];

MCP_CAN CAN0(9);                                // CAN0 interface usins CS on digital pin 10

#define CAN0_INT 2                              // Set INT to pin 2

//--------------------------------------------- // Setup the hardware
void setup()
{
#ifdef SerMon
  Serial.begin(115200);                         // open up the serial port if the option is turned on
#endif
                                                // init CAN0 bus, baudrate: 125k@8MHz
  if(CAN0.begin(MCP_ANY, CAN_125KBPS, MCP_8MHZ) == CAN_OK){ //MCP_EXT Vs MCP_ANY?
#ifdef SerMon
	  Serial.print("CAN0: Init OK!\r\n");
#endif
  CAN0.setMode(MCP_NORMAL);
  }
  else {
#ifdef SerMon
	  Serial.print("CAN0: Init Fail!!!\r\n");
#endif
  }
  
#ifdef SerMon 
 // Serial.end();
#endif

  SPI.setClockDivider(SPI_CLOCK_DIV2);          // Set SPI to run at 8MHz (16MHz / 2 = 8 MHz)
}

//--------------------------------------------- // Run the main program
void loop(){
	if (!digitalRead(CAN0_INT)) {                 // If pin 2 is low, read CAN0 receive buffer
		CAN0.readMsgBuf(&rxId, &len, rxBuf);        // Read data: len = data length, buf = data byte(s)
    
			#ifdef SerMon
				Serial.print(rxId);                     // Print to serial port the ID of the received message
          Serial.print("\t");
				for (int i = 0; i<8; i++)               // Use a loop to print to serial port the data in the buffer
				{

					Serial.print("0x");
					Serial.print(rxBuf[i], HEX);
					Serial.print("\t");
				}
				Serial.print("\r\n");                   // Dont forget to move to the next line!
			#endif

		}
	}
