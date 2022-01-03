/*
通过两次可以先确定首字母。然后还剩下n-1位，之后每一位只有三种可能。
最简单的方法是每次确定一位，通过两次询问显然可以确定。但是只能一次询问。
首字母只会出现一次，即我们可以将串分割成4个进行一次询问。我们是可以一次询问确定一位的。
比如：首字母为a，其它字母为bcd，ans为已确定的前i-1位，则询问ans+bb+ans+bc+ans+bd+ans+c，就能确定i了。
这样第n位我能需要单独判断，可以直接用两次。
则总询问次数为：2+n-2+2=n+2。
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
