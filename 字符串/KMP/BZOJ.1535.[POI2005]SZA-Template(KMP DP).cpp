/*
20760kb	320ms
$Description$
����һ���ַ���$s$����һ����̵��ַ���$t$���㣬��$t$ƴ�Ӷ�κ󣬿��Եõ�$s$��ƴ����ָ�����Խ�$t$���ڵ�ǰ��������λ�ã���Ҫ��֤��Ӧλ����ͬ������̫��˵����������...��
$|s|\leq5\times10^5$��
$Solution$
����$t$����$s$��ǰ׺Ҳ��$s$�ĺ�׺����$s$��$border$��$border$��$border$...
����$KMP$����$fail$������ô$t$��$n$�����ڵ�·���ϵ�ĳ���ڵ㡣����·���������Ľڵ��ǺϷ��ġ�
$s$���ܹ���$t$��λ��$i$���㣬$t$��$s[1...i]$��$border$����$border$��$border$...����$fail$����$i$��$t$�������ڡ���������$i$��Ҫ�������ڵ�$i$֮�������಻����$|t|$������$t$���ǺϷ��ġ�
ע�⵽�Ӹ��ڵ㵽$n$��·���У�Ҫά�������������ǵݼ��ģ�ÿ��ɾ�����ɿ������е�$i$������ôɾ��һ��λ��ʱ��������ά��������λ�õ������Ϳ����ˡ�
����һ�����򵥵�DP��������������ɣ�~~�һ����Ǻ����Ͳ�д��~~��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=5e5+5;

int fail[N],H[N],nxt[N],way[N],L[N],R[N],Max;
char s[N];

inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v;
}
void Delete(int x)
{
	L[R[x]]=L[x], R[L[x]]=R[x], Max=std::max(Max,R[x]-L[x]);
	for(int v=H[x]; v; v=nxt[v]) if(v!=way[x]) Delete(v);
}

int main()
{
	scanf("%s",s+1); int n=strlen(s+1);
	for(int i=2,j=0; i<=n; ++i)
	{
		while(j&&s[i]!=s[j+1]) j=fail[j];
		fail[i]=s[i]==s[j+1]?++j:0;
	}
	for(int i=1; i<=n; ++i) L[i]=i-1, R[i]=i+1, AE(fail[i],i);
	for(int x=n; x; x=fail[x]) way[fail[x]]=x;
	int x=0;
	for(Max=1; Max>x; x=way[x]) Delete(x);
	printf("%d\n",x);

	return 0;
}
