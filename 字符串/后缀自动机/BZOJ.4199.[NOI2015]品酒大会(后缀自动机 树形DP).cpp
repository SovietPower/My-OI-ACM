/*
95648kb	2744ms
ֻ�����󼫳���ͬ�Ӵ��������к�׺֮���LCP��
����׺��LCP�ں�׺����LCA����ͬ[����](https://www.cnblogs.com/SovietPower/p/9249744.html)����⣬��ÿ���㴦����DPͳ������ΪLCAʱ�Ĺ��׼��ɣ��ж��ٶԺ�׺����ΪLCA����
���ڶ��ʣ�ͬ��ά�������ڵ����ֵ�δ�ֵ����Сֵ��Сֵ��Ϊ�𰸼��ɡ�
�Ǻ�׺�ڵ��$size=0$����ֵ�ĳ�ֵͬ��Ҫ���$INF$...�������ҲҪһ��DP��
��ʼ���$INF$�����ת�Ƶ�ʱ��ͬ��Ҫ��...������������$INF$��ˣ�����ֱ��ֻ��$size\geq2$��ʱ��DFS/���´𰸡�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=3e5+5,INF=1<<30;

//char OUT[8000000],*O=OUT;//7e6 isn't enough...
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
//inline void print(LL x)
//{
//	static char obuf[20];
//	if(x<0) x=-x, *O++='-';
//	if(x)
//	{
//		int t=0; while(x) obuf[++t]=x%10+48, x/=10;
//		while(t) *O++=obuf[t--];
//	}
//	else *O++='0';
//}

struct Suffix_Automaton
{
	#define S N<<1
	int las,tot,son[S][26],len[S],fa[S],tm[S],A[S],sz[S],mx1[S],mx2[S],mn1[S],mn2[S];
	LL sum[N],Ans[N];
	char s[N];
	#undef S
	void Insert(int c,int v)
	{
		int p=las,np=++tot;
		len[las=np]=len[p]+1, sz[np]=1;
		mx1[np]=mn1[np]=v, mx2[np]=-INF, mn2[np]=INF;
		for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot; len[nq]=len[p]+1;
				mx1[nq]=mx2[nq]=-INF, mn1[nq]=mn2[nq]=INF;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Solve(const int n)
	{
		las=tot=1, scanf("%s",s+1);
		for(int i=1; i<=n; ++i) A[i]=read();
		for(int i=n; i; --i) Insert(s[i]-'a',A[i]);

		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=n; ++i) tm[i]+=tm[i-1];
		for(int i=tot; i; --i) A[tm[len[i]]--]=i;

		for(int i=tot,v=A[i],x,l; i; v=A[--i])
		{
			x=fa[v], l=len[x];
			sum[l]+=1ll*sz[x]*sz[v], sz[x]+=sz[v];
			mx1[v]>mx1[x]?(mx2[x]=mx1[x],mx1[x]=mx1[v]):(mx2[x]=std::max(mx2[x],mx1[v]));
			mx2[x]=std::max(mx2[x],mx2[v]);
			mn1[v]<mn1[x]?(mn2[x]=mn1[x],mn1[x]=mn1[v]):(mn2[x]=std::min(mn2[x],mn1[v]));
			mn2[x]=std::min(mn2[x],mn2[v]);
		}
		memset(Ans,-0x3f,sizeof Ans);
		for(int x=1; x<=tot; ++x)
			sz[x]>=2 && (Ans[len[x]]=std::max(Ans[len[x]],std::max(1ll*mx1[x]*mx2[x],1ll*mn1[x]*mn2[x])));

		for(int i=n-1; ~i; --i) sum[i]+=sum[i+1], Ans[i]=std::max(Ans[i],Ans[i+1]);
		for(int i=0; i<n; ++i) printf("%lld %lld\n",sum[i],sum[i]?Ans[i]:0);
//		for(int i=0; i<n; ++i) print(sum[i]),*O++=' ',print(sum[i]?Ans[i]:0),*O++='\n';
//		fwrite(OUT,1,O-OUT,stdout);
	}
}sam;

int main()
{
	sam.Solve(read());
	return 0;
}
