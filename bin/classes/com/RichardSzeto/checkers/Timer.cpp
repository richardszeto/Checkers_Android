/** Class that holds a timer
  *
  * @author Richard Szeto
  *
  *
  */

#include <iostream>
#include <ctime>
#include "Timer.h"

namespace CheckersSzeto
{
	Timer::Timer()
	{
		resetted = true;
		running = false;
		beg = 0;
		end = 0;
	}

	Timer::~Timer()
	{
		// deliberately left empty
	}

	void Timer::start()
	{
		if(!running)
		{
			if(resetted)
			{
				beg = static_cast<unsigned long>(clock());
			}
			else
			{
				beg = beg - end - static_cast<unsigned long>(clock());
			}

			running = true;

			resetted = true;
		}
	}

	void Timer::stop()
	{
		if(running)
		{
			end = static_cast<unsigned long>(clock());

			running = false;
		}
	}

	void Timer::reset()
	{
		bool wereRunning = running;

		if(wereRunning)
		{
			stop();
		}

		resetted = true;

		beg = 0;

		end = 0;

		if(wereRunning)
		{
			start();
		}
	}

	bool Timer::isRunning() const
	{
		return running;
	}

	unsigned long Timer::getTime() const
	{
		if(running)
		{
			return ((static_cast<unsigned long>(clock()) - beg) / static_cast<double>(CLOCKS_PER_SEC) * 1000);
		}
		else
		{
			return ((end - beg) / static_cast<double>(CLOCKS_PER_SEC) * 1000);
		}
	}

	bool Timer::isOver(const unsigned long &milliseconds) const
	{
		return milliseconds <= getTime();
	}
}