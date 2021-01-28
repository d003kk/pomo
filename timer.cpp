#define BOOST_CHRONO_HAS_CLOCK_STEADY 1

#include <boost/chrono.hpp>
#include <boost/asio.hpp>
#include <boost/asio/system_timer.hpp>
#include <ctime>
#include <iostream>


using namespace boost::chrono;
using namespace std;

template< class Clock >
class timer
{
public:
  timer()
  : start( Clock::now() )
  , stopped(false)
  {}
  typename Clock::duration elapsed() const
  {
    return Clock::now() - start;
  }
  long int display() const
  {
    return round<boost::chrono::seconds>(elapsed() ).count();
  }
  void  reset()
  {
  	start = Clock::now();
  }
  void  stop()
  {
  	stopped = true; 
  }
  void  restart()
  {
  	stopped = false; 
  }
private:
  bool stopped;
  typename Clock::time_point start;
  typename Clock::time_point stopped_time;
};

enum{
	STOP=0,
	DISPLAY,
	RESTART,
	RESET
};


void do_stuff()
{

 timer<system_clock> t1;	
 int option = 0;
 while(1) {

	 cout<<"Options Stop, Display, Restart, Reset"<<endl;
	 cin>>option;
	 switch(option) {
		 case STOP:
			 t1.stop();
			 break;
		 case DISPLAY:
	 		cout<<t1.display()<<endl;
			break;
		 case RESTART:
			t1.restart();
			break;
		 case RESET:
			t1.reset();
			break;
	 };
 }


}
