#include "mbed.h"
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


int main() {
  wait_ms(3000);
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
