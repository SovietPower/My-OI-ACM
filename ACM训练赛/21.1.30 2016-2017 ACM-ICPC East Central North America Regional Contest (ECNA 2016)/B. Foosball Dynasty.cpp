/*
¼òµ¥Ä£Äâ ÄÃ¸öqueue 
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
using namespace std;
typedef long long LL;
const int N=1e3+5;

char s[N];
string name[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) std::cin>>name[i];
	scanf("%s",s+1); int m=strlen(s+1);

	static std::queue<int> q;
	for(int i=5; i<=n; ++i) q.push(i);
	int now=0,wo=1,bo=2,wd=3,bd=4,mx=0,las=-1;//las=0:W las=1:B
	for(int i=1; i<=m; ++i)
		if(s[i]=='B')
		{
			if(las==1) ++now;
			else now=1;
			las=1, mx=std::max(mx,now);
			std::swap(bo,bd);
			q.push(wd), wd=wo, wo=q.front(), q.pop();
		}
		else
		{
			if(las==0) ++now;
			else now=1;
			las=0, mx=std::max(mx,now);
			std::swap(wo,wd);
			q.push(bd), bd=bo, bo=q.front(), q.pop();
		}

	int ans=mx; while(!q.empty()) q.pop();
	for(int i=5; i<=n; ++i) q.push(i);
	now=0,wo=1,bo=2,wd=3,bd=4,mx=0,las=-1;//las=0:W las=1:B
	for(int i=1; i<=m; ++i)
		if(s[i]=='B')
		{
			if(las==1) ++now;
			else now=1;
			las=1;
			std::swap(bo,bd);
			if(now==ans)
			{
				int a=now&1?bo:bd,b=now&1?bd:bo;
				if(now==i) std::swap(a,b);
				std::cout<<name[a]<<' '<<name[b]<<'\n';
			}
			q.push(wd), wd=wo, wo=q.front(), q.pop();
		}
		else
		{
			if(las==0) ++now;
			else now=1;
			las=0;
			std::swap(wo,wd);
			if(now==ans)
			{
				int a=now&1?wo:wd,b=now&1?wd:wo;
				if(now==i) std::swap(a,b);
				std::cout<<name[a]<<' '<<name[b]<<'\n';
			}
			q.push(bd), bd=bo, bo=q.front(), q.pop();
		}
	

	return 0;
}
