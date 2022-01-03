/*
60476kb	92ms
~~����·~~������Ϊ�����֣�����S->row->column->T��
S������е�Ԫ������cap(A[i][n])(�������½�Ϊ����ȡ��)�������е�Ԫ����T����cap(A[n][i])������ÿ��Ԫ��(i,j)����i����j����cap(A[i][j]).
�������ǽ�������ͼʵ��������ʲô������S->Row_i->(i,j)->Col_j->T��������x��������ʵ�ʱ�ʾA[i][n]�����x��A[i][j]�����x��A[n][i]�����x��
��Ҫ�����������������������*3���ɡ�
��Դ�����½粻��Ҫ��ͳ��ÿ���ߵ����������ˣ���Ϊ��һ��T->S�ıߣ��ڵ�һ���������ʱ���бߵ����������Ѿ��ӵ������S->T���ˣ����Եڶ���ֱ����S->T��������ɡ�
*/
#include <cstdio>
#include <algorithm>
const int N=1e6,M=1e6,INF=0x3f3f3f3f;

int n,src,des,dgr[N],Enum,cur[N],H[N],fr[M<<1],to[M<<1],nxt[M<<1],cap[M<<1],lev[N],num[N],q[N],pre[N];
double A[103][103];
bool inq[N];

inline void AddEdge(int u,int v,int w)
{
	if(w)
		to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w,
		to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	for(int i=0; i<des; ++i) lev[i]=des+1;
	q[0]=des, lev[des]=0; int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==des+1 && cap[i^1])
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[src]<=des;
}
int Augment()
{
	int mn=INF;
	for(int i=des; i!=src; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
	return mn;
}
int ISAP()
{
	if(!BFS()) return 0;
	for(int i=0; i<=des; ++i) ++num[lev[i]],cur[i]=H[i];
	int x=src,res=0;
	while(lev[src]<=des)
	{
		if(x==des) x=src,res+=Augment();
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=des;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1];
			cur[x]=H[x];
			if(x!=src) x=fr[pre[x]];
		}
	}
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	int S=0, T=n<<1|1; Enum=1, src=S, des=T;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) scanf("%lf",&A[i][j]);
	int res=0;
	for(int i=1; i<n; ++i) dgr[src]-=(int)A[i][n],dgr[i]+=(int)A[i][n], AddEdge(src,i,(A[i][n]-(int)A[i][n])>0);
	for(int i=1; i<n; ++i) dgr[i+n]-=(int)A[n][i],dgr[des]+=(int)A[n][i], AddEdge(i+n,des,(A[n][i]-(int)A[n][i])>0);
	for(int i=1; i<n; ++i)
		for(int j=1; j<n; ++j)
			dgr[i]-=(int)A[i][j],dgr[j+n]+=(int)A[i][j], AddEdge(i,j+n,(A[i][j]-(int)A[i][j])>0);
	int SS=des+1,TT=des+2; src=SS, des=TT;
	for(int i=S; i<=T; ++i)
		if(dgr[i]>0) dgr[SS]+=dgr[i],AddEdge(SS,i,dgr[i]);
		else if(dgr[i]<0) AddEdge(i,TT,-dgr[i]);
	AddEdge(T,S,INF);
	if(ISAP()==dgr[SS]) src=S,des=T,printf("%d",3*ISAP());
	else printf("No");

	return 0;
}
