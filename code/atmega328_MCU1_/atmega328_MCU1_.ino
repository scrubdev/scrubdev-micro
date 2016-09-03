//#include <SerialCommand.h>

//vars
bool checkUART = false;
char paramTerminator = ',';
int paramArrayNumber = 0;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.setTimeout(3000);
}

void loop() {
  // put your main code here, to run repeatedly
  //Serial.read();
  if(checkUART){
    //checkUART = false;
    UARTSwitcher();
  }
}

void serialEvent(){
   checkUART = true;
}

void UARTSwitcher(){
  uint8_t commandArray[3];
  for(int i = 0; i<3;i++)
  {
    commandArray[i] = Serial1.read();
  }
  //get ride of Pipe
  Serial1.read();
  //concat into e.g. 000 
  int commandInt = (commandArray[1]*100)+(commandArray[2]*10)+(commandArray[3]);

  switch(commandInt)
  {
    case 000:
    {
      ResetRec();
      break;
    }
  }
  
}

String paramRetreive(){
  //change for loop and array size to max parrams
  String paramArray[5];
  for(int i = 0; i<5; i++){
    if(Serial1.peek() == '|'){
      Serial1.read();
      Serial1.readStringUntil(paramTerminator);
      break;
    }
    paramArray[i] =  Serial1.readStringUntil(paramTerminator);
  }
  return paramArray[paramArrayNumber];
}


void ResetRec(){
  int resetType = int(paramRetreive());
  switch(resetType){
    case 0:
    {
      
    }
  }
}

void LowPowerRec(){
  
}

void MoveRec(){
  
}

void RotateRec(){
  
}

void ModeRec(){
  
}

