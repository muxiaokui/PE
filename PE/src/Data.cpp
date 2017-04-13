#include "Data.h"
#include "StrType.h"
Data::Data() {
	//ctor
	avg = true;
	srand(time(NULL));
	now=0;
}

Data::~Data() {
	//dtor
}

void Data::create_out() {

	int p = rand()%100;
			if(p<25){
				search.x = a[0][0]+rand()%18;
				search.y = a[0][1]+rand()%25;
			}
			else if(p<50){
				search.x = a[1][0]+rand()%18;
				search.y = a[1][1]+rand()%25;
			}
			else {
				search.x= rand()%360;
				search.y =rand()%50;
			}

	return ;
}


struct Queue{
			int id;
			int val;

		}que[MAXPICTURE];
bool cmp(const Queue a ,const Queue b){
	return a.val>b.val;
}


void Data::create_in() {
	this->produce = new Pic[MAXPICTURE];
	int now = 0;


	if (avg) {
		while (now != MAXPICTURE) {
			for (double i = 0; i < 360; i += 1.5) {
				for (double j = 0; j < 50; j += 3) {
					produce[now].x = i;
					produce[now++].y = j;
					if(now == MAXPICTURE)break;
				}
				if(now == MAXPICTURE)break;
			}
		}
	}
	else{


		for(int i=0;i<MAXPICTURE;i++){
			que[i].id= i;
			que[i].val =rand();
		}
		sort(que,que+MAXPICTURE,cmp);

		area[0] = rand()%40;
		area[1] = rand()%40;
		while(area[1] == area[0])area[1]=rand()%40;

		a[0][0] = (area[0]%20)*18;
		a[0][1] = (area[0]/20)*25;
		a[1][0] = (area[1]%20)*18;
		a[1][1] = (area[1]/20)*25;
		int x,y;
		for(int i=0;i<MAXPICTURE;i++){
			int p = rand()%100;
			if(p<25){
				x = a[0][0]+rand()%18;
				y = a[0][1]+rand()%25;
			}
			else if(p<50){
				x = a[1][0]+rand()%18;
				y = a[1][1]+rand()%25;
			}
			else {
				x= rand()%360;
				y =rand()%50;
			}
			produce[que[i].id].x = x;
			produce[que[i].id].y = y;
		}

	}


	return ;
}
void Data::out_to_file(){
	freopen("a.in","w",stdout);
	for(int i=0;i<MAXPICTURE;i++){
		cout<<produce[i].x<<" "<<produce[i].y<<endl;
	}
	return ;
}
void Data::filetoproduce(){
	freopen("avg.in","r",stdin);
	this->produce = new Pic[MAXPICTURE];
	for(int i=0;i<MAXPICTURE;i++){
		cin>>produce[i].x>>produce[i].y;
	}
	return ;

}
void Data::read_from_in(){
	search.x = produce[now].x;
	search.y = produce[now].y;
	now++;
	while(search.x == 360.0 || search.y == 50.0){
		search.x = produce[now].x;
		search.y = produce[now].y;
		now++;
	}
	return ;



}

