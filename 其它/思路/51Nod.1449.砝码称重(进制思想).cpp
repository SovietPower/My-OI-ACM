/*
首先将m表示成w进制 
如果是构成m，则看每一位上是否仅为1或0即可 
但这是一个天平 
所以如果m的w进制第i位为w-1，可以将i+1放在砝码盘，将m^i放在m那一侧 
将砝码盘看做构成它的元素，则如果i+1放在砝码盘了，相当于那一位加了1，第i位的w-1变为1了 
*/
#include<cstdio>
using namespace std;
const int N=100;

int w,m,cnt,bit[N];

int main()
{
	scanf("%d%d",&w,&m);
	while(m)//边分解边求即可 
	{
		if(!(m%w) || m%w==1)
			m/=w;
		else if(m%w==w-1)
			m=m/w+1;//i+1需要一个砝码，下一位加上1 
		else
		{
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}
/*----------90分------------ 
int main()
{
	scanf("%d%d",&w,&m);
	while(m) bit[++cnt]=m%w, m/=w;
	bool f=1;
	for(int i=1; i<=cnt && f; ++i)
		if(bit[i]==w-1)
		{
			if(use[i+1]) f=0;
			else use[i+1]=use[i]=1,++bit[i+1];//强行加1...
		}
		else if(bit[i]==1)
		{
			if(use[i]) f=0;
			use[i]=1;
		}
		else if(bit[i]) f=0;
	printf(f?"YES":"NO");

	return 0;
}*/
