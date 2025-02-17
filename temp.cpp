#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Cell {
    int x, y, cap_k;
    bool operator>(const Cell& other) const {
        return cap_k > other.cap_k;
    }
};

int kir_M, kir_N, kir_K;
vector<vector<int>> kir_alt_curr;
vector<vector<int>> kir_result;
vector<pair<int, int>> kir_directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool isValid(int kir_x, int kir_y) {
    return kir_x >= 0 && kir_x < kir_M && kir_y >= 0 && kir_y < kir_N;
}

bool canReach(int kir_startX, int kir_startY, int cap_k_val) {
    vector<vector<bool>> curr_vis(kir_M, vector<bool>(kir_N, false));
    queue<pair<int, int>> q;
    q.push({kir_startX, kir_startY});
    curr_vis[kir_startX][kir_startY] = true;
    int count_val = 0;

    while (!q.empty()) {
        //auto [x, y] = q.front(); q.pop();
        int x = q.front().first, y = q.front().second;
        q.pop();
        count_val++;
        if (count_val > kir_K) return true;

        for (auto i : kir_directions) {
            int nx = x + i.first, ny = y + i.second;
            if (isValid(nx, ny) && !curr_vis[nx][ny] && 
                abs(kir_alt_curr[x][y] - kir_alt_curr[nx][ny]) <= cap_k_val) {
                curr_vis[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    return false;
}

int findMinCapability(int x, int y) {
    int low = 0, high = 1e9, ans = high;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (canReach(x, y, mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

int main() {
    //cin >> M >> N >> K;
    //int M = 2, N = 2, K = 1;
    //int M, N, K;
    cin >> kir_M >> kir_N >> kir_K;
    //M = kir_M, N = kir_N, K = kir_K;
    //cout << "hello" << endl;
    kir_alt_curr.resize(kir_M, vector<int>(kir_N));
    kir_result.resize(kir_M, vector<int>(kir_N));
    //cout << "hello" << endl;
    for (int i = 0; i < kir_M; i++) {
        for (int j = 0; j < kir_N; j++) {
            cin >> kir_alt_curr[i][j];
        }
    }
    //kir_alt_curr = {{-3, -9}, {-8, 2}};
    
    for (int i = 0; i < kir_M; i++) {
        for (int j = 0; j < kir_N; j++) {
            kir_result[i][j] = findMinCapability(i, j);
        }
    }
    
    for (int i = 0; i < kir_M; i++) {
        for (int j = 0; j < kir_N; j++) {
            cout << kir_result[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}