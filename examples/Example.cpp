#include "mbed.h"
#include "Tickers.h"

uint8_t countdown = 5;
uint16_t counterUS;

void printMessage();
void printCounter();
void printCountdown();
void blink();
void printCountUS();

DigitalOut  myled(LED1);

Tickers timer1(printMessage, 0, 1);
Tickers timer2(printCounter, 1000);
Tickers timer3(printCountdown, 1000, countdown);
Tickers timer4(blink, 500);
Tickers timer5(printCountUS, 100, 0, MICROS);


int main() {
  wait_ms(2000);
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
    if(timer4.counter() == 20) timer4.interval(200);
    if(timer4.counter() == 80) timer4.interval(1000);
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
