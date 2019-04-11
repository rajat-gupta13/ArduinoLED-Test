#include<Uduino.h>
Uduino uduino("MassSpec");

#include<FastLED.h>
#define LED_PIN     5
#define NUM_LEDS    23
#define BRIGHTNESS  100
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[23];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

bool machineOn = false;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  fill_solid( currentPalette, 16, CRGB::Black);
  currentBlending = LINEARBLEND;
  
  uduino.addCommand("turnOn", turnOnMachine);
  uduino.addCommand("turnOff", turnOffMachine);
}

void turnOnMachine(){
  machineOn = true;
  SetupBlackAndWhiteStripedPalette();
}

void turnOffMachine(){
  machineOn = false;
  fill_solid( currentPalette, 16, CRGB::Black);
}

void loop() {
  uduino.update();
  delay(10);
  // Your operations here
  if (machineOn)
  {
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
  }
  else if (!machineOn)
  {
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
  }
  
  
}

void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
