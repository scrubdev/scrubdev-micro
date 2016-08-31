#include <TinyWireS.h>
#include <Stepper.h>

#define I2C_SLAVE_ADDR  0x26 

//Variables
const int stepsPerRev = 200;

void setup() {
  // put your setup code here, to run once:
  TinyWireS.begin(I2C_SLAVE_ADDR);
  
  // register the onReceive() callback function
  TinyWireS.onReceive(receiveEvent);
  
  // register the onRequest() callback function
  TinyWireS.onRequest(requestEvent);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void receiveEvent(uint8_t num_bytes){
  uint8_t dataByte = TinyWireS.receive();
  switch(dataByte)
  {
    case 00000000:
    //resets MCU
    //Bit o' C
      #define soft_reset()        \
      do                          \
      {                           \
          wdt_enable(WDTO_15MS);  \
          for(;;)                 \
          {                       \
          }                       \
      } while(0)
      break;

      case 00000001:
        //move instruction
        
        break;

      case 00000010:
        //update speed function
        break;
  }

  
}

void requestEvent(){
  
}

void moveFunction(){
  
}

