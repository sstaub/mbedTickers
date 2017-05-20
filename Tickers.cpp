/* Ticker library code is placed under the MIT license
 * Copyright (c) 2017 Stefan Staub
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

#include "Tickers.h"

Tickers::Tickers() {
	init(NULL, 0, 0);
	}

Tickers::Tickers(fptr callback, uint32_t interval, uint16_t repeats) {
	init(callback, interval, repeats);
	}

Tickers::~Tickers() {}

void Tickers::init(fptr callback, uint32_t interval, uint16_t repeats) {
	setInterval(interval);
	setRepeats(repeats);
	setCallback(callback);
	enabled = false;
	lastTime = 0;
	counter = 0;
	}

void Tickers::start() {
	if (getCallback() == NULL) return;
	lastTime = us_ticker_read();
	enabled = true;
	counter = 0;
	state = RUNNING;
	}

void Tickers::resume() {
	if (getCallback() == NULL) return;
	lastTime = us_ticker_read() - diffTime;
	if(state == STOPPED) counter = 0;
	enabled = true;
	state = RUNNING;
	}

void Tickers::stop() {
	enabled = false;
	counter = 0;
	state = STOPPED;
	}

void Tickers::pause() {
	diffTime = us_ticker_read() - lastTime;
	enabled = false;
	state = PAUSED;
	}

void Tickers::update() {
	if(tick()) call();
	}

bool Tickers::tick() {
	if(!enabled)	return false;
	if ((us_ticker_read() - lastTime) >= _interval) {
		lastTime = us_ticker_read();
		if(_repeats - counter == 1)
			{
			enabled = false;
			counter++;
			}
		else {
			counter++;
			}
		return true;
		}
	return false;
	}

void Tickers::setInterval(uint32_t interval) {
	_interval = interval * 1000;
	}

void Tickers::setCallback(fptr callback) {
	call = callback;
	}

void Tickers::setRepeats(uint16_t repeats) {
	_repeats = repeats;
	}

uint32_t Tickers::getElapsedTime() {
	//return millis() - lastTime;
	return us_ticker_read() - lastTime;
	}

status_t Tickers::getState() {
		return state;
		}

uint32_t Tickers::getInterval() {
	return _interval;
	}

fptr Tickers::getCallback() {
	return call;
	}

uint16_t Tickers::getRepeats() {
	return _repeats;
	}

uint16_t Tickers::getRepeatsCounter() {
	return counter;
	}
