/*
1112kb	728ms
$Description$
����$n$����$m$���ߵ�����ͼ����ȨΪ1������õ������޻�ͼ��ʹ���·��̡�
$n\leq 15,\ m\leq 100$
$Solution$
DAG�У�����$Dilworth$������ $�����=��С������$��Ҳ�� $���=��С����������-1$���������̵�����������������е㻮�ֳ����ٵļ��ϣ�ʹ�ü����ڵĵ�����֮��û�бߡ�
ֱ��״ѹ����$f[s]$��ʾ$s$�����ڵĵ��Ƿ���������֮��û�бߣ�$g[s]$��ʾ���ٿ��Խ�$s$����Ϊ��������ʹ�ü���������û�бߡ�
��ô���$f[s']=1\ (s'\in s)$��$g[s]=\min(g[s],\ g[s\ \text{xor}\ s']+1)$��
���Ӷ�$O(m2^n+3^n)$��
~~��ô������Ҫ���Ǹ��߶���= =
��һ������Ӧ��$Dilworth$����ĺ����ǵ����������⣿~~
��������¸�����֮�󣬲���BZOJ4145һ����=v=
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lb(x) (x&-x)
const int N=15,M=(1<<N)+1;

int g[M],id[233],ref[M];
bool mp[N][N],f[M];

int main()
{
	char s1[3],s2[3];
	memset(id,0xff,sizeof id);
	int n=0,m; scanf("%d",&m);
	for(int p1,p2; m--; )
	{
		scanf("%s%s",s1,s2);
		if(id[p1=s1[0]]==-1) id[p1]=n++;
		if(id[p2=s2[0]]==-1) id[p2]=n++;
		mp[id[p1]][id[p2]]=1, mp[id[p2]][id[p1]]=1;
	}
	int lim=(1<<n)-1;
	for(int i=0; i<n; ++i) ref[1<<i]=i;
	for(int s=0; s<=lim; ++s)
	{
		f[s]=1;
		for(int s1=s; s1&&f[s]; s1^=lb(s1))
			for(int s2=s,i=ref[lb(s1)]; s2; s2^=lb(s2))
				if(mp[i][ref[lb(s2)]]) {f[s]=0; break;}
	}
	g[0]=0;
	for(int s=1; s<=lim; ++s)
	{
		int tmp=1<<30;
		for(int ss=s; ss; ss=(ss-1)&s)
			if(f[ss]) tmp=std::min(tmp,g[s^ss]+1);
		g[s]=tmp;
	}
	printf("%d\n",g[lim]-2);

	return 0;
}
