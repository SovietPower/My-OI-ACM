/*
ͨ�����ο�����ȷ������ĸ��Ȼ��ʣ��n-1λ��֮��ÿһλֻ�����ֿ��ܡ�
��򵥵ķ�����ÿ��ȷ��һλ��ͨ������ѯ����Ȼ����ȷ��������ֻ��һ��ѯ�ʡ�
����ĸֻ�����һ�Σ������ǿ��Խ����ָ��4������һ��ѯ�ʡ������ǿ���һ��ѯ��ȷ��һλ�ġ�
���磺����ĸΪa��������ĸΪbcd��ansΪ��ȷ����ǰi-1λ����ѯ��ans+bb+ans+bc+ans+bd+ans+c������ȷ��i�ˡ�
������nλ������Ҫ�����жϣ�����ֱ�������Ρ�
����ѯ�ʴ���Ϊ��2+n-2+2=n+2��
*/
#include <string>
#include <algorithm>
#include "combo.h"

std::string guess_sequence(int n)
{
	char a,b,c,d;
	std::string ans="";
	if(press("AB")) c='X', d='Y', press("A")?(b='B',a='A'):(b='A',a='B');
	else c='A', d='B', press("X")?(b='Y',a='X'):(b='X',a='Y');
	ans=a;
	if(n==1) return ans;//!
	for(int i=1,t; i<n-1; ++i)
	{
		if((t=press(ans+b+b+ans+b+c+ans+b+d+ans+c))==i) ans+=d;
		else if(t==i+1) ans+=c;
		else ans+=b;
	}
	if(press(ans+b)==n) ans+=b;
	else if(press(ans+c)==n) ans+=c;
	else ans+=d;
	return ans;
}
