// schrdh 2024
// Interfaced for pinduino shield v0.3
// Uses pinduino library
// v0.1.5

#include <pinduino.h>

int aLEDNum1 = 32; // Number of LEDs in LED strip 1
int aLEDNum2 = 20; // Number of LEDs in LED strip 2

pinduino pd(aLEDNum1, aLEDNum2, "Nano");

int attract_on = 1;
unsigned long timeLastEvent = 0;  // time last event was last triggered
int attractWaitTime = 2000;       // Amount of time to wait before chase lights start up again 1000 == 1 second
String attractColor = "red";      // color of LEDs that attract mode starts with
unsigned long timeFirstEvent = 0; // The time the very first event was triggered

void setup()
{
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.pinState()->reset();
}

void loop()
{
  pd.pinState()->update();
  // Print the pin states out to serial
  // pd.pinState()->print();
  checkPinStates();
  if (millis() - timeLastEvent > attractWaitTime)
  {
    attract_on = 1;
  }
  if (attract_on)
  {
    attractMode();
  }
}

void checkPinStates()
{
  int trigger = 0;

  // 17 Hot Dog Flash Lamps
  if (pd.pinState()->J126(1))
  {
    pd.adrLED1()->chase("red", 4, 5, -1);
    delay(25);
    pd.adrLED1()->chase("red", 4, 5, 1);
    trigger = 1;
  }

  // 18 Right Sling Flashlamps
  if (pd.pinState()->J126(2))
  {
    pd.colorAllAdr("white");
    pd.fadeOutAllAdr(50);
    trigger = 1;
  }

  // 19 Left Sling Flashlamps
  if (pd.pinState()->J126(3))
  {
    pd.colorAllAdr("white");
    pd.fadeOutAllAdr(50);
    trigger = 1;
  }

  // 20 Left Lock Flashlamps
  if (pd.pinState()->J126(4))
  {
    pd.adrLED1()->chase2ColorFromPoint(16, "red", "blue", 10, 10);
    pd.adrLED1()->spreadInFromPoint2Color(16, "blue", "red", 150);
    pd.adrLED1()->spreadOutToPoint(16, 150);
    trigger = 1;
  }

  // 21 Gun Flashlamps
  if (pd.pinState()->J126(5))
  {
    pd.adrLED1()->color("blue");
    delay(500);
    pd.adrLED1()->color("red");
    delay(500);
    trigger = 1;
  }

  // 22 Right Ramp Flashlamps
  if (pd.pinState()->J126(6))
  {
    pd.adrLED1()->chase2ColorFromPoint(16, "blue", "blue", 10, 2);
    pd.adrLED1()->chase2ColorFromPoint(16, "blue", "blue", 10, 2);
    trigger = 1;
  }

  // 23 Left Ramp Flashlamps
  if (pd.pinState()->J126(7))
  {
    pd.adrLED1()->chase2ColorFromPoint(16, "red", "red", 10, 2);
    pd.adrLED1()->chase2ColorFromPoint(16, "red", "red", 10, 2);
    trigger = 1;
  }

  // 24 Backglass Flashlamp
  if (pd.pinState()->J126(8))
  {
    pd.adrLED1()->explosion(16, "red", 32);
    trigger = 1;
  }

  // 25 Target Flashlamps
  // extended WPC with extra 4-pin plug
  if (pd.pinState()->J126(13))
  {
    pd.adrLED1()->explosion(16, "red", 32);
    trigger = 1;
  }

  // 26 Left Popper Flashlamps
  // extended WPC with extra 4-pin plug
  if (pd.pinState()->J126(14))
  {
    //trigger = 1;
  }

  // 27 Right Popper
  // extended WPC with extra 4-pin plug
  if (pd.pinState()->J126(15))
  {
    //trigger = 1;
  }

  // 28 Flash Lamps Drop Target
  // extended WPC with extra 4-pin plug
  if (pd.pinState()->J126(16))
  {
    //trigger = 1;
  }

  // trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger)
  {
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.pinState()->reset();
    trigger = 0;
    attract_on = 0;
    timeLastEvent = millis();

    if(timeFirstEvent == 0)
    {
      timeFirstEvent = millis();
      randomSeed(timeFirstEvent);
    }
  }
  // end function checkPinStates
}

void attractMode()
{
  pd.adrLED1()->sparkle(attractColor, 20);
  pd.adrLED2()->sparkle(attractColor, 20);
  if (random(250) == 0)
  {
    if (attractColor == "red")
      attractColor = "blue";
    else
      attractColor = "red";
  }
}
