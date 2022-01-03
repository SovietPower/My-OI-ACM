/*
30268kb	2620ms
Ҫ�����$a_{p_j}=p_k$��$k\lt j$���������Ϊ$k$Ҫ��$j$֮ǰѡ��
��ô���ڸ�����$a_j=k$�����ǿ�������$k\to j$��һ��ͼ�����ͼ�л�����ô�޽⣻��������һ����$0$Ϊ��������
���ƾͱ���ˣ�ѡһ����ǰ����Ҫѡ�丸�ף������$k$��ѡ��$i$��$i$�Ĺ�����$k\cdot w_i$��

Ȼ����ô����...
���赱ǰ��С������$x$����ô���$fa[x]$ѡ��������һ��ѡ$x$�����������һ��ѡ��$fa[x]$����һ��һ��ѡ$x$��
���ǵ���˳��ѡ��ʵ���ǹ���һ�����У��������$x$һ����$fa[x]$�������а���һ�����Կ��ǰ�$x,fa[x]$�ϲ���һ�����У��ٿ��������ġ�
֮ǰ�Ǳȵ�Ȩ����������Ҫ�Ƚ�����������֮��˭���ں�����š�
������������$a,b$����$a$����$t_1$���㣬$b$����$t_2$���㣬���������Ѿ�ѡ��$k$���㣬��ô$ab,ba$�Ĺ��׷ֱ�Ϊ$$W_{ab}=\sum_{i=1}^{t_1}(k+i)w_{a_i}+\sum_{i=1}^{t_2}(k+i+t_1)w_{b_i}\\W_{ba}=\sum_{i=1}^{t_2}(k+i)w_{b_i}+\sum_{i=1}^{t_1}(k+i+t_2)w_{a_i}\\W_{ab}-W_{ba}=t_1\sum w_{b_i}-t_2\sum w_{a_i}$$

��ô$W_{ab}>W_{ba}\Rightarrow \frac{\sum w_{b_i}}{t_2}>\frac{\sum w_{a_i}}{t_1}$����ƽ������С�ķŵ�ǰ����š�
�������ǾͿ����ö�ά���ˣ�ÿ��ȡ����С�ģ������븸�ڵ��������кϲ�����������ô��޸Ķ��޸ĸ��ڵ��״̬��Ҳ���Դ�����ɾ�����ڵ��״̬����ʵ��һ��$sz$�Ƿ���ڵ�ǰ״̬�µ�$sz$�Ϳ����ˣ���
�𰸾���һ�����б��ŵ������ʱ��ͳ�ƾͿ����ˡ�

�����Ҳ������[$STL$���$heap$]��ֻ��Ҫ`#include <algorithm>`��
����Ӧ���Ǳ�`priority_queue`СһЩ�ģ���������д�ĳ�...
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int Cnt,fa[N],Enum,H[N],nxt[N],to[N],F[N],sz[N];
LL w[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int x,sz; LL val;
	bool operator <(const Node &x)const
	{
		return val*x.sz>x.val*sz;
	}
};

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void DFS(int x)
{
	static bool vis[N];
	++Cnt, vis[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]) DFS(to[i]);
		else {puts("-1"); exit(0);}
}
int Find(int x)
{
	return x==F[x]?x:F[x]=Find(F[x]);
}

int main()
{
//	freopen("perm.in","r",stdin);
//	freopen("perm.out","w",stdout);

	const int n=read();
	for(int i=1; i<=n; ++i) AE(fa[i]=read(),i);
	DFS(0);
	if(Cnt<=n) return puts("-1"),0;
	std::priority_queue<Node> q;
	for(int i=0; i<=n; ++i) F[i]=i, sz[i]=1;//from 0
	for(int i=1; i<=n; ++i) q.push((Node){i,1,w[i]=read()});
	LL ans=0;
	while(!q.empty())
	{
		Node tmp=q.top(); q.pop();
		int x=Find(tmp.x);
		if(tmp.sz!=sz[x]) continue;
		int r=Find(fa[x]);
		F[x]=r, ans+=tmp.val*sz[r], sz[r]+=sz[x], w[r]+=w[x];
		if(r) q.push((Node){r,sz[r],w[r]});
	}
	printf("%lld\n",ans);

	return 0;
}
