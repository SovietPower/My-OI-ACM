/*
46ms	600KB
$Description$
����һ������$a_i$��������ǰ׺������Ϊ$a_1\ \mathbb{mod}\ n,\ (a_1a_2)\ \mathbb{mod}\ n,...,(a_1a_2...a_n)\ \mathbb{mod}\ n$��
����$n$����һ��$n$�����У�ʹ�ø����е�ǰ׺��������$[0,1,2,...,n-1]$��һ�����С��޽����$NO$��
$n\leq10^5$��
$Solution$
�����޽���������Ϊ$n!\equiv0\ (\mathbb{mod}\ n)$������$(n-1)\not\equiv0\ (\mathbb{mod}\ n)$��
$n$Ϊ������Ȼ�������㡣������$n=pq$��
��$p\neq q$����ô��$(n-1)!\equiv0\ (\mathbb{mod}\ n)$��GG�ˡ�
��$p=q$����$n>4$ʱ��$2p<n$������Ҳ��$(n-1)!\equiv0\ (\mathbb{mod}\ n)$��GG��
����$n$Ϊ����$4$�ĺ���ʱ�޽⡣����һ��$n=4$��

����$a_1$Ҫ��$1$��$a_n$Ҫ��$n$��
�����ܲ���ֱ����ǰ׺�����б��$1,2,...,0$����ô$a_i=\frac{i}{i-1}\ \mathbb{mod}\ n,\ i>1$��
ֻ��Ҫ�ж��Ƿ���$\frac{a}{a-1}=\frac{b}{b-1},\ 1\lt a\neq b\lt n$��
��΢��һ�£�$\frac{a}{a-1}=1+\frac1a,\ \frac{b}{b-1}=1+\frac1b$��������֪��ÿ��������Ԫ��Ψһ�ģ�������ô����OK����
*/
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=1e5+5;

int A[N],inv[N];

bool IsPrime(int x)
{
	int t=0;
	for(int i=2; x!=1; ++i)
		while(!(x%i))
		{
			x/=i;
			if(++t>1) return 0;
		}
	return 1;
}

int main()
{
	int n; scanf("%d",&n);
	if(n==4) return printf("YES\n1\n3\n2\n4\n"),0;
	if(!IsPrime(n)) return puts("NO"),0;
	A[1]=1, A[n]=n, inv[1]=1;
	for(int i=2; i<n; ++i) inv[i]=1ll*(n-n/i)*inv[n%i]%n, A[i]=1ll*i*inv[i-1]%n;
	puts("YES");
	for(int i=1; i<=n; ++i) printf("%d\n",A[i]);

	return 0;
}
