/*
7996kb	596ms
�±ߵĲ��ԣ�Ҫ��ǡ��K�������Ǿͻ�һ�ַ�ʽ��f���岻�䣬ö����ʲô�ַ���ȥ����f���������Щ�ַ�������ƥ��ĳ��״̬(��code��...)��
Ԥ���������Щ�ַ����ڵ�iλ����ת�Ƶ�ĳ���ַ�c��dpʱ&һ��״̬���ɡ�

����˼·(�������������'?'��������ζ���ƥ��): f[i][s]��ʾ��ǰ��iλ��ƥ����ַ���Ϊs�����е��ַ�������ʱ�ķ�������
ö�ٳ��ȡ�s��ÿ��������s�����C(15,7)=6435�֣����Ӷ�OK��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod (1000003)
const int N=(1<<15)+3,L=55;

int n,K,bit[N],f[L][N],match[L][29];
char s[17][L];

int main()
{
	for(int i=1; i<(1<<15); ++i)
		for(int j=i; j; j>>=1) bit[i]+=j&1;
	int T; scanf("%d",&T);
	while(T--)
	{
		memset(f,0,sizeof f), memset(match,0,sizeof match);
		scanf("%d%d",&n,&K);
		for(int i=0; i<n; ++i) scanf("%s",s[i]);

		int len=strlen(s[0]),lim=1<<n;
		for(int i=0; i<len; ++i)
			for(int j=0; j<n; ++j)
				if(s[j][i]=='?') for(int k=0; k<26; ++k) match[i][k]|=(1<<j);//(1<<j)����j��
				else match[i][s[j][i]-'a']|=(1<<j);//ͬ��.
		f[0][lim-1]=1;
		for(int i=0; i<len; ++i)
			for(int j=0; j<lim; ++j)
				if(f[i][j])
					for(int k=0; k<26; ++k)//ö����һλ���ַ�k����ֻ��һ�ַ����������ǼӲ��ǳˣ�
						(f[i+1][j&match[i][k]]+=f[i][j])%=mod;
		int res=0;
		for(int i=0; i<lim; ++i)
			if(bit[i]==K) (res+=f[len][i])%=mod;
		printf("%d\n",res);
	}
	return 0;
}
