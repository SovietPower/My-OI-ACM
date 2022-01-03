/*
93MS	11940K
$Description$
����$n$����$m$���ߵ�����ͼ�����Ƿ����һ������Ϊ����/ż���ļ򵥻���n<=1e5,m<=3e5��
$Solution$
�����뵽DFSʱֱ�Ӻڰ�Ⱦɫ������ֻ��������©һ��ż����
�����滷�ڰ�Ⱦɫ���ɣ�����ͼһ���������滷�������滷һ�����Ƕ���ͼ��
����ż������Ϊ�����滷���������һ�������㣬���Ƕ�ȥ���������ֺ���ż������ͬ���ͻ��γ�ż����
���Զ����滷�����ڵ��ϴ��Ǽ��ɡ�
Ҳ����Tarjan��ÿ��˫��ͨ������ֻ�������˫��ͨ��������һ���滷ʱ�����в�����ż����
�����и���ʱҪ��p!=0����ѭ����why��
*/
//#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,M=6e5+5;

int Enum,H[N],nxt[M],to[M],vis[N],fa[N];
bool odd,even,tag[N];
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
void DFS(int x)
{
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			if(vis[v]==-1) fa[v]=x, vis[v]=vis[x]^1, DFS(v);
			else if(vis[x]^vis[v]) even=1;
			else
			{
				odd=1; int p=x;
				while(!even && p!=v && p)//p!=0???
				{
					if(tag[p]) even=1;
					tag[p]=1, p=fa[p];
				}
//				if(tag[v]) even=1;//������ĵ�...����ν�ˣ�
//				else tag[v]=1;
			}
		}
}
void Work()
{
	odd=even=Enum=0, memset(H,0,sizeof H);
	memset(vis,0xff,sizeof vis), memset(tag,0,sizeof tag);

	int n=read(),m=read();
	while(m--) AE(read(),read());
	for(int i=1; i<=n&&(!odd||!even); ++i)
		if(vis[i]==-1) vis[i]=fa[i]=0, DFS(i);
	puts(odd?"YES":"NO"), puts(even?"YES":"NO");
}

int main()
{
	for(int T=read(); T--; Work());
	return 0;
}
