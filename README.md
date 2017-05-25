# mbed Tickers Library

The **mbed Tickers Library** allows you to create easily Ticker callbacks, which can call a function in a predetermined interval. You can change the number of repeats of the callbacks, if repeats is 0 the ticker runs in endless mode. Works like a "thread", where a secondary function will run when necessary. The library use no interupts of the hardware timers and works with the ```us_ticker_read()``` function. You are not (really) limited in the number of Tickers.
The internal resolution is microseconds, this works with intervals up to 70 minutes. The library works similar as the Arduino Ticker library https://github.com/sstaub/Ticker and is different to the mbed Ticker / Timer libraries.

## Installation

1. "Download": https://github.com/sstaub/mbedTickers/archive/master.zip the Master branch from GitHub.
2. Unzip and modify the folder name to "mbedTickers"
3. Move the modified folder in your Library folder (e.g. in your `lib` folder inside PlatformIO).


## How to use

First, include the TickersObject to your project:

```
#include "Tickers.h"
```

Now, you can create a new object in setup():

```
Tickers tickerObject;
tickerObject.setInterval(1000);
tickerObject.setCallback(callbackFunction);
tickerObject.start(); //start the ticker.
```

In your loop(), add:

```
tickerObject.update(); //it will check the Ticker
and if necessary, it will run the callback function.
```


## IMPORTANT
If you use wait_ms(), the Ticker will be ignored! You cannot use delay() command with the TimerObject. Instead of using delay, you can use the Ticker itself. For example, if you need that your loop run twice per second, just create a Ticker with 500 ms. It will have the same result that delay(500), but your code will be always state.

## Example

Complete example. Here we created three timers, you can run it and test the result in the Serial monitor and the on board LED.

```
#include "Tickers.h"

void printMessage();
void printCounter();
void printCountdown();
void blink();

DigitalOut  myled(LED1);

Tickers timer1(printMessage, 0, 1);
Tickers timer2(printCounter, 1000);
Tickers timer3(printCountdown, 1000, 5);
Tickers timer4;

void main() {
  wait_ms(2000);
  timer4.setCallback(blink);
  timer4.setInterval(500);
  timer1.start();
  timer2.start();
  timer3.start();
  timer4.start();

  while(1) {
    timer1.update();
    timer2.update();
    timer3.update();
    timer4.update();
    }
  }

  void printCounter() {
    printf("Counter %u\n", timer2.getRepeatsCounter());
    }

  void printCountdown() {
    printf("Countdowm %u\n", timer3.getRepeats() - timer3.getRepeatsCounter());
    }

  void printMessage() {
    printf("Hello! \n");
    }

  void blink() {
    myled=!myled;
    }
```

## Documentation

### States
STOPPED / RUNNING / PAUSED

### Constructors / Destructor
**Tickers()**<br>
Creates a Ticker object without parameters.

**Tickers(fptr callback, uint32_t interval, uint16_t repeats = 0)**<br>
Creates a Ticker object
- parameter callback for the function name you want to call
- parameter interval sets the interval time in ms
- parameter repeats sets the number of repeats the callback should executed, 0 is endless

**~Tickers()**<br>
Destructor for Ticker object

### Functions

**void start()**<br>
Start the Ticker. Will count the interval from the moment that you start it. If it is paused, it will restart the Ticker.

**void resume()**<br>
Resume the Ticker. If not started, it will start it. If paused, it will resume it. For example, in a Ticker of 5 seconds, if it was paused in 3 seconds, the resume in continue in 3 seconds. Start will set passed time to 0 and restart until get 5 seconds.

**void pause()**<br>
Pause the Ticker, so you can resume it.

**void stop()**<br>
Stop the Ticker.

**void update()**<br>
Must to be called in the loop(), it will check the Ticker, and if necessary, will run the callback

**void setInterval(uint32_t interval)**<br>
Set callback interval in ms.

**void setCallback(ftpr callback)**<br>
Set function callback.

**void setRepeats(uint16_t repeats)**<br>
Set the number of the repeats, 0 (standard) is endless mode.

**status_t getState()**<br>
Returns the state of the Ticker.

**uint32_t getElapsedTime()**<br>
Returns the time passed since the last tick.

**uint32_t getInterval()**<br>
Get the interval of the Ticker.

**fptr getCallback()**<br>
Get the callback of the Ticker.

**uint16_t getRepeats()**<br>
Get the number of the repeats.

**uint16_t getRepeatsCounter()**<br>
Get the number of executed callbacks.
