/*
77ms	2000KB
$Description$
��$S(n)$��ʾ��$S$��ʮ����λ��������������$S(324)=234$����$\sum_{i=1}^nS(i)$��
$n\leq 10^{700}$��
$Solution$
һ���򵥵�������ö��$1\sim 9$ÿ����$k$��DPʱά��$=k$��$\gt k$����λ���ж��ٸ������Ӷ���$O(100n^3)$��
�۲�һ��$S$����ʽ�����磺$112333=111111+1111+111$�����Է�����λ$1$�Ĺ�����$\begin{matrix}\underbrace{11...1}\\6��1\end{matrix}$����λ$2$�Ĺ�����$\begin{matrix}\underbrace{11...1}\\4��1\end{matrix}$...Ҳ����$k$�Ĺ�����$\begin{matrix}\underbrace{11...11}\\cnt��1\end{matrix}$������$cnt$��$\geq k$����λ������
����DPʱֻ��Ҫά��$\geq k$����λ�ж��ٸ���������������$\begin{matrix}\underbrace{11...11}\\cnt��1\end{matrix}$���ǹ��ס�
�������Ӷ�$O(100n^2)$��
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define mod 1000000007
typedef long long LL;
const int N=705;

char s[N];
int f[N][N];
LL val[N];

int DFS(int len,bool lim,int cnt,const int K)
{
	if(!lim && ~f[len][cnt]) return f[len][cnt];
	if(!len) return val[cnt];
	LL res=0;
	for(int i=0,up=lim?(s[len]-48):9; i<=up; ++i)
		res+=DFS(len-1,lim&&i==up,cnt+(i>=K),K);
	res%=mod;
	if(!lim) return f[len][cnt]=res;
	return res;
}

int main()
{
	scanf("%s",s+1); int n=strlen(s+1);
	std::reverse(s+1,s+1+n);
	int t=1;
	for(int i=1; i<=n; ++i) val[i]=t, t=(t*10ll+1)%mod;

	LL ans=0;
	for(int k=1; k<=9; ++k)
		memset(f,0xff,sizeof f), ans+=DFS(n,1,0,k);
	printf("%lld\n",ans%mod);

	return 0;
}
