#include "Adafruit_TLC59711.h"
#include <SPI.h>

// Initialize LED driver boards and pins
#define NUM_TLC59711 1
#define data   52
#define clock  53
Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data);

// Set the maximum power level for LEDs. Sure beats using resistors...
// 65,535 is the upper limit.
const int max_signal_pwm = 1000;

// ################################################################
// Build out mapping of signal lights to driver boards and channels
// ################################################################

// SOUTH GANTRY
// Freight line - Board 0, channels 0 for red (B +W ) + channel 1 for green (O + W)
uint8_t freight_south_red = 0;
uint8_t freight_south_green = 1;
// Southbound line - Board 0, channels 2 for red (O + W) + channel 3 for green (G + W)
uint8_t southbound_main_red = 2;
uint8_t southbound_main_green = 3;
// Northbound line, southbound - Board 0, channels 4 for red (B + W) + channel 5 for green (G + W)
uint8_t northbound_main_south_red = 4;
uint8_t northbound_main_south_green = 5;

// SOUTH STATION SIGNALS
// Northbound line - Board 0, channels 6 for red (B + W) + channel 7 for green (G + W)
uint8_t northbound_main_north_red = 6;
uint8_t northbound_main_north_green = 7;

void setup() {

  // Start serial monitor for logging out what the signals should be doing
  Serial.begin(9600);
  Serial.println("Model railroad signal lights controller\n");

  // Start the LED driver board
  tlc.begin();

  // Initialize default south station signal lights
  Serial.println("Setting default sigals for south side of the station...\n");
  tlc.setPWM(northbound_main_north_red, 0);
  tlc.setPWM(northbound_main_north_green, max_signal_pwm);
  tlc.setPWM(freight_south_red, max_signal_pwm);
  tlc.setPWM(freight_south_green, 0);
  tlc.setPWM(southbound_main_red, 0);
  tlc.setPWM(southbound_main_green, max_signal_pwm);
  tlc.setPWM(northbound_main_south_red, max_signal_pwm);
  tlc.setPWM(northbound_main_south_green, 0);
  Serial.println("Set northbound main to green.\nOn gantry, set northbound main southbound to red, southbound main to green, southbound freight to red.\n");

  // Write out the required LED channel updates.
  // Must be done after each setPWM command. Can set multiple channels before write();
  tlc.write();
}

void loop() {

}
