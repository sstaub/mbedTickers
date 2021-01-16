/* Ticker library code is placed under the MIT license
 * Copyright (c) 2018 Stefan Staub
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef TICKERS_H
#define TICKERS_H

#include "mbed.h"

/** Ticker status
 *
 * @param STOPPED default, ticker is stopped
 * @param RUNNING ticker is running
 * @param PAUSED ticker is paused
 *
 */
enum status_t {
	STOPPED,
	RUNNING,
	PAUSED
	};

/** Ticker interval mode
 *
 * @param MILLIS default, ticker is stopped
 * @param MICROS ticker is running

 *
 */
enum interval_t {
	MILLIS,
	MICROS
	};

typedef void (*fptr)();

class Tickers {

public:

	/** create a Ticker object
	 *
	 * @param callback the name of the function to call
	 * @param ms interval length
	 * @param repeats default 0 -> endless, repeats > 0 -> number of repeats
	 * @param mode interval resolution MILLIS (default) or MICROS
	 *
	 */
	Tickers(fptr callback, uint32_t timer, uint16_t repeats = 0, interval_t mode = MILLIS);

	/** destructor for the Ticker object
	 *
	 */
	~Tickers();

	/** start the ticker
	 *
	 */
	void start();

	/** resume the ticker. If not started, it will start it.
	 *
	 */
	void resume();

	/** pause the ticker
	 *
	 */
	void pause();

	/** stops the ticker
	 *
	 */
	void stop();

	/** must to be called in the main loop(), it will check the Ticker, and if necessary, will run the callback
	 *
	 */
	void update();

	/**
	 * @brief set the interval timer
	 * 
	 * @param timer interval length in ms or us
	 */
	void interval(uint32_t timer);

	/** actual ellapsed time
	 *
	 * @returns the elapsed time after the last tick in us
	 *
	 */
	uint32_t elapsed();

	/** get the state of the ticker
	 *
	 * @returns the state of the ticker: STOPPED, RUNNING or PAUSED
	 */
	status_t state();

	/** get the numbers of executed repeats
	 *
	 * @returns the number of executed repeats
	 *
	 */
	uint32_t counter();


private:
	bool tick();
	bool enabled;
	uint8_t mode;
	uint32_t timer;
	uint16_t repeats;
	uint32_t counts;
	status_t status;
	fptr callback;
	uint32_t lastTime;
	uint32_t diffTime;
};

#endif
