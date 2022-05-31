#include <Servo.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <WiFiMulti.h>
#include <SPIFFS.h>

#define TFT_CS 15
#define TFT_DC 2
#define TFT_RST 4
#define TFT_BL 19

uint16_t x_offset, y_offset = 0;

#include "Arduino_HWSPI.h"
#include "Arduino_ESP32SPI.h"
#include "Arduino_SWSPI.h"
#include "Arduino_GFX.h"     // Core graphics library
#include "Arduino_Display.h" // Various display driver
#include "JpegDec.h"
#include <Adafruit_GFX.h>

// FreeFonts from Adafruit_GFX
//#include <Fonts/FreeMono24pt7b.h>

static JpegDec jpegDec;
WiFiMulti wifiMulti;
WebServer server(80);

Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, 18 /* SCK */, 23 /* MOSI */, -1 /* MISO */, VSPI /* spi_num */);
Arduino_GC9A01 *gfx = new Arduino_GC9A01(bus, TFT_RST, 0 /* rotation */, true /* IPS */);

const char* host = "esp32";

#include "pins.h"
#include "login_page.h"
#include "wifi.h"
#include "display.h"

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Startup");
  wifiMulti.addAP("corniche2", "corniche2");
  wifiMulti.addAP("corniche", "cornichon");
  wifiMulti.addAP("TP-Link_A91A", "30309838");
  //wifiMulti.addAP("ssid", "mdp");

  wifi_begin();
  
  display_begin();
  pins_begin();
  //ledcSetup(0, 5000, 8);
  //ledcAttachPin(TFT_BL, 0);

  // Init SPIFFS
  if (!SPIFFS.begin())
  {
    Serial.println(F("ERROR: SPIFFS Mount Failed!"));
    gfx->println(F("ERROR: SPIFFS Mount Failed!"));
  }

  //ledcWrite(0, 50);
  //brightness(10);  //from 0 to 10

  jpg("/empty_grad.jpg", 0, 0);
  delay(500);
}

void loop(void) 
{

  server.handleClient();  //wifi loop
  read_pins();
  smart_refresh_display();
  //set_temp(20); //
  delay(100);

  }
