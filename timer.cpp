#define BOOST_CHRONO_HAS_CLOCK_STEADY 1

#include <boost/chrono.hpp>
#include <boost/asio.hpp>
#include <boost/asio/system_timer.hpp>
#include <ctime>
#include <iostream>

// A custom implementation of the Clock concept from the standard C++ library.
struct time_t_clock
{
  // The duration type.
  typedef boost::chrono::steady_clock::duration duration;

  // The duration's underlying arithmetic representation.
  typedef duration::rep rep;

  // The ratio representing the duration's tick period.
  typedef duration::period period;

  // An absolute time point represented using the clock.
  typedef boost::chrono::time_point<time_t_clock> time_point;

  // The clock is not monotonically increasing.
  static const bool is_steady = false;

  // Get the current time.
  static time_point now()
  {
    return time_point() + boost::chrono::seconds(std::time(0));
  }
};

// The boost::basic_waitable_timer template accepts an optional WaitTraits
// template parameter. The underlying time_t clock has one-second granularity,
// so these traits may be customised to reduce the latency between the clock
// ticking over and a wait operation's completion. When the timeout is near
// (less than one second away) we poll the clock more frequently to detect the
// time change closer to when it occurs. The user can select the appropriate
// trade off between accuracy and the increased CPU cost of polling. In extreme
// cases, a zero duration may be returned to make the timers as accurate as
// possible, albeit with 100% CPU usage.
struct time_t_wait_traits
{
  // Determine how long until the clock should be next polled to determine
  // whether the duration has elapsed.
  static time_t_clock::duration to_wait_duration(
      const time_t_clock::duration& d)
  {
    if (d > boost::chrono::seconds(1))
      return d - boost::chrono::seconds(1);
    else if (d > boost::chrono::seconds(0))
      return boost::chrono::milliseconds(10);
    else
      return boost::chrono::seconds(0);
  }

  // Determine how long until the clock should be next polled to determine
  // whether the absoluate time has been reached.
  static time_t_clock::duration to_wait_duration(
      const time_t_clock::time_point& t)
  {
    return to_wait_duration(t - time_t_clock::now());
  }
};

typedef boost::asio::basic_waitable_timer<
  time_t_clock, time_t_wait_traits> time_t_timer;

void handle_timeout(const boost::system::error_code&)
{
  std::cout << "handle_timeout\n";
}

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
  try
  {
    time_t_clock::duration zero_duration();
    boost::asio::io_service io_service;

    time_t_timer timer(io_service);

    timer.expires_from_now(time_t_clock::duration(5));
    std::cout << "Starting synchronous wait\n";
    timer.wait();
    std::cout << "Finished synchronous wait\n";
	    

    timer.expires_from_now(time_t_clock::duration(5));
    std::cout << "Starting asynchronous wait\n";
    timer.async_wait(&handle_timeout);
    while(1)
	std::cout<<time_t_wait_traits::to_wait_duration(timer.expires_from_now())<<std::endl;
    io_service.run();
    std::cout << "Finished asynchronous wait\n";
  }
  catch (std::exception& e)
  {
    std::cout << "Exception: " << e.what() << "\n";
  }


}
