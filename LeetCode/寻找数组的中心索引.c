// 引入标准输入输出库，用于使用 printf 函数打印结果
#include <stdio.h>

/**
 * 函数名：pivotIndex
 * 功能：在整数数组中寻找“中心下标”
 *
 * 什么是中心下标？
 *   - 指数组中某个位置，其左侧所有元素之和等于右侧所有元素之和
 *   - 注意：中心下标处的元素不包含在左、右和中
 *   - 例如：数组 [1, 7, 3, 6, 5, 6]
 *           下标 3（值为 6）是中心下标，因为：
 *           左边和 = 1 + 7 + 3 = 11
 *           右边和 = 5 + 6 = 11
 *
 * 参数：
 *   - int* nums: 指向整数数组的指针（即数组首地址）
 *   - int numsSize: 数组的长度（元素个数）
 *
 * 返回值：
 *   - 如果存在中心下标，返回其索引（从 0 开始）
 *   - 如果不存在，返回 -1
 */
int pivotIndex(int* nums, int numsSize) {
    // 第一步：计算整个数组所有元素的总和
    int totalSum = 0;  // 初始化总和为 0

    // 使用 for 循环遍历数组每一个元素
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];  // 将每个元素累加到 totalSum
    }
    // 此时 totalSum 就是数组所有数的和

    // 第二步：从左到右遍历每个位置，检查是否是中心下标
    int leftSum = 0;  // 初始化“左边和”为 0（第一个元素左边没有数）

    // 遍历每个下标 i
    for (int i = 0; i < numsSize; i++) {
        // 计算“右边和”：
        // 总和 = 左边和 + 当前元素 + 右边和
        // 所以：右边和 = 总和 - 左边和 - 当前元素
        int rightSum = totalSum - leftSum - nums[i];

        // 判断左边和是否等于右边和
        if (leftSum == rightSum) {
            // 如果相等，说明当前位置 i 就是中心下标
            return i;  // 直接返回这个下标，函数结束
        }

        // 如果不相等，就把当前元素加到 leftSum 中
        // 为下一次循环（检查下一个位置）做准备
        // 注意：leftSum 是“当前元素左边”的和，不包含当前元素
        leftSum += nums[i];
    }

    // 如果整个循环结束都没有找到中心下标
    // 说明不存在这样的位置，返回 -1
    return -1;
}

/**
 * 主函数 main
 * 作用：程序的入口，用于测试 pivotIndex 函数是否正确
 * 注意：每个 C 程序必须有且只有一个 main 函数
 */
int main() {
    // 定义一个测试数组：[1, 7, 3, 6, 5, 6]
    // 题目期望结果：下标 3（因为 1+7+3 = 11，5+6 = 11）
    int nums[] = { 1, 7, 3, 6, 5, 6 };

    // 计算数组的元素个数
    // sizeof(nums) 是整个数组占用的字节数
    // sizeof(nums[0]) 是一个元素占用的字节数
    // 相除就得到元素个数
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    // 调用 pivotIndex 函数，传入数组和长度
    // 函数会返回中心下标，或 -1
    int result = pivotIndex(nums, numsSize);

    // 使用 printf 输出结果
    // %d 表示输出一个整数
    printf("中心下标是：%d\n", result);

    // main 函数正常结束，返回 0 表示程序成功执行
    return 0;
}