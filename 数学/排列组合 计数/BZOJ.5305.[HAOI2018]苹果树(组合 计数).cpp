/*
16540kb	196ms
���ȣ�$n=1$ʱ��$2$��λ�÷�Ҷ�ӣ�$n=2$ʱ��$3$��... ��֪$n$������б�Ŷ�������$n!$�֡���һ�������������������Ψһ�ģ���$n!$�֣�Ҳ���Եõ�������ۣ�

$Sol1$
���Ƕ�ÿ�������ߵĵ㼯���㹱�ס�����һ����һ����$size$���㣬��һ����$n-size$���㣬��ô���Ĺ�����$size(n-size)$��
ֱ�Ӱѱ߷ŵ����ϣ�ö��ÿ����$i$���߾���$i\to fa[i]$������ö��$size_i$��$size_i$����$i$�����Ĵ�С��
���Ǵ�ʱ�ķ�������$i$������$i$�������Ƕ����ġ�
����$i$��������$size_i!$��������̬������ŷ�����$C_{n-i}^{size_i-1}$�ַ�����$i$�����ڵ�ı��Ҫ$\geq i$��������$i$������$size_i!\times C_{n-i}^{size_i-1}$�֡�
����$i$�����ⲿ�����ȹ����$i$���������$i!$�ַ�����Ȼ����$n-i-size_i+1$������Ҫ����$i$�����������λ�ã���������$(i+1-2)(i+2-2)...(i+n-i-size_i+1-2)$������������������$i(i-1)(n-size_i-1)!$��
��ô�𰸾���$$\sum_{i=2}^n\sum_{size_i=1}^{n-i+1}size_i(n-size_i)size_i!\cdot C_{n-i}^{size_i-1}\cdot i(i-1)(n-size_i-1)!$$

$Sol2$
���ơ�������ö�ٴ�СΪ$L,R$�����������������õ�$L+R+1$�����������ô֪����ȾͿ���������������ľ����ˡ�
��$f[i]$��ʾ$i$���ڵ����������$i!$�ֿ����У����е���ȵĺͣ����ڵ����Ϊ$1$����
��$g[i]$��ʾ$i$���ڵ����������$i!$�ֿ����У����е�����֮��ľ���ĺ͡�
ת�Ƶ�ʱ��ö�����������Ĵ�С$L,R=i-L-1$����$$\begin{aligned}f[i]&=i*i!+\sum_{L=0}^{i-1}C_{i-1}^L(f[L]*R!+f[R]*L!)\\g[i]&=\sum_{L=0}^{i-1}C_{i-1}^L(g[L]*R!+g[R]*L!+f[L]*R!*(R+1)+f[R]*L!*(L+1))\end{aligned}$$

����$g[n]$���Ǵ�����
*/
#include <cstdio>
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=2005;
const LL LIM=1ll<<61;

int C[N][N],fac[N],g[N];

int main()
{
	int n,mod; scanf("%d%d",&n,&mod);
	C[0][0]=fac[0]=fac[1]=1;
	for(int i=2; i<=n; ++i) fac[i]=1ll*i*fac[i-1]%mod;
	for(int i=1; i<=n; ++i)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; ++j) C[i][j]=C[i-1][j-1]+C[i-1][j], Mod(C[i][j]);
	}
	for(int i=1; i<=n; ++i) g[i]=1ll*i*(n-i)*fac[n-i-1]%mod*fac[i]%mod;
	LL ans=0;
	for(int i=2; i<=n; ++i)
		for(int sz=n-i+1,tmp=i*(i-1); sz; --sz)
			if((ans+=1ll*C[n-i][sz-1]*g[sz]%mod*tmp)>=LIM) ans%=mod;
	printf("%lld\n",ans%mod);

	return 0;
}
