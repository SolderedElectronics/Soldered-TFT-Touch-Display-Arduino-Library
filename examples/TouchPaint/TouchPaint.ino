/***************************************************
  For this example, you will need a TFT display with a touch screen, 
  Dasduino, a USB cable, and a few wires. Also, you have to install 
  the Adafruit GFX library: https://github.com/adafruit/Adafruit-GFX-Library

  Connect TFT Display according to the following wiring diagram and enjoy:
  VCC - VCC(5V)
  GND - GND
  DC - D9
  BL - VCC
  CLK - D13
  DO - D13
  DI - D11
  CS1 - D10
  CS - D6

  link: solde.red/333211

  Original author Adafruit, modified by Soldered.

  "This is our touchscreen painting example for the Adafruit ILI9341 Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution"
 ****************************************************/

// Include needed libraries
#include "TFT-Touch-Display-SOLDERED.h"
#include <Adafruit_GFX.h> // Core graphics library
#include <SPI.h>

// Create a touchscreen object
TFTTouch ts;

// The display uses hardware SPI, plus #9 & #10
#define TFT_CS  10
#define TFT_DC  9
#define TFT_RST -1 // -1 if not used
TFTDisplay tft(TFT_CS, TFT_DC, TFT_RST);

// Size of the color selection boxes and the paintbrush size
#define BOXSIZE   40
#define PENRADIUS 3
int oldcolor, currentcolor;

// Struct for the points in the coordinate system
struct point
{
    int x;
    int y;
} p;

void setup(void)
{
    // Init serial communication
    Serial.begin(115200);
    Serial.println(F("Touch Paint!"));

    // Init tft display and touchscreen
    tft.begin();
    ts.begin();
    Serial.println("Touchscreen started");

    // Calibrate your touch like in the example TouchScreenRaw
    ts.calibrate(540, 1000, 34, 460);

    // Put black background
    tft.fillScreen(ILI9341_BLACK);

    // Make the color selection boxes
    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
    tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
    tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
    tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
    tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);

    // Select the current color 'red'
    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
    currentcolor = ILI9341_RED;
}


void loop()
{
    // Read data from the touchscreen
    ts.service();

    // Check if the touchscreen is touched
    // NOTE: The screen must be pressed a bit more than on a smartphone to detect touch
    if (!ts.getPressure())
    {
        return;
    }

    // Get pressed coordinates
    p.x = ts.getX();
    p.y = ts.getY();

    // Print the coordinates of the pressed point on the screen
    Serial.print("X = ");
    Serial.print(p.x);
    Serial.print("\tY = ");
    Serial.println(p.y);



    if (p.y < BOXSIZE)
    {
        oldcolor = currentcolor;

        if (p.x < BOXSIZE)
        {
            currentcolor = ILI9341_RED;
            tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
        }
        else if (p.x < BOXSIZE * 2)
        {
            currentcolor = ILI9341_YELLOW;
            tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
        }
        else if (p.x < BOXSIZE * 3)
        {
            currentcolor = ILI9341_GREEN;
            tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
        }
        else if (p.x < BOXSIZE * 4)
        {
            currentcolor = ILI9341_CYAN;
            tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
        }
        else if (p.x < BOXSIZE * 5)
        {
            currentcolor = ILI9341_BLUE;
            tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
        }
        else if (p.x < BOXSIZE * 6)
        {
            currentcolor = ILI9341_MAGENTA;
            tft.drawRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
        }

        if (oldcolor != currentcolor)
        {
            if (oldcolor == ILI9341_RED)
                tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
            if (oldcolor == ILI9341_YELLOW)
                tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
            if (oldcolor == ILI9341_GREEN)
                tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
            if (oldcolor == ILI9341_CYAN)
                tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
            if (oldcolor == ILI9341_BLUE)
                tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
            if (oldcolor == ILI9341_MAGENTA)
                tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);
        }
    }
    if (((p.y - PENRADIUS) > BOXSIZE) && ((p.y + PENRADIUS) < tft.height()))
    {
        tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
    }
}