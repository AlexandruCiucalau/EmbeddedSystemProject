#ifndef Helper_h
#define Helper_h

// File Manager
#include "FileManagerE.h"

// TFT
#include <TFT_eSPI.h>

// EEPROM
#include "EEPROME.h"

// DIAG
#define DEBUG_HELPER false

// Return the minimum of two values a and b
#define minimum(a, b) (((a) < (b)) ? (a) : (b))
#define DEG2RAD 0.0174532925

#define HELPER_TFT_ORIENTATION 0 // ?0 & 2 Portrait. || 1 & 3 landscape

#define HELPER_WIDTH_CENTER (TFT_WIDTH / 2)
#define HELPER_HEIGHT_CENTER (TFT_HEIGHT / 2)

#define HELPER_WIDTH_IMAGE_CENTER(IMG_WIDTH) (HELPER_WIDTH_CENTER - (IMG_WIDTH / 2))
#define HELPER_HEIGHT_IMAGE_CENTER(IMG_HEIGHT) (HELPER_HEIGHT_CENTER - (IMG_HEIGHT / 2))

// *************** DESIGN MACROS *************** //
//?COLORS
#define HELPER_COLOR_BACKGROUND 0x4208
#define HELPER_COLOR_TEXT 0x5350
#define HELPER_COLOR_SPEED_GAUGE 0x31A6
#define HELPER_COLOR_GREY_PRIMARY 0xBDD7
#define HELPER_COLOR_GREY_SECONDARY 0xBDD7

#define HELPER_COLOR_LOADING_PRIMARY 0x2B20
#define HELPER_COLOR_LOADING_SECONDARY 0x5CA4

#define HELPER_COLOR_GREEN_PRIMARY 0x2B20
#define HELPER_COLOR_GREEN_SECONDARY 0x2B20

#define HELPER_COLOR_RED_PRIMARY 0xF800
#define HELPER_COLOR_RED_SECONDARY 0xF800

#define HELPER_COLOR_YELLOW_PRIMARY 0xBDA0
#define HELPER_COLOR_YELLOW_SECONDARY 0xCE00

//?CIRCLE MACROS
#define HELPER_DESIGN_RADIUS_PX 100
#define HELPER_DESIGN_CIRCLE_WIDTH_PX 14
#define HELPER_DESIGN_INTERIOR_CIRCLE (HELPER_DESIGN_RADIUS_PX - HELPER_DESIGN_CIRCLE_WIDTH_PX)

//? CONVERTERS
#define HELPER_POINT_TO_PX(pt) ((pt)*1.3333333)
#define HELPER_PX_TO_POINT(px) ((px) / 1.3333333)

class HMI_Helper
{
private:
  // TFT_eSPI tft;
  void jpegRender(TFT_eSPI &tft, int xpos, int ypos);

public:
  HMI_Helper()
  {
  }
  void drawJpeg(TFT_eSPI &tft, String filename, int xpos, int ypos);
  void fillSegment(TFT_eSPI &tft, int x, int y, int start_angle, int sub_angle, int r, unsigned int colour);
  void fillArc(TFT_eSPI &tft, int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour);
  void drawArc(TFT_eSPI &tft, int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour);
  unsigned int brightness(unsigned int colour, int brightness);
  unsigned int color24Bto16B(unsigned int RGB888);
  //
  void drawImage(TFT_eSPI &tft, const char *icon, int x, int y);
  void drawLoading(TFT_eSPI &tft, unsigned int color);
  void drawProgress(TFT_eSPI &tft, unsigned int elapsed, unsigned int end);
  void resetCircle(TFT_eSPI &tft, unsigned int color);
  void drawMenuLine(TFT_eSPI &tft, String text, int x, int y, bool selected);
};

#endif