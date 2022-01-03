/*
由于序列长度n是固定的，我们可以假设最初有n个1，然后用5,10,50去替换，即求从{0,4,9,49}中选n个数能组成多少个不同的。
先看{0,4,9}。问题在于一个数可以有多种表示。在使用4的个数大于9之后，一部分4是可以用9替换的，多余的位置用0补。
所以如果暴力的话，4的个数只需从0枚举到min(n,8)，然后选一些9，这样每次都能组成一个不同的数。
对于{0,4,9,49}，可以用类似方法暴力计算(9只需要枚举到min(n,48)吗...并不清楚)。
打表后可以发现，n>=12时，n每加一，组成数的个数+49，即都能组成。然后只需要算n<=12的就OK了。
嗯。。不会证。

还有种思路(Way2)：
我们考虑一下有多种表示的数字的可能。可以先通过打表找到有多种表示的数字，能发现从45往后都可以。(然而好像并没什么用)
9*5 = 4*10 + 5*1
9*10 = 1*50 + 8*5
5*10 + 1*5 = 1*50 + 5*1
这意味着我们不需要 超过8个的5、超过8个的10、超过4个的10且至少1个5。那枚举时范围就很小了。
后面没看明白 不写了。。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=1e4+5;
const int Ans[17]={0,4,10,20,35,56,83,116,155,198,244,292,341,390};

namespace Way2
{
	bool use[200];
	int Judge(int n)
	{
		memset(use,0,sizeof use);
		for(int i=0; i<=20; ++i)
			for(int j=0; j<=20; ++j)
				for(int k=0; k<=20; ++k)
					for(int l=0; l<=20; ++l)
						if(i+j*5+k*10+l*50==n && use[i+j+k+l]) return 1;
						else if(i+j*5+k*10+l*50==n) use[i+j+k+l]=1;// printf("%d=%d+%d*5+%d*10+%d*50\n",n,i,j,k,l);
		return 0;
	}
	void Main()
	{
		for(int i=1; i<=100; ++i)
			if(Judge(i)) printf("%d\n",i);	
	}
}

long long Calc(int n)
{
	return Ans[n];
	static bool vis[N];
	memset(vis,0,sizeof vis);
	long long ans=0;
	for(int i=0; i<=8; ++i)
		for(int j=0; j<=8; ++j)
			for(int k=0; k<=48; ++k)//我也不知道最小可以枚举到多少...大点吧 
				if(i+j+k<=n && !vis[i*4+j*9+k*49])
					vis[i*4+j*9+k*49]=1, ++ans;
	return printf("%d:",n),ans;
}

int main()
{
	int n; scanf("%d",&n);
	if(n<=12) printf("%I64d\n",Calc(n));
	else printf("%I64d\n",Calc(12)+1ll*(n-12)*49);

	return 0;
}
