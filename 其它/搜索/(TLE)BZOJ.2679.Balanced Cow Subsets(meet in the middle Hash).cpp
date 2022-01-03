/*
89344kb	7060ms
$Description$
����$n$����$A_i$�������ж��ٸ��Ӽ��������ܱ�����Ϊ��������ȵļ��ϡ�
$n\leq 20,1\leq A_i\leq10^8$��
$Solution$
��Ȼ����ҪԤ������Щ���Ͽ��Ա�����Ϊ��������ȵļ��ϡ�ÿ��Ԫ������״̬���������ǾͿ��Եõ�һ��$O(3^n)$����������
��Ȼ���а������Ǻ�������ֶ��������۰밡��
�����зֳ�����ֿ�DFS��������������ȵļ���$S_1,S_2$�е�Ԫ�ؿ��ܻᱻ�ֿ�����$a$Ϊ$S_1$��ǰһ�������е�Ԫ�صĺͣ�$b$Ϊ$S_1$�ں�һ�������е�Ԫ�صĺͣ�$c,d$�ֱ�Ϊ$S_2$��ǰһ��/��һ��������Ԫ�صĺ͡���ô��$a+b=c+d\to a-c=d-b$����������ͳ��������������Щ$a-c$��ȵļ��ϾͿ����ˡ�
��Ϊ$a-c$�ļ��Ͽ����ж����ֱ��$Hash/map+vector$��һ������Щ���ϾͿ����ˣ����⼯�Ͽ���ֱ�Ӷ�����״ѹ����
���Ӷ��ǲ��ǻ��ᱻ����$O(6^{\frac n2})$��������SPOJ��T�ˣ����ܹ�BZOJ��
��ʵ�ϲ�״̬����sort�����Ժϲ����Ϳ�ܶ��ˡ������԰����о����ӶȲ�డ==����hashд̫���ˣ���
��Ȼ��Ҳ�������⣬���и���ģ����磺https://blog.csdn.net/u014609452/article/details/51872702
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 20000000
typedef long long LL;
const int N=61005;//Ϊɶ60005��BZOJ��RE�����Բ�ɹ���

int n,mid,A[23];
bool vis[(1<<20)+5];
struct Hash_Table
{
	int delta,Enum,H[mod+2],nxt[N],s[N]; LL sum[N];//���ܳ�ͻ �ٴ�һ��sum 
	inline void Insert(int S,LL Sum)
	{//ע��Ϳ����Ǹ��ġ�������һ��mod���ͺ���==��
		int x=(Sum+delta)%mod;
		s[++Enum]=S, sum[Enum]=Sum, nxt[Enum]=H[x], H[x]=Enum;
	}
	inline void Solve(int S,LL Sum)
	{
		int x=(Sum+delta)%mod;
		for(int i=H[x]; i; i=nxt[i])
			if(sum[i]==Sum) vis[S|s[i]]=1;
	}
}hs;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void DFS1(int x,int s,LL sum)
{
	if(x==mid) {hs.Insert(s,sum); return;}
	DFS1(x+1,s,sum), DFS1(x+1,s|(1<<x),sum+A[x]), DFS1(x+1,s|(1<<x),sum-A[x]);
}
void DFS2(int x,int s,LL sum)
{
	if(x==n) {hs.Solve(s,sum); return;}
	DFS2(x+1,s,sum), DFS2(x+1,s|(1<<x),sum+A[x]), DFS2(x+1,s|(1<<x),sum-A[x]);
}

int main()
{
	n=read(),mid=n>>1; int s=0;
	for(int i=0; i<n; ++i) s+=A[i]=read();
	hs.delta=s, DFS1(0,0,0), DFS2(mid,0,0);
	int ans=0;
	for(int i=1,l=1<<n; i<l; ++i) ans+=vis[i];//ͬһ�����ϻ����ذ� 
	printf("%d\n",ans);

	return 0;
}
