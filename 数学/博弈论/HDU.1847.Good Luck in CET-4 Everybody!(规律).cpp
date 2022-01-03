//%3!=0一定是必胜态，否则必败。因为3及3x是一个必败态，而3x+1,3x+2均能走到一个3x，3x走不到一个必败态3y。 
#include <cstdio>

int main()
{
	int n;
	while(~scanf("%d",&n)) puts(n%3?"Kiki":"Cici");
	return 0;
}
