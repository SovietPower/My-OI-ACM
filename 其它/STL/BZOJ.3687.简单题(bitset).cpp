/*
求异或和，容易想到，如果同一个数异或偶数次相当于0 
∑ai还不大，那想一下每个子集和出现多少次，显然只需要知道次数的奇偶，可以用bitset 
bit[i]=0/1表示子集和为i出现了偶数次/奇数次 
有个简单的dp方程: f[x+a[i]]+=f[x]
对于一个x，bit(注意bit就代表了所有子集和)有两种选择: 加上它 对应到bitset里就是bit<<x；不加它 还是bit 
那么这两种情况异或 即 bit = (bit << x) ^ bit 
*/
#include<cstdio>
#include<bitset>
const int N=2e6+5;

std::bitset<N> bit(1);//有0这一位 

int main()
{
	int n,a,sum=0; scanf("%d",&n);
	while(n--)
		scanf("%d",&a), sum+=a, bit^=(bit<<a);
	int res=0;
	for(int i=0;i<=sum;++i)
		if(bit[i]) res^=i;
	printf("%d",res);

	return 0;
}
