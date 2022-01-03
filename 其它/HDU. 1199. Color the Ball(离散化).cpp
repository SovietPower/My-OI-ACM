/*
$Description$
��$n$�����Σ������ھ�����Ⱦĳ����ɫ���Ḳ��֮ǰ��λ��Ⱦ����ɫ���������ÿ����ɫ���ֵ�����͡�$n\leq 1000$��
$Solution$
ͬ1199����$4n$�����ζ˵���ɢ������$x,y$�ֱ𣩣�Ȼ����Ⱦ��ɢ��������е���ɫ��
ע��$(1,1),(2,2)$�������ε������$1$����$4$������Ⱦɫ��ʵ�ʷ�Χ��$[l,r-1],[u,d-1]$��
����ͬ1199��λ��$(i,j)$���������$(X[i+1]-X[i])\cdot(Y[j+1]-Y[j])$��ע��$X[nx+1]=X[nx]+1, Y[ny+1]=Y[ny]+1$��������λ��Ҳû����ɫ����
���Ӷ�$O(n^2)$��
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=1e4+5;

LL Ref[N];
int col[N];
struct Opt
{
	int l,r,v;
}A[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
char Get()
{
	char c=gc(); while(c!='w'&&c!='b') c=gc();
	return c;
}

int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		int m=0;
		for(int i=1; i<=n; ++i) A[i]=Opt{read(),read(),Get()=='w'};
		for(int i=1; i<=n; ++i) Ref[++m]=A[i].l, Ref[++m]=A[i].r, Ref[++m]=A[i].r+1;
		std::sort(Ref+1,Ref+1+m);
		m=std::unique(Ref+1,Ref+1+m)-Ref-1;
		for(int i=1; i<=n; ++i)
		{
			int l=std::lower_bound(Ref+1,Ref+1+m,A[i].l)-Ref;
			int r=std::lower_bound(Ref+1,Ref+1+m,A[i].r)-Ref;
			for(int j=l,v=A[i].v; j<=r; ++j) col[j]=v;
		}
		LL ans=0,l=0,r=0; Ref[m+1]=Ref[m]+1;
		for(int i=1,las=-1; i<=m; ++i)
			if(col[i])
			{
				if(las==-1) las=i;
				if(Ref[i+1]-Ref[las]>ans) ans=Ref[i+1]-Ref[las], l=Ref[las], r=Ref[i+1]-1;
			}
			else las=-1;
		if(ans) printf("%lld %lld\n",l,r);
		else puts("Oh, my god");
		memset(col,0,m+2<<2);
	}

	return 0;
}
