/*
17520kb	4980ms
��Ȼֻ��Ҫ���Ǽ�������ͬ�Ӵ��Ĺ��ף�Ȼ�����׺��/��׺$\max$�Ϳ����ˡ�
������ͬ�Ӵ����������뵽�Ժ�׺��height��Ҳ������ ��׺����+����ջ ά��һ��$height$��ͬ�����䣬����ջ�е�$height$������˳��ά��������Сֵ���и����������ֵ��Ԫ�ظ�����
��Ȼ���ҾͲ���д��...��
ÿ�ε�������ʱ������������Ҷ˵�ͺ���ĵ���������ڵĵ�Ĵ𰸣��������ڵĵ���Ϊ�Ҷ˵�Ĵ��Ѿ��������ϲ�������ջʱͳ�ƹ��ˣ���
���忴�����...�о��е���...
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=3e5+5;

int A[N];
LL sum[N],Ans[N];
//char OUT[7000000],*O=OUT;//5e6 isn't enough...
struct Node
{
	int ht,mn,mx,s;
}sk[N];
struct Suffix_Array
{
	int sa[N],sa2[N],rk[N],tm[N],ht[N];
	char s[N];
	void Build(const int n)
	{
		scanf("%s",s+1);
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
				x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
			if(p>=n) break;
		}
		for(int i=1; i<=n; ++i) rk[sa[i]]=i;
		ht[1]=0;
		for(int k=0,p,i=1; i<=n; ++i)
		{
			if(rk[i]==1) continue;
			if(k) --k;
			p=sa[rk[i]-1];
			while(i+k<=n && p+k<=n && s[i+k]==s[p+k]) ++k;
			ht[rk[i]]=k;
		}
	}
}sa;

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

int main()
{
	const int n=read(); sa.Build(n);
	for(int i=1; i<=n; ++i) A[i]=read();
	memset(Ans,-0x3f,sizeof Ans);
	int top=0; sa.ht[n+1]=0;
	for(int i=1; i<=n; ++i)
	{
		int ht=sa.ht[i+1],mx=A[sa.sa[i]],mn=mx,s=1;
		while(top && sk[top].ht>=ht)
		{
			int v=sk[top].ht;
			sum[v]+=1ll*s*sk[top].s;
			Ans[v]=std::max(Ans[v],std::max(1ll*mx*sk[top].mx,1ll*mn*sk[top].mn));
			s+=sk[top].s, mx=std::max(mx,sk[top].mx), mn=std::min(mn,sk[top].mn);
			--top;
		}
		sk[++top]=(Node){ht,mn,mx,s};
	}
	for(int i=n-1; ~i; --i) sum[i]+=sum[i+1], Ans[i]=std::max(Ans[i],Ans[i+1]);
	for(int i=0; i<n; ++i) printf("%lld %lld\n",sum[i],sum[i]?Ans[i]:0);
//	for(int i=0; i<n; ++i) print(sum[i]),*O++=' ',print(sum[i]?Ans[i]:0),*O++='\n';
//	fwrite(OUT,1,O-OUT,stdout);

	return 0;
}
