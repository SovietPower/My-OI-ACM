/*
3900kb	68ms
直接在AC自动机上DP。
f[i][j]表示 当前是文本第i位，匹配到了AC自动机上的j节点 此时的文章数。
转移时就枚举26个字母，转移到AC自动机上的下一个节点。
任意匹配一个单词就可以，所以当前节点j如果是模式串的结束节点，不再跳到下一个节点，而是直接*26给f[i+1][j]。
不是结束节点的话 跳到下一个节点直接加上。

注意一个节点如果能通过fail指针跳到模式串的结束节点，那么它也是一个结束节点。。已经忘了。
容斥去算不满足条件的文本数量也可以。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mod (10007)
#define gc() getchar()
const int N=6e3+7;

int n,num,tot,f[103][N];
char s[105];
struct AC_Automaton
{
	int tot,son[N][26],fail[N],q[N];
	bool val[N];

	void Insert(char *s)
	{
		int l=strlen(s),x=0;
		for(int id,i=0; i<l; ++i)
		{
			if(!son[x][id=s[i]-'A']) son[x][id]=++tot;;
			x=son[x][id];
		}
		val[x]=1;
	}
	void Build()
	{
		int h=0,t=0;
		for(int i=0; i<26; ++i)
			if(son[0][i]) fail[son[0][i]]=0, q[t++]=son[0][i];
		while(h<t)
		{
			int x=q[h++];
			val[x]|=val[fail[x]];//!
			for(int v,i=0; i<26; ++i)
				if(son[x][i]) fail[son[x][i]]=son[fail[x]][i], q[t++]=son[x][i];
				else son[x][i]=son[fail[x]][i];
		}
	}
}ac;

int main()
{
	scanf("%d%d",&num,&n);
	while(num--) scanf("%s",s), ac.Insert(s);
	ac.Build();

	f[0][0]=1, tot=ac.tot;
	for(int i=0; i<n; ++i)
		for(int j=0; j<=tot; ++j)
			if(f[i][j]){
				if(ac.val[j]) f[i+1][j]+=f[i][j]*26%mod;//%mod
				else{
					for(int k=0; k<26; ++k)
						(f[i+1][ac.son[j][k]]+=f[i][j])%=mod;
				}
			}
	int Ans=0;
	for(int i=0; i<=tot; ++i)
		if(ac.val[i]) Ans+=f[n][i];
	printf("%d",Ans%mod);

	return 0;
}
