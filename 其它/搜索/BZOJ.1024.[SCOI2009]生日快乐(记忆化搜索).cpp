/*
824kb	56ms
搜索，枚举切的n-1刀。
对于长n宽m要切x刀，可以划分为若干个 长n'宽m'要切x'刀 的子问题，对所有子问题的答案取max 对所有子问题的方案取min 就是当前状态答案。
这显然是会有很多重复状态的，用map记忆化(长宽都是double)。
每一刀会将当前分成两份。比如当前是横着切，枚举上边再切i刀(分成i+1份)(下边就再切x-1-i刀)，由m不变，有 n'*m=n*m*(i+1)/(x+1)，可以得到n'。同理可以得到每种切法的n',m'。
double可以用pair<LL.LL>表示最简分数，不用也没太大问题吧。
总结：1.划分子问题；记忆化。
2.按切成块数划分面积。(肯定是啊)
*/
#include <map>
#include <cstdio>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<double,double>
//typedef Status std::pair<pr,int>

std::map<pr,double> f[10];
std::map<pr,double>::iterator it;

double DFS(double n,double m,int x)
{
	if(!x) return std::max(n,m)/std::min(n,m);
	if((it=f[x].find(mp(n,m)))!=f[x].end()) return it->second;
	double res=1e15, nn=n/(x+1), mm=m/(x+1);
	for(int i=0; i<x; ++i)//剩余可切次数为x-1(注意这就是一次) 
		res=std::min(res,std::max(DFS((i+1)*nn,m,i),DFS((x-i)*nn,m,x-1-i))),//x是刀数，别混了。
		res=std::min(res,std::max(DFS(n,(i+1)*mm,i),DFS(n,(x-i)*mm,x-1-i)));
	f[x][mp(n,m)]=f[x][mp(m,n)]=res;
	return res;
}

int main()
{
	int n,m,x; scanf("%d%d%d",&n,&m,&x);
//	double Ans=DFS(n,m,x-1);//一样 
	printf("%.6lf",DFS(n,m,x-1));
	return 0;
}
