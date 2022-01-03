/*
��С������һ���ߣ����ִ𰸡�Ȼ��ͱ���˸�һ������ͼ����ʹ��Ϊŷ����· 
���ִ𰸺����һ��λ�õ������߿��ܶ���������˫��ߣ���Ҫ�������򣻿���ֻ����С��һ����������ߣ����迼�� 
��θ��������أ�����˵��ô�γ�ŷ����·�� 
�γ�ŷ����·�ĳ�Ҫ����������ͨͼ��ÿ�������=��� 
�ǵ�i�Ķ��� dgr[i]=out[i]-in[i] 
����һ������ȷ���ı�(u,v)������ı����ķ��򣬻�ʹdgr[u]-=2,dgr[v]+=2��Ҳ����˵u��2�����������v 
����in[x]!=out[x]�ĵ㶼Ҫͨ���ı�ĳЩ�߷�������in[x]==out[x] 
���������ͼ�Ͳ�˵�� 
�տ�ʼʱ��һ������߱���һ��������Ļ��ᣬ��㶨���򣬾�ȨֵС�İ� 

ע�������ÿ��u,v���ı�1�ģ�����ʱdgr/2 
�����ĳ��������֮��Ϊ�������򲻿����γ�ŷ����· 
ISAP��ʼ���������ֵҪ��des+1...
����TLE(Dinic)ԭ����MС��...mmp..
����WA(ISAP)�����Ҳ���ԭ��...
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define gc() getchar()
const int N=1005,M=2005+2*N,INF=1e9;

int n,m,src,des,dgr[N],u[M],v[M],A[M],B[M];
int Enum,cur[N],H[N],nxt[M<<1],fr[M<<1],to[M<<1],cap[M<<1],lev[N],q[N],path[N],num[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], cap[Enum]=w, H[u]=Enum;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], cap[Enum]=0, H[v]=Enum;
}
int Rebuild(int x)
{
	Enum=1, memset(H,0,sizeof H), memset(dgr,0,sizeof dgr);
	for(int i=1;i<=m;++i)
	{
		if(A[i]<=x) ++dgr[u[i]],--dgr[v[i]];//ѡ����Ϊ����߻���ѡ��������� ��ı�Ķ�������1��
		if(B[i]<=x) AddEdge(u[i],v[i],1);//��u->v���Ը���1���� 
	}
	int tot=0;
	for(int i=1;i<=n;++i)
		if(dgr[i]>0) AddEdge(src,i,dgr[i]>>1),tot+=dgr[i]>>1;
		else if(dgr[i]<0) AddEdge(i,des,-dgr[i]>>1);
	return tot;//���ز�ƽ��Ķ��� 
}
bool BFS()
{
	for(int i=src;i<=des;++i) lev[i]=des+1,cur[i]=H[i];
	q[0]=des, lev[des]=0;
	int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(lev[to[i]]==des+1 && cap[i^1])//i^1
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[src]<=des;
}
int Augment()
{
	int mn=INF;
	for(int i=des;i!=src;i=fr[path[i]])
		mn=std::min(mn,cap[path[i]]);
	for(int i=des;i!=src;i=fr[path[i]])
		cap[path[i]]-=mn, cap[path[i]^1]+=mn;
	return mn;
}
int ISAP()
{
	if(!BFS()) return -1;
	memset(num,0,sizeof num);//mmp
	for(int i=src;i<=des;++i) ++num[lev[i]];
	int x=src,flow=0;
	while(lev[src]<=des)
	{
		if(x==des) flow+=Augment(),x=src;
		bool can=0;
		for(int i=cur[x];i;i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, path[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=des;
			for(int i=H[x];i;i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x!=src) x=fr[path[x]];
		}
	}
	return flow;
}
int MF()
{
	for(int i=1;i<=n;++i)
		if(dgr[i]&1) return -1;//����ж���Ϊ1�ĵ㣬�򲻿����γ�ŷ����· 
	return ISAP();
}

int main()
{
	n=read(),m=read(),src=0,des=n+1;
	int mx=0,mn=INF;
	for(int i=1;i<=m;++i)
	{
		u[i]=read(),v[i]=read(),A[i]=read(),B[i]=read();
		if(A[i]>B[i]) std::swap(A[i],B[i]),std::swap(u[i],v[i]);//��A����С�ıߣ������Ҳ�϶��ǽ�С�ı߰� 
		mn=std::min(mn,A[i]), mx=std::max(mx,B[i]);
	}
	int l=mn,r=mx+1,mid;
	while(l<r)
	{
		mid=l+r>>1;
		if(Rebuild(mid)==MF()) r=mid;
		else l=mid+1;
	}
	if(l==mx+1) printf("NIE");
	else printf("%d",l);

    return 0;
}
