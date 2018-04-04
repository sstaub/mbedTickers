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

#include "Tickers.h"

Tickers::Tickers(fptr callback, uint32_t timer, uint16_t repeats, interval_t mode) {
	if (mode == MILLIS) timer *= 1000;
	this->mode = mode;
	this->timer = timer;
	this->repeats = repeats;
	this->callback = callback;
	enabled = false;
	lastTime = 0;
	counts = 0;
	}

Tickers::~Tickers() {}

void Tickers::start() {
	if (callback == NULL) return;
	lastTime = us_ticker_read();
	enabled = true;
	counts = 0;
	status = RUNNING;
	}

void Tickers::resume() {
	if (callback == NULL) return;
	lastTime = us_ticker_read() - diffTime;
	if (status == STOPPED) counts = 0;
	enabled = true;
	status = RUNNING;
	}

void Tickers::stop() {
	enabled = false;
	counts = 0;
	status = STOPPED;
	}

void Tickers::pause() {
	diffTime = us_ticker_read() - lastTime;
	enabled = false;
	status = PAUSED;
	}

void Tickers::update() {
	if(tick()) callback();
	}

void Tickers::interval(uint32_t timer) {
	if (mode == MILLIS) timer *= 1000;
	this->timer = timer;
	}

uint32_t Tickers::elapsed() {
	return us_ticker_read() - lastTime;
	}

status_t Tickers::state() {
	return status;
	}

uint32_t Tickers::counter() {
	return counts;
	}

bool Tickers::tick() {
	if (!enabled)	return false;
	if ((us_ticker_read() - lastTime) >= timer) {
		lastTime = us_ticker_read();
		if (repeats - counts == 1) enabled = false;
		counts++;	
		return true;
		}
	return false;
	}