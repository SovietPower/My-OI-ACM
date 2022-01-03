/*
$Description$
����һ������ͼ���������Щ�㣬ɾ�����������������ߺ�ͼû�л���$n\leq 5\times10^5,m\leq 10^6$��
$Solution$
��Ŀ�ȼ��������л��Ľ�����
�����������У����ԭͼû�л���������е㣻���ɾ��ԭͼ��ĳ�������Դ��ڻ������$0$����Ҳ�ǲ��ٷ��ˡ�
�����ͼ�е�ĳ������������Ȼ��������ϡ�����ֻ��Ҫ�����������
�ѻ���������������г�����Ļ�ֻ�����������
���ڵ�һ������������������Subtask�������׷��֣���Ҳ��Ȼ���Ϸ��ĵ�ֻ��������Щ���Ľ������Ѻ�߿����߶Σ�����������Ľ�����֮ǰ�ĵڶ����л��������ˣ�Ȼ������������ӳ���Ϊ0�ĵ�����ܵ����ĵ������λ��$pl$�������Ϊ0�ĵ���������ĵ������λ��$pr$��Ȼ��Ϳ����ҵ����ҵ���˵�������Ҷ˵㡣
���ڵڶ����������Ȼ��������ں��$x\rightarrow y$����$x,y$֮��ĵ㶼���ǺϷ��ġ�
��������������ӳ���Ϊ0�ĵ���µ����ĵ������λ��$pr$��Ȼ��ɨһ�顣
����������Ϸ��ĵ���Ǵ��ˡ�
����ͼ��ֻ�����������һ���Ϊ1����ʱ��������ǺϷ��ģ�����ɾ�����ߺ�ͼ�Դ��ڻ����᷵���޽⡣���Ƿ��������ÿ���������ͳ��㣬��������Ϳ��Դ����ˡ����ѻ����ӵ㼯��ɱ߼���
���Ӷ�$O(n+m)$��
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e6+5,M=1e6+5+N;

int n,m,Enum,H[N],nxt[M],to[M],dgr[N],cir[N],sz,pre[N],fa[N],q[N],pl[N],pr[N];
bool find_circle,vis[N],ins[N],isc[M],ok[N];
std::vector<int> ans;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int v,int u)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void DFS(int x)
{
	vis[x]=ins[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]])
		{
			fa[v]=x, pre[v]=i, DFS(v);
			if(find_circle) return;
		}
		else if(ins[v])
		{
			for(int p=x; p!=v; p=fa[p]) cir[++sz]=p, isc[pre[p]]=1;
			cir[++sz]=v, isc[i]=1;
			std::reverse(cir+1,cir+1+sz);
			find_circle=1; return;
		}
	ins[x]=0;
}
bool Toposort()
{
	int h=0,t=0;
	for(int i=1; i<=Enum; ++i) if(!isc[i]) ++dgr[to[i]];//��Ҳ��ɾ����ģ�
	for(int i=1; i<=n; ++i) if(!dgr[i]) q[t++]=i;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(!isc[i] && !--dgr[to[i]]) q[t++]=to[i];
	}
	return t==n;
}
void Solve()
{
	for(int i=1; i<=n; ++i)
		if(!vis[i]) {DFS(i); if(find_circle) break;}
	if(!find_circle)
	{
		n>>=1;
		for(int i=1; i<=n; ++i) ans.push_back(i);
		return;
	}
	if(!Toposort()) return;

	int ansl=1,ansr=sz;
	for(int i=1; i<=sz; ++i) pl[cir[i]]=pr[cir[i]]=i;
	for(int i=n,x; i; --i)
	{
		if(!pl[x=q[i]]) pl[x]=N;//���⻷���Ӱ�� 
		for(int j=H[x]; j; j=nxt[j])
			if(!isc[j]/*!*/) pl[x]=std::min(pl[x],pl[to[j]]);//�ǻ��ߣ��������� 
	}
	for(int i=1; i<=sz; ++i)
		if(pl[cir[i]]<i) {ansr=i; break;}//������˶˵�Ӧ����pl[i]==i 
	for(int i=1,x; i<=n; ++i)
	{
//		if(!pr[x=q[i]]) pr[x]=0;
		for(int j=H[x=q[i]]; j; j=nxt[j])
			if(!isc[j]) pr[to[j]]=std::max(pr[to[j]],pr[x]);
	}
	for(int i=sz; i; --i)
		if(pr[cir[i]]>i) {ansl=i; break;}
	if(ansl>ansr) return;

	memset(pr,0,sizeof pr);
	for(int i=1; i<=sz; ++i) pr[cir[i]]=i;
	for(int i=n,x; i; --i)//����һ�������pr����һ�� 
	{
//		if(!pr[x=q[i]]) pr[x]=0;
		for(int j=H[x=q[i]]; j; j=nxt[j])
			if(!isc[j]) pr[x]=std::max(pr[x],pr[to[j]]);
	}
	int nowr=0;
	for(int i=1; i<=sz; ++i)
	{
		if(i>=nowr) ok[i]=1;
		nowr=std::max(nowr,pr[cir[i]]);
	}
	for(int i=ansl; i<ansr; i+=2) if(ok[i]) ans.push_back(cir[i]);//anslһ���Ǹ���� 
	std::sort(ans.begin(),ans.end());
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) AE(i+n,i);//in:x out:x+n ����˳��
	for(int m=read(); m--; AE(read(),read()+n));
	n<<=1, Solve();
	printf("%d\n",ans.size());
	for(int i=0,l=ans.size(); i<l; ++i) printf("%d ",ans[i]);

	return 0;
}
