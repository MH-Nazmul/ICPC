// MH_Nazmul
// Let it be as simple

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
long double PI = 3.14159265358979323846;
#define int long long int
#define all(x) x.begin(), x.end()
#define allr(x) x.rbegin(), x.rend()

vector<int> LIS(vector<int> &a)
{
    int n = a.size();

    vector<int> tails;
    vector<int> tails_index;
    vector<int> parent(n, -1);

    for (int i = 0; i < n; i++)
    {
        int x = a[i];
        int pos = lower_bound(all(tails), x) - tails.begin();
        if (pos == tails.size())
        {
            tails.push_back(x);
            tails_index.push_back(i);
        }
        else
        {
            tails[pos] = x;
            tails_index[pos] = i;
        }
        if (pos > 0)
            parent[i] = tails_index[pos - 1];
    }
    vector<int> lis;
    int idx = tails_index.back();

    while (idx != -1)
    {
        lis.push_back(a[idx]);
        idx = parent[idx];
    }

    reverse(all(lis));
    return lis;
}

void MH(void)
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    vector<int> lis = LIS(a);
    cout << "LIS Length: " << lis.size() << "\n";
    cout << "LIS Sequence: ";
    for (auto x : lis)
        cout << x << " ";
    cout << "\n";
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, Test;
    // cin >> t;

    for (Test = 1; Test <= t; Test++)
    {
        MH();
    }
    return 0;
}
