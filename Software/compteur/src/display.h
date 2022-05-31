/*
 * 1 - 80. 57
2
3
4
5
N
empty_no_grad 0. 0
empty_grad
oil_no_grad
oil_grad
beq 29. 178
right 145. 210
left 45. 210
off 94. 218
croisement
route
 */

int number = 5;
float pi = 3.14159267;
double temp_rad = 0.000000;

void brightness(uint32_t value)
{
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / 255) * value;

  // write duty to LEDC
  ledcWrite(0, duty);
}

void jpg(String jpg_name, uint16_t _x_offset, uint16_t _y_offset)
{
  File jpegFile = SPIFFS.open(jpg_name, "r");
  if (!jpegFile)
  {
    Serial.println(F("ERROR: open jpegFile Failed!"));
    gfx->println(F("ERROR: open jpegFile Failed!"));
  }
  else
  {
    // read JPEG file header
    x_offset = _x_offset;
    y_offset = _y_offset;
    jpegDec.prepare(jpegDec.file_reader, &jpegFile);
    // scale to fit height
    jpg_scale_t scale;
    float ratio = (float)jpegDec.height / gfx->height();
    if (ratio <= 1)
    {
      scale = JPG_SCALE_NONE;
    }
    else if (ratio <= 2)
    {
      scale = JPG_SCALE_2X;
    }
    else if (ratio <= 4)
    {
      scale = JPG_SCALE_4X;
    }
    else
    {
      scale = JPG_SCALE_8X;
    }
    // decode and output
    jpegDec.decode(scale, jpegDec.gfx_writer, gfx);
  }  
}



void display_begin()
{
  gfx->begin();
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  // init LCD constant
  int  w = gfx->width();
  int  h = gfx->height();
    
}

void set_temp(int temp)
{
  temp_rad = map(temp + 160, 0, 200, 0, 360) * 0.0174532925;
  //Serial.println(temp_rad);
  gfx->fillArc(120, 120, 100, 110, temp + 160, temp + 165, RED);
  
  /*
  int temp_center_x = 60;
  int temp_center_y = 120;
  int radius = 25;
  Serial.print(temp);
  Serial.print("  ");
  Serial.print(360 * 2 * pi);
  Serial.print("  ");
  Serial.println(temp_rad);
  gfx->fillCircle(temp_center_x, temp_center_y, radius, WHITE);
  gfx->drawLine(temp_center_x, temp_center_y, temp_center_x + cos(temp_rad) * radius, temp_center_y + sin(temp_rad) * radius, BLACK);
  */
}



void smart_refresh_display(){
  //---------------------------------oil
  if(oil != prev_oil){
    switch(oil)
    {
      case 0:
        jpg("/empty_grad.jpg", 0, 0);
        break;
      case 1:
        jpg("/oil_grad.jpg", 0, 0);
        break;
    }
    prev_oil = oil;
  }

  //-----------------------------------light
  if(light != prev_light){
    switch(light)
    {
      case 0:
        jpg("/light_off.jpg", 95, 218);
        break;     
      case 1:
        jpg("/light_crossing.jpg", 95, 218);
        break;
      case 2:
        jpg("/light_road.jpg", 95, 218);
        break;
    }
    prev_light = light;
  }

  //---------------------------------speed
  if(speed != prev_speed){
    switch(speed)
    {     
      case 0:
        jpg("/empty_grad.jpg", 0, 0);
        break;
      case 1:
        jpg("/n.jpg", 80, 57);
        break;
      case 2:
        jpg("/1.jpg", 80, 57);
        break;
      case 3:
        jpg("/2.jpg", 80, 57);
        break;
      case 4:
        jpg("/3.jpg", 80, 57);
        break;
      case 5:
        jpg("/4.jpg", 80, 57);
        break;
      case 6:
        jpg("/5.jpg", 80, 57);
        break;
    }
    prev_speed = speed;
  }

  //---------------------------------beq
  if(beq != prev_beq){
    switch(beq)
    {
      case 0:
        jpg("/beq.jpg", 29, 178);
        break;
      case 1:
        jpg("/no_beq.jpg", 29, 178);
        break;
    }
    prev_beq = beq;
  }

  //---------------------------------right
  if(right != prev_right){
    switch(right)
    {
      case 0:
        jpg("/no_left.jpg", 145, 210);
        break;
      case 1:
        jpg("/right.jpg", 145, 210);
        break;
    }
    prev_right = right;
  }
  
  //---------------------------------left
  if(left != prev_left){
    switch(left)
    {
      case 0:
        jpg("/no_left.jpg", 45, 210);
        break;
      case 1:
        jpg("/left.jpg", 45, 210);
        break;
    }
    prev_left = left;
  }
  
}
