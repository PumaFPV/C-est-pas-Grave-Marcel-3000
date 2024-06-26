void wifi_begin;


void wifi_begin()
{
  int tentative = 0;
  // Connect to WiFi network
  //WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (wifiMulti.run() != WL_CONNECTED && tentative < 2) 
  {
    delay(500);
    Serial.print(".");
    tentative++;
  }
  if(tentative > 2){
    Serial.println("couldnt connect");
    return;
  }
  
  Serial.println("");
  //Serial.print("Connected to ");
  //Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) 
  { //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) 
    {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) 
    {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) 
      { //start with max available size
        Update.printError(Serial);
      }
    } 
    else if (upload.status == UPLOAD_FILE_WRITE) 
    {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) 
      {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) 
    {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } 
      else 
      {
        Update.printError(Serial);
      }
    }
  });
  server.begin();
}
