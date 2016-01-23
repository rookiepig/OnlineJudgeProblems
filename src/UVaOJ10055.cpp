// 10055 - Hashmat the Brave Warrior
// easy problem
// do not use abs...

#include<stdio.h>
#include<stdlib.h>

int main(void) {
	long long a = 0, b = 0;
	while (scanf("%lld%lld", &a, &b) != EOF) {
		if (a > b) {
			printf("%lld\n", a - b);
		}
		else {
			printf("%lld\n", b - a);
		}
	}
	return 0;
}