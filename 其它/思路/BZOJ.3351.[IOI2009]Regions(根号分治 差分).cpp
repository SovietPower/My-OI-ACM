/*
28360kb	7720ms
$Description$
����һ��$n$���������ÿ������һ������$1\leq r_i\leq R$��$Q$��ѯ�ʣ�ÿ��ѯ�ʸ���$r1,r2$�����ж��ٵ��$(x,y)$���㣬$r_x=r1,\ r_y=r2$����$x$��$y$�����ȡ�
$n,q\leq2\times10^5,\ R\leq25000$��

$Solution$
������Ϊ$r2$���ж��ٸ���������ۡ�
��$\leq\sqrt n$����ÿ���㴦����ͳ�������ȵĹ��ף�
��$\gt\sqrt n$�������������Բ�����$\sqrt n$�֣�������Ϊ$r1$�ĵ��ϱ���ö����Щ$r2$���´𰸣�������Բ�֣���������ǰ������������󣩡�
��Ȼ���ڵڶ����������ÿ�����ϣ�Ҫ��ѯ�ʵ�$r2$ȥ�ز��ܱ�֤���Ӷȣ�Ȼ������û����ȥ�غ���Ҳ�ܹ�...����
�������ȥ�أ��Լ�����ǣ���$r2$��ͬ��һЩѯ�ʣ�Ҫͬʱ�������ǡ������$r2$Ϊ�ؼ���`sort`�£��Ϳ��Բ���ˣ�
��ʵ�϶�ѯ�ʵ��$(r1,r2)$��һ���ؾͿ�����...������ֹ�ѯ��$(r1,r2)$����ֱ����֮ǰ�����𰸡�
���Ӷ�$O(n\sqrt n+q\sqrt n)$��

��[���ֿ�����]��Ȼ�����ÿ���
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5,M=25005;

int Enum,H[N],nxt[N],A[N],Ans[N];
std::vector<pr> v1[M],v2[M];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v;
}
void DFS(int x)
{
	static int sum1[N],sum2[N];

	const std::vector<pr> &vec2=v2[A[x]];//һ��ʼ&����д...��˵��ôMLE=-= 
	for(int i=0,l=vec2.size(); i<l; ++i)
		Ans[vec2[i].second]+=sum2[vec2[i].first];

	++sum1[A[x]], ++sum2[A[x]];
	const std::vector<pr> &vec1=v1[A[x]];
	for(int i=0,l=vec1.size(); i<l; ++i)
		Ans[vec1[i].second]-=sum1[vec1[i].first];

	for(int v=H[x]; v; v=nxt[v]) DFS(v);

	for(int i=0,l=vec1.size(); i<l; ++i)
		Ans[vec1[i].second]+=sum1[vec1[i].first];
	--sum2[A[x]];
}

int main()
{
	static int pos[N],cnt[M];

	const int n=read(),R=read(),Q=read(),size=sqrt(n);
	++cnt[A[1]=read()];
	for(int i=2; i<=n; ++i) AE(read(),i), ++cnt[A[i]=read()];

	std::map<pr,int> f;
	std::map<pr,int>::iterator it;
	for(int i=1; i<=Q; ++i)
	{
		int r1=read(),r2=read();
		if((it=f.find(mp(r1,r2)))==f.end())
		{
			f[mp(r1,r2)]=pos[i]=i;
			if(cnt[r2]<=size) v2[r2].push_back(mp(r1,i));
			else v1[r1].push_back(mp(r2,i));
		}
		else pos[i]=it->second;
	}
	DFS(1);
	for(int i=1; i<=Q; ++i) printf("%d\n",Ans[pos[i]]);//��ʵӦ����long long��=v= 

	return 0;
}
