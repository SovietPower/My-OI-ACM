/*
4884kb	9220ms
$Description$
����һ��n���������ͼ������������֮�����ҽ�һ������ߡ�����ÿ����v�������v������һ������������࣬��û���ظ�����ͬһ����һ�����ϵļ�·����
n<=2000
$Solution$
����ͼ�����õ�������ͼһ����һ��������Ϊ����ͼ��������ǰ���ϵȷ��������ֻ��һ���������� 
��ǰ��ǿ��ͨ�����е�����һ����� �����Ե�����ǿ��ͨ����������һ�� 
��Ϊ����ͼ��ÿ��ǿ��ͨ����һ������һ�����ܶٻ�· 
����ֻ��Ҫ���ÿһ��ǿ��ͨ�����Ĺ��ܶٻ�·��Ȼ���������ߣ���ÿ��ǿ��ͨ�����Ļ�·�������У����������Ӻ���ǰ������� 
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define gc() getchar()
const int N=2005;

int n,dfn[N],low[N],id,cnt,bel[N],sk[N],top,nxt[N],dgr[N],pos[N];
bool mp[N][N],ins[N];
std::vector<int> scc[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Tarjan(int x)
{
	dfn[x]=low[x]=++id, sk[++top]=x, ins[x]=1;
	for(int i=1; i<=n; ++i)
		if(mp[x][i])
			if(!dfn[i]) Tarjan(i),low[x]=std::min(low[x],low[i]);
			else if(ins[i]) low[x]=std::min(low[x],dfn[i]);
			else ;//
	if(low[x]==dfn[x])
	{
		++cnt;
		do{
			bel[sk[top]]=cnt, ins[sk[top]]=0, scc[cnt].push_back(sk[top]);
		}while(x!=sk[top--]);
	}
}
inline bool cmp(const int &a,const int &b){
	return dgr[a]<dgr[b];
}
void Insert(int x)
{
	sk[++top]=x;
	for(int i=nxt[x]; i/*necessary(���ڵ���һ����)*/&&i!=x; i=nxt[i]) sk[++top]=i;
}

int main()
{
	n=read();
	for(int i=2; i<=n; ++i)
		for(int j=1; j<i; ++j)
			mp[j][i]=read(), mp[i][j]=mp[j][i]^1;
	for(int i=1; i<=n; ++i)
		if(!dfn[i]) Tarjan(i);
	for(int l,r,sz,i=1; i<=cnt; ++i)
	{
		l=r=scc[i][0], sz=scc[i].size();
		for(int tmp,j=1; j<sz; ++j)//��1���㿪ʼ ��չ�ɹ��ܶ�·�� 
		{
			tmp=scc[i][j];
			if(mp[tmp][l]) nxt[tmp]=l, l=tmp;
			else if(mp[r][tmp]) nxt[r]=tmp, r=tmp;
			else
			{
				for(int k=l; nxt[k]; k=nxt[k])
					if(mp[k][tmp]&&mp[tmp][nxt[k]])//�ڵ�ǰ·������ ����tmpͬʱtmp�������߽ڵ�� 
					{
						nxt[tmp]=nxt[k], nxt[k]=tmp;
						break;
					}
			}
		}
		r=0;
		for(int j=l; j; j=nxt[j])
			if(r)
			{
				for(int k=r,las=l; ; las=k,k=nxt[k])
				{
					if(mp[j][k])
					{
						nxt[las]=nxt[l];
						if(las!=l) nxt[l]=r;
						r=k, l=j;
						break;
					}
					if(k==l) break;
				}
			}
			else if(mp[j][l]) r=l, l=j;
		nxt[l]=r;
	}
	for(int i=1; i<=n; ++i)//��ÿ��ǿ��ͨ������������ 
		for(int j=1; j<=n; ++j)
			if(bel[i]!=bel[j]&&mp[i][j]) ++dgr[bel[j]];
	for(int i=1; i<=cnt; ++i) pos[i]=i, dgr[i]/=scc[i].size();
	//����Ҫ����size ��Ϊ����ǿ��ͨ����i�ĵ������i�����е�(����ͼ) ����ʱ������Ҫ��ǿ��ͨ������������� 
	std::sort(pos+1,pos+1+cnt,cmp);
	for(int i=1; i<=n; ++i)
	{
		top=0, Insert(i);//ֱ�Ӽ���i���ǿ��ͨ�������ɣ���һ���·��Ȼ���ٴ��յ��ߵ���һ��ǿ��ͨ���� 
		//bel[i]��ÿ����һ���������ߵ���һ��ǿ��ͨ����j������bel[i]��j�ͳ��˻�(ͬһ��ǿ��ͨ����)�� 
		for(int j=1; j<=cnt; ++j)//�������������scc(·��) 
			if(dgr[pos[j]]>dgr[bel[i]])
				Insert(scc[pos[j]][0]);
		printf("%d ",top);
		for(int i=1; i<top; ++i) printf("%d ",sk[i]);
		printf("%d\n",sk[top]);
	}
	return 0;
}
