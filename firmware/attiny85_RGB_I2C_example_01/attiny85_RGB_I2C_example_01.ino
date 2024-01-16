/*  
 *  Created 2022 by Robert Sedak
 *  
 *  This example code is in the public domain.
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
 *  
 *  This example demonstrates communication between Arduino and ATTiny85 RGB I2C module
 *  
 */

#include <Wire.h>


byte LED_I2C_addr = 0x09;
byte LED_blink = 0;

void setup() {
  Wire.begin(); // join i2c bus
} // end of setup function

void loop() {
  // do not blink
  Wire.beginTransmission(LED_I2C_addr); // transmit to device #9
  Wire.write("b");                      // sends one byte
  Wire.write(0);                        // sends one byte
  Wire.endTransmission();               // stop transmitting

  for (int i = 0; i <= 7; i++) {
    Wire.beginTransmission(LED_I2C_addr); // transmit to device #9
    Wire.write("c");           // sends one byte
    Wire.write(i);             // sends one byte
    Wire.endTransmission();    // stop transmitting
    delay(2000);
  }

  // start blinking
  Wire.beginTransmission(LED_I2C_addr); // transmit to device #9
  Wire.write("b");                      // sends one byte
  Wire.write(1);                        // sends one byte
  Wire.endTransmission();               // stop transmitting

  for (int i = 0; i <= 7; i++) {
    Wire.beginTransmission(LED_I2C_addr); // transmit to device #9
    Wire.write("c");           // sends one byte
    Wire.write(i);             // sends one byte
    Wire.endTransmission();    // stop transmitting
    delay(2000);
  }

} // end of loop function
