class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();
        int sx, sy, cnt = 0;
        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
                if (classroom[i][j] == 'L') {
                    id[i][j] = cnt++;
                }
            }
        }

        int full = (1 << cnt) - 1;

        vector<vector<vector<int>>> best(
            m, vector<vector<int>>(n, vector<int>(1 << cnt, -1))
        );

        queue<array<int, 5>> q;
        q.push({sx, sy, 0, energy, 0});
        best[sx][sy][0] = energy;

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        while (!q.empty()) {
            auto [x, y, mask, e, moves] = q.front();
            q.pop();

            if (mask == full)
                return moves;

            if (e == 0)
                continue;

            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];

                if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                    continue;

                if (classroom[nx][ny] == 'X')
                    continue;

                int ne = e - 1;
                int nmask = mask;

                if (classroom[nx][ny] == 'L')
                    nmask |= (1 << id[nx][ny]);

                if (classroom[nx][ny] == 'R')
                    ne = energy;

                if (best[nx][ny][nmask] >= ne)
                    continue;

                best[nx][ny][nmask] = ne;

                q.push({nx, ny, nmask, ne, moves + 1});
            }
        }

        return -1;
    }
};