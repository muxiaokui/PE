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

		void create_in();//��������
		void create_out();//����һ��ѯ��
		void out_to_file();//����������ļ�
		void read_from_in();//���ļ���ȡ��
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
