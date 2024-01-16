/*
/* ATTiny85 RGB I2C firmware 1
 *  
 * Created 2022 by Robert Sedak
 * 
 * This example code is in the public domain.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHOR(S) OR 
 *  CONTRIBUTOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 *  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR 
 *  THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Tested on ATTiny85 running at 1MHz.
 * 
 * Module receives two I2C commands with respective argument.
 * 
 * Command ‘c’ accepts values:
 * 0 – no light
 * 1 – red is on
 * 2 – orange is on
 * 3 – green is on
 * 4 – cyan is on
 * 5 – blue is on
 * 6 – violet is on
 * 7 – white is on
 * 
 * Command ‘b’ accept vales:
 * 0 – light does not blink
 * 1 – light is blinking
 *
 */

#include <Wire.h>
const int redPin = 1; 
const int grnPin = 3; 
const int bluPin = 4;

volatile byte option = 0;
volatile char command;
byte LED_I2C_addr = 0x09;
volatile byte BlinkLED = 0;

void setup() {
  pinMode(redPin, OUTPUT);    
  pinMode(grnPin, OUTPUT);    
  pinMode(bluPin, OUTPUT);
  digitalWrite(redPin, LOW);
  digitalWrite(grnPin, LOW);
  digitalWrite(bluPin, LOW);
  Wire.begin(LED_I2C_addr);     // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}

void loop() {
  delay(10);
  switch (command) {
    case 'c' :
      switch (option) {
        case 0 :
          digitalWrite(redPin, LOW);
          digitalWrite(grnPin, LOW);
          digitalWrite(bluPin, LOW);
          break;
        case 1 :
          digitalWrite(redPin, HIGH);
          digitalWrite(grnPin, LOW);
          digitalWrite(bluPin, LOW);
          break;
        case 2 :
          digitalWrite(redPin, HIGH);
          digitalWrite(grnPin, HIGH);
          digitalWrite(bluPin, LOW);
          break;
        case 3 :
          digitalWrite(redPin, LOW);
          digitalWrite(grnPin, HIGH);
          digitalWrite(bluPin, LOW);
          break;
        case 4 :
          digitalWrite(redPin, LOW);
          digitalWrite(grnPin, HIGH);
          digitalWrite(bluPin, HIGH);
          break;
        case 5 :
          digitalWrite(redPin, LOW);
          digitalWrite(grnPin, LOW);
          digitalWrite(bluPin, HIGH);
          break;
        case 6 :
          digitalWrite(redPin, HIGH);
          digitalWrite(grnPin, LOW);
          digitalWrite(bluPin, HIGH);
          break;
        case 7 :
          digitalWrite(redPin, HIGH);
          digitalWrite(grnPin, HIGH);
          digitalWrite(bluPin, HIGH);
          break;
        default:
          digitalWrite(redPin, LOW);
          digitalWrite(grnPin, LOW);
          digitalWrite(bluPin, LOW);        
      }
      break;

  }
  if (BlinkLED) {
      delay(500);
      int redPinState = digitalRead(redPin);
      int grnPinState = digitalRead(grnPin);
      int bluPinState = digitalRead(bluPin);
      if (redPinState) digitalWrite(redPin, LOW);
      if (grnPinState) digitalWrite(grnPin, LOW);
      if (bluPinState) digitalWrite(bluPin, LOW);
      delay(500);
      if (redPinState) digitalWrite(redPin, HIGH);
      if (grnPinState) digitalWrite(grnPin, HIGH);
      if (bluPinState) digitalWrite(bluPin, HIGH);
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    command = (char)Wire.read(); // receive byte as a character
  }
  option = (byte)Wire.read();    // receive byte as an integer
  if (command == 'b') BlinkLED=option;
}
