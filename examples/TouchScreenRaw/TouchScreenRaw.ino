/*
    For this example, you will need any Dasduino board, TFT 2.4" display, a USB cable, and a few wires.
    Connect TFT Display according to the following wiring diagram:
    VCC - VCC(5V)
    GND - GND
    DC - D9
    BL - VCC or the digital pin if you want to controll backlight
    CLK - D13
    DO - D13
    DI - D11
    CS1 - D10
    CS - D6

    link: solde.red/333211

    When you touch the screen, on the Serial Monitor you will see the coordinates you pressed on the touchscreen.

    Watterott electronic, modified by Soldered.
*/

// Include needed libraries
#include "SPI.h"
#include "TFT-Touch-Display-SOLDERED.h"

// Define pins for DC, CS, and Reset
#define TFT_DC  9
#define TFT_CS  10
#define TFT_RST -1 // If not used, put -1

// Use hardware SPI (#13, #12, #11) and the above for CS, DC, and reset
TFTDisplay tft(TFT_CS, TFT_DC, TFT_RST);

// Create a touchscreen object
TFTTouch ts;

void setup()
{
    // Init serial communication
    Serial.begin(115200);

    // Init Touch-Controller
    Serial.println("Init...");
    ts.begin();

    // Init display
    tft.begin();

    // Print message to know default orientation
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_GREEN);
    tft.setTextSize(5);
    tft.println("Hello!");

    // If you want to get pressed pixel value when touching the screen instead 
    // of weird numbers, you have to calibrate the touchscreen.
    // For calibration run this example and touch the edges of the screen. 
    // Remember the numbers for both axis printed on the serial monitor and 
    // call the function calibrate() with these parameters. For example: 
    // ts.calibrate(540, 1000, 34, 460);
    // Parameters are: 
    // X value when touching the left edge of the display
    // X value when touching the right edge of the display
    // Y value when touching the top edge of the display
    // Y value when touching the bottom edge of the display
}


void loop()
{
    // Read data from the touchscreen
    ts.service();

    // Get raw values of the x, and y coordinates, and pressure (z coordinate)
    uint16_t x = ts.getXraw();
    uint16_t y = ts.getYraw();
    uint16_t z = ts.getPressure();

    // Check if the touchscreen is touched
    // NOTE: The screen must be pressed a bit more than on a smartphone to detect touch
    if (z)
    {
        // Print the raw values on the Serial Monitor
        Serial.print("X: ");
        Serial.print(x, DEC);
        Serial.print(" Y: ");
        Serial.print(y, DEC);
        Serial.print(" Pressure: ");
        Serial.println(z, DEC);
    }

    // Wait a bit
    delay(100);
}