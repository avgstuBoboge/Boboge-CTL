/**
 * Author: Yuhao Yao
 * Source: From tourist's header.
 * Date: 22-10-30
 * Description: debug header.
*/
#include <bits/stdc++.h>

using namespace std;

template<class A, class B>
string to_string(const pair <A, B> &p);

string to_string(const string s) { return '"' + s + '"'; }

string to_string(const char *s) { return to_string((string) s); }

string to_string(char c) { return "'" + string(1, c) + "'"; }

string to_string(bool x) { return x ? "true" : "false"; }

template<class A>
string to_string(const A &v) {
    bool first = 1;
    string res = "{";
    for (const auto &x: v) {
        if (!first) res += ", ";
        first = 0;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template<class A, class B>
string to_string(const pair <A, B> &p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }

void debug_out() { cerr << endl; }

template<class H, class... T>
void debug_out(const H &h, const T &... t) {
    cerr << " " << to_string(h);
    debug_out(t...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
