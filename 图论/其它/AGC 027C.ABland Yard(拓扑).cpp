/*
35ms	6656KB
$Description$
����һ��ͼ�����ܴ����Ի�����ÿ��������A��B�����Ƿ����һ��·����ʹ�������治���ߣ��ܹ��õ�����AB����ϣ������ظ������㣩��
$n\leq2\times10^5,m\leq2\times10^5$��
$Solution$
����һ���㣬������ĺ��ֻ��A��B������û�к�̣�����Ȼ������������·���ϡ�
$Sol 1$
���ǰ������ĵ�ɾ����Ȼ�����ж��������ĵ��Ƿ�Ҫ��ɾ��...����һֱɾ���ж�����Ƿ����δ��ɾ���ĵ㡣�����������ࡣ
$Sol 2$
������Ľ���Ҳ���Կ�����·��ֻ����AABB�����Ļ�������AABBAABB...��������ÿ����ʹ�������ת�ƣ���
AA,AB,BB,BA�������Ļ����ǿ���ͨ������ͼ�ң���������ͬ�ַ���һ��S->T�ıߣ���ͬ�ַ���һ��T->S�ıߣ�����л���
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1],t,q[N],cnt[N][2];
char s[N];
bool del[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	++cnt[u][s[v]-'A'], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	++cnt[v][s[u]-'A'], to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void Del(int x)
{
	if(del[x]||(cnt[x][0]&&cnt[x][1])) return;
	q[++t]=x, del[x]=1;
}

int main()
{
	int n=read(),m=read(); scanf("%s",s+1);
	while(m--) AE(read(),read());
	for(int i=1; i<=n; ++i) Del(i);
	for(int h=1; h<=t; ++h)
	{
		int x=q[h];
		for(int i=H[x]; i; i=nxt[i]) --cnt[to[i]][s[x]-'A'],Del(to[i]);
	}
	puts(t==n?"No":"Yes");

	return 0;
}
