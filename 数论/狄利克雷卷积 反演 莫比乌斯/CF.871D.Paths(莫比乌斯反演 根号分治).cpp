/*
296ms	161300KB
$Description$
����$n$����ʾ��һ��$n$���������ͼ��������$x,y$֮����ȨֵΪ$1$�ıߵ��ҽ���$\gcd(x,y)\neq1$����$1\sim n$��������֮������·���ȵĺ��Ƕ��١������㲻��ͨ���·����Ϊ$0$��
$n\leq10^7$��
$Solution$
���忴[����](https://www.cnblogs.com/bestFy/p/10423989.html)�ɣ�ǰ��Ҳͦ��Ҫ����~~������~~�ͼ򵥼�һ���ˡ�
�ȷ�������һ�£�Ȼ���$mn_x$Ϊ$x$����С�����ӣ���Ҫ������������$$\sum_{x,y}[\gcd(x,y)=1][mn_x\times mn_y\leq n]$$

����һ�£���Ȼ�������ʽ�������Ҫ����$2$����$$\begin{aligned}��ʽ&=\sum_{d=1}^n\mu(d)\sum_{d\mid x}\sum_{d\mid y}[mn_x\times mn_y\leq n]\\&=\sum_{x=1}^n\sum_{y=1}^n[mn_x\times mn_y\leq n]+\sum_{d=2}^n\mu(d)\sum_{d|x}\sum_{d|y}[mn_x\times mn_y\leq n]\end{aligned}$$

ǰ�沿�ֿ���ֱ���ø�ͰȻ��ǰ׺��һ�¡����ں���Ĳ��֣����ǿ��ǣ�
1. $d\leq\sqrt n$ʱ����Ϊ$d\mid x$��������$mn_x\leq mn_d$����һ����$mn_x\times mn_y\leq n$����ô�Ϸ���������$\lfloor\frac nd\rfloor^2$��
2. $d>\sqrt n$ʱ����$x=k_1d,y=k_2d$����ô��$k_1,k_2\leq\sqrt n$��$k_1,k_2\neq1$ʱ��$k_1\times k_2\leq n$��Ȼ�Ϸ���
$k$��һ����$1$ʱ��������$k_2$��$mn_x\times mn_y$����$k_1d=x$����ȻҲ��$\leq n$��
$k_1=k_2=1$ʱ����$d$������������ô$d$һ������һ������$\leq\sqrt n$����ôҲ��$mn_x\times mn_y=mn_d^2\leq n$��
���Ե��ҽ���$k_1=k_2=1$��$d$Ϊ����ʱ��$(x,y)$���Ϸ�����ô�Ϸ�����������$\lfloor\frac nd\rfloor^2$-1��

��ôö��$d$�Ϳ������������
*/
#include <cmath>
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=1e7+5;

int P[N>>3],phi[N],mu[N],mn[N],cnt[N];

void Init(const int n)
{
	phi[1]=mu[1]=1;
	for(int i=2,cnt=0; i<=n; ++i)
	{
		if(!mn[i]) P[++cnt]=mn[i]=i, phi[i]=i-1, mu[i]=-1;
		for(int j=1,v; j<=cnt&&(v=i*P[j])<=n; ++j)
		{
			mn[v]=P[j];
			if(i%P[j]) phi[v]=phi[i]*(P[j]-1), mu[v]=-mu[i];
			else {phi[v]=phi[i]*P[j], mu[v]=0; break;}
		}
	}
}

int main()
{
	int n; scanf("%d",&n); Init(n);
	LL ans=0,t2=0,t3=0,tot=0;
	for(int i=2,half=n>>1; i<=n; ++i) if(mn[i]!=i||i<=half) ++tot, t2+=i-1-phi[i], ++cnt[mn[i]];
	tot=tot*(tot-1)>>1;//�ܺϷ����� 
	for(int i=2; i<=n; ++i) cnt[i]+=cnt[i-1];
	for(int i=2,half=n>>1; i<=n; ++i) if(mn[i]!=i||i<=half) t3+=cnt[n/mn[i]];
	for(int d=2,m=sqrt(n); d<=n; ++d)
	{
		LL tmp=1ll*(n/d)*(n/d);
		if(d>m&&mn[d]==d) --tmp;
		t3+=mu[d]*tmp;
	}
	t3>>=1, ans+=t2+(t3<<1)+(tot-t2-t3)*3;
	printf("%I64d\n",ans);

	return 0;
}
