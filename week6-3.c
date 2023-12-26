//이진 탐색 응용
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int findElement(int l, int r, char *s, int n) {
    for (int i = 0; i < n; i++) {
        int mid = (l + r) / 2;
        if (s[i] == 'Y')
            l = mid + 1;
        else if (s[i] == 'N')
            r = mid;
    }
    return (l + r) / 2;
}

int main()
{
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);

    char YesNo[n];
    scanf("%s", YesNo);

    printf("%d\n", findElement(a, b, YesNo, n));
    
    return 0;
}
