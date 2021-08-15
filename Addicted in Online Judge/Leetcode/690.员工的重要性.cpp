/*
// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
*/

class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) 
    {
        int pos;
        for (int i = 0; i < employees.size(); i ++ )
            if (employees[i] -> id == id)
            {
                pos = i;
                break;
            }
        int ans= employees[pos] -> importance;
        for (int i = 0; i < employees[pos] -> subordinates.size(); i ++ )
           ans += getImportance(employees, employees[pos] -> subordinates[i]);
        return ans;      
    }
};