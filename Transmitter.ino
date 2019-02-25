#define TRANSMIT 8
#define CLOCK 9

bool clockStatus = LOW;
String s = "Hello World! I am an Arduino NANO\n";
int bitLength = (s.length()+1)*8;
bool bits[800];
int index = 0;
void setup(){

  pinMode(TRANSMIT, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  delay(1000); 
  Serial.begin(9600);
  //Serial.println(s);
  stringToBits(s);
 
 digitalWrite(CLOCK, !clockStatus);
 delay(1000);
 digitalWrite(CLOCK, clockStatus);
 delay(50);

}

void loop()
{ 
   transmitBits(s, 40);
}
void transmitSignal(){
 delay(50);
 digitalWrite(CLOCK, !clockStatus);
 delay(1000);
 digitalWrite(CLOCK, clockStatus);
 
}

void transmitBits(String str, int pulse){
  //transmitSignal();
  if(index < bitLength){
    digitalWrite(TRANSMIT, bits[index++]);
    //delay(1);
    clockPulse(pulse);
  }else{index = 0;}
  //delayMicroseconds(pulse/2);
}

void clockPulse(int pulse){
   digitalWrite(CLOCK, !clockStatus);
   delayMicroseconds(pulse);
   digitalWrite(CLOCK, clockStatus);
   delayMicroseconds(pulse);
}

void stringToBits(String str){
  int arrLength = (str.length()+1)*8;
  //bool stringBits[arrLength];

  for(int i = 0; i <= str.length(); i++){
    char c = str.charAt(i);
    for(int j = 7; j >= 0; j--){
      bits[i*8 + j] = c & 1;
      c = c >> 1;
    }
  }
  for(int k = 0; k < arrLength; k++){
    if(k%8 == 0) Serial.print(" ");
    Serial.print(bits[k]);
    }
}
