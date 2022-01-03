/*
824kb	56ms
������ö���е�n-1����
���ڳ�n��mҪ��x�������Ի���Ϊ���ɸ� ��n'��m'Ҫ��x'�� �������⣬������������Ĵ�ȡmax ������������ķ���ȡmin ���ǵ�ǰ״̬�𰸡�
����Ȼ�ǻ��кܶ��ظ�״̬�ģ���map���仯(������double)��
ÿһ���Ὣ��ǰ�ֳ����ݡ����統ǰ�Ǻ����У�ö���ϱ�����i��(�ֳ�i+1��)(�±߾�����x-1-i��)����m���䣬�� n'*m=n*m*(i+1)/(x+1)�����Եõ�n'��ͬ����Եõ�ÿ���з���n',m'��
double������pair<LL.LL>��ʾ������������Ҳû̫������ɡ�
�ܽ᣺1.���������⣻���仯��
2.���гɿ������������(�϶��ǰ�)
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
	for(int i=0; i<x; ++i)//ʣ����д���Ϊx-1(ע�������һ��) 
		res=std::min(res,std::max(DFS((i+1)*nn,m,i),DFS((x-i)*nn,m,x-1-i))),//x�ǵ���������ˡ�
		res=std::min(res,std::max(DFS(n,(i+1)*mm,i),DFS(n,(x-i)*mm,x-1-i)));
	f[x][mp(n,m)]=f[x][mp(m,n)]=res;
	return res;
}

int main()
{
	int n,m,x; scanf("%d%d%d",&n,&m,&x);
//	double Ans=DFS(n,m,x-1);//һ�� 
	printf("%.6lf",DFS(n,m,x-1));
	return 0;
}
