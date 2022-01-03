/*
1261ms	20MB
$Description$
��$f(d)$��ʾ�ռ��е�ԭ�����Ϊ$d$���������������$L,R,k,p$����
$$\sum_{d=L}^Rf(d)\ \mathbb{xor}\ k\mod p$$

$L,R\leq 10^{13},R-L+1\leq 10^6$��

$Solution$
��Ȼ���ҹ��ɡ�[OEIS](http://oeis.org/A016725)����ֱ���ҵ����ɣ����ߴ��

$f$����$6$�ı�������$g(x)=\frac{f(x)}{6}$�����Է���$g(x)$Ϊ���Ժ�������$g(\prod p_i^{k^i})=\prod g(p_i^{k_i})$��
�г�$g(p)\ ��pΪ������$����֪������$p\%4=1$��$g(p)=p$����$p\%4=3$��$g(p)=p+2$��
�ٿ�$g(p^2)\ ��pΪ������$����֪������$p\%4=1$��$g(p^2)=p^2$����$p\%4=3$��$g(p^2)=p^2+h(p)$������$h(p)=8k$��$k$��$p$Ϊ�ڼ���$\%4=3$������![/whl](https://img2020.cnblogs.com/blog/1143196/202009/1143196-20200905001111605-807403868.png)��
������θ��õر�ʾ$h(p)$��
��OEIS���ۿɷ���$(p-1)h(p)=2(p^2-1)$����$g(p^2)=p^2+\frac{2(p^2-1)}{p-1}$���Ҹý��۶�$p^k$ͬ��������
����
$$f(p^k)=\begin{cases}1,&p=2\\p^k,&p\%4=1\\p^k+\frac{2(p^k-1)}{p-1},&p\%4=3\end{cases}$$

���$\sqrt n$���ڵ���������ÿ�����Ϳ���$O(\log n)$�ֽ����������ˡ�
���Ӷ�$O(Tn\log n)$��

PS��ע��`&`���������ȼ���`==`�͡���`&`����Ҫ�����ţ�
$ans$��͹����������$10^6$��$2\times 10^{13}$���������Ի���Ҫȡģ��
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=3162300,M=1e6+5;
const LL LIM=2e18;

int cnt,P[230000];
bool not_P[N];

inline LL read()
{
	LL now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Init(const int n)
{
	for(int i=2; i<=n; ++i)
	{
		if(!not_P[i]) P[++cnt]=i;
		for(int j=1; j<=cnt && i*P[j]<=n; ++j)
		{
			not_P[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
}
void Solve()
{
	static LL A[M],f[M];

	LL L=read(),R=read(),K=read(),mod=read(),ans=0;
	if(!L) ans+=K, ++L;
	int n=(int)(R-L+1);
	for(int i=1; i<=n; ++i) A[i]=i+L-1,f[i]=1;

	for(int i=1,lim=::cnt; i<=lim&&P[i]<=R; ++i)
	{
		int p=P[i];
		LL now=L/p*p; now<L&&(now+=p);
		for(now-=L-1; now<=n; now+=p)
		{
			LL pk=1;
			while(!(A[now]%p)) A[now]/=p, pk*=p;
			if(p==2) pk=1;
			else if((p&3)==3) pk+=2*(pk-1)/(p-1);
			f[now]*=pk;
		}
	}
	for(int i=1; i<=n; ++i)
	{
		if((A[i]&3)==3) f[i]*=(A[i]+2);//����/ʣ��Ϊ������ 
		else f[i]*=A[i];
		ans+=((f[i]*6)^K)%mod;
		ans>=LIM&&(ans%=mod);//ȡģ�� 
	}
	printf("%lld\n",ans%mod);
}

int main()
{
	Init(N-2);
	for(int T=read(); T--; Solve());

	return 0;
}
