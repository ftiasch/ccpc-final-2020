#include <bits/stdc++.h>

const int MOD = 1e9 + 7;

const int NUM[] = {1, 2, 1009, 2018};

int solve(std::vector<int>& a, int n, int m, int i)
{
    if (i == n * m) {
        return 1;
    }
    int result = 0;
    for (a[i] = 0; a[i] < 4; ++ a[i]) {
        int x = i / m;
        int y = i % m;
        if (x && NUM[a[i - m]] % NUM[a[i]] != 0) {
            continue;
        }
        if (y && NUM[a[i - 1]] % NUM[a[i]] != 0) {
            continue;
        }
        result += solve(a, n, m, i + 1);
        if (result >= MOD) {
            result -= MOD;
        }
    }
    return result;
}

int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        std::vector<int> a(n * m);
        a[0] = 3;
        printf("%d\n", solve(a, n, m, 1));
    }
}
