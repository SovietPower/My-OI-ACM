/*
$Description$
在一个$n*n$的二维平面中有两个不相交的整点矩形，每次可以询问两个矩形有几个完全在你给出的一个矩形中。200次询问内确定两个矩形坐标。
$Solution$
容易想到二分。整个矩形好像不好判断？那就每次二分判断矩形两个点的横纵坐标。次数为 8*26<200。
前四次二分什么都不知道，可以确定出一个矩形的位置。然后第二个矩形就可以随便二分下了。
*/
#include <cstdio> 
#include <cctype>
#define gc() getchar()

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Query(int a,int b,int c,int d)
{
	printf("? %d %d %d %d\n",a,b,c,d);
	fflush(stdout);
	return read();
}

int main()
{
	int n=read();
	int x1,x2,y1,y2,x3,x4,y3,y4;
	int l=1, r=n, mid;
	while(l<=r){//x2
		if(Query(1,1,mid=l+r>>1,n)) x2=mid,r=mid-1;
		else l=mid+1;
	}
	l=1, r=n;
	while(l<=r){//y2
		if(Query(1,1,x2,mid=l+r>>1)) y2=mid,r=mid-1;
		else l=mid+1;
	}
	l=1, r=x2;
	while(l<=r){//x1
		if(Query(mid=l+r>>1,1,x2,y2)) x1=mid,l=mid+1;
		else r=mid-1;
	}
	l=1, r=y2;
	while(l<=r){//y1
		if(Query(x1,mid=l+r>>1,x2,y2)) y1=mid,l=mid+1;
		else r=mid-1;
	}
	l=1, r=n;
	while(l<=r){
		if(Query(1,1,mid=l+r>>1,n)-(x1>=1&&y1>=1&&x2<=mid&&y2<=n)) x4=mid,r=mid-1;
		else l=mid+1;
	}
	l=1, r=n;
	while(l<=r){
		if(Query(1,1,x4,mid=l+r>>1)-(x1>=1&&y1>=1&&x2<=x4&&y2<=mid)) y4=mid,r=mid-1;
		else l=mid+1;
	}
	l=1, r=x4;
	while(l<=r){
		if(Query(mid=l+r>>1,1,x4,y4)-(x1>=mid&&y1>=1&&x2<=x4&&y2<=y4)) x3=mid,l=mid+1;
		else r=mid-1;
	}
	l=1, r=y4;
	while(l<=r){
		if(Query(x3,mid=l+r>>1,x4,y4)-(x1>=x3&&y1>=mid&&x2<=x4&&y2<=y4)) y3=mid,l=mid+1;
		else r=mid-1;
	}
	printf("! %d %d %d %d %d %d %d %d\n",x1,y1,x2,y2,x3,y3,x4,y4);
	fflush(stdout);

	return 0;
}
