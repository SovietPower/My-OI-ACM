/*
1680kb	256ms
����ͼƥ���ܽ�һ�¾�[����](https://www.cnblogs.com/SovietPower/p/14433906.html)��
$Description$
һ��$N*M$�����ϰ������̣����ַ������Ӻ󣬴Ӻ��ֿ�ʼ�����ƶ����ӣ��������ظ���λ�ã������ƶ����䡣������Щλ�÷����������ֱ�ʤ�ġ�
$Solution$
�����Ⱥڰ�Ⱦɫ���ƶ����Ӷ�Ӧһ��ƥ�䡣
��ôԭͼ�����������
һ�Ǵ�������ƥ�䣺��ô��������ѡ�ĸ��㿪ʼ��������S����ĳ�㣬��ô������ƥ����ߣ�����Ҫô��ƥ������ߵ�S����ĳ�㣬Ҫôû���ߡ������ֱذܣ�
���ǲ���������ƥ�䣺
1.���ִ����ƥ��㿪ʼ������ʤ��������У��Ȳ����ǣ�
2.���ִӷ����ƥ��㣨��ĳ�����ƥ�䷽����δ��ƥ�䣩��ʼ������ֻ���ߵ�һ�����ƥ��㣨�����ߵ���ƥ���������һ��ƥ�䣬�����ƥ��ì�ܣ���Ȼ����������ƥ��ߣ����ֺ���ֻ����ƥ��ߡ�
��Ϊ��ǰ��������ڷ�ƥ��ߣ���������Ǹ���ƥ������γ���һ������·�������ƥ��ì�ܡ�
�����ֳ������һ�ˣ������ֱذܡ�
���������Ƿ����ƥ������ʤ�����ֻҪ��ĳ�����ƥ���²������ƥ�������㡣
�ٿ��������1����������Բ������ƥ��㣬�����ֱ�ʤ���������ֱذܣ����������2�Ľ���һ����

�����������ж�����Щ�㲻һ�������ƥ���С�������һ�����ƥ�䣬δƥ��ĵ�϶��ǡ�
Ȼ����Щδƥ���$x$�����滻���ڽӵ�$v$��һ��ƥ��ߣ���$match[v]$Ҳ���Բ������ƥ���У�ԭ�ȵ�ƥ���$v\rightarrow match[v]$�滻Ϊ$v\rightarrow x$����
��δƥ���DFSһ��Ϳ����ˡ�
���Ӷ�����ƥ�䣬$O(nm)$��

�����������ƥ��Ҫ��㡣�����ߺڰ�Ⱦɫ��Ҳ���ò�����Ⱦɫ��ÿ���������ܶ����߼��ɡ�
�����Ҫע��`match[]/lk[]`�����������ߵļ��϶�Ҫ������ֵ��ƥ�䣨`bool OK()`����ʱ��֤��֮ǰû��ƥ�䡣��
����ǰ�Ѿ��������ƥ�䳤ʲô����...
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 350000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define ID(i,j) ((i-1)*m+j)
#define Ck(i,j) (mp[i][j]&&1<=(i)&&(i)<=n&&1<=(j)&&(j)<=m)
const int N=10005,M=N<<2;

int n,m,vis[N],Time,Enum,H[N],nxt[M],to[M],lk[N],q[N];
bool mp[105][105],ok[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
#define AE(u,v) to[++Enum]=v,nxt[Enum]=H[u],H[u]=Enum,to[++Enum]=u,nxt[Enum]=H[v],H[v]=Enum
bool OK(int x)
{
	vis[x]=Time;
	for(int i=H[x],v; i; i=nxt[i])
		if(vis[v=to[i]]!=Time)
		{
			vis[v]=Time;
			if(!lk[v]||OK(lk[v])) return lk[v]=x,lk[x]=v;//�������а� 
		}
	return 0;
}
void DFS(int x)
{
	ok[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(lk[to[i]] && !ok[lk[to[i]]]/*vis[lk[to[i]]]!=Time*/) DFS(lk[to[i]]);
}

int main()
{
	n=read(), m=read();
	for(int i=1; i<=n; ++i)
	{
		register char c=gc();
		for(; c!='.'&&c!='#'; c=gc());
		for(int j=1; j<=m; ++j,c=gc()) mp[i][j]=c=='.';		
	}
	int t=0;
	for(int i=1,tot=0; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(++tot,mp[i][j])
			{
				if(mp[i+1][j]/*i+1<=n*/) AE(tot,tot+m);
				if(mp[i][j+1]) AE(tot,tot+1);
			}
	for(int i=1,tot=0; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if((++tot,mp[i][j]) && !lk[tot]/*!*/ && (++Time,!OK(tot)))
				q[++t]=tot;
	if(!t) return puts("LOSE"),0;
	puts("WIN");
	for(int i=1; i<=t; ++i) DFS(q[i]);
	for(int i=1,tot=0; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(ok[++tot]) printf("%d %d\n",i,j);

	return 0;
}
