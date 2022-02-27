//
//  main.cpp
//  SherlockAndCost
//
//  Created by mndx on 27/02/2022.
//

#include <iostream>
#include <vector>

typedef struct memo_table {
    bool is_set;
    int val;
} m_table;

m_table ** table;

void init_table(int n) {
    table = new m_table * [n + 5];
    for(int i = 0; i < n + 5; ++i) {
        table[i] = new m_table[2];
        table[i][0].is_set = false;
        table[i][0].val = 0;
        table[i][1].is_set = false;
        table[i][1].val = 0;
    }
}

int max_int(int a, int b) {
    int res = 0;
    if(a > b) { res = a; }
    else { res = b; }
    
    return res;
}

int cost_func(std::vector<int> & B, int n, bool prev_is_one) {
    int max = 0;
    
    int size = (int) B.size();
    
    if(table[n][prev_is_one].is_set) {
        return table[n][prev_is_one].val;
    }
    
    if(n < size) {
        if(prev_is_one) {
            int max_ll1 = abs(B[n] - 1) + cost_func(B, n + 1, false);
            int max_ll2 = cost_func(B, n + 1, true);
            int max_loc = max_int(max_ll1, max_ll2);
            max = max_int(max, max_loc);
        }
        if(!prev_is_one) {
            int max_ll1 = abs(B[n - 1] - 1) + cost_func(B, n + 1, true);
            int max_ll2 = abs(B[n] - B[n - 1]) + cost_func(B, n + 1, false);
            int max_loc = max_int(max_ll1, max_ll2);
            max = max_int(max, max_loc);
        }
    }
    
    table[n][prev_is_one].is_set = true;
    table[n][prev_is_one].val = max;
    
    return max;
}

int cost(std::vector<int> B) {
    int res = 0;
    
    int size = (int) B.size();
    
    init_table(size);
    
    res = max_int(cost_func(B, 1, false), cost_func(B, 1, true));
    
    return res;
}

int main(int argc, const char * argv[]) {

    //Declarations
    std::vector<int> B;
    
    //Size input array B
    int size_B = 10;
    
    //Populate B with random data between 1 and 100, inclusive
    for(int i = 0; i < size_B; ++i)
        B.push_back(rand() % 100 + 1);
    
    //Determine max cost
    int max_cost = cost(B);
    
    //Print max cost
    std::cout << "max cost: " << max_cost << std::endl;
    
    return 0;
}
