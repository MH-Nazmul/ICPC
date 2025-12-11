#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "MHNHM";
    cout << "Full string: " << s << endl;
    cout << "s[1-3]: " << s.substr(0, 3) << endl;  // positions 1-3 in 1-indexed
    cout << "s[3-5]: " << s.substr(2, 3) << endl;  // positions 3-5 in 1-indexed
    
    s = "ababa";
    cout << "\nFull string: " << s << endl;
    cout << "s[1-3]: " << s.substr(0, 3) << endl;  // positions 1-3 in 1-indexed
    cout << "s[3-5]: " << s.substr(2, 3) << endl;  // positions 3-5 in 1-indexed
    return 0;
}
