/*
$Description$
����$n$����$m$���ߵ�����ͼ�����ж��ٸ��߼����Ӽ������ɵ�ͼû�л���
$n\leq17$��
$Solution$
����Ҳ�ȼ��ڣ��ò�ͬ�ı߼�����DAG���ж����ֺϷ����������ǿ�����ô����DAGʹ�÷������ز�©��
����֪��һ��DAG����������Ψһȷ���ġ��������ǰ���������ÿ��ת��һ���㼯��
$f[s][s']$��ʾ ���� �Ѿ�ѡ��ĵ㼯Ϊs����ǰ���һ��㼯Ϊs'��DAG �ķ�������
ת��ʱö�ٲ���s�е��Ӽ�k��k�Ϸ�����Ҫ����s'��k�����е��бߡ�
Ȼ����s^s'��k��ĳ���������$cnt1_i$����s'��k�иõ��������$cnt2_i$������õ�ĺϷ�������Ϊ$2^{cnt1_i}*(2^{cnt2_i}-1)$��
$f[s|k][k]=��f[s][s']*��2^{cnt1_i}*(2^{cnt2_i}-1)$��
���Ӷ�$O(4^n*m)$��
���Ǽ����ڶ�ά��ֱ��ö�ٵ�ǰ�㼯i��Ȼ��ö�ٲ������Ӽ�j��ֻҪ���ǰ������ڵ���ܱ�֤��DAG��
i,j֮����Բ����ڱߣ���i����j�ı���cnt������$f[i|j]+=f[i]*2^j$��
��Ȼû��ô�򵥡����׷���i|j�����ɺܶ���i,j���ɡ����ԼӸ��ݳ⣬�ݳ�ϵ����(-1)^{sz[j]+1}��
���Ǻܶ�����ݳ�ϵ�������Ǽ�1�����Ȼ���ȥ���������������...��
���Ӷ�$O(3^nm)$�������Ż���$O(3^n+2^nm)$�������ˣ���
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define In(x,s) (s>>x&1)
#define gc() getchar()
#define mod 1000000007
const int N=20,S=(1<<17)+3;

int n,m,pw[N*N],mp[N][N],num[N][S],f[S];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Calc(int s)
{
	int res=0;
	for(; s; s>>=1) res+=s&1;
	return res;
}

int main()
{
	n=read(),m=read();
	pw[0]=1;
	for(int i=1; i<=m; ++i) pw[i]=pw[i-1]<<1, pw[i]>=mod&&(pw[i]-=mod);
	for(int i=1; i<=m; ++i) mp[read()-1][read()-1]=1;
	int all=(1<<n)-1;
	for(int s=0; s<=all; ++s)
		for(int v=0; v<n; ++v)
			if(In(v,s))
				for(int x=0; x<n; ++x) num[x][s]+=mp[x][v];
	f[0]=1;
	for(int i=0; i<=all; ++i)
	{
		if(!f[i]) continue;
		int rest=all^i;
		for(int j=rest; j; j=(j-1)&rest)
		{
			int sz=Calc(j), cnt=0;
			for(int k=0; k<n; ++k)
				if(In(k,i)) cnt+=num[k][j];
			if(sz&1) f[i|j]+=1ll*f[i]*pw[cnt]%mod, f[i|j]>=mod&&(f[i|j]-=mod);
			else f[i|j]-=1ll*f[i]*pw[cnt]%mod-mod, f[i|j]>=mod&&(f[i|j]-=mod);
		}
	}
	printf("%d\n",f[all]);

	return 0;
}
