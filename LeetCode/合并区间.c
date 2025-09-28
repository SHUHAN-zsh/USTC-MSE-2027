// ==================== 1. 引入必要的头文件 ====================
// 就像做饭前要准备锅碗瓢盆
#include <stdio.h>   // 用来打印结果（printf）
#include <stdlib.h>  // 用来申请内存（malloc）和排序（qsort）
#include <string.h>  // 字符串操作（虽然这里没用，但习惯带上）

// ==================== 2. 定义比较函数 cmp ====================
// 这个函数告诉 qsort：两个区间谁该排在前面？
// a 和 b 是两个区间的地址
int cmp(const void* a, const void* b) {
    // 把 void* 转成 int**，再解引用，得到真正的 int*（区间）
    int* intervalA = *(int**)a;  // 拿到第一个区间，比如 [1,3]
    int* intervalB = *(int**)b;  // 拿到第二个区间，比如 [2,6]

    // 按“开始时间”排序：谁的开始时间小，谁排前面
    // 返回负数：a 排前面
    // 返回正数：b 排前面
    // 返回 0：一样，随便排
    return intervalA[0] - intervalB[0];
}

// ==================== 3. 主函数：合并区间 ====================
// 这是 LeetCode 要求的函数签名，一个字母都不能改
// 输入：intervals = 一堆时间段，比如 [[1,3],[2,6],[8,10]]
// 输出：合并后的结果，比如 [[1,6],[8,10]]
int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
    int* returnSize, int** returnColumnSizes) {

    // 第一步：先排序！让所有区间按“开始时间”从小到大排队
    // qsort(数组, 元素个数, 每个元素占的字节数, 比较函数)
    qsort(intervals, intervalsSize, sizeof(int*), cmp);

    // 第二步：准备一个“大盒子”，用来装合并后的结果
    // 最多可能有 intervalsSize 个结果（最坏情况：全不重叠）
    // malloc 是“申请内存”的意思，就像去仓库领一个空箱子
    int** result = (int**)malloc(intervalsSize * sizeof(int*));

    // 第三步：准备一张“标签纸”，记录每个结果区间有几列
    // 因为每个区间都是 [start, end]，所以每行都是 2 列
    // 题目要求我们必须告诉调用者，所以要写在这张纸上
    *returnColumnSizes = (int*)malloc(intervalsSize * sizeof(int));

    // 第四步：准备一个“计数器”，记录我们装了多少个区间
    // 最开始是 0，一个都没装
    *returnSize = 0;

    // 第五步：开始处理每一个输入的区间（一个一个来）
    for (int i = 0; i < intervalsSize; i++) {
        // 拿出当前区间的“开始”和“结束”时间
        int start = intervals[i][0];  // 当前区间的开始时间
        int end = intervals[i][1];  // 当前区间的结束时间

        // 判断：要不要新建一个区间？
        // 情况1：如果大盒子还是空的（*returnSize == 0），说明是第一个，必须新建
        // 情况2：如果上一个区间的结束时间 < 当前开始时间，说明不重叠，要新建
        if (*returnSize == 0 || result[*returnSize - 1][1] < start) {
            // 要新建！做一张新“小纸条”
            // malloc(2 * sizeof(int)) 表示：申请能装 2 个整数的空间
            result[*returnSize] = (int*)malloc(2 * sizeof(int));

            // 在这张小纸条上写：开始时间和结束时间
            result[*returnSize][0] = start;  // 写开始
            result[*returnSize][1] = end;    // 写结束

            // 在“标签纸”上写下：这一行有 2 列
            (*returnColumnSizes)[*returnSize] = 2;

            // 计数器 +1，表示我们多装了一个区间
            (*returnSize)++;
        }
        // 否则：和上一个区间重叠了，就合并（不新建，只改结尾）
        else {
            // 不做新纸条！只改上一个区间的“结束时间”
            // 改成：原来结束时间和现在结束时间中，更大的那个
            // 比如 [1,3] 和 [2,6] 合并成 [1,6]
            result[*returnSize - 1][1] = (result[*returnSize - 1][1] > end) ?
                result[*returnSize - 1][1] : end;
            // 上面这行等价于 fmax，但不用包含 math.h
        }
    }

    // 全部处理完，把“大盒子”交出去
    return result;
}

// ==================== 4. 辅助函数：打印结果 ====================
// 用来打印合并后的结果，方便你看
void printResult(int** result, int returnSize, int* returnColumnSizes) {
    printf("合并后的结果：[");
    for (int i = 0; i < returnSize; i++) {
        printf("[%d,%d]", result[i][0], result[i][1]);
        if (i < returnSize - 1) {
            printf(",");
        }
    }
    printf("]\n");
}

// ==================== 5. 主函数 main ====================
// 程序的入口，从这里开始执行
int main() {
    // 1. 创建测试数据：[[1,3], [2,6], [8,10], [15,18]]
    int n = 4;  // 一共 4 个区间

    // 创建 intervals 数组（大册子）
    int** intervals = (int**)malloc(n * sizeof(int*));

    // 手动创建每个小纸条（区间）
    int a[] = { 1, 3 };
    int b[] = { 2, 6 };
    int c[] = { 8, 10 };
    int d[] = { 15, 18 };

    intervals[0] = a;  // 第0页贴 [1,3]
    intervals[1] = b;  // 第1页贴 [2,6]
    intervals[2] = c;  // 第2页贴 [8,10]
    intervals[3] = d;  // 第3页贴 [15,18]

    // 创建 intervalsColSize（每行有2列）
    int* intervalsColSize = (int*)malloc(sizeof(int));
    *intervalsColSize = 2;

    // 准备两个“盒子”用来接返回值
    int returnSize;           // 接“有几个区间”
    int* returnColumnSizes;   // 接“每行有几列”

    // 2. 调用 merge 函数
    printf("原始区间：[[1,3],[2,6],[8,10],[15,18]]\n");
    int** result = merge(intervals, n, intervalsColSize, &returnSize, &returnColumnSizes);

    // 3. 打印结果
    printResult(result, returnSize, returnColumnSizes);

    // 4. 释放内存（好习惯）
    free(intervals);
    free(intervalsColSize);
    // 注意：result 中的每个小数组是 malloc 的，实际项目中也应释放
    // 为简化，这里省略

    return 0;  // 程序正常结束
}