	#include <iostream>      // 用于输入输出（如 cout）
	#include <vector>        // 使用 vector
	using namespace std;     // 使用标准命名空间
	
	class Solution {
	public:
	    /**
	     * 两数之和：暴力解法 - 遍历所有两两组合
	     * 时间复杂度：O(n²)
	     * 空间复杂度：O(1)
	     * 
	     * @param nums: 输入数组
	     * @param target: 目标和
	     * @return: 两个数的下标，没找到返回空 vector
	     */
	    vector<int> twoSum(vector<int>& nums, int target) {
	        // 外层循环：i 从 0 到 倒数第二个元素
	        for (int i = 0; i < nums.size(); i++) {
	            // 内层循环：j 从 i+1 开始，避免重复和自己配对
	            for (int j = i + 1; j < nums.size(); j++) {  // ✅ 修复：用分号，加括号
	                if (nums[i] + nums[j] == target) {
	                    // 找到一对，返回下标 {i, j}
	                    return vector<int>{i, j};
	                }
	            }
	        }
	        // 没找到，返回空 vector
	        return vector<int>();
	    }
	};
	
	// ============ 主函数测试 ============
	int main() {
	    Solution solution;
	    vector<int> nums = {2, 7, 11, 15};
	    int target = 9;
	
	    vector<int> result = solution.twoSum(nums, target);
	
	    if (result.size() == 2) {
	        cout << "找到下标: [" << result[0] << ", " << result[1] << "]" << endl;
	        cout << "对应值: " << nums[result[0]] << " + " << nums[result[1]] << " = " << target << endl;
	    } else {
	        cout << "未找到结果。" << endl;
	    }
	
	    return 0;
	}