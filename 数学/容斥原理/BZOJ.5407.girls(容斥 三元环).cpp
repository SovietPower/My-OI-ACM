/*
24736kb	2884ms
$Description$
有n个点，其中有m条边连接两个点。每一个没有连边的三元组(i,j,k)(i<j<k)对答案的贡献为A*i+B*j+C*k，求所有无连边三元组的贡献和。
$Solution$
直接求无连边三元组依旧很难。考虑用所有方案去减，那 Ans=所有方案-至少有1条连边+至少有2条连边-有3条边（"至少"显然比较好做啊）。
对于所有方案，A,B,C可以分别统计，即枚举哪个是A/B/C，剩下的随便组合。
对于至少1条连边，可以枚举每个点及其出边($O(n+m)$)。因为连的双向边，所以对于i,to=link[i]，只在i<to时计算i作为A/A/B，to作为B/C/C时的值就行了。
对于至少2条连边，枚举两条边的公共端点(so得建无向图)，组合一下。不好求其它连边的和，所以算to的贡献。
对于三条连边，直接$O(m\sqrt{m})$枚举三元环。
*/
#include <set>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <iostream>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 250000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Vec std::vector<int>
#define Output printf("%I64u\n",ans)
typedef long long LL;
typedef unsigned long long ull;
const int N=2e5+5;

int m,dgr[N],Link[N];
ull n,A,B,C,sumA[N],sumB[N],sumC[N];
Vec vec[N];
std::set<int> s[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline ull readull()
{
	ull now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read()-1, m=read(), A=readull(), B=readull(), C=readull();//id:0~n
	for(int u,v; m--; )
		u=read(), v=read(), vec[u].push_back(v), vec[v].push_back(u), s[u].insert(v), s[v].insert(u);
	for(int i=0; i<=n; ++i) dgr[i]=vec[i].size(), std::sort(vec[i].begin(),vec[i].end());

	ull ans=0;
//All
	for(ull i=0; i<=n-2; ++i) ans+=A*i*((n-i)*(n-i-1)>>1);//All
	for(ull i=1; i<n; ++i) ans+=B*i*i*(n-i);
	for(ull i=2; i<=n; ++i) ans+=C*i*(i*(i-1)>>1);
//One & Two
	for(ull i=1; i<=n; ++i) sumA[i]=sumA[i-1]+i*A, sumB[i]=sumB[i-1]+i*B, sumC[i]=sumC[i-1]+i*C;
	for(ull i=0; i<=n; ++i)
	{
		const Vec &to=vec[i]; ull cnt0=0,cnt1=0;
		for(int j=0,len=to.size()-1; j<=len; ++j)
		{
			ull v=to[j];
			if(v<i) ++cnt0, ans+=A*v*(len-j)+B*v*j;//同下，无论i为B/C，v有len-j种可能为A。
			else//v>i
			{//要找一个位置使得i<to[x]<v，所以在v<i时再算v作为A/B的答案(写出三种可能就比较清楚了) 
				++cnt1;
				ans-=(A*i+B*v)*(n-v)+sumC[n]-sumC[v];
				ans-=(A*i+C*v)*(v-i-1)+sumB[v-1]-sumB[i];
				if(i) ans-=(B*i+C*v)*i+sumA[i-1];

				ans+=C*v*j+B*v*(len-j);//无论i作为A还是B，v就是有j种可能作为C(前j种任选一个都能确定i是A or B)。
			}
		}
		ans+=i*(A*(cnt1*(cnt1-1)>>1)+B*cnt0*cnt1+C*(cnt0*(cnt0-1)>>1));
		//上面只算了i作为两边端点时其它点的贡献，并没有算i的。(枚举别的枚举到i时也不是i作为要枚举的两边端点了)
	}
//Three
	for(int i=0,size=sqrt(m); i<=n; ++i)
	{
		const Vec &to=vec[i]; int len=to.size();
		for(int j=len-1; ~j; --j) Link[to[j]]=i;
		for(int j=len-1; ~j; --j)
			if(i<to[j])
			{
				int v=to[j];
				if(dgr[v]<=size)
				{
					for(int k=vec[v].size()-1; ~k; --k)
						if(v<vec[v][k]) ans-=A*i+B*v+C*vec[v][k];
						else break;
				}
				else
				{
					for(int k=len-1; ~k; --k)
						if(v<to[k])
							if(s[v].count(to[k])) ans-=A*i+B*v+C*to[k];
							else ;
						else break;
				}
			}
	}

	printf("%llu",ans);

	return 0;
}
