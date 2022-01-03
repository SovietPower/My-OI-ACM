/*
$Description$
������s������һ���������������������Ϊ2��3�ĺ�׺�����ɣ�Ҫ�����������>4�����ں�׺������ͬ���ڻ���������ȷ��������£������п��ܵĺ�׺����
$|s|\leq 10^4$��
$Solution$
�Ѵ���������ǰ׺����Щ��
���Ե�dp��f[i][2/3]��ʾ��ǰ��i����һ����׺������Ϊ2/3�Ƿ���С���ת�Ʊ߸��´𰸾����ˡ�
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define pc putchar
const int N=10005;

int n;
bool f[N][2]/*0:2 1:3*/,ok2[28][28],ok3[28][28][28];
char s[N];

int main()
{
	scanf("%s",s+1), n=strlen(s+1);
	std::reverse(s+1,s+1+n);

	int tot=0; n-=5;
	if(n>=2) f[2][0]=1, ++tot, ok2[s[2]-'a'][s[1]-'a']=1;
	if(n>=3) f[3][1]=1, ++tot, ok3[s[3]-'a'][s[2]-'a'][s[1]-'a']=1;

	for(int i=4; i<=n; ++i)
	{
		int a=s[i]-'a', b=s[i-1]-'a', c=s[i-2]-'a';
		if(f[i-2][1]||(f[i-2][0]&&(s[i]!=s[i-2]||s[i-1]!=s[i-3])))
		{
			f[i][0]=1;
			if(!ok2[a][b]) ++tot, ok2[a][b]=1;
		}
		if(f[i-3][0]||(f[i-3][1]&&(s[i]!=s[i-3]||s[i-1]!=s[i-4]||s[i-2]!=s[i-5])))//i>=6
		{
			f[i][1]=1;
			if(!ok3[a][b][c]) ++tot, ok3[a][b][c]=1;
		}
	}
	printf("%d\n",tot);
	for(int i=0; i<27&&tot; ++i)
	{
		for(int j=0; j<27; ++j)
		{
			if(ok2[i][j]) --tot,pc(i+'a'),pc(j+'a'),pc('\n');
			for(int k=0; k<27; ++k)
				if(ok3[i][j][k]) --tot,pc(i+'a'),pc(j+'a'),pc(k+'a'),pc('\n');
		}
	}

	return 0;
}
