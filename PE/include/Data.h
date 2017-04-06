#ifndef DATA_H
#define DATA_H
#include "StrType.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <ctime>
#define MAXPICTURE 216000
using namespace std;
class Data
{
	public:
		Data();
		virtual ~Data();

		void create_in();//产生数据
		void create_out();//制造一次询问
		void out_to_file();//数据输出到文件
		void read_from_in();//从文件读取数
		void read_out();
		void filetoproduce();
		Pic *produce;
		Pic search;
		int now;
		int area[2];
		int a[2][2];
	protected:
	private:

		bool avg;




};

#endif // DATA_H
