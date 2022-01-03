/*
3900kb	68ms
ֱ����AC�Զ�����DP��
f[i][j]��ʾ ��ǰ���ı���iλ��ƥ�䵽��AC�Զ����ϵ�j�ڵ� ��ʱ����������
ת��ʱ��ö��26����ĸ��ת�Ƶ�AC�Զ����ϵ���һ���ڵ㡣
����ƥ��һ�����ʾͿ��ԣ����Ե�ǰ�ڵ�j�����ģʽ���Ľ����ڵ㣬����������һ���ڵ㣬����ֱ��*26��f[i+1][j]��
���ǽ����ڵ�Ļ� ������һ���ڵ�ֱ�Ӽ��ϡ�

ע��һ���ڵ������ͨ��failָ������ģʽ���Ľ����ڵ㣬��ô��Ҳ��һ�������ڵ㡣���Ѿ����ˡ�
�ݳ�ȥ�㲻�����������ı�����Ҳ���ԡ�
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
