class Solution {
public:
    int numRabbits(vector<int>& answers) {
        if (!answers.size()) return 0;
        int f[1001]={0};
        int total = 0;

        for (int i = 0; i < answers.size(); ++ i){
            ++ f[answers[i]];
        }

        total += f[0];
        for (int i = 1; i < 1000; ++ i){
            if (!f[i]) continue;
            int t = i + 1;
            total = total + (f[i] / t) * t;
            if (f[i] % t != 0) total += t;
        }

        return total;
    }
};