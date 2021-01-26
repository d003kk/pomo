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
  typename Clock::time_point start;
public:
  timer() : start( Clock::now() ) {}
  typename Clock::duration elapsed() const
  {
    return Clock::now() - start;
  }
  long int seconds() const
  {
    return round<boost::chrono::seconds>(elapsed() ).count();
  }
};


void do_stuff()
{

 timer<system_clock> t1;	
 while(1) {

	 cout<<t1.seconds()<<endl;
	 
 }


}
