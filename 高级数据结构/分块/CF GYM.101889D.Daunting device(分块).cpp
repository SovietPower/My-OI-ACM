/*
202ms	1400KB
$Description$
$n$��λ�ã���ʼÿ��λ����ɫ��Ϊ$1$��
$m$�β�����ÿ�θ���$p,x$�����㵱ǰ�ж��ٸ�λ����ɫΪ$p$�����ô𰸼������������$[l,r]$����$[l,r]$ȾɫΪ$x$��
���������ִ���������ɫ�ĳ��ִ�����
$Solution$
���Ǳ����ֿ飬ÿ����ά��һ�����$tag_i$����$tag_i\neq 0$��ʾ��$i$��ɫ��Ϊ$tag_i$��������ɫ��ͳһ��
�޸�ʱ����$tag_i\neq 0$�Ŀ����$O(1)$����$tag$��������Ҫ$O(\sqrt n)$�������¡����µ�ʱ��$O(1)$ά��һ����ɫ���ִ���$sum$��
����һ�¸��Ӷȡ�ÿ�α������¶���ʹ$tag=0$�Ŀ��Ϊͳһ��ɫ�Ŀ飬��ÿ�β���������$2$��$tag=0$�Ŀ飬���Ա������µ��ܸ��Ӷ�Ϊ$O(2n\sqrt n)$���Ǳ��������ܸ��Ӷ�$O(n\sqrt n)$��
ע��ֿ��Ҷ˵���`min(n,bel[R]*size)`���Ҷ˵�ı߽����⣩��
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,B=316;

int n,size,A[N],sum[N],bel[N],tag[N];
int CNT=0;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Modify(int l,int r,int c)
{
	++CNT;
	for(int i=l; i<=r; ++i) --sum[A[i]], A[i]=c;
}
void Cover(int l,int r,int c)
{
	for(int i=bel[l]+1; i<bel[r]; ++i)
		if(tag[i]) sum[tag[i]]-=size, sum[c]+=size, tag[i]=c;
		else Modify((i-1)*size+1,i*size,0), sum[c]+=size, tag[i]=c;
	int L=bel[l],t=std::min(r,L*size);
	if(tag[L])
	{
		for(int i=(L-1)*size+1,x=tag[L]; i<l; ++i) A[i]=x;
		for(int i=r+1,x=tag[L],lim=L*size; i<=lim; ++i) A[i]=x;
		sum[tag[L]]-=t-l+1, sum[c]+=t-l+1;
		tag[L]=0, Modify(l,t,c);
	}
	else Modify(l,t,c), sum[c]+=t-l+1;
	int R=bel[r];
	if(L!=R)
	{
		if(tag[R])
		{
			for(int i=r+1,t=std::min(n,R*size)/*��nȡmin!!!*/,x=tag[R]; i<=t; ++i) A[i]=x;
			sum[tag[R]]-=r-(R-1)*size, sum[c]+=r-(R-1)*size;
			tag[R]=0, Modify((R-1)*size+1,r,c);
		}
		else Modify((R-1)*size+1,r,c), sum[c]+=r-(R-1)*size;
	}
}

int main()
{
	int n=read(),C=read(),m=read(); size=sqrt(n), ::n=n;
	sum[1]=n;
	for(int i=1; i<=n; ++i) bel[i]=(i-1)/size+1;
	int cnt=bel[n];
	for(int i=1; i<=cnt; ++i) tag[i]=1;
	for(; m--; )
	{
		int S=sum[read()],x=read(),A=read(),B=read(),l=(A+1ll*S*S)%n+1,r=(A+1ll*(S+B)*(S+B))%n+1;
		l>r&&(std::swap(l,r),0), Cover(l,r,x);
	}
	int ans=sum[1];
	for(int i=2; i<=C; ++i) sum[i]>ans&&(ans=sum[i]);
	printf("%d\n",ans);

	return 0;
}
