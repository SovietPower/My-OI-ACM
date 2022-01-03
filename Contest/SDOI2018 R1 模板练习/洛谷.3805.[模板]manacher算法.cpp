/*
记录当前ex[]最大的回文中心id和最远延伸范围mx！
关于串的构造: 
应该是 @ #A#B#C#B#A# $，而不是 @ A#B#C#B#A $ 
比如 @a#b#b#c$，答案应是max{ex[i]}-1，而第二种很多情况下答案是max{ex[i]}.
最优解不改串分奇偶讨论感觉sxbk。。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=22000010;

int n,ex[N];
char tmp[N>>1],s[N];

void Init()
{
	n=strlen(tmp), s[0]='@';
	for(int i=0; i<n; ++i)
		s[i<<1|1]='#', s[(i<<1)+2]=tmp[i];
	s[n=2*n+2]='$', s[n-1]='#';
}
void Manacher()
{
	int res=0,mx=0,id;
	for(int i=1; i<n; ++i)
	{
		if(i<mx) ex[i]=std::min(ex[id*2-i],mx-i);
		else ex[i]=1;
		while(s[i+ex[i]]==s[i-ex[i]]) ++ex[i];
//		if(ex[i]>res) res=ex[i];//不在这更新也对，懒得想了。。
		if(i+ex[i]>mx) id=i,mx=i+ex[i],res=std::max(res,ex[i]);
	}
	printf("%d",res-1);
}

int main()
{
	scanf("%s",tmp), Init(), Manacher();
	return 0;
}
