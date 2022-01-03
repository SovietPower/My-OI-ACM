/*
2384kb	288ms
ֱ��������Ȼ��ô�����С�
�Ȱ��ٻ�ʱ����������������ģ���;�����ٸ��޵Ľ�����
ö��ÿ������x������ܣ����ޣ����ܵĻ�����֮ǰҪ�޵Ľ�������һ����ʱ����need[top]�����need[x]<need[top]�������top������x��
����ÿ�����Ҳ����һ����һ�������ܱ�֤���š�
�ö�ά�����ɡ�

������ô����DP ��_��
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define pr std::pair<int,int>
#define gc() getchar()
const int N=150007;

int n;
pr s[N];
std::priority_queue<int> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) s[i].second=read(),s[i].first=read();
	std::sort(s+1,s+1+n);
	int now=0;
	for(int i=1; i<=n; ++i)
		if(now+s[i].second<=s[i].first) now+=s[i].second, q.push(s[i].second);
		else if(s[i].second<q.top() && now+s[i].second<=s[i].first+q.top()){
			now-=q.top(), q.pop(), q.push(s[i].second);
			now+=s[i].second;
		}
	printf("%d",q.size());

	return 0;
}
