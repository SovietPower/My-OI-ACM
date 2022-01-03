/*
5892kb	784ms
��$st[i]$��ʾ��$i$Ϊ��ͷ�ж��ٸ�$AA$�������Ӵ���$ed[i]$��ʾ��$i$��β�ж��ٸ�$AA$�������Ӵ�����ô$Ans=\sum_{i=1}^{n-1}ed[i]*st[i+1]$��
���������$st[i],ed[i]$�������Ļ�����ö��$i$��Ȼ���ϣ��һ�¡�����$O(n^2)$����$95$���ˡ���
�����ǣ�ö�ٳ���$len$���ж�ÿ��λ���Ƿ���ڳ�Ϊ$2*len$��$AA$�������Ӵ���
ÿ��$len$�ľ����һ���ؼ��㣬����һ������Ϊ$2*len$�Ĵ�һ���ᾭ���������ڵĹؼ��㡣
����ö���������ڵĹؼ��㣬����$i=k*len,\ j=i+len$������$x$��ʾ$i,j$�������ǰ׺���������׺����$len$ȡ$\min$����$y$��ʾ$i,j$������ĺ�׺�������ǰ׺����$len$ȡ$\min$����
�����뻭ͼ�ˣ�ע��𿴴������ø�������`aabaabab`��һ�£�
��$x+y-1<len$ʱ����Ϊ�м�û����ͬ�Ĳ��������Ҳ���һ������$i,j$��Ϊ$2*len$��$AA$����
��$x+y-1\geq len$ʱ�����Ƿ�����Ϊ$i,j$���������Ϊ$len$�ĵ㣬����ȡ$i-x+len,\ j-x+len$����������֮�����γɳ�$2*len$��$AA$�Ӵ���ͬʱ�������㲻�������ƶ���ֱ��$i+y-1,\ j+y-1$�������γ�һ��$AA$�Ӵ���
Ҳ���ǵ�$p$ȡ$[j-x+len,\ j+y-1]$�е�ĳ��λ��ʱ�����ܵõ���$p$Ϊ��β�ĳ�Ϊ$2*len$��$AA$����ͬ��$p$��$[i-x+1,\ i+y-len]$��ʱ��Ҳ���ܵõ���$p$��ͷ�ĳ�Ϊ$2*len$��$AA$����
���Ծ��������һ�����һ�¾Ϳ����ˡ�
ֻ��ö��$len$��Ȼ��ÿ��$len$��һ���㣬ͳ�����������Ĺ��ס����Ը��ӶȻ���$O(n\log n)$��
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=3e4+5;

int Log[N];
struct Suffix_Array
{
	int tm[N],sa[N],sa2[N],rk[N],ht[N],st[N][15];

	inline void Init_ST(const int n)
	{
		for(int i=1; i<=n; ++i) st[i][0]=ht[i];
		for(int j=1; j<=Log[n]; ++j)
			for(int t=1<<j-1,i=n-t; i; --i)
				st[i][j]=std::min(st[i][j-1],st[i+t][j-1]);
	}
	inline int LCP(int l,int r)
	{
		l=rk[l], r=rk[r]; if(l>r) std::swap(l,r);
		++l;
		int k=Log[r-l+1];
		return std::min(st[l][k],st[r-(1<<k)+1][k]);
	}
	void Build(char *s,const int n)
	{
		memset(rk,0,sizeof rk);
		memset(sa2,0,sizeof sa2);//Ҫ���...! ��Ϊ����Ƚ����ü�<=n�ˡ�
		int m=26,*x=rk,*y=sa2;
		for(int i=0; i<=m; ++i) tm[i]=0;
		for(int i=1; i<=n; ++i) ++tm[x[i]=s[i]-'a'+1];
		for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
		for(int i=n; i; --i) sa[tm[x[i]]--]=i;
		for(int k=1,p=0; k<n; k<<=1,m=p,p=0)
		{
			for(int i=n-k+1; i<=n; ++i) y[++p]=i;
			for(int i=1; i<=n; ++i) if(sa[i]>k) y[++p]=sa[i]-k;

			for(int i=0; i<=m; ++i) tm[i]=0;
			for(int i=1; i<=n; ++i) ++tm[x[i]];
			for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
			for(int i=n; i; --i) sa[tm[x[y[i]]]--]=y[i];

			std::swap(x,y), x[sa[1]]=p=1;
			for(int i=2; i<=n; ++i)
				x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;//because of this
			if(p>=n) break;
		}
		for(int i=1; i<=n; ++i) rk[sa[i]]=i;
		ht[1]=0;
		for(int i=1,k=0,p; i<=n; ++i)
		{
			if(rk[i]==1) continue;
			if(k) --k;
			p=sa[rk[i]-1];
			while(i+k<=n && p+k<=n && s[i+k]==s[p+k]) ++k;
			ht[rk[i]]=k;
		}
		Init_ST(n);
	}
}sa1,sa2;

inline void Init_Log(const int n)
{
	for(int i=2; i<=n; ++i) Log[i]=Log[i>>1]+1;
}
void Solve()
{
	static int st[N],ed[N];
	static char s[N];
	scanf("%s",s+1); const int n=strlen(s+1);
	sa1.Build(s,n), std::reverse(s+1,s+1+n), sa2.Build(s,n);

	memset(st,0,n+1<<2), memset(ed,0,n+1<<2);
	for(int len=1,lim=n>>1; len<=lim; ++len)
		for(int i=len,j=len<<1; j<=n; i=j,j+=len)
		{
			int x=std::min(len,sa2.LCP(n-i+1,n-j+1)),y=std::min(len,sa1.LCP(i,j));
			if(x+y-1>=len)
				++st[i-x+1], --st[i+y-len+1], ++ed[j-x+len], --ed[j+y];
		}
	LL ans=0;
	for(int i=1; i<n; ++i) st[i+1]+=st[i], ed[i+1]+=ed[i], ans+=1ll*ed[i]*st[i+1];
	printf("%lld\n",ans);
}

int main()
{
	Init_Log(30000);
	int T; scanf("%d",&T);
	while(T--) Solve();
	return 0;
}
