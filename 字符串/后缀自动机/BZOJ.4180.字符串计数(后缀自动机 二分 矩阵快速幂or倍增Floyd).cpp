/*
10296kb	384ms
�ȿ��� ����Sȷ����ʹ����S����������С�ķ���Ӧ�ǣ���T��SAM��S��SAM��ƥ�䣬�����S��ת�ƾ�ת�ƣ����������++���ᵽ���ڵ����ƥ��S����ÿ�β���һ����һ�μ���ƥ�䡣
��֤��������S="ABCD"��T���Ӵ�"A","AB","CD","BCD"����ô������С������ѡ"AB"�ٽ���"CD"����������ǰ�Ͽ�ѡ��"A"+"BCD"����Ϊ����ֻ��ʹ������Ӵ��䳤��"CD"�п��ܼ������Ӵ���"BCD"ȴ���ܡ�
��ô���ڱ��⣬����Ҫʹ���������࣬ƴ�ӵ��Ӵ������̣�Ӧ��ѡ����̵ĵ���һ������ƥ��ĳ�ַ���λ�ã���!son[x][c]����ô�´α��ǴӸ���son[root][c]����һ�������ַ������·���ߡ�
�����ַ�����Сֻ��4����f[i][j]��ʾ�Ӹ��ڵ����ַ�i���߳���������ĳ��û���ַ�jת�ƵĽڵ�����·����
��ô���β����γɵ�S����Ϊl[i][k]=f[i][j]+f[j][k]�����ǿ��Ƕ��ֲ�������m����m�β�������Եõ���S��̵ĳ����Ƿ�<=n�������þ��������/����Floyd����ת�ơ�
f������SAM������g[x][c]��ʾ��x�ڵ㵽��һ��û��cת�ƵĽڵ����̾��룬��g[x][c]=min{g[son[x]][c]+1}��
���f[i][j]=g[son[1][i]][j]+1��
�������ֱ��ת��Ϊͼ�����⡣�����ת�Ʊ߱�ȨΪ0������ת�Ƶ����ظ��ڵ��Ӧת�Ƶ㣬��ȨΪ1����ô���ǴӸ��ڵ��������n����������ֵ����������û�õı�Ȼ�����+����Floyd��
����ö���ӽڵ����fa[x] ����ö��son[x]����x��mdzz��
����������ﵽlonglong����
INFҪ��Ϊ2e18����1e18������minlen==nʱֱ��ans=mid,break���ԡ������������������ⲻ�ԣ� 
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=2e5+7;
const LL INF=2e18;//!...

struct Suffix_Automaton
{
	int tot,las,fa[N],son[N][4],len[N],A[N],tm[N],g[N][4],f[4][4];
	LL n;//,g[N][4],f[4][4];
	char s[N>>1];
	struct Matrix
	{
		LL a[4][4];
		Matrix operator *(const Matrix &x)const
		{
			Matrix res;
			for(int i=0; i<4; ++i)
				for(int j=0; j<4; ++j)
				{
					LL tmp=INF;
					for(int k=0; k<4; ++k)
						tmp = std::min(tmp, a[i][k]+x.a[k][j]);
					res.a[i][j]=tmp;
				}
			return res;
		}
	}Base;
	Matrix FP(Matrix x,LL k)
	{
		Matrix t=x;
		for(--k; k; k>>=1, x=x*x)
			if(k&1) t=t*x;
		return t;
	}
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
		las=tot=1;
		scanf("%lld%s",&n,s+1); int l=strlen(s+1);
		for(int i=1; i<=l; ++i) Insert(s[i]-'A');
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=l; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;

		memset(g,0x3f,sizeof g);
		for(int i=1; i<=tot; ++i)
			for(int j=0; j<4; ++j)
				if(!son[i][j]) g[i][j]=0;
		for(int i=tot,x=A[i]; i; x=A[--i])
			for(int j=0,s; j<4; ++j)
				if(s=son[x][j])
					for(int k=0; k<2; ++k)
						g[x][k]=std::min(g[x][k],g[s][k]+1),
						g[x][k+2]=std::min(g[x][k+2],g[s][k+2]+1);//�е�...����û��չ��...
		for(int i=0; i<4; ++i)
			for(int j=0; j<4; ++j)
				Base.a[i][j]=g[son[1][i]][j]+1;
	}
	int Check(LL x)
	{
		Matrix res = FP(Base,x);
		int s=0;
		for(int i=0; i<4; ++i)
			for(int j=0; j<4; ++j)
				if(res.a[i][j]==n) s=1;
				else if(res.a[i][j]<n) return 2;
		return s;//��̳���=n�Ѿ������� <n��x��һ������ 
	}
	void Solve()
	{
		LL l=1,r=n,mid,ans=1,s;
		while(l<=r)
		{
			if((s=Check(mid=l+r>>1))==1) {ans=mid; break;}//ans=mid, r=mid-1;
			else if(!s) r=mid-1;
			else ans=l=mid+1;
		}
		printf("%lld\n",ans);
	}
}sam;

int main()
{
	sam.Build(), sam.Solve();
	return 0;
}
