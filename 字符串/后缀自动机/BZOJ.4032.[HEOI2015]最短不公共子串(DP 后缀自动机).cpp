/*
17224kb	528ms
1.��A������Ӵ���������B���Ӵ���
�Ӵ��������ģ���B��SAM��ö����㣬��SAM���ҵ���һ���޷�ƥ��㼴�ɡ�O(n)��SAM�����𡣡���ʼ����ˡ�
2.��A������Ӵ���������B�������С�
������...ֱ�ӽ�SAMûɶ�á�����A[i]����һλA[i-1]����f[i][j]��ʾ��A[i]ƥ�䵽B[j]ʱ������A���Ӵ����ȣ����A[i]==B[j]����f[i][j]=max{f[i-1][k]+1}(k<j)��
��ȡmax������ΪB�ᾡ����ƥ�䡣ö����B[n]����max{f[i][k]}!=i(����A[i]ǰ��һλ)������max{f[i][k]}+1���´𰸡�
3.��A����������У�������B���Ӵ���
�����еĻ�����ǰ��Ļ�Ժ���Ĳ���Ӱ�졣��Ϊ��B���Ӵ����������ǻ�����SAM������
��f[p]��ʾƥ�䵱SAM�ϵ�p��ʱ AĿǰ��������еĳ��ȡ�����ÿ��A[i]��ö�ٵ�p����p��A[i]��ת��Ϊ0����ô�����õ�ǰ��f[p]���´𰸣�����f[ת�Ƶ�]=min(f[ת�Ƶ�],f[p]+1)��
f[1]=0������ΪINF��ֻ�дӸ��ڵ㿪ʼ�߲���B���Ӵ���
4.��A����������У�������B�������С�
��son[i][c]��ʾ����ǰΪA[i]�������i���������A[j]==c��j���ġ�ת�Ʋ��䣬f[j]=min(f[j],f[i]+1)��
Ҳ���Խ������Զ���...�����Զ������۸��Ӷ���O(n^2)�ģ���Ϊÿ����һ���ַ���֮ǰû�и�ת�Ƶĵ㶼Ҫ�������ߡ�
Ϊ�˲�����ô������ö�����е㣬���Զ�ÿ���ַ�ά��һ��las[c']�����ϴβ���c'����λ�á�����cʱö������c'����las[c']���ϸ�������ֱ����ת�ơ�

ע��4.��DPҪ����ö�٣�����ĳλ�ñ�A[i]���¶�Ρ��о�3.Ҳ��Ҫ����ʵ�ʲ��ã���֪��Ϊʲô����
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2007;

int n,m;
char A[N],B[N];
struct Suffix_Automaton
{
	#define S 4007
	int n,tot,las,fa[S],son[S][26],len[S];

	Suffix_Automaton() {tot=las=1;}
	void Insert(int c)
	{
		int np=++tot,p=las; len[las=np]=len[p]+1;
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
				fa[nq]=fa[q], fa[np]=fa[q]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Build(char *s)
	{
		las=tot=1, n=strlen(s+1);
		for(int i=1; i<=n; ++i) Insert(s[i]-'a');
	}
}sam;

void Solve1()
{
	int ans=N;
	for(int i=1; i<=n; ++i)
		for(int j=i,p=1,now=1; j<=n; ++j)
			if(sam.son[p][A[j]-'a']) ++now, p=sam.son[p][A[j]-'a'];
			else {ans=std::min(ans,now); break;}
	printf("%d\n",ans==N?-1:ans);
}
void Solve2()
{
	static int f[N][N];
	int ans=N;
	for(int i=1; i<=n; ++i)
	{
		int bef=0,mx=0;
		for(int j=1; j<=m; ++j)
		{
			if(A[i]==B[j]) f[i][j]=bef+1;
			mx=std::max(mx,f[i][j]);
			bef=std::max(bef,f[i-1][j]);
		}
		if(mx!=i) ans=std::min(ans,mx+1);//, printf("%d %d\n",i,mx);
	}
	printf("%d\n",ans==N?-1:ans);
}
void Solve3()
{
	static int f[S];//2N!
	memset(f,0x3f,sizeof f);
	f[1]=0; int ans=N;
	for(int i=1; i<=n; ++i)
		for(int j=1,t,tot=sam.tot; j<=tot; ++j)
			if(!(t=sam.son[j][A[i]-'a'])) ans=std::min(ans,f[j]);
			else f[t]=std::min(f[t],f[j]+1);
	printf("%d\n",ans==N?-1:ans+1);
}
void Solve4()
{
	static int f[N],son[N][26],las[26];
	B[0]='a';
	for(int i=m; ~i; --i)
	{
		for(int j=0; j<26; ++j) son[i][j]=las[j];
		las[B[i]-'a']=i;
	}
	memset(f,0x3f,sizeof f);
	f[0]=0/*0����������ת�� ��0Ϊ���ڵ�*/; int ans=N;
	for(int i=1; i<=n; ++i)
		for(int j=m,t; ~j; --j)
			if(!(t=son[j][A[i]-'a'])) ans=std::min(ans,f[j]);
			else f[t]=std::min(f[t],f[j]+1);
	printf("%d\n",ans==N?-1:ans+1);
}

int main()
{
	scanf("%s%s",A+1,B+1), n=strlen(A+1), m=strlen(B+1);
	sam.Build(B);
	Solve1(), Solve2(), Solve3(), Solve4();

	return 0;
}
