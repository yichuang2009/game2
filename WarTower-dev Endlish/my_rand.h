#ifndef _MY_RAND_H_
#define _MY_RAND_H_
#include<fstream>
#include<mutex>
class MyRand{
	public:
		static void srand(short s){
			using namespace std;
			lock_guard<mutex> l(lock);
			seed=s;
		}
		static int rand(){
			using namespace std;
			lock_guard<mutex> l(lock);
			return ((seed=seed*214013L+2531011L)>>16)&0x7fff;
		}
	private:
		static int seed;
		static std::mutex lock;
};
#endif
