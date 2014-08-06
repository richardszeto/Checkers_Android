/** Class that holds a timer
  *
  * @author Richard Szeto
  *
  *
  */

#ifndef TIMER_H
#define TIMER_H

namespace CheckersSzeto
{
	class Timer
	{
	public:
		Timer();
		~Timer();
		void start();
		void stop();
		void reset();
		bool isRunning() const;
		unsigned long getTime() const;
		bool isOver(const unsigned long &milliseconds) const;

	private:
		bool resetted;
		bool running;
		unsigned long beg;
		unsigned long end;
	};
}

#endif