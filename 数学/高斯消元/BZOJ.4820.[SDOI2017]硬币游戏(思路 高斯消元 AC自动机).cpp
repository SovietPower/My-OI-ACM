/*
4460kb	192ms(�������...����ܵĺ͹�ϣ���)
$Description$
��$n$����Ϊ$m$���ַ���ֻ��H,T�Ĵ�����������ַ�����ÿ�εȸ�������H��T����ĩβ��������г�����$n$�����е�һ�����������ÿ���������������ɵĴ�������β�ĸ��ʡ�
$n,m\leq 300$��
$Solution$
����AC�Զ�����ÿ�����������������ߣ����Եõ�һ������ͼ������ [[SDOI2012]���Թ�] ���Եõ�һ��$Tarjan$+��˹��Ԫ��$O((nm)^3)$����������������$60$�ְ����ǵ�$5.6$����WA��smg��
��ʵ$O((nm)^3)$���� [[JSOI2009]��Ȥ����Ϸ]...ֻ�轨��AC�Զ���һ���˹��Ԫ���ɣ��������Ǹ���֪����д������ȥ����

$40$�ֵ�������������״̬��������̫�ࡣ���ǰ����Ƶ�״̬�ϲ���һ����
��������һ����������$TTH$��$HTT$������������ֹ�ڵ�ֱ����$A,B$��û�о�����ֹ�ڵ��״̬����$N$��
$N$����$TTH$һ������ֹ�����������ַ�����$TTH$ʱ���������������$N$�ĺ�׺��$TT$������$B$��ֹ��$N$�ĺ�׺��$T$������$B$��ֹ......���������ǣ�$$NTTH=A+BH+BTH$$

����$BH$�ͱ�ʾ$N$��$B$����ֹ���������$H$��
��Ϊ$N$�г���$B$�ĸ��ʾ���$p(B)$�����ں�����ض���$k$���ַ������ʾ���$p(B)\times\frac{1}{2^k}$��
�����У�$$p(N)\times\frac18=p(A)+p(B)\times\frac12+p(B)\times\frac14\\0.125p(N)=p(A)+0.75p(B)$$

��չ�����������$pre_{i,k}$��ʾ$s_i$����Ϊ$k$��ǰ׺��$suf_{i,k}$��ʾ$s_i$����Ϊ$k$�ĺ�׺����ô$$p(N+s_i)=p(s_i)+\sum_{j=1}^n\sum_{k=1}^m[pre_{i,k}=suf_{j,k}]\frac{1}{2^{m-k}}p(s_j)=\frac{1}{2^m}p(N)$$

�������ǾͿ��Եõ�$n$�������ˣ�������$n+1$��������ʣ�µ�һ�����̾���$\sum_{i=1}^np_i=1$���Ϳ��Ը�˹��Ԫ�ˡ�
���Ӷ�$O(n^3+n^2m)$��

������������֮�����й���ǰ��׺�����Թ�ϣ��KMP����AC�Զ�����
��$fail$ʲô�����Ĳ����...����дһ�¡�
**��ϣ��**ûʲô��˵�ġ���ǰ��׺��ϣ�Ͱ��ַ�������һ��$P$���������ˡ�����$Kelin\ dalao$ѧһ��orz��
**KMP��**��ÿ��$a$�����$fail$���飬��$s_a$��$s_b$��ƥ�䣬����$j$ָ��λ�þ���$s_a$��ĵ���$s_b$��׺��ǰ׺��Ȼ��$j$������$fail[j]$��ͳ�ƴ𰸼��ɡ���ע����$a=b$�����$p(s_a)$һ�Σ�Ҳ������$j=fail[j]$һ�Σ�
**AC�Զ�����** AC�Զ�����ÿ���������ߵ����Ĵ���һ���ߡ�Ȼ���$s_b$����ֹ�ڵ㲻����$fail$�����о����ڵ�$x$�������ı�$s_a$������ʾ$s_a$��$len_x$��ǰ׺��$s_b$�ĺ�׺��ͬ��
*/
#include <cmath>
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=305,M=N*N;

double pw2[N],A[N][N],Ans[N];

struct AC_Automaton
{
	int tot,len[M],son[M][2],fail[M],q[M],H[M],Enum,nxt[M],to[M],ed[N];
	char s[N];
	inline void AE(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
	void Insert(int n,int id)
	{
		scanf("%s",s);
		int x=0;
		for(int i=0,c; i<n; ++i)
		{
			if(!son[x][c=s[i]=='H']) len[son[x][c]=++tot]=len[x]+1;
			x=son[x][c], AE(x,id);
		}
		ed[id]=x;
	}
	void Build()
	{
		int h=0,t=0;
		if(son[0][0]) q[t++]=son[0][0];//, fail[son[0][0]]=0;
		if(son[0][1]) q[t++]=son[0][1];//, fail[son[0][1]]=0;
		while(h<t)
		{
			int x=q[h++];
			for(int i=0,v; i<2; ++i)
				if((v=son[x][i])) fail[v]=son[fail[x]][i], q[t++]=v;
				else son[x][i]=son[fail[x]][i];
		}
	}
	void Calc(int id,int m)
	{
		for(int x=ed[id]; x; x=fail[x])
			for(int i=H[x]; i; i=nxt[i])
				A[to[i]][id]+=pw2[m-len[x]];
	}
}ac;

void Gauss(int n)
{
	for(int j=0; j<n; ++j)
	{
		int mx=j;
		for(int i=j+1; i<n; ++i) if(fabs(A[mx][j])<fabs(A[i][j])) mx=i;
		if(mx!=j) for(int k=j; k<=n; ++k) std::swap(A[mx][k],A[j][k]);
		for(int i=j+1; i<n; ++i)
			if(A[i][j])//���ǲ�Ҫд>eps��= = 
			{
				double t=A[i][j]/A[j][j];
				for(int k=j; k<=n; ++k) A[i][k]-=t*A[j][k];
			}
	}
	for(int i=n-1; ~i; --i)
	{
		for(int j=i+1; j<n; ++j) A[i][n]-=A[i][j]*Ans[j];
		Ans[i]=A[i][n]/A[i][i];
	}
}

int main()
{
	int n,m; scanf("%d%d",&n,&m);
	pw2[0]=1;
	for(int i=1; i<=m; ++i) pw2[i]=pw2[i-1]*0.5;
	for(int i=1; i<=n; ++i) ac.Insert(m,i);
	ac.Build();
	for(int i=1; i<=n; ++i) ac.Calc(i,m);
	for(int i=1; i<=n; ++i) A[0][i]=1, A[i][0]=-pw2[m];
	A[0][n+1]=1, Gauss(n+1);
	for(int i=1; i<=n; ++i) printf("%.10lf\n",Ans[i]);

	return 0;
}
