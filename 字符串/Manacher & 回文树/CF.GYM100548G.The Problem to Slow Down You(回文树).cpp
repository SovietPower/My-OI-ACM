/*
202ms	51800KB
$Description$
����������$S,T$�����������ж��ٶ���ͬ�����Ӵ���
$|S|,|T|\leq 2\times 10^5$��

$Solution$
�ò˰�QAQ  �ⶼû�뵽
���������ֱ𽨻�����������������ͬ�Ļ��Ĵ����ҽ���������ͬ�Ľڵ㡣
���Էֱ������������������$0$��$1$��DFS��ֻ����������ͬ�Ľڵ㣬�Ѿ����ڵ�Ĺ��׼��Ͼ����ˡ�
��Ҫ���ʲ�ͬ������Ҫ����һ��`val[fail[x]]`��

����������`'$'`�ӳ�һ������ֱ�ӽ�$PAM$���ֱ������ߵ�$val$Ҳ���ԣ�������һ���ġ�����[���](https://www.cnblogs.com/JYYHH/p/9214003.html)��
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=2e5+5;

struct PAM
{
	int tot,las,son[N][26],len[N],val[N],fail[N];
	char s[N];
	inline void Init()
	{
		las=tot=1, fail[0]=1, len[1]=-1, s[0]='$';
		memset(son[0],0,sizeof son[0]), memset(son[1],0,sizeof son[1]);//ֻ����������Ϳ����˰� 
	}
	inline int Find(int x,int n)
	{
		while(s[n]!=s[n-len[x]-1]) x=fail[x];
		return x;
	}
	void Insert(int c,int n)
	{
		int p=Find(las,n);
		if(!son[p][c])
		{
			int np=++tot;
			memset(son[np],0,sizeof son[np]), val[np]=0;
			fail[np]=son[Find(fail[p],n)][c];
			son[p][c]=np, len[np]=len[p]+2;
		}
		++val[las=son[p][c]];
	}
	void Build()
	{
		Init(), scanf("%s",s+1);
		for(int i=1,l=strlen(s+1); i<=l; ++i) Insert(s[i]-'a',i);
		for(int i=tot; i>1; --i) val[fail[i]]+=val[i];
		val[0]=val[1]=0;
	}
}S,T;

LL DFS(int x,int y)
{
	LL res=1ll*S.val[x]*T.val[y];
	for(int i=0; i<26; ++i)
		if(S.son[x][i]&&T.son[y][i]) res+=DFS(S.son[x][i],T.son[y][i]);
	return res;
}

int main()
{
	int tot; scanf("%d",&tot);
	for(int Cs=1; Cs<=tot; ++Cs)
		S.Build(), T.Build(), printf("Case #%d: %I64d\n",Cs,DFS(0,0)+DFS(1,1));
	return 0;
}
