#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using Pos = pair<int, int>;

/**
 * https://csacademy.com/contest/archive/task/mountain-time/statement/
 * (input ommitted due to length)
 */
int main() {
    int row_num;
    int col_num;
    std::cin >> row_num >> col_num;
    vector<pair<int, Pos>> mountains;
    int highest = INT32_MIN;
    for (int r = 0; r < row_num; r++) {
        for (int c = 0; c < col_num; c++) {
            int elev;
            std::cin >> elev;
            highest = std::max(highest, elev);
            mountains.push_back({elev, {r, c}});
        }
    }

    vector<vector<Pos>> parent(row_num, vector<Pos>(col_num));
    vector<vector<int>> size(row_num, vector<int>(col_num, 1));
    vector<vector<int>> prominence(row_num, vector<int>(col_num));
    vector<vector<bool>> processed(row_num, vector<bool>(col_num));
    vector<vector<pair<int, vector<Pos>>>> tallest(
        row_num, vector<pair<int, vector<Pos>>>(col_num)
    );
    for (int r = 0; r < row_num; r++) {
        for (int c = 0; c < col_num; c++) {
            tallest[r][c] = {mountains[r * col_num + c].first, {{r, c}}};
            parent[r][c] = {r, c};
            prominence[r][c] = mountains[r * col_num + c].first;
        }
    }

    // made these lambdas because i hate globals that much
    std::function<Pos(const Pos& p)> get_ultimate = [&] (const Pos& p) -> Pos {
        if (parent[p.first][p.second] == p) {
            return p;
        } else {
            return parent[p.first][p.second] = get_ultimate(parent[p.first][p.second]);
        }
    };
    int curr_elev;
    auto link = [&] (Pos m1, Pos m2) -> void {
        m1 = get_ultimate(m1);
        m2 = get_ultimate(m2);
        if (m1 == m2) {
            return;
        }
        if (size[m1.first][m1.second] < size[m2.first][m2.second]) {
            std::swap(m1, m2);  // make m1's size >= m2's size
        }
        pair<int, vector<Pos>>& t1 = tallest[m1.first][m1.second];
        pair<int, vector<Pos>>& t2 = tallest[m2.first][m2.second];
        if (t1.first > t2.first) {
            for (const Pos& p : t2.second) {
                prominence[p.first][p.second] = t2.first - curr_elev;
            }
        } else if (t1.first < t2.first) {
            for (const Pos& p : t1.second) {
                prominence[p.first][p.second] = t1.first - curr_elev;
            }
            t1 = t2;
        } else {
            t1.second.insert(t1.second.end(), t2.second.begin(), t2.second.end());
        }
        // this part is just standard DSU
        parent[m2.first][m2.second] = m1;
        size[m1.first][m1.second] += size[m2.first][m2.second];
    };

    std::sort(
        mountains.begin(), mountains.end(),
        std::greater<pair<int, Pos>>()
    );
    for (const auto& [elev, p] : mountains) {
        processed[p.first][p.second] = true;
        if (elev == highest) {
            prominence[p.first][p.second] = elev;
            continue;
        }
        curr_elev = elev;
        if (p.first > 0 && processed[p.first - 1][p.second]) {
            link(p, {p.first - 1, p.second});
        }
        if (p.second > 0 && processed[p.first][p.second - 1]) {
            link(p, {p.first, p.second - 1});
        }
        if (p.first < row_num - 1 && processed[p.first + 1][p.second]) {
            link(p, {p.first + 1, p.second});
        }
        if (p.second < col_num - 1 && processed[p.first][p.second + 1]) {
            link(p, {p.first, p.second + 1});
        }
    }
    for (int r = 0; r < row_num; r++) {
        for (int c = 0; c < col_num - 1; c++) {
            cout << prominence[r][c] << ' ';
        }
        cout << prominence[r][col_num - 1] << endl;
    }
}
