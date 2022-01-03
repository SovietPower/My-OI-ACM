/*
126308kb	5512ms
$Description$
�����ַ���S�������KС�Ӵ���(��T=0����ͬλ�õ���ͬ�Ӵ���1���������������)
$Solution$
��SAM�����������ÿ���ڵ㣬�����������к�̰������Ӵ�����sz[](����ж����Ӵ�)(��Ҷ�����ö��ת�Ƹ��¼���)��Ȼ����SAM���ߡ�
ÿ�����ȿ��ֵ���С�ı�(��ᵽ��v)����sz[v]<K����K-=sz[v]��ö����һ���ߣ�����K-=A[v]��������ת�ƣ�Ȼ��p=v��(��A[v]����ƥ����v�ڵ�)
���T=0������ʱsz[p]�ĳ�ֵΪ1��A[p]=1�����T=1����ô����ʱsz[p]�ĳ�ֵΪ|right[p]|��A[p]=|right[p]|��
right���󷨣���ԭ����SAM����һ�飬���¾������right��Ȼ����parent�������Ϻϲ���fa��right�Ϳ����ˡ�

�о�����и�����������Ȼһ���ڵ��ǻ�������������ǡ������һ��״̬����������˵ƥ����������������д������Ծ�sz[]=1 or |right|���Ժ���ƥ���ϱ�ĵ���Ȼ��ӡ�
���������º���û������_��
ÿ��״̬s��������д���ԭ���еĳ��ִ�����ÿ�γ��ֵ��Ҷ˵���ͬ��
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=1e6+3;

struct Suffix_Automaton
{
	int T,K,L,las,tot,fa[N],son[N][26],len[N],sz[N],right[N],A[N],tm[N];
	char s[N>>1];
	void Insert(int c)
	{
		int p=las,np=++tot; len[las=np]=len[p]+1;
		for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot; len[nq]=len[p]+1;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Build()
	{
		scanf("%s",s), las=tot=1, L=strlen(s);
		for(int i=0; i<L; ++i) Insert(s[i]-'a');
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=L; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;
	}
	void Query()
	{
		scanf("%d%d",&T,&K);
		if(!T) for(int i=1; i<=tot; ++i) sz[i]=right[i]=1;
		else{
			for(int p=1,i=0; i<L; ++i) ++right[p=son[p][s[i]-'a']];
			for(int i=tot,x=A[i]; i; x=A[--i]) right[fa[x]]+=right[x];//x not i!
			for(int i=1; i<=tot; ++i) sz[i]=right[i];
		}
//		sz[0]=sz[1]=0;
		for(int i=tot,x=A[i]; i; x=A[--i])
			for(int j=0; j<26; ++j) sz[x]+=sz[son[x][j]];
//		sz[1]=0;
		if(K>sz[1]) {printf("-1"); return;}//��ʵ��û�����������Ҫ�����-1��10����233 
		int p=1;
		while(K>0)
		{
			for(int i=0; i<26; ++i)
				if(son[p][i])//...
					if(sz[son[p][i]]<K) K-=sz[son[p][i]];
					else{
						putchar(i+'a'), K-=right[p=son[p][i]];
						break;
					}
		}
	}
}sam;

int main()
{
	sam.Build(), sam.Query();
	return 0;
}
