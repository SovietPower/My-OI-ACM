/*
62ms	400KB
$Description$
������Ϊn����Сд��ĸa~f��ɵ��ַ���s����m�����ƣ�������$pos_i$��ֻ����ĳЩ��ĸ���($pos$������ͬ)��
��������⽻��ԭ��������ĸ��λ�ã����Ƿ��ܵõ��������Ƶ��ַ��������ܣ�����������Ƶ���С�ֵ�����ַ�����
$Solution$
��n���ַ���ÿ���ַ����Է���ĳЩλ�ã�Ҫ����Щ�ַ�ȫ������->�걸ƥ�䡣
�����������������������Ƿ����n�����߱ȽϺ��롣Ȼ�������Ҫ��iλ�÷��ַ�c�����ԭ���������Ҫc->i�����ߣ���ô���ԣ�����������������������-1���ټ��������Ƿ����n��
���������λ��i���ַ�c����ôҪʹc->i�����ߵ�����-1.
ûд����һ���������е㡣��Tutorial��˵���Ӷ�$O(n*2^A*A^2)$(AΪ�ַ�����С)����֪��$2^A$��Ϊʲô����

���Կ���Hall������������һ���ַ����Ӽ��������ַ�����Ҫ<=�ܹ�ƥ�������ַ���λ�ø�����
�����Ļ�����ͬһ���ַ�����Ȼֻ��Ҫ��������������Ӽ���λ��������䣩����������Ҫ�����Ӽ�ֻ��$2^A=64$��(AΪ�ַ�����С)��
�����Ӽ������ַ��ĸ���sum����$O(A*2^A)$��$O(2^A)$�㡣����(ֻҪ)�ܹ�ƥ��ĳ�Ӽ�s�������ַ� ��λ�������ǿ���ȥ�㣺λ������-ֻ��ƥ���s���ַ����λ������
��s���ַ�����Ӽ����Ա�ʾΪ2^A-1-s��Ԥ����������������Ӽ���λ�������ɣ���Ϊf[]��
�������Ҫȷ��iλ�÷�ʲô����Ҫ�ȼ���i��f�Ĺ��ף���ö�����а��� λ��i�ɷ��ַ��Ӽ� ���Ӽ�������-1��Ҫ��ĳ�ַ�����Ҫ�ܷţ�Ȼ������-1����Check�����ˡ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define lb(i) (i&-i)
const int N=1e5+7;

int n,num[7],can[N],sum[69],f[69],bit[69];
char s[N],tmp[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool Check()
{
	for(int i=1; i<64; ++i)
	{
		sum[i]=sum[i^lb(i)]+num[bit[lb(i)]];
		if(sum[i]>f[63]/*not n��or nҲ-1*/-f[63-i]) return 0;
	}
	return 1;
}

int main()
{
	scanf("%s",s+1), n=strlen(s+1);
	for(int i=1; i<=n; ++i) can[i]=63, ++num[s[i]-'a'];
	for(int m=read(),p; m--; )
	{
		can[p=read()]=0, scanf("%s",tmp+1);
		for(int j=1,l=strlen(tmp+1); j<=l; ++j)
			can[p]|=1<<tmp[j]-'a';
	}
	for(int i=1; i<=n; ++i) ++f[can[i]];
	for(int i=0; i<6; ++i)//��������������Ӽ� ��ö��i��
		for(int j=1; j<64; ++j)
			if(j>>i & 1)
				f[j]+=f[j^(1<<i)];
	for(int i=0; i<6; ++i) bit[1<<i]=i;
	if(!Check()) return puts("Impossible"),0;
	for(int i=1; i<=n; ++i)
	{
		for(int s=can[i]; s<=63; s=(s+1)|can[i]) --f[s];
		for(int j=0; j<6; ++j)
		{
			if(!(can[i]>>j&1)) continue;
			--num[j];
			if(Check()) {putchar(j+'a'); break;}
			++num[j];
		}
	}
	return 0;
}
