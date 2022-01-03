/*
���⣺����һ���ַ����������ֲ��������ַ����в���һ���ַ���ѯ��ĳ����λ�ÿ�ʼ��LCP�ĳ��� 

�����Hash��LCP����ͨ�� ����+Hash ��� 
�����޸Ĵ�����С��ֻ��200��ֱ�ӱ����޸��ع� Hash 

����������len����Ҫ����l�ˡ��� 
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ULL unsigned long long
using namespace std;
const int N=51000,base=131;

int n,len,pos[N];
char s[N];
ULL pw[N],hs[N];

void Init(int fr)
{
	for(int i=fr;i<=len;++i)
		hs[i]=hs[i-1]*base+s[i];
}
ULL Get_Hash(int l,int r)
{
	return hs[r]-hs[l-1]*pw[r-l+1];
}
int Solve(int x,int y)
{
	int l=0,r=len-max(x,y)+1,m;
	while(l<=r)
	{
		m=l+r>>1;
		if(Get_Hash(x,x+m-1)==Get_Hash(y,y+m-1)) l=m+1;
		else r=m-1;
	}
	return r;
}

int main()
{
//	freopen("2758.in","r",stdin);

	pw[0]=1;
	for(int i=1;i<N;++i)
		pw[i]=pw[i-1]*base;
	
	scanf("%s",s+1);
	n=len=strlen(s+1);
	Init(1);
	for(int i=1;i<=n;++i)
		pos[i]=i;
	int t,a,b;char opt[5];
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",opt);
		if(opt[0]=='Q')
		{
			scanf("%d%d",&a,&b);
			printf("%d\n",Solve(pos[a],pos[b]));
		}
		else
		{
			scanf("%s%d",opt,&a);
			++len;
			if(a>len) a=len;
			memcpy(s+a+1,s+a,(len-a)*sizeof(char));
			s[a]=opt[0];
			for(int i=n;pos[i]>=a;--i)//ÿһλ���ƣ��������� 
				++pos[i];
			Init(a);
		}
	}
	return 0;
}
