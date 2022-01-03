#include <bits/stdc++.h>
#define gc() getchar()
#define mp std::make_pair
#define pr std::pair<int,int>
typedef long long LL;
const int N=1e5+5;
using namespace std;

int A[N],L[N],Max[N],Ans[N],delta[N];
bool fri[205][205];
string str[222],Ref[222];
unordered_map<string,int> mps;
struct Node
{
	int num,bel,pos;
	bool operator <(const Node &x)const
	{
		return num==x.num?bel>x.bel:num>x.num;
	}
};
priority_queue<Node> Q;
priority_queue<pr,vector<pr>,greater<pr> > q[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(; !isdigit(c); c=='-'&&(f=-1),c=gc());
	for(; isdigit(c); now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{	
	int S = read(), l = read(), n = read();
	
	for (int i = 1 ; i <= S ; ++i) cin >> str[i];
	sort(str+1,str+S+1);
	for (int i = 1 ; i <= S ; ++i) mps[str[i]]=i, Ref[i]=str[i];

	string s1,s2;
	for(int i=1,x,y; i<=l; ++i) 
		cin>>s1>>s2, x=mps[s1], y=mps[s2], fri[x][y]=1, fri[y][x]=1;
	for(int i=1; i<=n; ++i) cin>>s1, A[i]=mps[s1];

	for(int i=1; i<=n; ++i)
	{
		int mx=0,now=A[i];
		for(int j=1; j<=S; ++j)
			if(!fri[now][A[j]]) mx=std::max(mx,Max[A[j]]);
		L[i]=Max[now]=std::max(Max[now],mx+1);
	}
//	printf("A:\n"); for(int i=1; i<=n; ++i) printf("%d ",A[i]); puts("");
//	printf("L:\n"); for(int i=1; i<=n; ++i) printf("%d ",L[i]); puts("");
	for(int i=1; i<=n; ++i) q[L[i]].push(mp(A[i],i));
	for(int i=1,now=0,sum=0; i<=n; ++i)
	{
		sum+=delta[i];
		while(now<i-sum)
		{
			if(!q[++now].empty()) Q.push((Node){q[now].top().first,now,q[now].top().second}), q[now].pop();
//			printf("Update now:%d size:%d\n",now,Q.size());
			if(!sum) break;
		}

		assert(!Q.empty());
		int x=Q.top().num,y=Q.top().bel,z=Q.top().pos; Q.pop();
		Ans[i]=x;//y:belong which heap	x:num
//		printf("i:%d num:%d bel:%d pos:%d now:%d sum:%d size:%d\n",i,x,y,z,now,sum,Q.size());
		if(!q[y].empty()) Q.push((Node){q[y].top().first,y,q[y].top().second}), q[y].pop();
		
		int pos=z;
		++sum, --delta[std::max(i+1,pos+1)];
		
//		if(!q[i].empty()) Q.push(mp(q[i].top(),i)), q[i].pop();
//		assert(!Q.empty());
//		int x=Q.top().first,y=Q.top().second; Q.pop();
//		Ans[i]=x;//y:pos x:num
//		printf("Ans[%d]=%d y:%d\n",i,x,y);
//		if(!q[y].empty()) Q.push(mp(q[y].top(),y)), q[y].pop();
	}
	for(int i=1; i<=n; ++i) cout<<Ref[Ans[i]]<<' ';
	

	return 0;
}
