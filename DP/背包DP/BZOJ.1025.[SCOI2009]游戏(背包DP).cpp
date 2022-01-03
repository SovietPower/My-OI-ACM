/*
836kb	56ms
һ������Ϊ$n$��ѭ���ڣ���$k\times n(k\geq 1)$��֮��һ����ص�ԭ����
��$a_i$��ʾÿ��ѭ����$i$�ĳ��ȣ���ô����$n$�����ֵ�����Ϊ$lcm(a_1,a_2,\cdots,a_k)(+1)$������$a_i$����$\sum_{i=1}^ka_i=n$.
������Ŀʵ�������Ϊ$n$��$k$���������ǵ�$lcm$�ж����ֿ��ܵ�ȡֵ��
��Ϊ$1$�ǲ�Ӱ��$lcm$�ģ����Ժ�ֻ��Ҫ$\leq n$(ʣ�µ���$1$���)(��Ϊ0Ҳ�Ϸ�).
��Ϊ$lcm$��ÿ����������ȡ�������ģ����Զ�ÿ�������ӿ��Էֱ��ǣ���������$p_1^{a_1}+p_2^{a_2}+\cdots+p_k^{a_k}\leq n$��$a_1,a_2,\cdots,a_k$�ж����顣
ÿ�������ӿ���һ����Ʒ������Ƕ��ر����ˡ���
���Ӷ�$O(N*N/logN*logN)=O(N^2)$.
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
	for(int i=0; i<=n; ++i) res+=f[i];//f[0]Ҳ�ǺϷ��� 
	printf("%lld",res);

	return 0;
}
