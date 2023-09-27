#include "Arduino.h"
#include "Helper.h"

// JPEG decoder library
#include <JPEGDecoder.h>

//====================================================================================
//   Print information decoded from the Jpeg image
//====================================================================================
void jpegInfo()
{
  Serial.println("===============");
  Serial.println("JPEG image info");
  Serial.println("===============");
  Serial.print("Width      :");
  Serial.println(JpegDec.width);
  Serial.print("Height     :");
  Serial.println(JpegDec.height);
  Serial.print("Components :");
  Serial.println(JpegDec.comps);
  Serial.print("MCU / row  :");
  Serial.println(JpegDec.MCUSPerRow);
  Serial.print("MCU / col  :");
  Serial.println(JpegDec.MCUSPerCol);
  Serial.print("Scan type  :");
  Serial.println(JpegDec.scanType);
  Serial.print("MCU width  :");
  Serial.println(JpegDec.MCUWidth);
  Serial.print("MCU height :");
  Serial.println(JpegDec.MCUHeight);
  Serial.println("===============");
  Serial.println("");
}

//====================================================================================
//   Decode and render the Jpeg image onto the TFT screen
//====================================================================================
void HMI_Helper::jpegRender(TFT_eSPI &tft, int xpos, int ypos)
{

  // retrieve infomration about the image
  uint16_t *pImg;
  int16_t mcu_w = JpegDec.MCUWidth;
  int16_t mcu_h = JpegDec.MCUHeight;
  int32_t max_x = JpegDec.width;
  int32_t max_y = JpegDec.height;

  // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
  // Typically these MCUs are 16x16 pixel blocks
  // Determine the width and height of the right and bottom edge image blocks
  int32_t min_w = minimum(mcu_w, max_x % mcu_w);
  int32_t min_h = minimum(mcu_h, max_y % mcu_h);

  // save the current image block size
  int32_t win_w = mcu_w;
  int32_t win_h = mcu_h;

  // record the current time so we can measure how long it takes to draw an image
  uint32_t drawTime = millis();

  // save the coordinate of the right and bottom edges to assist image cropping
  // to the screen size
  max_x += xpos;
  max_y += ypos;

  // read each MCU block until there are no more
  while (JpegDec.readSwappedBytes())
  { // Swapped byte order read

    // save a pointer to the image block
    pImg = JpegDec.pImage;

    // calculate where the image block should be drawn on the screen
    int mcu_x = JpegDec.MCUx * mcu_w + xpos; // Calculate coordinates of top left corner of current MCU
    int mcu_y = JpegDec.MCUy * mcu_h + ypos;

    // check if the image block size needs to be changed for the right edge
    if (mcu_x + mcu_w <= max_x)
      win_w = mcu_w;
    else
      win_w = min_w;

    // check if the image block size needs to be changed for the bottom edge
    if (mcu_y + mcu_h <= max_y)
      win_h = mcu_h;
    else
      win_h = min_h;

    // copy pixels into a contiguous block
    if (win_w != mcu_w)
    {
      for (int h = 1; h < win_h - 1; h++)
      {
        memcpy(pImg + h * win_w, pImg + (h + 1) * mcu_w, win_w << 1);
      }
    }

    // draw image MCU block only if it will fit on the screen
    if (mcu_x < tft.width() && mcu_y < tft.height())
    {
      // Now push the image block to the screen
      tft.pushImage(mcu_x, mcu_y, win_w, win_h, pImg);
    }

    else if ((mcu_y + win_h) >= tft.height())
      JpegDec.abort();
  }

  // calculate how long it took to draw the image
  drawTime = millis() - drawTime; // Calculate the time it took

  if (DEBUG_HELPER)
  {
    // print the results to the serial port
    Serial.print("Total render time was    : ");
    Serial.print(drawTime);
    Serial.println(" ms");
    Serial.println("=====================================");
  }
}

//====================================================================================
//   Opens the image file and prime the Jpeg decoder
//====================================================================================
void HMI_Helper::drawJpeg(TFT_eSPI &tft, String filename, int xpos, int ypos)
{
  if (DEBUG_HELPER)
  {
    Serial.println("===========================");
    Serial.print("Drawing file: ");
    Serial.println(filename);
    Serial.println("===========================");
  }

  // Open the named file (the Jpeg decoder library will close it after rendering image)
  fs::File jpegFile = SPIFFS.open(filename, "r"); // File handle reference for SPIFFS
  //  File jpegFile = SD.open( filename, FILE_READ);  // or, file handle reference for SD library

  // ESP32 always seems to return 1 for jpegFile so this null trap does not work
  if (!jpegFile)
  {
    if (DEBUG_HELPER)
    {
      Serial.print("ERROR: File \"");
      Serial.print(filename);
      Serial.println("\" not found!");
    }
    return;
  }

  // Use one of the three following methods to initialise the decoder,
  // the filename can be a String or character array type:

  // boolean decoded = JpegDec.decodeFsFile(jpegFile); // Pass a SPIFFS file handle to the decoder,
  // boolean decoded = JpegDec.decodeSdFile(jpegFile); // or pass the SD file handle to the decoder,
  boolean decoded = JpegDec.decodeFsFile(filename); // or pass the filename (leading / distinguishes SPIFFS files)

  if (decoded)
  {
    if (DEBUG_HELPER)
    {
      // print information about the image to the serial port
      jpegInfo();
    }

    // render the image onto the screen at given coordinates
    jpegRender(tft, xpos, ypos);
  }
  else
  {
    if (DEBUG_HELPER)
    {
      Serial.println("Jpeg file format not supported!");
    }
  }
}

