/*
840kb	64ms
���⣺01������������Ϊ$a\times 2^b$��ʽ�����ܴܺ�
��������ʾΪ$a\times2^b$����ʽ��Ȼ��$b$����
�Ӹߵ���ö��ÿһλ��$f[i]$��ʾ��ǰλ����Ϊ$i$ʱ������ֵ��������$a\times2^{bit}$��������ͬһλ��ֱ��$01$���������ˡ�
���ת�Ƶ���һλ��$f[i]$ת�Ƶ�$f[i\times2+\text{W����һλ�Ƿ�Ϊ1}]$��ע�⵽ÿһλ���������ᳬ��$n\times a_{max}=1000$�������ٶ�$1000$ȡ$\min$���ɡ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1005;

struct Node
{
	int a,b,val;
	bool operator <(const Node &x)const
	{
		return b>x.b;
	}
}A[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
void Solve(int n,int m)
{
	static int f[N],g[N];
	int mx=0;
	for(int i=1,a,b; i<=n; ++i)
	{
		a=read(), A[i].val=read();
		for(b=0; b<30&&!(a&1); ++b,a>>=1);
		mx=std::max(mx,a), A[i].a=a, A[i].b=b;
	}
	std::sort(A+1,A+1+n);

	const int lim=n*mx;
	memset(f,-0x3f,sizeof f);
	f[0]=0, A[n+1].b=-1;
	for(int i=30,now=1; ~i; --i)
	{
		memset(g,-0x3f,sizeof g);
		for(int j=0,p; j<=lim; ++j)
			p=std::min((j<<1)+(m>>i&1),lim), g[p]=std::max(g[p],f[j]);
		memcpy(f,g,sizeof f);
		for(; A[now].b==i; ++now)
			for(int ai=A[now].a,vi=A[now].val,j=0; j<=lim-ai; ++j)
				f[j]=std::max(f[j],f[j+ai]+vi);//f[i]:ʣ������Ϊi 
	}
	int ans=0;
	for(int i=0; i<=lim; ++i) ans=std::max(ans,f[i]);
	printf("%d\n",ans);
}

int main()
{
	int n,m;
	while(n=read(),m=read(),n!=-1&&m!=-1) Solve(n,m);
	return 0;
}
