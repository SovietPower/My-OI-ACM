/*
1408kb	72ms
$Description$
��n��ģʽ�������Ƿ���ڳ������޵�������ʹ���κ�һ��ģʽ����û���������г��֡�
$Solution$
�Ƚ�AC�Զ�����
������������һ�����޳��İ�ȫ���룬Ȼ����AC�Զ�����ƥ��Ӧ�÷���ʲô��
Ӧ����ƥ�䵽һ��λ��ʧ������ȥ��֮��Ҫ��ƥ�䵽���λ��(�������ص�ǰ��)��ʧ������ȥ������ȥ����ͨ��failָ�롣
Trie��������failָ��ıߺ���ʵ����Buildʱ�ĵ�son������������������ͼ���ҵ�������TAK��
���ߣ���ȫ�������޳��Ļ�ǰ��Ҫ��ƴ��������ǰ��׺��ͬ(ͬ��Ҫ���ص�ǰ��)���ұ�֤��������в���ƥ���κ�ģʽ����
ǰ��׺��ͬ����ͨ��failָ������ȥ(����ǰ��)��
��ͼ�����ǽ�AC�Զ�������DFSһ��Ϳ��ԡ�ע�����fail[x]ƥ�䣬��ôxҲƥ�䡣
ע����ʹ��ĵ��û��Ҫ�ٷ����ˡ�
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
const int N=30005;

struct AC_Automaton
{
	int tot,son[N][2],q[N],fail[N];
	bool ed[N],vis[N],ins[N];
	char s[N];

	void Insert()
	{
		scanf("%s",s);
		int l=strlen(s),x=0;
		for(int i=0,v; i<l; ++i)
		{
			if(!son[x][v=s[i]-'0']) son[x][v]=++tot;
			x=son[x][v];
		}
		ed[x]=1;
	}
	void Build()
	{
		int h=0,t=0;
		if(son[0][0]) q[t++]=son[0][0];
		if(son[0][1]) q[t++]=son[0][1];
		while(h<t)
		{
			int x=q[h++];
			ed[x]|=ed[fail[x]];//WA:fail[x]һ����x�������·�� fail[x]��x�ֲ�һ����ͬһ��·����_�� 
			for(int i=0; i<2; ++i)
				if(son[x][i]) fail[son[x][i]]=son[fail[x]][i], q[t++]=son[x][i];
				else son[x][i]=son[fail[x]][i];
		}
	}
	void DFS(int x)
	{
		if(ins[x]) puts("TAK"),exit(0);//������ڵ�ǰ���ϣ���Ҳû����ֹ�ڵ� 
		if(vis[x]||ed[x]) return;
		vis[x]=ins[x]=1;
		DFS(son[x][0]), DFS(son[x][1]);
		ins[x]=0;
	}
	void Query()	
	{
		Build(), DFS(0), puts("NIE");
	}
}AC;

int main()
{
	int n;
	for(scanf("%d",&n); n--; AC.Insert());
	AC.Query();
	return 0;
}
