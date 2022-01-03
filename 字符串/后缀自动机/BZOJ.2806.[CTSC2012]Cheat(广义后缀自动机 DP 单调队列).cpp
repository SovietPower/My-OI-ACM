/*
63128kb	820ms
���ȶ��ִ�L��Ȼ������ж��ܷ�ԭ�����ֳ�һЩ���Ȳ�С��L���Ӵ�����Щ�Ӵ�Ҫ�Ǹ���n�����е�ĳ�������Ӵ������������ǵĳ���֮�Ͳ�С��ԭ�����ȵ�90%��
̰�Ķ೤ѡһ��ʲô����Ȼ���ԡ�����ʵʵDP��
��f[i]Ϊ��i���ֳ�������ȣ�������ʲô����ֵֹ�״̬����_��������f[i]=max{f[i-1],f[j]+i-j}(s[i~j]Ϊn������ĳ�����Ӵ�����i-j>=L)��
����ĳλ�ý�β���Ӵ��Ƿ�ƥ�䣬���Զ�n����������SAM��ԭ��������ƥ����ܵõ�ÿ��λ����Ϊ��׺����ƥ�����󳤶ȣ���Ϊmx[i]��
��ôj�ķ�Χ����i-mx[i]<=j<=i-L.
����n^2�ģ�Ҫ�Ż�����Ϊ̰�Ĳ��ԣ������ڵ�������Ҫ�����Ը���һ��ġ��۲����λ���Ƿ��е����ԣ�����i��i+1����mx[i]+1>=mx[i+1]��
mx[i]+1>=mx[i+1]
i-mx[i]<=i+1-mx[i+1] (�ո�i+1)
������λ���ǵ��������ġ�ֻ���õ�������ά����ǰ����f[j]-j����ֵ�Ϳ����ˡ�
���⿨���ȣ�0.9*n��ƫ��Ҫ����eps���������ٿ��������洢...̫sxbk�˰ɣ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define eps 1e-8
const int N=2200007;//�ֽڡ���

int n,m;
struct Suffix_Automaton
{
	int tot,las,son[N][2],fa[N],len[N],mx[N],q[N],f[N];
	char s[N];

	Suffix_Automaton() {tot=las=1;}
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
		scanf("%s",s), las=1;//!
		for(int i=0,l=strlen(s); i<l; ++i) Insert(s[i]-'0');
	}
	void Get_mx(char *s)
	{
		for(int c,now=0,p=1,i=1,l=strlen(s+1); i<=l; mx[i++]=now)
			if(son[p][c=s[i]-'0']) ++now, p=son[p][c];
			else
			{
				for(; p&&!son[p][c]; p=fa[p]);
				if(!p) now=0, p=1;
				else now=len[p]+1, p=son[p][c];
			}
	}
	bool Check(int L,int n)
	{
		int h=1,t=0; f[0]=0;
		for(int i=1; i<=n; ++i)
		{
			f[i]=f[i-1];
			if(i>=L && L<=mx[i])
			{
				int p=i-L;
				while(h<=t && f[q[t]]-q[t]<=f[p]-p) --t;
				q[++t]=p;
			}
			while(h<=t && q[h]<i-mx[i]) ++h;
			if(h<=t) f[i]=std::max(f[i],i+f[q[h]]-q[h]);//����f[0]=INF��̫���� 
		}
		return (double)f[n]>=0.9*n-eps;//0.89999999
	}
	void Query()
	{
		scanf("%s",s+1), Get_mx(s);
		int len=strlen(s+1);
		int l=1,r=len,mid,ans=0;
		while(l<=r)
			if(Check(mid=l+r>>1,len)) ans=mid,l=mid+1;
			else r=mid-1;
		printf("%d\n",ans);
	}
}sam;

int main()
{
	scanf("%d%d",&n,&m);
	while(m--) sam.Build();
	while(n--) sam.Query();
	return 0;
}
