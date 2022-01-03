#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=6e4+5,M=N<<1;
int n,m,last,size[N],sum,SIZE,w[N],top[N];
struct node{
	int v[M],next[M],head[M],tot;
	bool del[M];
	inline void add(int x,int y){
		v[++tot]=y;next[tot]=head[x];head[x]=tot;
	}
}g,block,linked;
vector<int>list[N];
inline void init(int u,int f){
	int root=top[u];
	list[root].push_back(w[u]);
	for(int i=g.head[u];i;i=g.next[i]){
		if(g.v[i]==f){g.del[i]=1;continue;} 
		if(size[root]<SIZE)
			size[root]++,top[g.v[i]]=root;
		else
			block.add(root,g.v[i]);
		init(g.v[i],u);
	}
}
inline void query_block(int u,int x){
	sum+=list[u].end()-upper_bound(list[u].begin(),list[u].end(),x);
	for(int i=block.head[u];i;i=block.next[i])
		query_block(block.v[i],x);
}
inline void query_out_board(int u,int x){
	if(w[u]>x) sum++;
	for(int i=g.head[u];i;i=g.next[i]){
		if(g.del[i]) continue; 
		if(top[u]==top[g.v[i]])
			query_out_board(g.v[i],x);
		else
			query_block(g.v[i],x);
	}
}
int main(){
	freopen("gtygirltree.in","r",stdin);
	freopen("gtygirltree.out","w",stdout);
	n=read();
	SIZE=(int)ceil(2.0*sqrt(n)*log2(n));
	for(int i=1,x,y;i<n;i++){
		x=read();y=read();
		g.add(x,y);g.add(y,x);
	}
	for(int i=1;i<=n;i++) w[i]=read(),top[i]=i,size[i]=1;
	init(1,0);
	for(int i=1;i<=n;i++) if(top[i]==i) sort(list[i].begin(),list[i].end());
	m=read(),last=0;
	for(int opt,u,x,tp;m--;){
		opt=read();u=read()^last;x=read()^last;
		if(!opt){
			sum=0;
			if(u==top[u])
				query_block(u,x);
			else
				query_out_board(u,x);
			printf("%d\n",last=sum);
		}
		else if(opt==1){
			tp=top[u];
			list[tp].erase(lower_bound(list[tp].begin(),list[tp].end(),w[u]));
			list[tp].insert(lower_bound(list[tp].begin(),list[tp].end(),x),x);
			w[u]=x;
		}
		else{
			w[++n]=x;
			tp=top[u];
			g.add(u,n);
			if(size[tp]<SIZE){
				top[n]=tp;
				size[tp]++;
				list[tp].insert(lower_bound(list[tp].begin(),list[tp].end(),x),x);
			}
			else{
				top[n]=n;
				size[u]=1;
				list[n].push_back(x);
				block.add(tp,n);
			}
		}
	}
	return 0;
}
