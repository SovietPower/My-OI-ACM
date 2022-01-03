/*
1684ms	23800KB
$Description$
$q$�β�����ÿ�θ����������$(x,y)$����ʾ����һ����$(x,y)$����ɾ��һ����$(x,y)$����ѯ�ʣ�������Ҫ��ƽ���м�����ٸ��㣬����ʹ�õ�ǰ���е����$(0,0)-(x,y)$����ֱ�߶Գơ�
$q\leq2\times10^5,\ 1\leq x,y\leq 112904$��
$Solution$
���������$(0,0)-(x,y)$�Գƣ������ǵ�ԭ��ľ�����һ���ģ���λ��ͬһ��Բ�ϡ�
���Բµ���һ�������ǣ���ԭ��ΪԲ�Ļ�Բ�����������ϵĵ㲻��ܶࡣ������$x^2+y^2=r^2$����������$(x,y)$����ܶࡣ
����ÿ����һ����$i$��ö�ٺ�����һ��Բ�ϵĵ�$j$����$i,j$�ĶԳ���Ĵ�$-2$��$i$�Լ����Գ���Ĵ�$-1$��ɾ��һ����$i$���͸�$i,j$�ĶԳ���Ĵ�$+2$����$i$���Գ���Ĵ�$+1$��
����ѯ��ֱ��������ɡ�
*/
#include <map>
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5,M=113000;

std::set<pr> st[N];
std::map<LL,int> id;
std::map<int,int> Ans[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int Getid(LL d)
{
	static int Index=0;
	return id.count(d)?id[d]:id[d]=++Index;
}
void Calc(int x,int y,int &xn,int &yn)
{
	int g=std::__gcd(x,y);//g!=0
	xn=x/g, yn=y/g;
}

int main()
{
	for(int Q=read(),tot=0; Q--; )
	{
		int opt=read(),x=read(),y=read(),xn,yn;
		if(opt==1)
		{
			int p=Getid(1ll*x*x+1ll*y*y);
			for(std::set<pr>::iterator it=st[p].begin(); it!=st[p].end(); ++it)
				Calc((*it).first+x,(*it).second+y,xn,yn), Ans[xn][yn]+=2;
			st[p].insert(mp(x,y)), Calc(x,y,xn,yn), ++Ans[xn][yn], ++tot;
		}
		else if(opt==2)
		{
			int p=Getid(1ll*x*x+1ll*y*y); st[p].erase(mp(x,y));
			for(std::set<pr>::iterator it=st[p].begin(); it!=st[p].end(); ++it)
				Calc((*it).first+x,(*it).second+y,xn,yn), Ans[xn][yn]-=2;
			Calc(x,y,xn,yn), --Ans[xn][yn], --tot;
		}
		else Calc(x,y,xn,yn), printf("%d\n",tot-Ans[xn][yn]);
	}

	return 0;
}
