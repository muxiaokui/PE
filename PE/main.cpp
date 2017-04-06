#include <iostream>
#include <data.h>
#include <disk.h>
#include <iomanip>
using namespace std;

int main()
{
   // cout << "Hello world!" << endl;
  /*  Data data;
    Disk disk;
    data.create_in();
    //data.out_to_file();
    data.read_from_in();
    for(int i=0;i<MAXPICTURE;i++){

		disk.push(data.produce[i]);

    }
    disk.endpush();


	for(int i=0;i<MAXDISKNUM;i++){
		cout<<i<<"  "<<disk.area[i].vol<<" "<<disk.area[i].p.size()<<endl;
		if(disk.area[i].vol == 8333){
			cout<<i<<"l  "<<disk.area[i].l->vol<<endl;
			cout<<i<<"r  "<<disk.area[i].r->vol<<endl;
			if( disk.area[i].l->vol == 8333  ){


			cout<<i<<"ll  "<<disk.area[i].l->l->vol<<endl;
			cout<<i<<"lr  "<<disk.area[i].l->r->vol<<endl;

		}

		}
	}

	data.create_out();
	disk.findpic(data.search);*/

//1492992000
/*double oo = 1;
oo =oo*64*360;
oo = oo * 24*60*60*0.75;
  cout<<setiosflags(ios::fixed)<<oo<<endl;
  */
	Data data;
    Disk disk;
	data.filetoproduce();
	//freopen("ans10.out","w",stdout);

	for(int i=0;i<MAXPICTURE;i++){

		disk.push(data.produce[i]);


    }


    double first = disk.endpush();
    double second =0;
    cout<<"first stage: "<<setiosflags(ios::fixed)<<first<<endl;
    for(int i=0;i<MAXPICTURE;i++){
		data.read_from_in();
		second=disk.findpic(data.search);
		cout<<i+1<<"   "<<second<<endl;
    }


    return 0;
}
