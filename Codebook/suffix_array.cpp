#include <bits/stdc++.h>
using namespace std;
struct SA
{
    string s;
    int n;
    vector<int> sa, lcp;

    SA(const string &str)
    {
        s = str + '$';
        n = s.size();
        sa.resize(n);
        lcp.resize(n - 1);
        build();
        kasai();
    }

    void build()
    {
        vector<pair<pair<int, int>, int>> t(n);
        vector<int> c(n);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&](int i, int j)
             { return s[i] < s[j]; });
        c[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            c[sa[i]] = c[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        for (int k = 1; k < n; k <<= 1)
        {
            for (int i = 0; i < n; i++)
                t[i] = {{c[i], c[(i + k) % n]}, i};
            sort(t.begin(), t.end());
            sa[0] = t[0].second;
            c[sa[0]] = 0;
            for (int i = 1; i < n; i++)
            {
                sa[i] = t[i].second;
                c[sa[i]] = c[sa[i - 1]] + (t[i].first != t[i - 1].first);
            }
        }
    }

    void kasai()
    {
        vector<int> inv(n);
        for (int i = 0; i < n; i++)
            inv[sa[i]] = i;
        int k = 0;
        for (int i = 0; i < n; i++)
        {
            if (inv[i] == n - 1)
            {
                k = 0;
                continue;
            }
            int j = sa[inv[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k])
                k++;
            lcp[inv[i]] = k;
            if (k)
                k--;
        }
    }

    // 1. Check if pattern exists
    bool contains(string pat)
    {
        int lo = 0, hi = n - 1, m = pat.size();
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            int cmp = s.compare(sa[mid], m, pat, 0, m);
            if (cmp == 0)
                return true;
            cmp < 0 ? lo = mid + 1 : hi = mid - 1;
        }
        return false;
    }

    // 2. Count occurrences
    int count(string pat)
    {
        int m = pat.size(), lo = 0, hi = n - 1, L = n, R = -1;
        // Lower bound
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            if (s.compare(sa[mid], m, pat, 0, m) >= 0)
            {
                L = mid;
                hi = mid - 1;
            }
            else
            {
                lo = mid + 1;
            }
        }
        // Upper bound
        lo = 0;
        hi = n - 1;
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            if (s.compare(sa[mid], m, pat, 0, m) <= 0)
            {
                R = mid;
                lo = mid + 1;
            }
            else
            {
                hi = mid - 1;
            }
        }
        return (L <= R) ? R - L + 1 : 0;
    }

    // 3. Find all occurrence positions
    vector<int> find(string pat)
    {
        vector<int> pos;
        int m = pat.size(), lo = 0, hi = n - 1, first = -1;
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            if (s.compare(sa[mid], m, pat, 0, m) >= 0)
            {
                first = mid;
                hi = mid - 1;
            }
            else
            {
                lo = mid + 1;
            }
        }
        if (first == -1 || s.compare(sa[first], m, pat, 0, m) != 0)
            return pos;
        for (int i = first; i < n && s.compare(sa[i], m, pat, 0, m) == 0; i++)
            pos.push_back(sa[i]);
        return pos;
    }

    // 4. Longest repeating substring
    string longestRepeat()
    {
        int mx = 0, idx = 0;
        for (int i = 0; i < n - 1; i++)
            if (lcp[i] > mx)
                mx = lcp[i], idx = sa[i];
        return s.substr(idx, mx);
    }

    // 5. Count distinct substrings
    long long distinct()
    {
        long long ans = 0;
        for (int i = 0; i < n; i++)
        {
            int len = n - sa[i] - 1; // exclude $
            ans += len;
            if (i)
                ans -= lcp[i - 1];
        }
        return ans;
    }

    // 6. Longest common substring of two strings (static method)
    static string lcs(string a, string b)
    {
        string combined = a + "#" + b;
        SA sa(combined);
        int mx = 0, idx = 0;
        for (int i = 0; i < sa.n - 1; i++)
        {
            bool diff = (sa.sa[i] < a.size()) != (sa.sa[i + 1] < a.size());
            if (diff && sa.lcp[i] > mx)
            {
                mx = sa.lcp[i];
                idx = min(sa.sa[i], sa.sa[i + 1]);
            }
        }
        return a.substr(idx, mx);
    }
};

// Usage example
int main()
{
    string text = "banana";
    SA sa(text);

    // 1. Check existence
    cout << sa.contains("ana") << endl; // true

    // 2. Count occurrences
    cout << sa.count("na") << endl; // 2

    // 3. Find positions
    auto pos = sa.find("ana");
    for (int p : pos)
        cout << p << " "; // 1 3

    // 4. Longest repeat
    cout << sa.longestRepeat() << endl; // ana

    // 5. Distinct substrings
    cout << sa.distinct() << endl; // 15

    // 6. LCS of two strings
    cout << SA::lcs("ABABC", "BABCA") << endl; // ABC

    return 0;
}