#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define gc() getchar()
const int N=5e5+5,mod=1e6+5,base=131;

int root,n,sz[N],fix[N],val[N],tim[N],son[N][2];
int Enum,H[mod+1],nxt[N],hash[mod+1];
char name[N][12];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
int New_Node(int v)
{
	val[n]=v, sz[n]=1, fix[n]=rand(), tim[n]=n;
	return n;
}
inline void Update(int rt)
{
	sz[rt]=sz[son[rt][0]]+sz[son[rt][1]]+1;
}
void Split(int rt,int v,int &x,int &y,bool f)
{
	if(!rt) x=y=0;
	else
	{
		if((!f&&val[rt]<=v)||(f&&tm[rt]>=v)) x=rt,Split(son[rt][1],v,son[rt][1],y);
		else y=rt,Split(son[rt][0],v,x,son[rt][0]);
		Update(rt);
	}
}
void Split_k(int rt,int k,int &x,int &y)
{
	if(!rt) x=y=0;
	else
	{
		if(sz[son[rt][0]]<k) x=rt,Split(son[rt][1],k-sz[son[rt][0]]-1,son[rt][1],y);
		else y=rt,Split(son[rt][0],k,x,son[rt][0]);
		Update(rt);
	}
}
int Merge(int x,int y)
{
	if(!x||!y) return x+y;
	if(fix[x]<fix[y])
	{
		son[x][1]=Merge(son[x][1],y);
		Update(x);
		return x;
	}
	else
	{
		son[y][0]=Merge(x,son[y][0]);
		Update(y);
		return y;
	}
}
int Pos(char *s)
{
	int tmp=0,len=strlen(s);
	for(int i=1;i<len;++i) tmp=(1ll*tmp*base+s[i])%mod;
//	while(hash[tmp]&&name[hash[tmp]]!=s) tmp==mod?tmp=1:++tmp;
//	s[len]='\0',printf("name:%s pos:%d val:%d\n",s,hash[tmp],tmp);
	return tmp;
}
bool cmp(char *s,int id)
{
	int l1=strlen(s),l2=strlen(name[id]);
	if(l1!=l2) return 0;
	for(int i=1;i<l1;++i)
		if(s[i]!=name[id][i]) return 0;
	return 1;
}
void Delete(int p)
{
	int u,w,x,y,z;
	Split(root,val[p],y,z), Split(y,val[p]-1,u,y);
	Split(y,tim[p]-1,w,y), Split(y,tim[p],x,y);
	root=Merge(Merge(u,Merge(w,y)),z);
}
void Insert(int p,)
void Ins(char *s)
{
	int p=Pos(s),v=read();
	for(int i=H[p];i;i=nxt[i])
	{
		if(cmp(s,i))
		{
			Delete()
			
		}
		
	}
	hash[p]=++n;
	memcpy(name[n],s,sizeof s);
	int y=New_Node(v),x,z;
	Split(root,v,x,z);
	root=Merge(Merge(x,y),z);
}
void Rank(int p)
{
	int x,y,z;
	Split(root,val[p]-1,x,y);
//	printf("pos:%d\n",p);
	printf("%d\n",sz[x]);
	root=Merge(x,y);
}
int Kth(int rt,int k)
{
	while(1)
	{
		if(sz[son[rt][0]]+1==k) return rt;
		if(sz[son[rt][0]]<k) k-=sz[son[rt][0]]+1,rt=son[rt][1];
		else rt=son[rt][0];
	}
}
void Print(int rt)
{
	if(son[rt][1]) Print(son[rt][1]);
	printf("rt:%d name:%s ",rt,name[rt]+1);
	if(son[rt][0]) Print(son[rt][0]);
}
void Index(char *s)
{
	int k=0,x,y,z,len=strlen(s),now=1;
	while(s[now]&&now<len) k=k*10+s[now++]-'0';
	k=n-k+1;
	Split_k(root,k,y,z),Split(y,std::max(k-10,0),x,y);
	Print(y);
	root=Merge(Merge(x,y),z);
	putchar('\n');
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("2584.in","r",stdin);
#endif

	int q=read();
	char s[15];
	while(q--)
	{
		scanf("%s",s);
		if(s[0]=='+') Ins(s);
		else if(!isdigit(s[1])) Rank(hash[Pos(s)]);
		else Index(s);
	}

	return 0;
}