void HMI_Helper::fillSegment(TFT_eSPI &tft, int x, int y, int start_angle, int sub_angle, int r, unsigned int colour)
{
  // Calculate first pair of coordinates for segment start
  float sx = cos((start_angle - 90) * DEG2RAD);
  float sy = sin((start_angle - 90) * DEG2RAD);
  uint16_t x1 = sx * r + x;
  uint16_t y1 = sy * r + y;

  // Draw colour blocks every inc degrees
  for (int i = start_angle; i < start_angle + sub_angle; i++)
  {

    // Calculate pair of coordinates for segment end
    int x2 = cos((i + 1 - 90) * DEG2RAD) * r + x;
    int y2 = sin((i + 1 - 90) * DEG2RAD) * r + y;

    tft.fillTriangle(x1, y1, x2, y2, x, y, colour);

    // Copy segment end to sgement start for next segment
    x1 = x2;
    y1 = y2;
  }
}

// #########################################################################
// Return the 16 bit colour with brightness 0-100%
// #########################################################################
unsigned int HMI_Helper::brightness(unsigned int colour, int brightness)
{
  byte red = colour >> 11;
  byte green = (colour & 0x7E0) >> 5;
  byte blue = colour & 0x1F;

  blue = (blue * brightness) / 100;
  green = (green * brightness) / 100;
  red = (red * brightness) / 100;

  return (red << 11) + (green << 5) + blue;
}

// #########################################################################
// Return the 24 bit colour to 16 bit color
// #########################################################################
unsigned int HMI_Helper::color24Bto16B(unsigned int RGB888)
{
  int RGB565 = 0;
  int byte_r = (RGB888 & 0xFF0000) >> 16;
  int byte_g = (RGB888 & 0xFF00) >> 8;
  int byte_b = RGB888 & 0xFF;

  // byte_r = (byte_r & 0x3E) >> 1;
  // byte_g = (byte_g & 0x3F);
  // byte_b = (byte_b & 0x3E) >> 1;

  byte_r = (byte_r * 249 + 1014) >> 11;
  byte_g = (byte_g * 253 + 505) >> 10;
  byte_b = (byte_b * 249 + 1014) >> 11;

  RGB565 = RGB565 | (byte_r << 11);
  RGB565 = RGB565 | (byte_g << 5);
  RGB565 = RGB565 | byte_b;

  return RGB565;
}

// #########################################################################
// Draw an arc with a defined thickness
// #########################################################################

// x,y == coords of centre of arc
// start_angle = 0 - 359
// seg_count = number of 3 degree segments to draw (120 => 360 degree arc)
// rx = x axis radius
// yx = y axis radius
// w  = width (thickness) of arc in pixels
// colour = 16 bit colour value
// Note if rx and ry are the same an arc of a circle is drawn

void HMI_Helper::fillArc(TFT_eSPI &tft, int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)
{

  byte seg = 3; // Segments are 3 degrees wide = 120 segments for 360 degrees
  byte inc = 3; // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Draw colour blocks every inc degrees
  for (int i = start_angle; i < start_angle + seg * seg_count; i += inc)
  {
    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * DEG2RAD);
    float sy = sin((i - 90) * DEG2RAD);
    uint16_t x0 = sx * (rx - w) + x;
    uint16_t y0 = sy * (ry - w) + y;
    uint16_t x1 = sx * rx + x;
    uint16_t y1 = sy * ry + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * DEG2RAD);
    float sy2 = sin((i + seg - 90) * DEG2RAD);
    int x2 = sx2 * (rx - w) + x;
    int y2 = sy2 * (ry - w) + y;
    int x3 = sx2 * rx + x;
    int y3 = sy2 * ry + y;

    tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
    tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
  }
}

