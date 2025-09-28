// ==================== 1. �����Ҫ��ͷ�ļ� ====================
// ��������ǰҪ׼������ư��
#include <stdio.h>   // ������ӡ�����printf��
#include <stdlib.h>  // ���������ڴ棨malloc��������qsort��
#include <string.h>  // �ַ�����������Ȼ����û�ã���ϰ�ߴ��ϣ�

// ==================== 2. ����ȽϺ��� cmp ====================
// ����������� qsort����������˭������ǰ�棿
// a �� b ����������ĵ�ַ
int cmp(const void* a, const void* b) {
    // �� void* ת�� int**���ٽ����ã��õ������� int*�����䣩
    int* intervalA = *(int**)a;  // �õ���һ�����䣬���� [1,3]
    int* intervalB = *(int**)b;  // �õ��ڶ������䣬���� [2,6]

    // ������ʼʱ�䡱����˭�Ŀ�ʼʱ��С��˭��ǰ��
    // ���ظ�����a ��ǰ��
    // ����������b ��ǰ��
    // ���� 0��һ���������
    return intervalA[0] - intervalB[0];
}

// ==================== 3. ���������ϲ����� ====================
// ���� LeetCode Ҫ��ĺ���ǩ����һ����ĸ�����ܸ�
// ���룺intervals = һ��ʱ��Σ����� [[1,3],[2,6],[8,10]]
// ������ϲ���Ľ�������� [[1,6],[8,10]]
int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
    int* returnSize, int** returnColumnSizes) {

    // ��һ�������������������䰴����ʼʱ�䡱��С�����Ŷ�
    // qsort(����, Ԫ�ظ���, ÿ��Ԫ��ռ���ֽ���, �ȽϺ���)
    qsort(intervals, intervalsSize, sizeof(int*), cmp);

    // �ڶ�����׼��һ��������ӡ�������װ�ϲ���Ľ��
    // �������� intervalsSize �������������ȫ���ص���
    // malloc �ǡ������ڴ桱����˼������ȥ�ֿ���һ��������
    int** result = (int**)malloc(intervalsSize * sizeof(int*));

    // ��������׼��һ�š���ǩֽ������¼ÿ����������м���
    // ��Ϊÿ�����䶼�� [start, end]������ÿ�ж��� 2 ��
    // ��ĿҪ�����Ǳ�����ߵ����ߣ�����Ҫд������ֽ��
    *returnColumnSizes = (int*)malloc(intervalsSize * sizeof(int));

    // ���Ĳ���׼��һ����������������¼����װ�˶��ٸ�����
    // �ʼ�� 0��һ����ûװ
    *returnSize = 0;

    // ���岽����ʼ����ÿһ����������䣨һ��һ������
    for (int i = 0; i < intervalsSize; i++) {
        // �ó���ǰ����ġ���ʼ���͡�������ʱ��
        int start = intervals[i][0];  // ��ǰ����Ŀ�ʼʱ��
        int end = intervals[i][1];  // ��ǰ����Ľ���ʱ��

        // �жϣ�Ҫ��Ҫ�½�һ�����䣿
        // ���1���������ӻ��ǿյģ�*returnSize == 0����˵���ǵ�һ���������½�
        // ���2�������һ������Ľ���ʱ�� < ��ǰ��ʼʱ�䣬˵�����ص���Ҫ�½�
        if (*returnSize == 0 || result[*returnSize - 1][1] < start) {
            // Ҫ�½�����һ���¡�Сֽ����
            // malloc(2 * sizeof(int)) ��ʾ��������װ 2 �������Ŀռ�
            result[*returnSize] = (int*)malloc(2 * sizeof(int));

            // ������Сֽ����д����ʼʱ��ͽ���ʱ��
            result[*returnSize][0] = start;  // д��ʼ
            result[*returnSize][1] = end;    // д����

            // �ڡ���ǩֽ����д�£���һ���� 2 ��
            (*returnColumnSizes)[*returnSize] = 2;

            // ������ +1����ʾ���Ƕ�װ��һ������
            (*returnSize)++;
        }
        // ���򣺺���һ�������ص��ˣ��ͺϲ������½���ֻ�Ľ�β��
        else {
            // ������ֽ����ֻ����һ������ġ�����ʱ�䡱
            // �ĳɣ�ԭ������ʱ������ڽ���ʱ���У�������Ǹ�
            // ���� [1,3] �� [2,6] �ϲ��� [1,6]
            result[*returnSize - 1][1] = (result[*returnSize - 1][1] > end) ?
                result[*returnSize - 1][1] : end;
            // �������еȼ��� fmax�������ð��� math.h
        }
    }

    // ȫ�������꣬�ѡ�����ӡ�����ȥ
    return result;
}

// ==================== 4. ������������ӡ��� ====================
// ������ӡ�ϲ���Ľ���������㿴
void printResult(int** result, int returnSize, int* returnColumnSizes) {
    printf("�ϲ���Ľ����[");
    for (int i = 0; i < returnSize; i++) {
        printf("[%d,%d]", result[i][0], result[i][1]);
        if (i < returnSize - 1) {
            printf(",");
        }
    }
    printf("]\n");
}

// ==================== 5. ������ main ====================
// �������ڣ������￪ʼִ��
int main() {
    // 1. �����������ݣ�[[1,3], [2,6], [8,10], [15,18]]
    int n = 4;  // һ�� 4 ������

    // ���� intervals ���飨����ӣ�
    int** intervals = (int**)malloc(n * sizeof(int*));

    // �ֶ�����ÿ��Сֽ�������䣩
    int a[] = { 1, 3 };
    int b[] = { 2, 6 };
    int c[] = { 8, 10 };
    int d[] = { 15, 18 };

    intervals[0] = a;  // ��0ҳ�� [1,3]
    intervals[1] = b;  // ��1ҳ�� [2,6]
    intervals[2] = c;  // ��2ҳ�� [8,10]
    intervals[3] = d;  // ��3ҳ�� [15,18]

    // ���� intervalsColSize��ÿ����2�У�
    int* intervalsColSize = (int*)malloc(sizeof(int));
    *intervalsColSize = 2;

    // ׼�����������ӡ������ӷ���ֵ
    int returnSize;           // �ӡ��м������䡱
    int* returnColumnSizes;   // �ӡ�ÿ���м��С�

    // 2. ���� merge ����
    printf("ԭʼ���䣺[[1,3],[2,6],[8,10],[15,18]]\n");
    int** result = merge(intervals, n, intervalsColSize, &returnSize, &returnColumnSizes);

    // 3. ��ӡ���
    printResult(result, returnSize, returnColumnSizes);

    // 4. �ͷ��ڴ棨��ϰ�ߣ�
    free(intervals);
    free(intervalsColSize);
    // ע�⣺result �е�ÿ��С������ malloc �ģ�ʵ����Ŀ��ҲӦ�ͷ�
    // Ϊ�򻯣�����ʡ��

    return 0;  // ������������
}