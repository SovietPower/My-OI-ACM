/*
30ms	0KB
首先可以$Query$一次得到$a,b$的大小关系（$c=d=0$）。
然后发现我们是可以逐位比较出$a,b$在这每位上的大小关系的。
最后还剩下$a,b$相等的位需要再判断是$0$还是$1$，$a,b$分别异或一个$1,0$就可以了（假如都是$0,0$，那异或之后$1,0$是$a>b$；如果都是$1,1$，异或之后就是$0,1$，$a<b$）。
询问次数$61$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define Flush() fflush(stdout)
#define BIT 29
typedef long long LL;
const int N=35;

int vis[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int Query(int c,int d)
{
	printf("? %d %d\n",c,d), Flush();
	return read();
}
void Equal(int &a,int &b,int c,int d)
{
	for(int i=BIT; ~i; --i)
		if(!vis[i])
			if(Query(c|(1<<i),d)==-1) a|=1<<i, b|=1<<i;
}
void Solve(int &a,int &b)
{//f=1:a>b
	a=0,b=0;
	int c=0,d=0,res=Query(0,0),f=res==1;
	if(!res) {Equal(a,b,0,0); return;}
	for(int i=BIT; ~i; --i)
	{
		res=Query(c|(1<<i),d|(1<<i));
		if((f&&res==-1)||(!f&&res==1))
		{
			vis[i]=1;
			if(f) c|=1<<i, a|=1<<i;
			else d|=1<<i, b|=1<<i;
			if(!(res=Query(c,d))) {Equal(a,b,c,d); return;}
			f=res==1;
		}
	}
	Equal(a,b,c,d);
}

int main()
{
	int a,b; Solve(a,b);
	printf("! %d %d\n",a,b), Flush();

	return 0;
}
