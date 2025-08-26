#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = NULL;
        ListNode* p = NULL;
        int a = 0; // 进位

        while (l1 != NULL && l2 != NULL) {
            int sum = l1->val + l2->val + a;
            if (p == NULL) {
                p = new ListNode(sum % 10);
            } else {
                p->next = new ListNode(sum % 10);
                p = p->next;
            }
            if (head == NULL) { 
                head = p; 
            }
            a = sum / 10;
            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1 != NULL) {
            p->next = new ListNode();
            p->next->val = (l1->val + a) % 10;
            a = (l1->val + a) / 10;
            p = p->next;
            l1 = l1->next;
        }

        while (l2 != NULL) {
            p->next = new ListNode();
            p->next->val = (l2->val + a) % 10;
            a = (l2->val + a) / 10;
            p = p->next;
            l2 = l2->next;
        }

        if (a != 0) {
            p->next = new ListNode(a);
        }

        return head;
    }
};

void deleteList(ListNode* head) {
    ListNode* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {

    ListNode* l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);

    ListNode* l2 = new ListNode(5);
    l2->next = new ListNode(6);
    l2->next->next = new ListNode(4);

    cout << "输入：" << endl;
    cout << "l1: ";
    ListNode* temp = l1;
    while (temp != nullptr) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << " (表示 342)" << endl;

    cout << "l2: ";
    temp = l2;
    while (temp != nullptr) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << " (表示 465)" << endl;

    Solution solution;
    ListNode* result = solution.addTwoNumbers(l1, l2);

    cout << "结果: ";
    temp = result;
    while (temp != nullptr) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << " (表示 807)" << endl;

    deleteList(l1);
    deleteList(l2);
    deleteList(result);

    return 0;
}