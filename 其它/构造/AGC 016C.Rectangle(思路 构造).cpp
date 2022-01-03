/*
20ms	1792KB
首先想到同样例1的构造方式。即不得不填负的格子填-h*w，其余填1。直接这样能过二三十个点。
只这样不对。比如1 4 1 3，会输出无解（会填[1 1 -3 1]）。怎么改呢。对于一个点，它可以覆盖多个h*w的子矩形，只要对每个子矩形满足负权和，它们的和可以尽量大。
将原方案中的所有正数扩大d倍，不得不填负的格子只需恰好大于一个子矩形的和。这样多个格子加起来的和就大了。
如1 4 1 3，可以填[1000 1000 -2001 1000]。
*/
#include <cstdio>
#include <algorithm>
const int N=505;

bool A[N][N];

int main()
{
	int H,W,h,w; scanf("%d%d%d%d",&H,&W,&h,&w);
	if(!(H%h) && !(W%w)) return puts("No"),0;//每个子矩形都是负的，拼一块还是负的(当然不判也行) 

	int r=h,c=w,tot=0;
	while(1)
	{
		while(1)
		{
			++tot, A[r][c]=1;
			if(c+w>W) break;
			c+=w;//每次只能加w而不是2w-1!
		}
		c=w;
		if(r+h>H) break;
		r+=h;
	}
	int v=-h*w*1000+999;
	if(-1ll*tot*v>=1000*(H*W-tot)) puts("No");
	else
	{
		puts("Yes");
		for(int i=1; i<=H; ++i,putchar('\n'))
			for(int j=1; j<=W; ++j) printf("%d ",A[i][j]?v:1000);
	}

	return 0;
}
