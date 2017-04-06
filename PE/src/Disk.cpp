#include "Disk.h"

Disk::Disk() {
	//ctor
	for (int i = 0; i < MAXDISKNUM; i++) {
		cachedisk.dis[i].clear();
		cachedisk.now = 0;
	}


	if (TYPE != 3) {
		for (int i = 0; i < MAXDISKNUM; i++) {
			area[i].l = NULL;
			area[i].r = NULL;
			area[i].p.clear();
			area[i].vol = 0;
			area[i].xl = (i % 20) * 18.0;
			area[i].xr = (i % 20) * 18.0 + 18.0;
			area[i].yl = ((int)(i / 20)) * 25.0;
			area[i].yr = ((int)(i / 20)) * 25.0 + 25.0;
		}
	}

	else {

		for (int i = 0; i < MAXDISKNUM; i++) {
			area[i].l = NULL;
			area[i].r = NULL;
			area[i].p.clear();
			area[i].vol = 0;
			area[i].xl = (i % 20) * 18.0;
			area[i].xr = (i % 20) * 18.0 + 18.0 + 1.5;
			area[i].yl = ((int)(i / 20)) * 25.0;
			area[i].yr = ((int)(i / 20)) * 25.0 + 25.0 + 3;
		}
	}


}

Disk::~Disk() {
	//dtor
}

void Disk::CachetoDisk(int pot) {
	if (TYPE == 1) {
		for (int i = 0; i < cachedisk.dis[pot].size(); i++) {
			Hard *pi = area + pot;

			while (pi->vol == MAXVOL) {
				pi = pi->l;
			}

			pi->p.push_back(cachedisk.dis[pot][i]);
			pi->vol++;

			if (pi->vol == MAXVOL) {
				//nowdisk++;
				pi->l = new Hard;
				pi->l->l = NULL;
				pi->l->r = NULL;
				pi->l->p.clear();
				pi->l->vol = 0;
			}
		}
	} else {

		for (int i = 0; i < cachedisk.dis[pot].size(); i++) {
			Hard * pi = area + pot;

			while (pi->vol == MAXVOL) {
				if (cachedisk.dis[pot][i].x >= pi->l->xl && cachedisk.dis[pot][i].x <= pi->l->xr && cachedisk.dis[pot][i].y >= pi->l->yl && cachedisk.dis[pot][i].y <= pi->l->yr) {
					pi = pi->l;
				} else {
					pi = pi->r;
				}
			}

			pi->p.push_back(cachedisk.dis[pot][i]);
			pi->vol++;

			if (pi->vol == MAXVOL) {
				pi->l = new Hard;
				pi->r = new Hard;
				pi->l->p.clear();
				pi->r->p.clear();
				pi->l->vol = 0;
				pi->r->vol = 0;
				pi->l->l = NULL;
				pi->l->r = NULL;
				pi->r->l = NULL;
				pi->r->l = NULL;
				//nowdisk += 2;

				if (pi->xr - pi->xl >= (pi->yr - pi->yl) / 2) {
					pi->l->xl = pi->xl;
					pi->l->xr = (pi->xl + pi->xr) / 2;
					pi->r->xl = (pi->xl + pi->xr) / 2;
					pi->r->xr = pi->xr;

					pi->l->yl = pi->yl;
					pi->l->yr = pi->yr;
					pi->r->yl = pi->yl;
					pi->r->yr = pi->yr;

				} else {
					pi->l->xl = pi->xl;
					pi->l->xr = pi->xr;
					pi->r->xl = pi->xl;
					pi->r->xr = pi->xr;
					pi->l->yl = pi->yl;
					pi->l->yr = (pi->yl + pi->yr) / 2;
					pi->r->yl = (pi->yl + pi->yr) / 2;
					pi->r->yr = pi->yr;
				}
			}
		}
	}
}


double Disk::push(Pic pic) {
	if (TYPE == 0) {
		for (int i = 0; i < MAXDISKNUM; i++) {
			if (area[i].vol != MAXVOL) {
				area[i].p.push_back(pic);
				area[i].vol++;

                power.incost += power.waitsecond*(nowdisk-1)*power.standby;
                power.incost += power.waitsecond*1*power.idle;

                power.incost += (nowdisk-1)*power.standby;
                power.incost += 1*power.active;

				break;
				//cal()
			}
		}
	} else {

		//int ii = pic.x / 18 + ((int)pic.y / 25) * 20;
		for (int i = 0; i < MAXDISKNUM; i++) {
			if (pic.x >= area[i].xl && pic.x <= area[i].xr && pic.y >= area[i].yl && pic.y <= area[i].yr) {
				cachedisk.dis[i].push_back(pic);
				cachedisk.now++;
			}
		}

        power.incost += power.waitsecond*(nowdisk)*power.standby;
		power.incost += power.waitsecond*1*power.idle;

		power.incost += nowdisk*power.standby;
        power.incost += 1*power.active;

		//cout<<cachedisk.now<<endl;
		if (cachedisk.now >= MAXVOL * 2) {
			int ma = 0 , man = 0;

			for (int i = 0; i < MAXDISKNUM; i++) {
				if (cachedisk.dis[i].size() > ma) {
					ma = cachedisk.dis[i].size();
					man = i;
				}
			}

			//cout << ma << "  " << man << endl;
			cachedisk.now -= ma;
			CachetoDisk(man);
			cachedisk.dis[man].clear();

			power.incost+=2*ma*power.active;
			power.incost-=ma*(power.idle+power.standby);
			power.incost+=power.standby_active+power.idle_standby;

		}


	}

	return power.incost;

}
double Disk::endpush() {
	if(TYPE == 0){
		for(int i=0;i<MAXDISKNUM;i++){
			if(area[i].vol!=0){
				power.incost+=power.idle_standby;
				power.incost+=power.standby_active;
			}
		}

	}

	if (TYPE != 0) {
		for (int i = 0; i < MAXDISKNUM; i++) {
			CachetoDisk(i);
			power.incost+=2*area[i].vol*power.active;
			power.incost-=area[i].vol*(power.idle+power.standby);
			power.incost+=power.standby_active+power.idle_standby;

		}
		power.incost+=(nowdisk-MAXDISKNUM)*(power.idle_standby+power.standby_active);

	}
	return power.incost;

}
double disk_pic(Hard * h, Pic p) {
	bool open = false;
	int ret = 0;
	double ans =0 ;
	for (int i = 0; i < h->vol; i++) {
		if (h->p[i].x <= p.x && h->p[i].x + 1.5 >= p.x &&  h->p[i].y <= p.y && h->p[i].y + 3.0 >= p.y) {
			ret++;
		}
	}

	if (ret != 0) {
		open = true;
	}

	if (h->l != NULL) {
		ans+=disk_pic(h->l, p);
	}

	if (h->r != NULL) {
		ans+=disk_pic(h->r, p);
	}

	//if (ret != 0) {
	//	cout<<h->xl<<"  "<<h->xr<<"  "<<h->yl<<"  "<<h->yr<<"  "<<ret<<endl;
	//}

	if(open)ans+=54+300;//need change
	ans+=ret*8.0;//need change

	return ans;
}


double Disk::findpic(Pic p) {
    double po=0;
	for (int i = 0; i < MAXDISKNUM; i++) {
		po+=disk_pic(area + i, p);
		if(TYPE==3 && po!=0 ){
			break;
		}
	}
	power.askcost+=po;
	return power.askcost;
}


