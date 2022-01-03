/*
836kb	56ms
一个长度为$n$的循环节，在$k\times n(k\geq 1)$次之后一定会回到原样。
用$a_i$表示每个循环节$i$的长度，那么所有$n$个数字的排数为$lcm(a_1,a_2,\cdots,a_k)(+1)$，其中$a_i$满足$\sum_{i=1}^ka_i=n$.
所以题目实际在求和为$n$的$k$个数，它们的$lcm$有多少种可能的取值。
因为$1$是不影响$lcm$的，所以和只需要$\leq n$(剩下的用$1$填充)(和为0也合法).
因为$lcm$中每个质因子是取次数最大的，所以对每个质因子可以分别考虑，即求满足$p_1^{a_1}+p_2^{a_2}+\cdots+p_k^{a_k}\leq n$的$a_1,a_2,\cdots,a_k$有多少组。
每个质因子看做一个物品，这就是多重背包了。。
复杂度$O(N*N/logN*logN)=O(N^2)$.
*/
#include <cstdio>
const int N=1005;

int n,cnt,P[N];
long long f[N];
bool Not_P[N];

void Make_Table()
{
	for(int i=2; i<=n; ++i)
	{
		if(!Not_P[i]) P[++cnt]=i;
		for(int j=1; j<=cnt&&i*P[j]<=n; ++j)
		{
			Not_P[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
}

int main()
{
	scanf("%d",&n);
	Make_Table();
	f[0]=1;
	for(int i=1; i<=cnt; ++i)//f[i][j]=\sum f[i-1][j-k*P[i]]
		for(int j=n; j>=P[i]; --j)
			for(int k=P[i]; k<=j/*not n..*/; k*=P[i]) f[j]+=f[j-k];
	long long res=0;
	for(int i=0; i<=n; ++i) res+=f[i];//f[0]也是合法的 
	printf("%lld",res);

	return 0;
}