void HMI_Helper::drawArc(TFT_eSPI &tft, int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)
{

  byte seg = 1; // Segments are 3 degrees wide = 120 segments for 360 degrees
  byte inc = 1; // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Calculate first pair of coordinates for segment start
  float sx = cos((start_angle - 90) * DEG2RAD);
  float sy = sin((start_angle - 90) * DEG2RAD);
  uint16_t x0 = sx * (rx - w) + x;
  uint16_t y0 = sy * (ry - w) + y;
  uint16_t x1 = sx * rx + x;
  uint16_t y1 = sy * ry + y;

  // Draw colour blocks every inc degrees
  for (int i = start_angle; i < start_angle + seg * seg_count; i += inc)
  {
    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * DEG2RAD);
    float sy2 = sin((i + seg - 90) * DEG2RAD);
    int x2 = sx2 * (rx - w) + x;
    int y2 = sy2 * (ry - w) + y;
    int x3 = sx2 * rx + x;
    int y3 = sy2 * ry + y;

    tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
    tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);

    // Copy segment end to sgement start for next segment
    x0 = x2;
    y0 = y2;
    x1 = x3;
    y1 = y3;
  }
}

void HMI_Helper::drawImage(TFT_eSPI &tft, const char *icon, int x, int y)
{
  HMI_Helper().drawJpeg(tft, icon, x, y);
}

void HMI_Helper::drawLoading(TFT_eSPI &tft, unsigned int color)
{
  static unsigned int angle = 0;
  HMI_Helper().drawArc(tft, HELPER_WIDTH_CENTER, HELPER_HEIGHT_CENTER, 0, angle, HELPER_DESIGN_RADIUS_PX, HELPER_DESIGN_RADIUS_PX, HELPER_DESIGN_CIRCLE_WIDTH_PX, HELPER_COLOR_GREY_PRIMARY);
  HMI_Helper().drawArc(tft, HELPER_WIDTH_CENTER, HELPER_HEIGHT_CENTER, angle, 25, HELPER_DESIGN_RADIUS_PX, HELPER_DESIGN_RADIUS_PX, HELPER_DESIGN_CIRCLE_WIDTH_PX, color);
  if (angle == 360)
  {
    angle = 0;
  }
  else
  {
    angle += 30;
  }
}

void HMI_Helper::drawProgress(TFT_eSPI &tft, unsigned int elapsed, unsigned int end)
{
  static uint16_t angle = 0;
  static bool OnceUpdated = false;
  static bool OnceUpdated2 = false;
  angle = map(elapsed, 0, end, 0, 360);
  if (angle == 0)
  {
    OnceUpdated = false;
    OnceUpdated2 = false;
  }
  if (angle >= 180 && angle < 270 && OnceUpdated == false)
  {
    OnceUpdated = true;
    HMI_Helper().drawArc(tft, HELPER_WIDTH_CENTER, HELPER_HEIGHT_CENTER, 0, 360, HELPER_DESIGN_RADIUS_PX, HELPER_DESIGN_RADIUS_PX, HELPER_DESIGN_CIRCLE_WIDTH_PX, HELPER_COLOR_YELLOW_PRIMARY);
  }
  else if (angle >= 270 && angle < 360 && OnceUpdated2 == false)
  {
    OnceUpdated2 = true;
    HMI_Helper().drawArc(tft, HELPER_WIDTH_CENTER, HELPER_HEIGHT_CENTER, 0, 360, HELPER_DESIGN_RADIUS_PX, HELPER_DESIGN_RADIUS_PX, HELPER_DESIGN_CIRCLE_WIDTH_PX, HELPER_COLOR_RED_PRIMARY);
  }
  else
  {
    // do nothing
  }
  HMI_Helper().drawArc(tft, HELPER_WIDTH_CENTER, HELPER_HEIGHT_CENTER, 0, angle, HELPER_DESIGN_RADIUS_PX, HELPER_DESIGN_RADIUS_PX, HELPER_DESIGN_CIRCLE_WIDTH_PX, HELPER_COLOR_GREY_PRIMARY);
}

void HMI_Helper::resetCircle(TFT_eSPI &tft, unsigned int color)
{
  HMI_Helper().drawArc(tft, HELPER_WIDTH_CENTER, HELPER_HEIGHT_CENTER, 0, 360, HELPER_DESIGN_RADIUS_PX, HELPER_DESIGN_RADIUS_PX, HELPER_DESIGN_CIRCLE_WIDTH_PX, color);
}

void HMI_Helper::drawMenuLine(TFT_eSPI &tft, String text, int x, int y, bool selected)
{
  if (selected == true)
  {
    tft.fillRect(0, HELPER_POINT_TO_PX(y - 1), TFT_WIDTH, HELPER_POINT_TO_PX(19), HELPER_COLOR_RED_PRIMARY);
    tft.setTextColor(HELPER_COLOR_BACKGROUND, HELPER_COLOR_RED_PRIMARY);
  }
  else
  {
    tft.fillRect(0, HELPER_POINT_TO_PX(y - 1), TFT_WIDTH, HELPER_POINT_TO_PX(19), HELPER_COLOR_BACKGROUND);
    tft.setTextColor(HELPER_COLOR_TEXT, HELPER_COLOR_BACKGROUND);
  }
  tft.drawString(text, x, HELPER_POINT_TO_PX(y), 1);
}