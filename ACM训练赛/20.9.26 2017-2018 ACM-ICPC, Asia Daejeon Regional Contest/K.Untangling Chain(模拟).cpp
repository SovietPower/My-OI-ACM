/*
30ms	100KB
���Է���������㲻��תȦ���ɡ�
תȦ�Ļ���Ҫ�ǵ�ǰ�߹��ģ������ϡ����¡����ϡ�����λ�ã��´���ʱԽ������λ�ü��ɡ�
�߳�����������������һ��ֱ�ߣ�ǡ����Ҫ��n����
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=10005;

struct Opt
{
	int len,way;
}opt[N];
struct Point
{
	int x,y;
};

inline int read()
{
	int now=0,f=1; char c=gc();
	for(; !isdigit(c); c=='-'&&(f=-1),c=gc());
	for(; isdigit(c); now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) opt[i]=(Opt){read(),read()};
	int x=0,y=0,now=2;//now:���� 0123:�������� 
	Point ul=(Point){0,0},ur=ul,dl=ul,dr=ul;
	for(int i=1; i<=n; ++i)
	{
		switch(now)
		{
			case 0:
			{
				int d=std::abs(x-std::min(ul.x,dl.x))+1;
				x-=d, printf("%d ",d);
				break;
			}
			case 1:
			{
				int d=std::abs(std::max(ul.y,ur.y)-y)+1;
				y+=d, printf("%d ",d);
				break;
			}
			case 2:
			{
				int d=std::abs(std::max(ur.x,dr.x)-x)+1;
				x+=d, printf("%d ",d);
				break;
			}
			case 3:
			{
				int d=std::abs(y-std::min(dl.y,dr.y))+1;
				y-=d, printf("%d ",d);
				break;
			}
		}
		if(x<=ul.x && y>=ul.y) ul=(Point){x,y};
		if(x>=ur.x && y>=ur.y) ur=(Point){x,y};
		if(x<=dl.x && y<=dl.y) dl=(Point){x,y};
		if(x>=dr.x && y<=dr.y) dr=(Point){x,y};
		now=((now-opt[i].way)%4+4)%4;
	}
	

	return 0;
}
