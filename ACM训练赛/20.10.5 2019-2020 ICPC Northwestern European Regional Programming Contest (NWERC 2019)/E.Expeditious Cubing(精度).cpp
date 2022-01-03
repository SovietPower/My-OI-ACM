/*
题很简单，但是 卡精度（绝了）。
读入时要将数乘100变为整数，不能读double再乘（迷之存储），写个`Read()`或`scanf("%d.%d",&x,&y)`。
输出两位小数时注意第一位小数可能要补0。
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int Read()
{
	int now=0; char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	for(c=gc();isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	static int A[55];
	for(int i=1; i<=4; ++i) A[i]=Read();//scanf("%d.%d",&x,&y);
	std::sort(A+1,A+1+4);
	int res=Read();
	if(A[2]+A[3]+A[4]<=res*3) return puts("infinite"),0;
	if(A[1]+A[2]+A[3]>res*3) return puts("impossible"),0;
	int tmp=(3*res-A[2]-A[3])%100;
	if(tmp<10) printf("%d.0%d\n",(3*res-A[2]-A[3])/100,(3*res-A[2]-A[3])%100);
	else printf("%d.%d\n",(3*res-A[2]-A[3])/100,(3*res-A[2]-A[3])%100);
	
	
	return 0;
}
/*
19.99
19.97
1.99
2.00
*/
