# mbed Tickers Library v2

The **mbed Tickers Library** allows you to create easily Ticker callbacks, which can call a function in a predetermined interval. You can change the number of repeats of the callbacks, if repeats is 0 the ticker runs in endless mode. Works like a "thread", where a secondary function will run when necessary. The library use no interupts of the hardware timers and works with the ```us_ticker_read()``` function. You are not (really) limited in the number of Tickers.
The internal resolution is microseconds, this works with intervals up to 70 minutes. The library works similar as the Arduino Ticker library https://github.com/sstaub/Ticker and is different to the mbed Ticker / Timer libraries.

## New in v2

- v2 simplified the API
- you have to declare all parameters in the constructor 
- the set and get function are deleted or replaced
- the resolution of the interval can changed into micro seconds
- added interval function to change time on fly

## Installation

1. "Download": https://github.com/sstaub/mbedTickers/archive/master.zip the Master branch from GitHub.
2. Unzip and modify the folder name to "mbedTickers"
3. Move the modified folder in your Library folder (e.g. in your `lib` folder inside PlatformIO).


## How to use

First, include the TickersObject to your project:

```cpp
#include "mbed.h"
#include "Tickers.h"

uint8_t countdown = 10;
uint16_t counterUS;

void printMessage();
void printCounter();
void printCountdown();
void blink();
void printCountUS();

DigitalOut  myled(LED1);

Tickers timer1(printMessage, 0, 1); once, immediately
Tickers timer2(printCounter, 1000); every second
Tickers timer3(printCountdown, 1000, countdown); every second, 10 times
Tickers timer4(blink, 500); every 500ms
Tickers timer5(printCountUS, 100, 0, MICROS); // interval 100us


int main() {
  timer1.start();
  timer2.start();
  timer3.start();
  timer4.start();
  timer5.start();
  while(1) {
    timer1.update();
    timer2.update();
    timer3.update();
    timer4.update();
    timer5.update();
    if (timer4.counter() == 20) timer4.interval(200);
    if (timer4.counter() == 80) timer4.interval(1000);
    }
  }

void printCounter() {
  printf("Counter %u\n", timer2.counter());
  }

void printCountdown() {
  printf("Countdowm %u\n", countdown - timer3.counter());
  }

void printMessage() {
  printf("Hello! \n");
  }

void blink() {
  myled=!myled;
  }

void printCountUS() {
  counterUS++;  
  if (counterUS == 10000) {
    printf("10000 * 100us \n");
    counterUS = 0;
    }
  }
```

## Documentation

### States

```cpp
enum status_t {
  STOPPED,
  RUNNING,
  PAUSED
  };
```

### Constructors

```cpp
Tickers::Tickers(fptr callback, uint32_t timer, uint16_t repeats, interval_t mode)
```

Creates a Ticker object

- **callback** for the function name you want to call
- **timer** set the interval time in ms or us depending from mode
- **repeats** set the number of repeats the callback should executed, 0 is endless (default)
- **mode** set the interval resolution to MILLIS (default) or MICROS

**Example**

```cpp
Tickers timer(blink, 1000); // calls function blink() every second
```

### Destructor

```cpp
Tickers::~Tickers()
```
Destructor for Ticker object

## Class Functions

### Ticker Start

```cpp
void Tickers::start()
```

Start the Ticker. Will count the interval from the moment that you start it. If it is paused, it will restart the Ticker.

**Example**

```cpp
timer.start();
```

### Ticker Resume

```cpp
void Tickers::resume()
```

Resume the Ticker. If not started, it will start it. If paused, it will resume it. For example, in a Ticker of 5 seconds, if it was paused in 3 seconds, the resume in continue in 3 seconds. Start will set passed time to 0 and restart until get 5 seconds.

**Example**

```cpp
timer.resume();
```

### Ticker Pause

```cpp
void Tickers::pause()
```

Pause the Ticker, so you can resume it.

**Example**

```cpp
timer.pause();
```

### Ticker Stop

```cpp
void Tickers::stop()
```

Stop the Ticker.

**Example**

```cpp
timer.stop();
```

### Ticker Update

```cpp
void Tickers::update()
```

Must to be called in the main while() loop, it will check the Ticker, and if necessary, will run the callback

**Example**

```cpp
while(1) {
  timer.update();
1.   }
```

### Ticker Interval Time

```cpp
void Tickers::interval(uint32_t timer)
```

Changes the interval time of the Ticker. Depending from the mode it can millis or micro seconds.

- **timer** set the interval time in ms or us depending from mode


**Example**

```cpp
timer.interval(500); // new interval time
```

### Ticker State

```cpp
status_t Tickers::state()
```

Returns the state of the Ticker.

**Example**

```cpp
status_t status;
status = timer.state();
```

### Ticker Elapsed Time

```cpp
uint32_t Tickers::elapsed()
```

Returns the time passed since the last tick in us.

**Example**

```cpp
uint32_t elapse;
elapse = timer.elapsed();
```

### Ticker Counter

```cpp
uint32_t Tickers::counter()
```

Get the number of executed callbacks.

**Example**

```cpp
uint32_t count;
count = timer.counter();
```