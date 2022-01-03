/*
24612kb	76ms
$Description$
����n��ģʽ����m��ѯ��һ�����ڶ��ٸ�ģʽ���г��ֹ���(�ַ���Ϊ26��Сд��ĸ)
$Solution$ 
��ÿ��ѯ�ʴ�����ƥ�����ջ�ﵽһ���ڵ㣬������Ҫ�õ�����ڵ���������Ӵ������ڶ��ٸ�ģʽ���С�
���������׺�Զ�����ÿ�β���һ��������root��ʼ������SAM��ÿ���ڵ�ά��cnt��bef���ֱ��ʾ�ýڵ����Ĵ������ڼ���ģʽ���� �� �ýڵ�������ĸ�ģʽ�����¹�cnt��
����bef[i]!=now�Ľڵ㣬++cnt[i],bef[i]=now����ģʽ��now�´�ƥ�䵽��ǰ�ڵ�ʱ���ٸ��¡�
���⣬���ƥ���˵�ǰ�ڵ�i��ôһ����ƥ����fa[i],fa[fa[i]]...������ǵ�bef[]!=now���򶼸���һ�顣ֱ���и��ڵ�p����bef[p]==now����ô�Ͳ���Ҫ�����ϸ����ˣ��������Ѿ����¹��ˣ���(�����insert����np���¾Ϳ��԰�)
ע���½�nqʱ bef[nq],cnt[nq]ҲҪ����(=..[q])��
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

struct Suffix_Automaton
{
	int las,tot,fa[N],son[N][26],len[N],cnt[N],bef[N];
	char s[360005];

	void Init(){
		las=tot=1;
	}
	void Insert(int now,int c)
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
				int nq=++tot;
				len[nq]=len[p]+1, bef[nq]=bef[q], cnt[nq]=cnt[q];//!
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
		for(; bef[np]!=now&&np; np=fa[np])
			++cnt[np], bef[np]=now;
	}
	void Build(int now)
	{
		las=1, scanf("%s",s);
		for(int i=0,l=strlen(s); i<l; ++i)
			Insert(now,s[i]-'a');
	}
	void Query()
	{
		int p=1; scanf("%s",s);
		for(int i=0,l=strlen(s); i<l&&p; ++i)
			p=son[p][s[i]-'a'];
		printf("%d\n",cnt[p]);
	}
}sam;

int main()
{
	int n,Q; scanf("%d%d",&n,&Q); sam.Init();
	for(int i=1; i<=n; ++i) sam.Build(i);
	while(Q--) sam.Query();

	return 0;
}
