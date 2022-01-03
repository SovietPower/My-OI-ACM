/*
9424kb	1132ms
因为有删除，考虑倒序处理某个p的询问。
那么每天删除xi的蔬菜就变成了每天运来xi的蔬菜。那么我们取当前最优的即可，早取晚取都一样，不需要留给后面取，还能给后面更优的留出空间。
这样就只需考虑现在了。于是我们能得到p为某个值的答案。多次询问显然需要递推。
而p-1与p相比只是少卖了m的蔬菜。把收益最小的m个删掉即可。
注意堆的插入删除顺序。
复杂度$O(mqlogn)$。
还有一种求询问p的方法，是直接按蔬菜价值排序，然后每次找到其出现位置往前覆盖。如果某天已卖m则用并查集合并掉。
递推的时候sort一遍挨着删就可以。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 400000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mp std::make_pair
#define pr std::pair<LL,int>
#define MAX 100000
typedef long long LL;
const int N=1e5+3;

int A[N],S[N],tot[N],dec[N],use[N];
LL Ans[N];
std::vector<int> v[N];
std::queue<int> tmp;
std::priority_queue<pr> q1;
std::priority_queue<pr,std::vector<pr>,std::greater<pr> > q2;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),m=read(),Q=read();
	for(int i=1; i<=n; ++i)
	{
		A[i]=read(),S[i]=read(),tot[i]=read(),dec[i]=read();
		if(!dec[i]) v[MAX].push_back(i);//上界！
		else v[std::min(MAX,(tot[i]+dec[i]-1)/dec[i])].push_back(i);
	}
	LL ans=0;
	for(int i=MAX; i; --i)
	{
		for(int j=0,k,l=v[i].size(); j<l; ++j)//处理第一次购买 
			k=v[i][j], q1.push(mp(A[k]+S[k],k));
		for(int l=m; l&&!q1.empty(); q1.pop())
		{
			int x=q1.top().second;
			if(!use[x])
				use[x]=1, ans+=q1.top().first, q1.push(mp(A[x],x)), --l;
			else
			{
				int cnt=std::min(l,tot[x]-use[x]-(i-1)*dec[x]);
				ans+=1ll*q1.top().first*cnt, l-=cnt;
				if((use[x]+=cnt)!=tot[x]/*x=0可能会用完!*/) tmp.push(x);//delete
			}
		}
		while(!tmp.empty()) q1.push(mp(A[tmp.front()],tmp.front())), tmp.pop();
	}
	Ans[MAX]=ans; int sum=0;
	for(int i=1; i<=n; sum+=use[i++])
		if(use[i]==1) q2.push(mp(A[i]+S[i],i));
		else if(use[i]) q2.push(mp(A[i],i));
	for(int i=MAX-1; i; --i)
	{
		Ans[i]=ans=Ans[i+1];
		if(sum<=m*i) continue;//总数不够！
		for(int l=sum-i*m/*同上！*/; l&&!q2.empty(); )
		{
			int x=q2.top().second;
			if(use[x]==1) ans-=q2.top().first, --l, q2.pop();
			else
			{
				int cnt=std::min(l,use[x]-1);
				ans-=1ll*q2.top().first*cnt, l-=cnt;
				if((use[x]-=cnt)==1) q2.pop(), q2.push(mp(A[x]+S[x],x));
			}
		}
		sum=i*m, Ans[i]=ans;
	}
	while(Q--) printf("%lld\n",Ans[read()]);

	return 0;
}
