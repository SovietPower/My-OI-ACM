//15ms	0KB
//����һ�¾��С���3�ο�����mmp����д�˸����֡�
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;

LL n,m,A,B;

int main()
{
	scanf("%I64d%I64d%I64d%I64d",&n,&m,&A,&B);
	LL l=0,r=n/m+1,mid,res=1;
	while(l<=r)
		if((mid=l+r>>1)<=(double)n/m) res=mid,l=mid+1;
		else r=mid-1;
	LL ans=std::min(B*(n-res*m),A*((res+1)*m-n));
	printf("%I64d",ans);

	return 0;
}
