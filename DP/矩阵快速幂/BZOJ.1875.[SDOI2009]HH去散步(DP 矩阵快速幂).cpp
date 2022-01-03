/*
1368kb	2900ms
�Ƚ������뵽��f[i][j]��ʾ����i���󵽴�j��ķ�������������ĿҪ��������һ���߹��ı� 
���������ʾ�ǲ���ת�Ƶ� 
���Կ��Ǳߣ�f[i][j]��ʾ����i���󵽴��j���ߵķ���������ô�� f[i][j] = ��f[i-1][k] (��k��ֱ�ӵ����j) 
ֻҪ���߷���ߣ��ͱ�֤�˲�������һ������ 
�����ܴ󣬶����������Ȼ�ǿ���ͨ����������ݼ���ת�Ƶ� 
���ʼ�߾����t-1�η���t'��Ȼ����ϵ������(��src�����ı�)����t'����Ϊ����t���ߺ�ķ����� 
(���ϵ��������Ϊ��ֻ���������������src��·��)
���մ�Ϊ������des�����ıߵ�dpֵ 
һ���߿϶�Ҫ������������ 
ע��������㼶��!=���͡���
O((2m)^3logt)=5e7 �ÿ�����  (Ϊʲô�Դ�����)
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
#define mod 45989//����Կ� 
const int N=150;//,mod=45989;

int n,m,K,src,des,Enum,H[70],nxt[N],to[N];
struct Matrix
{
	int A[N][N];
//	void Clear() {memset(A,0,sizeof A);}
	Matrix operator *(const Matrix &a)const
	{
		Matrix res;
		for(int i=1; i<=m; ++i)
			for(int j=1; j<=m; ++j)
			{
				res.A[i][j]=0;
				for(int k=1; k<=m; ++k)
					(res.A[i][j]+=A[i][k]*a.A[k][j])%=mod;
			}
		return res;
//		for(int i=1; i<=m; ++i)
//			for(int k=1; k<=m; ++k)
//				if(A[i][k])//�Ż����� ��ö��k ���ǿ������Ƿ�Ϊ0 -> ���Ǹ�����-- Ӧ����������������ɡ���
//					for(int j=1; j<=m; ++j)
//						res.A[i][j]+=A[i][k]*a.A[k][j]%mod,
//						res.A[i][j]>=mod ? res.A[i][j]-=mod : 0;
	}
}S,tmp;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
Matrix FP(Matrix x,int k)
{
	Matrix t=x; --k;
	for(; k; k>>=1,x=x*x)
		if(k&1) t=t*x;
	return t;
}

int main()
{
	Enum=1;
	n=read(),m=read(),K=read(),src=read(),des=read();
	for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),AddEdge(u,v);
	m=Enum;
	for(int i=H[src]; i; i=nxt[i]) S.A[1][i]=1;//��1����� �о�����ѧ������
	for(int i=2; i<=m; ++i)
		for(int j=H[to[i]]; j; j=nxt[j])//���iֱ�����ڵı߼��ߵĶ˵������ı� 
			if(i!=(j^1)) tmp.A[i][j]=1;//++tmp.A[i][j];//����ǲ���Ҫ+�ģ���Ϊ�Ѿ���ÿ���߶����� 
//			if(i^j^1) tmp.A[i][j]=1;
	tmp=FP(tmp,K-1);
	S=S*tmp;
	int res=0;
	for(int i=H[des]; i; i=nxt[i]) res+=S.A[1][i^1];//��㵽 �ܵ��յ�ı� 
	printf("%d",res%mod);

	return 0;
}
