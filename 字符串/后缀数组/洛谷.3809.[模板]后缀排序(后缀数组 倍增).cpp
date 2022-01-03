//输出ht见UOJ.35 
#include<cstdio>
#include<cstring>
#include<algorithm>
const int N=1e6+5;

int n,tm[N],t1[N],t2[N],SA[N],rk[N],ht[N];
//SA[i]=j:排名为i的后缀开头的下标为j 
//rk[i]=j:以下标i开头的后缀排名为j 
//ht[i]:排名为i的后缀与排名为i-1的后缀的LCP长度 
char s[N];

void Get_SA()
{
	int *x=t1,*y=t2,limit=80;//首先对单个字符进行排序，limit最初就为字符集大小(就是不同字符的个数) 
	for(int i=0;i<n;++i) ++tm[x[i]=s[i]-'0'];
	for(int i=1;i<limit;++i) tm[i]+=tm[i-1];
	for(int i=n-1;~i;--i) SA[--tm[x[i]]]=i;//基数排序
 	//x[]相当于是rank值 
	for(int p=0,k=1;k<n;k<<=1,limit=p,p=0)//每次更新limit为p 
	{//p实际就是不同字符串的个数 
		//首先对第二关键字进行排序，y保存的就是对第二关键字排序后的结果 
		//这一过程可以直接用上次得到的SA[]求出 
		for(int i=n-k;i<n;++i) y[p++]=i;//第二关键字长度不为k，故先排 
		for(int i=0;i<n;++i) if(SA[i]>=k) y[p++]=SA[i]-k;//剩下的有完整第二关键字的(SA[i]>=k)按顺序，即SA[i]排，第一关键字的位置自然就是SA[i]-k 
		//对第一关键字的排序同对单个字符排序 
		for(int i=0;i<limit;++i) tm[i]=0;
		for(int i=0;i<n;++i) ++tm[x[i]];//++tm[x[y[i]]];
		for(int i=1;i<limit;++i) tm[i]+=tm[i-1];
		for(int i=n-1;~i;--i) SA[--tm[x[y[i]]]]=y[i];
		//交换两个指针，因为要用到上一轮的rk(x)，而y是没有用了 
		std::swap(x,y), x[SA[0]]=0, p=1;
		//得到新的rank 
		for(int i=1;i<n;++i)
//			x[SA[i]]=(y[SA[i-1]]==y[SA[i]]&&y[SA[i-1]+k]==y[SA[i]+k])?p-1:p++;//对于连续字符的字符串会WA 
			if(y[SA[i-1]]==y[SA[i]]&&((y[SA[i-1]+k]==y[SA[i]+k]&&SA[i-1]+k<n&&SA[i]+k<n)||(SA[i-1]+k>=n&&SA[i]+k>=n))) x[SA[i]]=p-1;
			else x[SA[i]]=p++;
		if(p>=n) break;//不同字符串数已有n个，再继续倍增不会变了，break 
	}
}
void Calc_Ht()
{
	for(int i=0;i<n;++i) rk[SA[i]]=i;//rk[]与SA[]互为反函数 
//	有一个性质是:ht[i]>=ht[i-1]-1 
//	因为去掉开头字符 后缀一大部分是相等的。比较明显 
	for(int j,k=0,i=0;i<n;ht[rk[i++]]=k)
	{
		if(!rk[i])// continue;//排名为0的字符串ht为0 
		{ht[0]=0;continue;}
		j=SA[rk[i]-1], k?--k:0;//从k-1开始匹配(与上一名次字符串) 
		while(s[i+k]==s[j+k]&&i+k<n&&j+k<n) ++k;
	}
}

int main()
{
//	freopen("sais.in","r",stdin);
//	freopen("sais.out","w",stdout);

	scanf("%s",s),n=strlen(s);
	Get_SA();
	Calc_Ht();
	for(int i=0;i<n;++i) printf("%d ",SA[i]+1);
	putchar('\n');
	for(int i=1;i<n;++i) printf("%d ",ht[i]);

	return 0;
}
