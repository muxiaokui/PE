#ifndef POWER_H
#define POWER_H

#include <vector>
#include <algorithm>
using namespace std;
class Power
{
	public:
		Power();
		virtual ~Power();

		double waitsecond = 144;
		double incost =0;
		double askcost =0 ;
		double idle = 5.4;
		double standby = 0.75;
		double active = 8;
		double idle_standby =54;
		double standby_active = 300;
		double idletoclose = 30*0.75;
	protected:
	private:
};

#endif // POWER_H
