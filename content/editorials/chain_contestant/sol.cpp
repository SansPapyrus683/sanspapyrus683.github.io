#include <iostream>
#include <cassert>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

constexpr int TYPE_NUM = 10;
constexpr int MOD = 998244353;

int popcount(int x) {
    int res = 0;
    for (int i = 0; i < 31; i++) {  // not sure if 31 or 32 lol
        res += (bool) (x & (1 << i));
    }
    return res;
}

/**
 * https://atcoder.jp/contests/abc215/tasks/abc215_e
 * 4
 * BGBH should output 13
 */
int main() {
    int contest_num;
    std::cin >> contest_num;
    vector<int> contests;
    for (int c = 0; c < contest_num; c++) {
        char contest;
        std::cin >> contest;
        assert('A' <= contest && contest < 'A' + TYPE_NUM);
        contests.push_back(contest - 'A');
    }

    vector<vector<long long>> num_ways(
        1 << TYPE_NUM, vector<long long>(contest_num + 1)
    );
    for (int ss = 1; ss < (1 << TYPE_NUM); ss++) {
        vector<long long>& curr = num_ways[ss];
        /*
         * base case is when there's only one character we care about,
         * i didn't talk about this in the explanation srry
         */
        if (popcount(ss) == 1) {
            // get the first set bit
            int set = 0;
            for (; (ss & (1 << set)) == 0; set++);

            curr[0] = 1;
            for (int c = 1; c <= contest_num; c++) {
                if (contests[c - 1] == set) {
                    curr[c] = curr[c - 1] * 2 % MOD;
                } else {
                    curr[c] = curr[c - 1];
                }
            }
            for (long long& c : curr) {
                // can't have an empty string so we sub 1 from all of them
                c--;
            }
            continue;
        }

        for (int to_add = 0; to_add < TYPE_NUM; to_add++) {
            if ((ss & (1 << to_add)) == 0) {
                continue;
            }

            // that state where we didn't have to_add in this crapshow
            const vector<long long>& prev = num_ways[ss & ~(1 << to_add)];
            vector<long long> new_ways(contest_num + 1);
            new_ways[0] = 0;  // just making it obvious
            for (int c = 1; c <= contest_num; c++) {
                // wth we don't care about this contest at all get outta here
                if ((ss & (1 << contests[c - 1])) == 0) {
                    new_ways[c] = new_ways[c - 1];
                    continue;
                }
                // is this the one we can add on to the end?
                if (contests[c - 1] == to_add) {
                    new_ways[c] = (2 * new_ways[c - 1] + 1) % MOD;
                } else {
                    // oh i guess not, f
                    new_ways[c] = (
                        new_ways[c - 1] + prev[c] - prev[c - 1]
                    + 2 * MOD) % MOD;
                }
            }
            for (int c = 0; c <= contest_num; c++) {
                // we overcounted some though, be sure to account for that
                curr[c] = (curr[c] + new_ways[c] - prev[c] + MOD) % MOD;
            }
        }
    }

    cout << num_ways[(1 << TYPE_NUM) - 1][contest_num] << endl;
}
