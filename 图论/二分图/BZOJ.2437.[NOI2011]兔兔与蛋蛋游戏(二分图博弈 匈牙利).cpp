/*
1212kb	36ms
���ȿո���ƶ��ȼ��������ںڰ׸����ƶ�������㣬������ӽ����ĸ���Ϊ��ɫ�����Ҳ����ߵ���������Ϊ�����ĺڸ񡢵�������Ϊż���İ׸�ɾ��/�����ϰ������ˣ����Ҳ����ظ���һ�����ӣ��ز�ȥ����
��Ȼ����Ծ�ͬ�����ˣ�ֻ������һ���������ӣ�
���ǿ��Ƕ���ͼ���ƥ�䡣�����㲻һ�������ƥ���ϣ������ߵ����ƥ��㣬���������ƥ����ߣ�����Ҫô�޷���Ҫô�ص��ոյ�����������ֱذܣ����ƥ����һ��������·������
��֮��������һ�������ƥ���ϣ����ֱ�ʤ��
�ж�һ�����Ƿ�һ�������ƥ���Ͽ�������һ�飬�ٶԷ�ƥ���DFS�����Ǳ����ж���ƶ����൱��ɾ��֮ǰ�ĵ��������ƥ�䡣
���ɾ���ĵ�һ�������ƥ���ϣ���ô�ƶ�ǰ���˱�ʤ��
�ж�ɾ�ĵ��Ƿ�һ�������ƥ���У����ȵ�ǰ�����ƥ���У����ɾ�������x��û���µ�����·��match[x]�Ҳ�����ƥ�䣩��
ɾ���ǵ�������ŵĵ��link����
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1605,M=N<<2;

int n,m,mp[50][50],id[50][50],Enum,H[N],nxt[M],to[M],lk[N],Time,vis[N];
bool ban[N],ans[2005];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
bool OK(int x)
{
	vis[x]=Time;
	for(int i=H[x],v; i; i=nxt[i])
		if(vis[v=to[i]]!=Time && !ban[v])
		{
			vis[v]=Time;
			if(!lk[v]||OK(lk[v])) return lk[v]=x,lk[x]=v,1;
		}
	return 0;
}

int main()
{
	n=read(),m=read(); int x=0,y=0;
	for(int i=1; i<=n; ++i)
	{
		register char c=gc();
		for(; c!='X'&&c!='O'&&c!='.'; c=gc());
		for(int j=1; j<=m; ++j,c=gc())
			if(c=='X') mp[i][j]=1;//black
			else if(c=='O') mp[i][j]=0;//white
			else x=i, y=j, mp[i][j]=1;
	}
	int f=(x+y)&1,tot=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(mp[i][j]^f^((i+j)&1))//f^is_black^(i+j)&1
				id[i][j]=++tot;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			if(!id[i][j]) continue;//!
			if(id[i+1][j]) AE(id[i][j],id[i+1][j]);
			if(id[i][j+1]) AE(id[i][j],id[i][j+1]);
		}
	for(int i=1; i<=tot; ++i) if(!lk[i]/*!*/) ++Time, OK(i);
	int K=read()<<1;
	for(int i=1,p; i<=K; ++i)
	{
		ban[p=id[x][y]]=1;
		if(lk[p]) ++Time, lk[lk[p]]=0/*��գ�*/, ans[i]=!OK(lk[p]);//(x,y)�Ƿ��Ǳ�ʤ̬ 
		x=read(), y=read();
	}
	int res=0;
	for(int i=1; i<=K; i+=2) if(ans[i]&&ans[i+1]) ++res;
	printf("%d\n",res);
	for(int i=1; i<=K; i+=2) if(ans[i]&&ans[i+1]) printf("%d\n",i+1>>1);

	return 0;
}
