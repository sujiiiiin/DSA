#include <cstdio>
#include <vector>

std::vector<int> solveJosephus(int n, int m, std::vector<int>& nums) {
    std::vector<int> result(n);
    int pos = 0;
    
    // 数学方法直接计算最终位置
    for (int i = 1; i <= n; i++) {
        pos = (pos + m - 1) % i;
        result[n - i] = nums[pos];
        
        // 从数组中移除已处理元素（逻辑上）
        for (int j = pos; j < i - 1; j++) {
            nums[j] = nums[j + 1];
        }
    }
    
    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }
    
    std::vector<int> result = solveJosephus(n, m, nums);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    
    return 0;
}