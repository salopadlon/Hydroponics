/*
 * Pavel Sadlon
 * 05/2018
 * Source code for FEI STU subject DTV
 * Hydroponics system data gathering by DHT22, MCP9700 sensors
 * and visualisation on display PCD8544
 * 
 * *************************************************************
 * PCD8544 CONNECTION
 * ************************************************************
 * 
 * CLK   = 3   
 * DIN   = 4 
 * DC    = 5  
 * RESET = 6  
 * CE    = 7
 */

#include <DHT.h>;
#include <PCD8544.h>

#define DHTPIN 8     // What pin is DHT22 connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define MCPPIN A0       // What pin is MCP9700 connected to

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino

static PCD8544 lcd;
float hum;  // Stores air humidity value
float temp; // Stores air temperature value
float tempw; // Stores water temperature value

void setup()
{
  Serial.begin(9600);
  dht.begin();
  lcd.begin(84, 48);
}

void loop()
{
      hum = dht.readHumidity(); // Read air humidity
      temp = dht.readTemperature(); // Read air temperature

      /* Read water temperature 
       * we need to get the real value by mathematic operations based on datasheet */
  
      tempw = ((float)analogRead(MCPPIN) * 5 / 1024.0) - 0.5; 
      tempw = tempw / 0.01; 

      //Check if the sensors are reading numeric values
      if (isnan(temp) || isnan(hum)) {
        lcd.print("Failed to read from DHT");
    } else if (isnan(tempw)) {
        lcd.print("Failed to read from MCP");
    } else {
      

      //Set cursor position on display and print on display
      lcd.setCursor(0, 0); 
      lcd.print("Hum: ");
      lcd.print(hum);
      lcd.print("%");

      //Set cursor position on display and print on display
      lcd.setCursor(0, 2); 
      lcd.print("Temp: ");
      lcd.print(temp);
      lcd.print("C");

      //Set cursor position on display and print on display
      lcd.setCursor(0, 4); 
      lcd.print("Water: ");
      lcd.print(tempw);
      lcd.print("C");
    }

    delay(2000);
}
