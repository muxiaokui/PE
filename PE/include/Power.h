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

		double waitsecond;
		double incost ;
		double askcost;
		double idle = 5.4;
		double standby = 0.75;
		double active = 8;
		double idle_standby =54;
		double standby_active = 300;
	protected:
	private:
};

#endif // POWER_H
