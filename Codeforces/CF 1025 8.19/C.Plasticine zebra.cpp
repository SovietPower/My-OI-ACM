/*
��Щ�����Կ��Է��֣���ֻ�������ַ����治����Ϊʲô��abcd�԰��죩��������ô�ж��൱�ڽ���ѭ������ĳЩ���ȡ�
������ѭ����ʾ������ľͿ����ˡ�ע��𰸶�ԭ������ȡmin��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

char s[N];

int main()
{
	scanf("%s",s+1);
	int l=strlen(s+1),res=0;
	for(int i=1; i<=l; ++i) s[i+l]=s[i];
	l<<=1;
	for(int now=1,i=2; i<=l; ++i,res=std::max(res,now))
		if(s[i]!=s[i-1]) ++now;
		else now=1;
	printf("%d\n",std::min(res,l>>1));

	return 0;
}
