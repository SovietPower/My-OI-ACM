//46MS	3056K
//https://www.cnblogs.com/SovietPower/p/9638883.html
/*
$Description$
��һ��������1��������ÿ���������ֿ��ܣ�
1. ����$k_x$��ɱ�����ص�1��
2. ����$e_x$�ҵ����ڣ��߳��Թ���
3. ������������һ���õ�����ıߡ�

���߳��Թ�������������
$n\leq 10000$��
$Solution$
(ֱ��)��$F(i)$Ϊ��$i$���߳��Թ��������������𰸾���$F(1)$��
��$p_i=1-k_i-e_i$����ʾ$i$�����ű��ߵĸ��ʣ�$d_i=dgr[i]$������$i$������
ÿ����������״̬����$$F(i)=k_i\times F(1)+e_i\times 0+\frac{p_i}{d_i}\sum_{v=to[i]}(F(v)+1)$$
~~Ҫ��˹��Ԫ�𡣡�~~����Ҫ��һ����ͼ��һ����������Ҷ�ڵ�ֻ�ɸ��ڵ㣨��$1$��ת�ƶ����������ڵ��ת������ҪҶ�ڵ㣬���ǳ��԰�Ҷ�ڵ��$F$����ȥ�������ڵ�$F$�е�ʲô������
����Ҷ�ڵ㣺$$\begin{aligned}F(i)&=k_i\times F(1)+p_i\times(F(fa)+1)\\&=k_i\times F(1)+p_i\times F(fa)+p_i\end{aligned}$$
���ڷ�Ҷ�ڵ㣺$$F(i)=k_i\times F(1)+\frac{p_i}{d_i}F(fa)+\frac{p_i}{d_i}\sum_{v=son[i]}F(v)+p_i$$
��$$F(i)=A_i\times F(1)+B_i\times F(fa)+C_i$$
��Ҷ�ڵ��$F(v)=A_v\times F(1)+B_v\times F(fa)+C_v$�������ڵ��$F(i)$�У�$$F(i)=k_i\times F(1)+\frac{p_i}{d_i}F(fa)+\frac{p_i}{d_i}\sum_{v=son[i]}(A_v\times F(1)+B_v\times F(i)+C_v))+p_i$$$$(1-\frac{p_i}{d_i}\sum_{v=son[i]}B_v)F(i)=(k_i+\frac{p_i}{d_i}\sum_v A_v)F(1)+\frac{p_i}{d_i}F(fa)+p_i+\frac{p_i}{d_i}\sum_v C_v$$
����Ҷ�ڵ�$v$��$A_v=k_v,B_v=C_v=p_v$��
Ȼ�������$v$�õ�$A_i,B_i,C_i$��
���ڸ��ڵ㣬$F(1)=A_1\times F(1)+C_1$����$F(1)=\frac{C_1}{1-A_1}$��

$A_1=1$���ߴ���$(1-\frac{p_i}{d_i}\sum_{v=son[i]}B_v)=1$ʱ�޽⡣��ע���һ����
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define eps 1e-9//small
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=10005;

int Enum,H[N],nxt[N<<1],to[N<<1],dgr[N];
double A[N],B[N],C[N],K[N],P[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	++dgr[v], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	++dgr[u], to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
bool DFS(int x,int f)
{
	if(dgr[x]==1 && f)//������
	{
		A[x]=K[x], B[x]=C[x]=P[x];
		return 1;
	}
	double a=K[x],b=P[x]/dgr[x],c=P[x],d=0,p=b;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=f)
		{
			if(!DFS(v,x)) return 0;
			a+=p*A[v], c+=p*C[v], d+=p*B[v];
		}
	if(fabs(1-d)<eps) return 0;
	A[x]=a/(1-d), B[x]=b/(1-d), C[x]=c/(1-d);
	return 1;
}

int main()
{
	for(int T=read(),i=1; i<=T; ++i)
	{
		Enum=0, memset(H,0,sizeof H), memset(dgr,0,sizeof dgr);
		int n=read();
		for(int i=1; i<n; ++i) AE(read(),read());
		for(int i=1; i<=n; ++i) K[i]=1.0*read()/100,P[i]=1-K[i]-(1.0*read()/100);
		printf("Case %d: ",i);
		if(DFS(1,0) && fabs(1.0-A[1])>eps) printf("%.5lf\n",C[1]/(1.0-A[1]));
		else puts("impossible");
	}
	return 0;
}
