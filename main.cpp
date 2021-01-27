#include "timer.h"
#include<thread>
#include<iostream>
using namespace std;

void monkey()
{
	//cout<<"Monkey"<<endl;
	
}

int main()
{
	thread timer_thread(do_stuff);
	timer_thread.join();
	return 0;
}
