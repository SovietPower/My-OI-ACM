#include <map>
#include <set>
#include <cstdio>
#include <cctype>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
//#define mp std::make_pair
//#define pr std::pair<int,int>
#define pc putchar
#define gc() getchar()
using namespace std;
typedef long long LL;
const int N=1e5+5;
const char BEG[35]={"\\begin{thebibliography}{99}"};
const char END[35]={"\\end{thebibliography}"};
const string BEG_str[]="\\begin{thebibliography}{99}";

map<string,int> mp;
string A[N],B[N],Ans[N];
char tmp[N],tmp2[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
bool Begin(int t)
{//\begin{thebibliography}{99}
	if(t!=27) return 0;
	for(int i=1; i<t; ++i) if(tmp[i]!=BEG[i]) return 0;
	return 1;
}
bool End(int t)
{
	if(tmp[0]=='\\'&&tmp[1]=='e'&&tmp[2]=='n'&&tmp[3]=='d'&&tmp[4]=='{') return 1;
	return 0;
}

int main()
{
	#define MAX 100001
	char c; int cnt=0;
	while(1)
	{
		int t=0;
		while((c=gc())!=' '&&c!='.'&&c!=','&&c!=39&&c!='\n'&&c!='\r') tmp[t++]=c;
		if(!t) continue;
		tmp[t]='\0';
		if(tmp[0]=='\\'&&!Begin(t))
		{
			while(tmp[t-1]!='}') --t; --t;
			int t2=0;
			for(int i=6; i<t; ++i) tmp2[t2++]=tmp[i];
			tmp2[t2]='\0';
			A[++cnt]=tmp2, mp[A[cnt]]=cnt;
//			cout << cnt << ":" << A[cnt] << '\n';
		}
		else if(tmp[0]=='\\') break;
		tmp[0]='a';
	}
	bool OK=1; int now=0;
	while(1)
	{
		cin.getline(tmp,MAX); int t=strlen(tmp);
		if(Begin(t)) continue;
		if(End(t)) break;
		int t2=0; t=9;
		while(tmp[t]!='}') tmp2[t2++]=tmp[t++];
		tmp2[t2]='\0';
		string s=tmp2; Ans[t2=mp[s]]=tmp;
		if(t2!=++now) OK=0;
	}
	if(OK) return puts("Correct"),0;
	puts("Incorrect");
	puts(BEG);
	for(int i=1; i<=cnt; ++i) cout << Ans[i] << '\n';
	puts(END);

	return 0;
}
