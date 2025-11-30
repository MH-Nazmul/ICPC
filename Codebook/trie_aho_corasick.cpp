#include <bits/stdc++.h>
using namespace std;
// -------------------------
// ===== Core Block ========
// -------------------------
const int K = 26;
struct Node
{
    int next[K];
    int go[K];
    int link = -1, parent = -1;
    char pch;
    int wordCount = 0;
    int subtreeCount = 0;
    bool output = false;
    Node(int p = -1, char ch = '$') : parent(p), pch(ch)
    {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};

vector<Node> t(1);

inline void addString(const string &s)
{
    int v = 0;
    for (char ch : s)
    {
        int c = ch - 'a';
        if (t[v].next[c] == -1)
        {
            t[v].next[c] = (int)t.size();
            t.emplace_back(v, ch);
        }
        v = t[v].next[c];
    }
    t[v].output = true;
    t[v].wordCount++;
}

// -------------------------------
// ===== Prefix Match Block ======
// -------------------------------
void computeSubtreeCounts()
{
    vector<int> order;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        order.push_back(v);
        for (int c = 0; c < K; c++)
            if (t[v].next[c] != -1)
                q.push(t[v].next[c]);
    }
    for (int i = (int)order.size() - 1; i >= 0; --i)
    {
        int v = order[i];
        int cnt = t[v].wordCount;
        for (int c = 0; c < K; c++)
            if (t[v].next[c] != -1)
                cnt += t[t[v].next[c]].subtreeCount;
        t[v].subtreeCount = cnt;
    }
}

// Returns count of patterns starting with given prefix
int countPrefixMatches(const string &prefix)
{
    int v = 0;
    for (char ch : prefix)
    {
        int c = ch - 'a';
        if (t[v].next[c] == -1)
            return 0;
        v = t[v].next[c];
    }
    return t[v].subtreeCount;
}

// ---------------------------------------
// "Find inserted patterns inside a text"
// ---------------------------------------
inline int go(int v, char ch);

int getLink(int v)
{
    if (t[v].link == -1)
    {
        if (v == 0 || t[v].parent == 0)
            t[v].link = 0;
        else
            t[v].link = go(getLink(t[v].parent), t[v].pch);
    }
    return t[v].link;
}

int go(int v, char ch)
{
    int c = ch - 'a';
    if (t[v].go[c] == -1)
    {
        if (t[v].next[c] != -1)
            t[v].go[c] = t[v].next[c];
        else
            t[v].go[c] = (v == 0 ? 0 : go(getLink(v), ch));
    }
    return t[v].go[c];
}

// Returns total count of matched patterns in text
int countPatternsInText(const string &text)
{
    int v = 0, matches = 0;
    for (char ch : text)
    {
        v = go(v, ch);
        for (int u = v; u != 0; u = getLink(u))
            if (t[u].output)
                matches += t[u].wordCount;
    }
    return matches;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--)
    {
        string s;
        cin >> s;
        addString(s);
    }

    computeSubtreeCounts(); // Needed for prefix queries

    int q;
    cin >> q;
    while (q--)
    {
        string x;
        cin >> x;
        cout << "for " << x << "--\n";
        cout << "PrefixCount = " << countPrefixMatches(x) << '\n';
        cout << "InTextCount = " << countPatternsInText(x) << '\n';
    }
}

// ===============================================
// Complexity:
// Build Trie        : O(sum of |patterns|)
// Prefix Query      : O(|prefix|)
// Text Search Query : O(|text|)
// ===============================================
