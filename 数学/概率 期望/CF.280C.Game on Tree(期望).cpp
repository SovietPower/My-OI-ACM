/*
62ms	9872KB
$Description$
����һ����$n$���׵���и�����ÿ�����ѡ��һ���㣬�������������������е�Ⱦ�ڡ�
�������������ٴκ����е㶼��Ⱦ�ڣ�
$Solution$
��������������(�ð�����̫��) 
��Ϊ���ʾ��пɼ��ԣ�һ�������Էֽ�Ϊ����������������ֽ������״̬���ǵ㣬�������ǿ��Լ���ÿ���������������������ͣ���$E(�ܲ�������)=E(ÿ���㱻ѡ�в�������)$��
�����������������ָ��Ϊ�׵㱻ѡ��Ⱦ�ڵ�����������
��Ϊһ�������Ƚڵ㱻Ⱦ�ں�����ڵ����������Ϊ0�ˣ����Եó�һ����x������E(x)=1/dep[x].
ֱ��DFS����
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=1e5+5;

int n,Enum,H[N],nxt[N<<1],to[N<<1];
double Ans;

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
void DFS(int x,int f,int d)
{
	Ans+=1.0/d;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f) DFS(to[i],x,d+1);
}

int main()
{
	n=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v);
	DFS(1,1,1);
	printf("%.10lf",Ans);

	return 0;
}
