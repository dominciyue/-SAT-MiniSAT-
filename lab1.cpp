#include "common.h"

using namespace Minisat;

bool lab1(int states[], int n, int button[][2], int m, bool answer[])
{
    Solver solver;
    Var variables[1000];
    int i, j;
    for (i = 0; i < m; ++i)
        variables[i] = solver.newVar();

    // 对每个石头创建约束条件
    for (i = 0; i < n; ++i) {
        // 创建所有可能的组合，确保只有正确的奇偶性组合被满足
        vec<Lit> affected;
        
        // 收集影响当前石头的所有开关
        for (j = 0; j < m; ++j) {
            if (button[j][0] == i + 1 || button[j][1] == i + 1) {
                affected.push(mkLit(variables[j]));
            }
        }

        // 生成所有可能的组合
        int combinations = 1 << affected.size();
        for (int mask = 0; mask < combinations; mask++) {
            int count_ones = __builtin_popcount(mask);
            bool valid = (states[i] == 0) ? (count_ones % 2 == 1) : (count_ones % 2 == 0);
            
            if (!valid) {
                vec<Lit> clause;
                for (int k = 0; k < affected.size(); k++) {
                    if (mask & (1 << k)) {
                        clause.push(~affected[k]);
                    } else {
                        clause.push(affected[k]);
                    }
                }
                solver.addClause(clause);
            }
        }
    }

    // 解决SAT问题
    auto sat = solver.solve();
    if (sat) {
        for (i = 0; i < m; ++i)
            answer[i] = (solver.modelValue(variables[i]) == l_True);
        return true;
    }
    return false;
}
