/*
44372kb	3756ms
״ֻ̬��ڡ����������ɫ�йأ�������f[x][i][j]��ʾ��ǰ��xΪ���ڵ㣬��i���ڵ�j���׵㣬ʹ��x�����������������С���ѡ�
���𰸾���min{f[root][0][j],f[root][i][0/1]}��
��i>=1��״̬������i=1��j>=2��״̬������j=2.
����˳��ͬ���ϱ���һ�����ô�֮ǰ�����õ�����Ϣ�뵱ǰö�ٵ������ϲ�����ΪҪ�ϲ������Ϣ�����ٿ�һ�������¼������Щ��
ת��ʱҪ���ǵ�ǰ�ڵ����ɫ(��ʼ������)��
ÿ���ӽڵ�������ѡ��: ��������š����������Ҫ��֤�ӽڵ�״̬�Ϸ�����!i||j<2����ʱת�Ƶ���״̬�ǵ�ǰö�ٵ�x��״̬.
���Ӷ�O(n).(����������) 
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define INF 1e14
#define MAXIN 1000000
typedef long long LL;
const int N=3e5+5;

int n,Enum,A[N],H[N],nxt[N<<1],to[N<<1],val[N<<1];
LL f[N][2][3],tmp[2][3];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, val[Enum]=w;
}
void DFS(int x,int fa)
{
//	f[x][0][0]=f[x][0][1]=f[x][0][2]=f[x][1][0]=f[x][1][1]=f[x][1][2]=INF;
	for(int i=0; i<2; ++i)//wocչ�����ˡ��� 
		for(int j=0; j<3; ++j) f[x][i][j]=INF;
	f[x][A[x]==0][A[x]==1]=0;//�о������ʼ���е�keyi...
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS(v,x);
			for(int a=0; a<2; ++a)
				for(int b=0; b<3; ++b) tmp[a][b]=INF;
			for(int a=0; a<2; ++a)
				for(int b=0; b<3; ++b)
					if(f[x][a][b]!=INF)//
						for(int c=0; c<2; ++c)//ö���������������Ҫc<=a!
							for(int p1,p2,d=0; d<3; ++d)
								if(f[v][c][d]!=INF)//
								{
									p1=a+c>=1?1:0, p2=b+d>=2?2:b+d;
									tmp[p1][p2]=std::min(tmp[p1][p2],f[x][a][b]+f[v][c][d]);//
									if(!c||d<2) tmp[a][b]=std::min(tmp[a][b],f[x][a][b]+f[v][c][d]+val[i]);//
								}
			memcpy(f[x],tmp,sizeof tmp);
		}
}
inline LL Min(LL a,LL b,LL c,LL d,LL e){
	return std::min(a,std::min(b,std::min(c,std::min(d,e))));
}

int main()
{
	int T=read();
	while(T--)
	{
		Enum=0, memset(H,0,sizeof H);
		n=read();
		for(int i=1; i<=n; ++i) A[i]=read();
		for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v,read());
		DFS(1,1);
		printf("%lld\n",Min(f[1][0][0],f[1][0][1],f[1][0][2],f[1][1][0],f[1][1][1]));
	}
	return 0;
}
