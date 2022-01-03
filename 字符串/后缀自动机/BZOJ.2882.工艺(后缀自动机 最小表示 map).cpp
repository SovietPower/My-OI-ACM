/*
73240kb	2496ms
SAM���ַ�������Сѭ����ʾ�� 
��Ϊ�Ӹ��ڵ�������Եõ������Ӵ�������ÿ�����ֵ�����С��һ�������߼��ɡ���Ϊ���������ԭ����ƴ���ں���һ�Ρ�
��Ҫ��map��ת�ơ����Ӷ�O(nlogn)��
��Ȼ����O(n)����С��ʾ����
*/
#include <map>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=(3e5+5)*4;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
struct Suffix_Automaton
{
	int n,s[N],las,tot,fa[N],len[N];
	std::map<int,int> son[N];

	void Insert(int c)
	{
		int p=las,np=++tot; len[las=np]=len[p]+1;
		for(; p&&!son[p].count(c); p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot;
				len[nq]=len[p]+1, son[nq]=son[q];
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Build()
	{
		n=read(), las=tot=1;
		for(int i=1; i<=n; ++i) Insert(s[i]=read());
		for(int i=1; i<=n; ++i) Insert(s[i]);
	}
	void Solve()
	{
		std::map<int,int>::iterator it;
		for(int i=1,p=1; i<=n; ++i)
			it=son[p].begin(), p=it->second, printf("%d ",it->first);//�����map��first(ת��)��second(son)�� 
	}
}sam;

int main()
{
	sam.Build(), sam.Solve();
	return 0;
}
