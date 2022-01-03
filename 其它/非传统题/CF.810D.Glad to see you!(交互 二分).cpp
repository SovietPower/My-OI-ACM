/*
$Description$
有一个大小为$k$的集合$S$，元素两两不同且在$[1,n]$内。你可以询问不超过$60$次，每次询问你给出$x,y$，交互库会返回$\left[\ \min(|x-a|,a\in S)\leq \min(|y-a|,a\in S)\ \right]$是(TAK)否(NIE)为真。
求任意两个一定在集合$S$中出现过的数。
$Solution$
考虑对区间$[l,r]$二分，若Check(mid,mid+1)==1，则区间$[1,mid]$中一定存在一个数；否则区间$[mid+1,r]$中一定存在一个数。这样用$\log10^5=16$次可以确定一个数$A$。
对于第二个数，可以在$[1,A-1]$和$[A+1,n]$中分别二分。
*/
#include <cstdio>

int n;

inline bool Query(int x,int y)
{
	static char s[7];
	if(y>n) return 1;//!
	printf("1 %d %d\n",x,y); fflush(stdout);
	return scanf("%s",s),s[0]=='T';
}
int Check(int l,int r)
{
	if(l>r) return 0;
	int mid,ans=0;
	while(l<=r)
		if(mid=l+r>>1, Query(mid,mid+1)) ans=mid,r=mid-1;
		else l=mid+1;
	return ans;
}

int main()
{
	int k; scanf("%d%d",&n,&k);
	int A=Check(1,n), B=Check(1,A-1);
	if(!B) B=Check(A+1,n);
	printf("2 %d %d\n",A,B); fflush(stdout);

	return 0;
}
