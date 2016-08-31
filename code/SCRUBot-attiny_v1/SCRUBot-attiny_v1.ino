#include <TinyWireS.h>
#include <Stepper.h>

#define I2C_SLAVE_ADDR  0x26 

//Variables
const int stepsPerRev = 200;
int tnthMovesToComplete = 0;
bool checkBuffer = false;
//Initialisation
Stepper stepMotor(stepsPerRev, 1, 3, 4, 5);

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

  if(checkBuffer){
    checkBuffer = false;
    uint8_t typeByte = TinyWireS.receive();
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
          moveFunction(dataByte);
          break;
  
        case 00000010:
          //update speed function
          stepMotor.setSpeed(map(dataByte, 0, 255, 0, 100));
          break;
          
        case 00000011:
        //stop, sets moves to complete to zero
          tnthMovesToComplete = 0;
          break;
    }
  }
}

void receiveEvent(uint8_t num_bytes){
  checkBuffer = true;
}

void requestEvent(){
  
}

void moveFunction(uint8_t tnthMoves){
  //update moves to make
  tnthMovesToComplete = tnthMovesToComplete + tnthMoves;
  
  for(tnthMovesToComplete; tnthMovesToComplete>0; tnthMovesToComplete--)
  {
    stepMotor.step(20);
  }
  
  //send confirmation of rounds
  sendFunc(00001001, 00000000);
  
}

void sendFunc(uint8_t typeByte, uint8_t dataByte){
  TinyWireS.send(typeByte);
  TinyWireS.send(dataByte);
}




