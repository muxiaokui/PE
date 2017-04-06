#ifndef DISK_H
#define DISK_H
#include <time.h>
#include <cstdlib>
#include "strType.h"
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <ctime>
//#include <vector>
#include <power.h>
#define MAXVOL 8333
#define MAXDISKNUM 40
using namespace std;

struct Cache{
	int now;
	vector<Pic>dis[MAXDISKNUM];

};
struct Hard{
	int vol;
	vector<Pic> p;
	Hard *l=NULL,*r=NULL;
	double xl,xr,yl,yr;
};

class Disk
{
	public:
		Disk();

		double findpic(Pic p);

		Power power;
		virtual ~Disk();
		Cache cachedisk;
		Hard area[MAXDISKNUM];
		double push(Pic pic);
		void CachetoDisk(int pot);
		double endpush();
		int nowdisk = 64;
	protected:
	private:
		int TYPE=0;//0 putong 1 1 2 1+2 3 1+2+3

};

#endif // DISK_H
