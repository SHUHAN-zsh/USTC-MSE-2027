#include <iostream>      // 用于输入输出（如 cout）
#include <vector>        // 使用 vector
#include <unordered_map> // 使用 unordered_map（哈希表）
using namespace std;     // 使用标准命名空间，避免写 std::

class Solution {
public:
    /**
     * 两数之和：在数组中找到两个数，使得它们的和等于目标值 target
     * 返回这两个数的下标（任意顺序）
     * 
     * @param nums: 输入的整数数组（引用传递，避免拷贝）
     * @param target: 目标和
     * @return: 包含两个下标的 vector，如果没找到返回空 vector
     */
    vector<int> twoSum(vector<int>& nums, int target) {
        // 创建一个哈希表 mm，用于存储：键 = 数值，值 = 该数值在数组中的下标
        // 例如：如果 nums[0] = 2，就存入 mm[2] = 0
        unordered_map<int, int> mm;

        // 开始遍历数组，i 是当前元素的下标
        for (int i = 0; i < nums.size(); i++) {
            // 计算：为了使 nums[i] + ? = target，我们需要找的“另一个数”是多少
            int find = target - nums[i];

            // 检查哈希表中是否已经存过这个 "find" 数
            // mm.count(find) 返回 1 表示存在，0 表示不存在
            if (mm.count(find)) {
                // 找到了！
                // 当前下标是 i，之前存的 find 的下标是 mm[find]
                // 构造一个 vector，包含两个下标并返回
                // 注意：顺序可以是 {i, mm[find]} 或 {mm[find], i}
                return vector<int>{i, mm[find]};
            }

            // 如果没找到配对，就把当前的数和它的下标存进哈希表
            // 这样后面的数如果需要它，就能通过 mm[nums[i]] 找到它的下标
            mm[nums[i]] = i;

            // 注意：这句必须放在 if 判断之后
            // 否则会出现自己和自己配对的错误（比如 target=6, nums[i]=3）
        }

        // 如果整个循环结束都没找到，返回一个空 vector
        return vector<int>();
    }
};

// ============ 主函数：用于测试 ============
//int main() {
//    // 创建一个测试用的数组
//    vector<int> nums = {2, 7, 11, 15};
//    int target = 9;
//
//    // 创建 Solution 对象
//    Solution solution;
//
//    // 调用 twoSum 函数
//    vector<int> result = solution.twoSum(nums, target);
//
//    // 输出结果
//    if (result.size() == 2) {
//        cout << "找到两个数，下标为: [" << result[0] << ", " << result[1] << "]" << endl;
//        cout << "对应的值为: " << nums[result[0]] << " + " << nums[result[1]] << " = " << target << endl;
//    } else {
//        cout << "未找到两个数之和等于 " << target << endl;
//    }
//
//    return 0;
//}