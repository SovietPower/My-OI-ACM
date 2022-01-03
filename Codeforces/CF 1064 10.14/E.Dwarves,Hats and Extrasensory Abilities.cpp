#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mp std::make_pair
#define pr std::pair<int,int>
typedef long long LL;
const int N=2e6+5;

struct Node
{
	int col,pos;//0:w 1:b
	bool operator <(const Node &x)const
	{
		return col==x.col?pos<x.pos:col<x.col;
	}
}p[N];

bool Check(int pos,int now)
{
	static char s[233];
	p[now].pos=pos;
	printf("10 %d\n",pos); fflush(stdout);
	scanf("%s",s+1);
	if(s[1]=='w') return p[now].col=0,0;
	else return p[now].col=1,1;
}

int main()
{
	int n;
	scanf("%d",&n);
	int l=1,r=1e9,mid;
	for(int i=1; i<=n; ++i)
	{
		mid=l+r>>1;
		if(Check(mid,i)) r=mid;
		else l=mid+1;
	}
	int ans=0;
	std::sort(p+1,p+1+n);
	for(int i=2; i<=n; ++i)
		if(p[i].col!=p[i-1].col)
		{
			ans=p[i-1].pos+1;
			break;
		}
//	for(int i=1; i<=n; ++i) printf("%d:%d\n",p[i].col,p[i].pos);
	if(ans!=0) printf("9 %d 11 %d\n",ans-1,ans), fflush(stdout);
	else printf("9 %d 11 %d\n",ans,ans), fflush(stdout);

	return 0;
}
