#include <cstdio>
typedef long long LL;

int n,m;
LL k;

int main()
{
	scanf("%d%d%I64d",&n,&m,&k), ++k;
	if(k<=n) {printf("%d 1",k); return 0;}
	else k-=n+1, --m;
	LL tmp=k%m,tmp2=k/m;
//	printf("%I64d %I64d %I64d\n",k,tmp,tmp2);
	LL row=n-tmp2,col;
	if(tmp2&1) col=m-tmp+1;
	else col=tmp+2;
	printf("%I64d %I64d",row,col);

	return 0;
}
