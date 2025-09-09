// 这行是告诉电脑：“我们要用一些基本的功能，比如打印文字、读取用户输入”
// 就像你做饭前要先打开厨房的灯一样
#include <stdio.h>

// 下面是一个“小机器人”，它的名字叫 searchInsert
// 它的任务是：在一个从小到大排好队的数字队伍里，找一个数字应该站在哪里
// 参数说明（非常重要，我们一个一个解释）：

// int* nums：
//   想象有一排数字站成一队：[1, 3, 5, 6]
//   这个“nums”就是这队数字的名字
//   “*” 是 C 语言的特殊写法，意思是“指向第一个数字的箭头”
//   你可以把它想象成一个标签，贴在第一个数字上，告诉我们从哪开始找
//   虽然看起来奇怪，但你可以简单记住：int* nums 就是“一排数字”

// int numsSize：
//   这是这排数字一共有多少个
//   比如 [1,3,5,6] 有 4 个数字，所以 numsSize = 4

// int target：
//   这是我们要找的数字
//   比如我们要找 2，那么 target = 2

// 这个机器人最后会告诉我们一个“位置编号”（从0开始）
// 比如返回 1，表示应该站在第1个位置（也就是1和3之间）
int searchInsert(int* nums, int numsSize, int target) {

    // 我们需要两个“小旗子”来标记查找范围
    int left = 0;           // left 是左边的小旗子，最开始插在第0个位置（第一个数字前面）
    int right = numsSize - 1; // right 是右边的小旗子，最开始插在最后一个数字的位置
    // 比如有4个数字，位置是0,1,2,3，所以 right = 3

// 开始循环：只要左边的旗子没有超过右边的旗子，就继续找
// 当 left > right 时，说明所有位置都看过了，可以停下来了
    while (left <= right) {

        // 现在我们要找中间的位置
        // 就像你在尺子上找中点：从 left 到 right，中间是 (left + right) / 2
        // 但我们写成 left + (right - left) / 2 是为了防止数字太大，电脑算错
        // 比如 left=0, right=3，那么 mid = 0 + (3-0)/2 = 1
        int mid = left + (right - left) / 2;

        // 现在我们看看中间那个数字是多少
        // nums[mid] 表示“在 nums 这队数字中，位置为 mid 的那个数”
        // 比如 nums[1] 就是第1个位置的数字（3）

        // 如果中间的数字比我们要找的 target 小
        // 比如中间是 3，我们要找 5，3 < 5
        if (nums[mid] < target) {
            // 说明我们要找的数字肯定在中间的右边
            // 所以我们把左边的小旗子往右移动
            // 移到 mid + 1 的位置
            // 因为 mid 这个位置已经太小了，不用再看了
            left = mid + 1;
        }
        // 如果中间的数字比 target 大
        // 比如中间是 5，我们要找 3，5 > 3
        else if (nums[mid] > target) {
            // 说明我们要找的数字肯定在中间的左边
            // 所以我们把右边的小旗子往左移动
            // 移到 mid - 1 的位置
            // 因为 mid 这个位置已经太大了，也不能放 target
            right = mid - 1;
        }
        // 如果中间的数字正好等于 target
        // 比如中间是 5，我们要找 5，5 == 5
        else {
            // 恭喜！找到了！
            // 直接返回中间的位置编号 mid
            return mid;
        }

        // 注意：每次循环，我们都会移动 left 或 right，范围越来越小
        // 就像两个小旗子慢慢向中间靠拢
    }

    // 如果上面的循环结束了还没找到
    // 说明这个数字不在队伍里
    // 但是注意：此时 left 指向的位置，就是 target 应该插入的地方
    // 为什么？
    //   - left 左边的所有数字都比 target 小
    //   - right 右边的所有数字都比 target 大
    // 所以把 target 插在 left 的位置，队伍还是有序的
    return left;
}

// 这是整个程序的“开关”
// 电脑一运行，就从 main 函数开始执行
int main() {
    // 先打印一些提示信息，告诉用户怎么用
    printf("=== 二分查找插入位置程序 ===\n");
    printf("这是一个帮助你找数字位置的小工具\n");

    // 声明一个变量 numsSize，表示数组有多少个数字
    int numsSize;
    printf("请输入数组中有多少个数字：");

    // scanf 是“扫描输入”的意思
    // %d 表示我们要读取一个整数（比如 4）
    // &numsSize 表示把这个数字存到 numsSize 这个“盒子”里
    // & 是“地址”的意思，你可以理解为“把数字放进这个盒子”
    // 但是现代编译器认为 scanf 不安全，所以我们用 scanf_s（Windows）或加警告忽略

#ifdef _WIN32
    // 如果是 Windows 系统（如 Visual Studio），使用 scanf_s
    if (scanf_s("%d", &numsSize) != 1) {
#else
    // 其他系统（如 Linux, Mac）仍可用 scanf
    if (scanf("%d", &numsSize) != 1) {
#endif
        printf("输入错误：请输入一个有效的整数！\n");
        return 1;  // 返回1表示程序出错
    }

    // 检查用户输入是否合法
    if (numsSize <= 0) {
        printf("错误：数字个数必须大于0！\n");
        return 1;  // 返回1表示程序出错，结束运行
    }

    // 定义一个“盒子队列”，最多可以放1000个数字
    // 这个队列叫 nums，位置从0到999
    int nums[1000];

    // 让用户一个一个输入数字
    printf("请输入 %d 个数字（用空格或回车分隔）：", numsSize);
    for (int i = 0; i < numsSize; i++) {
        // 每次读取一个数字，放进 nums[i] 这个盒子里
        // i 从 0 开始，依次是 0,1,2,3...
#ifdef _WIN32
        if (scanf_s("%d", &nums[i]) != 1) {
#else
        if (scanf("%d", &nums[i]) != 1) {
#endif
            printf("输入错误：第 %d 个数字无效！\n", i + 1);
            return 1;
        }
        }

    // 打印用户输入的数组
    printf("你输入的数组是：");
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);  // 把每个数字打印出来
    }
    printf("\n");  // 换行

    // 让用户输入要查找的目标值
    int target;
    printf("请输入要查找的目标值：");
#ifdef _WIN32
    if (scanf_s("%d", &target) != 1) {
#else
    if (scanf("%d", &target) != 1) {
#endif
        printf("输入错误：请输入一个有效的目标值！\n");
        return 1;
    }

    // 现在调用我们之前写的“小机器人” searchInsert
    // 把 nums（数字队列）、numsSize（数字个数）、target（目标值）交给它
    // 它会返回一个位置编号，我们存到 result 里
    int result = searchInsert(nums, numsSize, target);

    // 判断结果
    // 如果 result 在有效范围内，并且那个位置的数字正好是 target
    if (result < numsSize && nums[result] == target) {
        printf("✅ 找到了！%d 的位置编号是：%d\n", target, result);
    }
    else {
        printf("❌ 没有找到 %d\n", target);
        printf("📌 它应该插入在位置编号 %d\n", result);

        // 显示插入后的数组长什么样
        printf("📊 插入后的数组会是：");
        // 先打印插入点前面的数字
        for (int i = 0; i < result; i++) {
            printf("%d ", nums[i]);
        }
        // 打印要插入的数字
        printf("%d ", target);
        // 再打印插入点后面的数字
        for (int i = result; i < numsSize; i++) {
            printf("%d ", nums[i]);
        }
        printf("\n");
    }

    // 程序成功运行完毕
    return 0;  // 返回0表示一切正常
    }