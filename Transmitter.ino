#define TRANSMIT 8
#define CLOCK 2
#define T 10

//PRESS THE RESET BUTTON AT THE SAME TIME

//bool clockStatus = LOW;
//String s = "Hello World! I am an Arduino NANO\n";
//int bitLength = (s.length()+1)*8;
//bool bits[800];
//int index = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TRANSMIT, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  delay(1000);
  transmitBits("HELLO", T);
  transmitBits("WORLD", T);
  transmitBits("THIS IS ARDUINO UNO", T);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void transmitBits(String str, int pulse){
  pinMode(CLOCK, INPUT_PULLUP);
  while(digitalRead(CLOCK) == LOW){}
  //delay(50);
  pinMode(CLOCK, INPUT);
  pinMode(CLOCK, OUTPUT);
  delay(20);
  //Serial.println("StartTranmit()");
  
  int bitLength = (str.length()+1)*8;
  bool bits[bitLength];
  int index = 0;
  stringToBits(str, bits, bitLength);
  /*
  for(int k = 0; k < bitLength; k++){
    if(k%8 == 0) Serial.print(" ");
    Serial.print(bits[k]);
    }Serial.println(""); 
  */
  while(index < bitLength){
    digitalWrite(TRANSMIT, bits[index++]);
    //delay(10);
    clockPulse(pulse);
  }
  delay(5); 
}
/*
void transmitBitsOLD(String str, int pulse){
  //transmitSignal();
  if(index < bitLength){
    digitalWrite(TRANSMIT, bits[index++]);
    //delay(1);
    clockPulse(pulse);
  }else{index = 0;}
  //delayMicroseconds(pulse/2);
}
*/
void clockPulse(int pulse){
   digitalWrite(CLOCK, HIGH);
   delayMicroseconds(pulse);
   digitalWrite(CLOCK, LOW);
   delayMicroseconds(pulse);
}

void stringToBits(String str, bool bits[], int arrLength){
  for(int i = 0; i <= str.length(); i++){
    char c = str.charAt(i);
    for(int j = 7; j >= 0; j--){
      bits[i*8 + j] = c & 1;
      c = c >> 1;
    }
  }
  /*
  for(int k = 0; k < arrLength; k++){
    if(k%8 == 0) Serial.print(" ");
    Serial.print(bits[k]);
    }Serial.println("");
  */
}
