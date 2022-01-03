/*
1100kb	324ms
m个方程，n个未知量，求解异或方程组。
复杂度比较高，需要借助bitset压位。
感觉自己以前写的(异或)高斯消元是假的。。而且黄学长的写法都不需要回代。
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
const int N=1004,M=2004;

int n,m;
char s[N];
std::bitset<N> A[M];

bool Gauss()
{
	int ans=0;
	for(int r,c=0; c<n; ++c)
	{
		r=c;
		while(!A[r][c]&&r<m) ++r;
		if(r==m) return 0;//存在自由元(c)。
		ans=std::max(ans,r);
		if(r!=c) std::swap(A[r],A[c]);
		for(int i=0; i<m; ++i)//直接枚举所有方程，(因为当前位置系数是1，前面也都是0了)这样就不需要回代了。最后A[i][n]就是i的结果。	
			if(A[i].test(c)&&i!=c) A[i]^=A[c];//这个好像更快些？
//			if(A[i][c]&&i!=c) A[i]^=A[c];
	}
	printf("%d\n",ans+1);
	for(int i=0; i<n; ++i) puts(A[i].test(n)?"?y7M#":"Earth");
	return 1;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int t,i=0; i<m; ++i){
		scanf("%s%d",s,&t), A[i][n]=t;
		for(int j=0; j<n; ++j)
			A[i][j]=s[j]-'0';
	}
	if(!Gauss()) puts("Cannot Determine");

	return 0;
}
