/*
1616kb	684ms
不会搜索了。。
DFS()中两个参数，枚举每两个队伍的比赛结果(分配当前队伍的分数)。
可以发现方案数量与具体哪只球队得了多少分无关，只与当前比赛的队伍数量和得分序列的组成有关。可以记忆化搜索。
DFS()中是从某支队伍和它后面的队伍一一进行比赛 分配得分，分配完当前后将其它队伍的得分情况哈希，看是否算过；
如果没就进行下一支队伍，其实就是计算去掉当前这支队伍的方案数。
n(n<=10)支队伍分数的情况最多为(28^9?)10^14级别，可以直接用longlong存。

这样做为什么必须要降序排？
*/
#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mod (1000000007)
typedef long long LL;
const int N=11;

int n,val[N];
std::map<LL,int> sta[N];//应该是每一位开一个map?
std::map<LL,int>::iterator it;

inline bool cmp(int a,int b){
	return a<b;
}
LL Get_Hash(int p)
{
	int tmp[N];
	for(int i=p; i<=n; ++i) tmp[i]=val[i];
	std::sort(tmp+p,tmp+n+1,cmp);//tmp+p！不是tmp+p+1 
	LL res=0;
	for(int i=p; i<=n; ++i) res=res*28+tmp[i];//tmp[i] not val[i]!!(神tm这还能写错 我说怎么还T)
	return res;
}
int DFS(int l,int r)
{
	if(val[l]>(r-l)*3) return 0;//根据上面的剪枝，不可能合法！
	if(l==r)
	{
//		if(val[l]) return 0;//只有把分数恰好分配完才合法!
		if(l==n) return 1;
		LL s=Get_Hash(l+1);
		if((it=sta[l].find(s))!=sta[l].end()) return it->second;//~~用迭代器效率反而低？求解。。~~本地辣鸡xp的事吧，在洛谷上快不少 
		return sta[l][s]=DFS(l+1,n);//这不能用迭代器赋值！
	}
	int res=0;
	if(val[l]>=3)
	{
		val[l]-=3;
		res+=DFS(l,r-1), res>=mod?res-=mod:0;
		val[l]+=3;
	}
	if(val[l]&&val[r])
	{
		--val[l], --val[r];
		res+=DFS(l,r-1), res>=mod?res-=mod:0;
		++val[l], ++val[r];
	}
	if(val[r]>=3)
	{
		val[r]-=3;
		res+=DFS(l,r-1), res>=mod?res-=mod:0;
		val[r]+=3;
	}
	return res;
}

int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&val[i]);
	std::sort(val+1,val+1+n,cmp);
	printf("%d",DFS(1,n));

	return 0;
}
