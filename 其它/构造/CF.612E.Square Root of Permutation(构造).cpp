/*
249ms	21300KB
$Description$
����һ��$n$������$p_i$����һ������$q_i$��ʹ�ö�������$1\leq i\leq n$��$q_{q_i}=p_i$���޽����$-1$��
$1\leq n\leq10^6$��
$Solution$
������$q_i$���ǽ�һ��ͼ����Ϊ$i\to q_i$����Ȼ����ͼ���ɼ��������ɡ�
���ֶ���$q_{q_i}$��ͼ��ԭ��$q_i$�е��滷���ǻ������Ƶ�һ���滷��ԭ����ż������ѳ�������С��ȵ�ż����
���Զ�$p_i$��ͼ���ҳ�����Ļ������滷�Ͱ����ڵ���Ϊ$2$�ز��뵽�����ż�����ҵ�����һ�����һ���ϲ����Ҳ������޽⡣�����Ϳ��Եõ�$q_i$��ͼ�ˡ���ÿ��ż��ֻ�ܺϲ�һ�Ρ�_����
���Ӷ�$O(n)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+5;

int nxt[N],q[N],tmp[N],tmp2[N],id[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) nxt[i]=read();
	for(int s=1; s<=n; ++s)
		if(!vis[s])
		{
			int cnt=0,x=s;
			do
			{
				tmp[++cnt]=x, vis[x]=1, x=nxt[x];
			}while(x!=s);
			if(cnt&1)
			{
				for(int i=1,now=0; i<=cnt; ++i,(now+=2)>=cnt&&(now-=cnt)) tmp2[now]=tmp[i];
				for(int i=0; i<cnt; ++i) q[tmp2[i]]=tmp2[i+1];
				q[tmp2[cnt-1]]=tmp2[0];
			}
			else
			{
				if(!id[cnt]) id[cnt]=s;
				else
				{
					int y=id[cnt],x=y,t=0;
					do
					{
						tmp2[++t]=x, x=nxt[x];
					}while(x!=y);
					for(int t1=1,t2=1,las=tmp[1],i=t<<1; i; --i)
						las=q[las]=i&1?tmp[++t1]:tmp2[t2++];
					q[tmp2[t]]=tmp[1], id[t]=0;
				}
			}
		}
	for(int i=2; i<=n; i+=2) if(id[i]) return puts("-1"),0;
	for(int i=1; i<=n; ++i) printf("%d ",q[i]);

	return 0;
}
