#include <bits/stdc++.h>
using namespace std;

struct StringHash
{
    const long long p1 = 31, p2 = 53, m1 = 1e9 + 7, m2 = 1e9 + 9;
    vector<long long> pw1, pw2, h1, h2, ipw1, ipw2;
    string s;

    long long power(long long a, long long b, long long mod)
    {
        long long res = 1;
        while (b)
        {
            if (b & 1)
                res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }

    void build(const string &str)
    {
        s = " " + str;
        int n = s.size() - 1;
        pw1.resize(n + 1);
        pw2.resize(n + 1);
        ipw1.resize(n + 1);
        ipw2.resize(n + 1);
        h1.resize(n + 1);
        h2.resize(n + 1);
        pw1[0] = pw2[0] = 1;
        h1[0] = h2[0] = 0;

        for (int i = 1; i <= n; i++)
        {
            pw1[i] = (pw1[i - 1] * p1) % m1;
            pw2[i] = (pw2[i - 1] * p2) % m2;
            h1[i] = (h1[i - 1] + (long long)s[i] * pw1[i - 1]) % m1;
            h2[i] = (h2[i - 1] + (long long)s[i] * pw2[i - 1]) % m2;
        }

        ipw1[n] = power(pw1[n], m1 - 2, m1);
        ipw2[n] = power(pw2[n], m2 - 2, m2);
        for (int i = n - 1; i >= 0; i--)
        {
            ipw1[i] = ipw1[i + 1] * p1 % m1;
            ipw2[i] = ipw2[i + 1] * p2 % m2;
        }
    }

    pair<long long, long long> get_hash(int l, int r)
    {
        if (l > r)
            return {0, 0};
        long long hh1 = (h1[r] - h1[l - 1] + m1) % m1 * ipw1[l - 1] % m1;
        long long hh2 = (h2[r] - h2[l - 1] + m2) % m2 * ipw2[l - 1] % m2;
        return {hh1, hh2};
    }

    pair<long long, long long> get_rev_hash(int l, int r)
    {
        if (l > r)
            return {0, 0};
        long long hh1 = 0, hh2 = 0;
        for (int i = r, j = 0; i >= l; i--, j++)
        {
            hh1 = (hh1 + (long long)s[i] * pw1[j]) % m1;
            hh2 = (hh2 + (long long)s[i] * pw2[j]) % m2;
        }
        return {hh1, hh2};
    }
};

struct SimpleHash
{
    long long p = 31, m = 1e9 + 9;
    vector<long long> pw, h;
    string s;

    void build(string str)
    {
        s = " " + str;
        int n = s.size() - 1;
        pw.resize(n + 1);
        h.resize(n + 1);
        pw[0] = 1;
        h[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            pw[i] = (pw[i - 1] * p) % m;
            h[i] = (h[i - 1] + (long long)s[i] * pw[i - 1]) % m;
        }
    }

    long long get(int l, int r)
    {
        if (l > r)
            return 0;
        long long res = (h[r] - h[l - 1] + m) % m;
        return res;
    }
};

int main()
{
    string s;
    cin >> s;
    StringHash sh;
    sh.build(s);
    auto h1 = sh.get_hash(1, 3);
    auto h2 = sh.get_hash(3, 5);
    if (h1 == h2)
        cout << "Found matching substrings!\n";

    if (sh.get_hash(1, s.size()) == sh.get_rev_hash(1, s.size()))
        cout << "Palindrome!\n";

    return 0;
}