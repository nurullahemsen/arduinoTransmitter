#define TRANSMIT 8
#define CLOCK 2
#define T 10 //TIME INTERVAL IN MICROSECONDS

/*
  FOR INITIAL SYNCHRONIZATION YOU MAY HAVE TO PRESS THE RESET BUTTON OF EACH
  DEVICE AT THE SAME TIME.
  
  IF RECEIVER SIDE SKIPS BITS, CHARS OR EVEN STRINGS IT MUST BE RESET OR ANY
  INCOMING BITS WILL BE INTERPRETED WRONG.

  THE CLOCK IS ASSIGNED TO PIN D2 (BECAUSE IT HAS INTERRUPTS). FROM MY TESTS
  THE ARDUINO UNO AND NANO PINS BEHAVE RANDOMLY (PROBABLY FLOATING) AND CAUSES
  UNWANTED INTERRUPTS AT THE RECEIVER SIDE WHEN RESET. (FOR ROUGHLY A HALF SECOND)
  TO PREVENT THAT FROM HAPPENING THE CLOCK PIN SHOULD BE PULLED DOWN TO GND
  WITH A RESISTOR. (FROM MY EXPERIENCES THE PULLDOWN RESISTOR CAN BE ANYTHING
  FROM 1K TO 100K BUT I RECOMMEND HIGHEST TO PREVENT TOO MUCH CURRENT GOING 
  WASTE. 100K DID THE JOB WELL)

  ARDUINO T D2 |-----
                    |
                    |   100K
                    -----ww----| GND (COMMON)
                    |
                    |
  ARDUINO R D2 |-----

  ARDUINO T D8 ------------ D7 ARDUINO R

  ALSO YOU HAVE TO HAVE A COMMON GROUND BETWEEN TRANSMITTER AND THE RECEIVER
  SIDE.

  WHEN TWO ARDUINOS WORKING WITHOUT ERROR. RESETTING THE TRANSMITTER ARDUINO
  CAUSES THE RECEIVER SERIAL PORT TO DISPLAY:
  
    HELLO
    WORLD!
    THIS IS ARDUINO UNO

  IF NOT, MOST PROBABLY A BIT IS SKIPPED. RESET THE RECEIVER ARDUINO AND TRY 
  AGAIN. IF THE ERROR PERSIST, YOU CAN TRY INCREASING THE TIME INTERVAL T. 
  BUT 10 MICROSECONDS WORKED FINE WITH ME.

  WITH T = 10 MICROSECONDS A BYTE WILL BE TRANSMITTED IN 160 MICROSECONDS.
  ALSO WHEN THE STRING TRANSMITTED A 5 MILLISECONS DELAY IS GIVEN IN ORDER TO
  GIVE TIME TO RECEIVER SIDE FOR ARRANGING RECEIVED CHARS TO A STRING.

  LASTLY, I DID NOT USE A BUFFER ON THE RECEIVER AND READ THE STRING OR A BYTE
  FROM BUFFER WHEN ANY AVAILABLE AS I SHOULD. I DIDNT GET INTO THAT BECAUSE 
  THIS IS JUST A PROOF OF CONCEPT.

  March 2019
  nurullah.emsen@gmail.com
  
*/


void setup() {
  pinMode(TRANSMIT, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  delay(1000);
  transmitBits("HELLO", T);
  transmitBits("WORLD!", T);
  transmitBits("THIS IS ARDUINO UNO", T);
}

void loop() {}

/*
 * Takes a string and transmits is bit by bit.
 * For each bit signal sent (from TRANSMIT pin), a "clock" pulse sent right 
 * after it.
 * 
 * The clock's rising edge tells the receiver side to read the incoming bit.
 * 
 * pulse is the time interval.
 */
void transmitBits(String str, int pulse){
  int bitLength = (str.length()+1)*8;
  bool bits[bitLength];
  int index = 0;
  stringToBits(str, bits);
  while(index < bitLength){
    digitalWrite(TRANSMIT, bits[index++]);
    //delay(10);
    clockPulse(pulse);
  }
  delay(5); //time needed for receiving side to arrange received chars to a string
}

/*
 * Produces a square wave at 2 pulse wavelength.
 * It causes interrupts on receiver side at rising edge.
 */
void clockPulse(int pulse){
   digitalWrite(CLOCK, HIGH);
   delayMicroseconds(pulse);
   digitalWrite(CLOCK, LOW);
   delayMicroseconds(pulse);
}

/*
 * Takes a string and converts it into a bit array.
 * Not an elegant and memory friendly solution since a boolean value also takes 1
 * byte memory.
 */
void stringToBits(String str, bool bits[]){
  for(int i = 0; i <= str.length(); i++){
    char c = str.charAt(i);
    for(int j = 7; j >= 0; j--){
      bits[i*8 + j] = c & 1;
      c = c >> 1;
    }
  }
}
