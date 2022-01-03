/*
$Description$
找一个点，使得这个点左上、左下、右上、右下四个区域水晶柱数最少的最大，并输出方案个数 
$Solution$
最小值最大，先二分一个答案mid 
这样如果能找出一个矩形区域[up~down,left~right]，满足在这个区域任意一点其上下左右水晶柱数>=mid，就OK了 
分开考虑，对于当前行i上方与下方分别有多少个记为up,down 
在变到i+1行时，up+=cnt[i], down-=cnt[i+1]，cnt[]为某行水晶柱个数，这样显然可以O(1)下一行 



*/
#include<cstdio>
#include<cctype>
#define gc() getchar()
const int N=



inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}


int main()
{
	
	
	
	
	
	
	
	

	return 0;
}
