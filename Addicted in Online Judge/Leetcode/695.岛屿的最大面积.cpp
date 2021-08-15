class Solution {
public:
    int dfs(vector<vector<int>>& grid, int i, int j)
    {
        int total = 1;
        grid[i][j] = 0;

        if (i + 1 >= 0 && i + 1 < grid.size() && grid[i + 1][j] == 1) total += dfs(grid, i + 1, j);
        if (i - 1 < grid.size() && i - 1 >= 0 && grid[i - 1][j] == 1) total += dfs(grid, i - 1, j);
        if (j + 1 >= 0 && j + 1 < grid[0].size() && grid[i][j + 1] == 1) total += dfs(grid, i, j + 1);
        if (j - 1 < grid[0].size() && j - 1 >= 0 && grid[i][j - 1] == 1) total += dfs(grid, i, j - 1);

        return total;
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ans = 0;
        for (int i1 = 0; i1 < grid.size(); i1 ++ )
            for (int j1 = 0; j1 < grid[0].size(); j1 ++ )
                if (grid[i1][j1] == 1) ans = max(ans, dfs(grid, i1, j1));
        
        return ans;
    }
};