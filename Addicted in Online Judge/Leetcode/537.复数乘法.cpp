class Solution 
{
    public:
        string complexNumberMultiply(string a, string b)
        {
            int ai, bi;
            string a1 = "", a2 = "", b1 = "", b2 = "";
            
            for (ai = 0; a[ai] != '+'; ai ++ ) a1 += a[ai];
            for (ai ++ ; a[ai] != 'i'; ai ++ ) a2 += a[ai];
            for (bi = 0; b[bi] != '+'; bi ++ ) b1 += b[bi];
            for (bi ++ ; b[bi] != 'i'; bi ++ ) b2 += b[bi];

            int A1 = stoi(a1), A2 = stoi(a2), B1 = stoi(b1), B2 = stoi(b2);
            int real = A1 * B1 - A2 * B2;
            int img = A1 * B2 + A2 * B1; 

            return to_string(real) + "+" + to_string(img) + "i";
    }
};