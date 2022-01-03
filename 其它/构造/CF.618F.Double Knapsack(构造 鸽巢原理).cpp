/*
421ms	23800KB
$Description$
����������СΪ$n$�Ŀ��ؼ���$A,B$�������е�Ԫ�ض���$[1,n]$�ڡ�����Ҫ�������������и�ѡһ���ǿ��Ӽ���ʹ���ǵĺ���ȡ����������
$n\leq10^6$��
$Solution$
���Ӽ��Ǽٵ�...���������ϰ�����˳�����ǰ׺�ͣ���Ϊ$SA_i,SB_i$����������$SA_n\leq SB_n$��
��ô�ܷ��֣�����ÿ��$SA_i\ (0\leq i\leq n)$���ҳ�����$SB_j\leq SA_i$��$j$��$SA_i-SB_j$��ȡֵ��Χ��$[0,n-1]$�����$\geq n$������ƶ�$j$����ֻ��$n$�֡���$i$��ȡֵ��$n+1$�֡��ɸ볲ԭ����ôһ������һ��$i,i'\ (i\neq i')$��ʹ��$SA_i-SB_j=SA_{i'}-SB_{j'}$����ΪԪ�ش���$0$������$j\neq j'$��
��ô��$SA_i-SA_{i'}=SB_j-SB_{j'}$���Ϳ��Եõ�������
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+5;

LL sa[N],sb[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Solve(const int n,LL *sa,LL *sb,int &la,int &ra,int &lb,int &rb)
{
	static int vis[N],vis2[N];
	sb[n+1]=1ll<<60;
	memset(vis,0xff,sizeof vis);
	for(int i=0,j=0,v; i<=n; ++i)
	{
		while(sb[j+1]<=sa[i]) ++j;
		if(~vis[v=sa[i]-sb[j]]) {la=vis[v], ra=i, lb=vis2[v], rb=j; break;}
		vis[v]=i, vis2[v]=j;
	}
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) sa[i]=sa[i-1]+read();
	for(int i=1; i<=n; ++i) sb[i]=sb[i-1]+read();
	int la,ra,lb,rb;
	if(sa[n]>sb[n]) Solve(n,sb,sa,lb,rb,la,ra);
	else Solve(n,sa,sb,la,ra,lb,rb);
	printf("%d\n",ra-la);
	for(int i=la+1; i<=ra; ++i) printf("%d ",i); putchar('\n');
	printf("%d\n",rb-lb);
	for(int i=lb+1; i<=rb; ++i) printf("%d ",i); putchar('\n');

	return 0;
}
