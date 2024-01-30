/**
 * TCA9548 I2CScanner.ino -- I2C bus scanner for Arduino
 *
 * Based on https://playground.arduino.cc/Main/I2cScanner/
 *
 */

 /*
 Red Ink = 5V line
 Always goes 5v -> Ground -> SCL -> SDA
 */

#include "Wire.h"
#include "SPL06-007.h" 

#define TCAADDR 0x70

uint8_t Ports[1][3] = {0,4,7};

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}


// standard Arduino setup()
void setup()
{
    int add_count = 0;

    while (!Serial);
    delay(1000);

    Wire.begin();
    
    Serial.begin(115200);
    Serial.println("\nTCAScanner ready!");
    
    for (uint8_t t=0; t<8; t++) {
      tcaselect(t);
      Serial.print("TCA Port #"); Serial.println(t);

      for (uint8_t addr = 0; addr<=127; addr++) {
        if (addr == TCAADDR) continue;

        Wire.beginTransmission(addr);
        if (!Wire.endTransmission()) {
          Serial.print("Found I2C 0x");  Serial.println(addr,HEX);
        }
        delay(10);
      }
    }
    Serial.println("done");
}

void loop() 
{
  
  delay(1000);
  for(int i=0;i<3;i++){
    tcaselect(Ports[0][i]);
    Wire.begin();    // begin Wire(I2C)
    Serial.begin(115200); // begin Serial
    char buffer[30];
    Serial.print("Goertek-SPL06-007 Demo: Setting up Sensor ");
    Serial.println(Ports[0][i]);
    SPL_init(); // Setup initial SPL chip registers
  }
  while(1){
  }
  /*
  while(1){
    Serial.print(115200);
    for(int i=0;i<3;i++){
      tcaselect(Addresses[1][i]);
      Serial.print("  ");
      Serial.print(get_pressure(),2);
      //Serial.println(1050);
    }
    Serial.println("  ");
  }*/
  
}