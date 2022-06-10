#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

inline bool bit_set(const long long& n, int pos) {
    return n & (1LL << pos);
}

long long more_bits(const long long& a, const long long& b) {
    return __builtin_popcountll(a) > __builtin_popcountll(b) ? a : b;
}

vector<long long> largest_clique(const vector<long long>& adj) {
    int sz = adj.size();  // just a shorthand
    vector<bool> valid(1 << sz);  // actually the scrapped dp definition lol
    valid[0] = true;
    for (int n1 = 0; n1 < sz; n1++) {
        valid[1 << n1] = true;
        for (int n2 = n1 + 1; n2 < sz; n2++) {
            valid[(1 << n1) + (1 << n2)] = adj[n1] & (1 << n2);
        }
    }
    for (int ss = 1; ss < (1 << sz); ss++) {
        if (__builtin_popcountll(ss) <= 2) {
            continue;
        }
        valid[ss] = true;
        for (int prev = 0; prev < sz; prev++) {
            if (bit_set(ss, prev) && !valid[ss & ~(1 << prev)]) {
                valid[ss] = false;
                break;
            }
        }
    }

    // here's our actual dp, the one we're gonna combine
    vector<long long> largest(1 << sz);
    for (int ss = 0; ss < (1 << sz); ss++) {
        if (valid[ss]) {
            largest[ss] = ss;
            continue;
        }
        for (int prev = 0; prev < sz; prev++) {
            if (bit_set(ss, prev)) {
                largest[ss] = more_bits(largest[ss], largest[ss & ~(1 << prev)]);
            }
        }
    }
    return largest;
}

/**
 * https://judge.yosupo.jp/problem/maximum_independent_set
 * (input omitted due to length)
 */
int main() {
    int node_num;
    int edge_num;
    std::cin >> node_num >> edge_num;
    vector<long long> adj(node_num, (1LL << node_num) - 1);
    for (int e = 0; e < edge_num; e++) {
        int n1, n2;
        std::cin >> n1 >> n2;
        adj[n1] &= ~(1LL << n2);
        adj[n2] &= ~(1LL << n1);
    }

    int half1 = node_num / 2;
    vector<long long> half1_adj(half1);
    for (int n = 0; n < half1; n++) {
        half1_adj[n] = adj[n] & ((1 << half1) - 1);
    }
    vector<long long> largest1 = largest_clique(half1_adj);

    int half2 = node_num - half1;
    vector<long long> half2_adj(half2);
    for (int n = 0; n < half2; n++) {
        half2_adj[n] = adj[half1 + n] >> half1;
    }
    vector<long long> largest2 = largest_clique(half2_adj);

    long long best_ss = 0;
    // here's the part where we combine the two dp things
    for (int ss1 = 0; ss1 < (1 << half1); ss1++) {
        // initially, everything in half2 is up for consideration
        long long ss2 = (1 << half2) - 1;
        for (int n = 0; n < half1; n++) {
            if (bit_set(ss1, n)) {
                // remove any nodes that aren't connected to the current node
                ss2 &= adj[n] >> half1;
            }
        }
        best_ss = more_bits(best_ss, largest1[ss1] + (largest2[ss2] << half1));
    }

    cout << __builtin_popcountll(best_ss) << endl;
    for (int i = 0; i < node_num; i++) {
        if (bit_set(best_ss, i)) {
            cout << i << ' ';  // trailing whitespace doesn't matter
        }
    }
}
