class Solution {
public:
    int f[10000];

    int find(int x)
    {
        int r = x, i = x;
        while (r != f[r]) r = f[r];

        while (r != f[i])
        {
            f[i] = r;
            i = f[i];
        }

        return r;
    }

    void mix(int x, int y)
    {
        int fx = find(x), fy = find(y);
        if (fx != fy) f[fy] = fx;
    }

    int findCircleNum(vector<vector<int>>& M) {
        int ans = 0;
        int t[100000];      
        memset(t, 0, 10000);

        for (int i = 0; i < M.size(); i ++ )f[i] = i;
        
        for (int i = 0; i < M.size(); i ++ )
            for (int j = 0; j < M.size(); j ++ )
                if (M[j][i]) mix(i, j);
        
        for (int i = 0; i < M.size(); i ++ ) t[find(i)] = 1;
        for (int i = 0; i < M.size(); i ++ ) if (t[i]) ans ++ ;

        return ans;
    }
};