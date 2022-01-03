/*
93MS	3004K
$Description$
��$[l,r]$���ж��ٸ�����������������ÿһλ�Ӹ�λ����λд��������LIS����Ϊ$k$��
$l,r\leq 2^{63}-2,\ k\leq 10$��
$Solution$
��λDP��������ô��LIS����Ϊֻ��10���������Կ��Բ���O(nlogn)��LIS�ķ�����״ѹ��¼״̬��
ÿ�μ�һ��������LISһ������״̬�����״̬��1�ĸ�������LIS�ĳ��ȡ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=(1<<10)+3;

int K,bit[21];
LL f[21][N][12];//f[i][j][k] ��ǰ��iλ ״̬Ϊj KΪk(������Ա���) 
bool vis[21][N][12];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Count(int x)
{
	int res=0;
	for(; x; res+=x&1,x>>=1);
	return res;
}
inline int Upd(int s,int x)//�滻����һ��>=x��λ 
{
	for(int i=x; i<10; ++i)
		if(s>>i&1) return (s^(1<<i))|(1<<x);
	return s|(1<<x);
}
LL DFS(int x,bool lim,bool lead,int s)
{
	if(!x) return Count(s)==K;
	if(!lim && vis[x][s][K]) return f[x][s][K];//������ǰ����Ҳ�ǿ���ֱ�ӷ��ذ�(����s״̬û���ûӰ��) 

	LL res=0; int up=lim?bit[x]:9;
	for(int i=0; i<=up; ++i)
		res+=DFS(x-1,lim&&i==up,lead&&!i,(lead&&!i)?0:Upd(s,i));

	if(!lim) vis[x][s][K]=1, f[x][s][K]=res;
	return res;
}
LL Calc(LL x)
{
	int cnt=0;
	for(; x; x/=10) bit[++cnt]=x%10;
	if(cnt<K) return 0;
	return DFS(cnt,1,1,0);
}
inline LL Solve()
{
	LL l=read(),r=read(); K=read();
	return Calc(r)-Calc(l-1);
}

int main()
{
	for(int i=1,T=read(); i<=T; printf("Case #%d: %lld\n",i++,Solve()));
	return 0;
}
