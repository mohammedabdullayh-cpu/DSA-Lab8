#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

const int MAX = 100;
ListNode* heap[MAX];
int heapSize = 0;

void swapNodes(int a, int b) { ListNode* t = heap[a]; heap[a] = heap[b]; heap[b] = t; }

void insertHeap(ListNode* n) {
    int i = heapSize++;
    heap[i] = n;
    while (i > 0) {                      
        int p = (i - 1) / 2;
        if (heap[p]->val <= heap[i]->val) break;
        swapNodes(p, i);
        i = p;
    }
}

ListNode* extractMin() {
    ListNode* top = heap[0];
    heap[0] = heap[--heapSize];
    int i = 0;
    while (true) {                        
        int l = 2 * i + 1, r = 2 * i + 2, s = i;
        if (l < heapSize && heap[l]->val < heap[s]->val) s = l;
        if (r < heapSize && heap[r]->val < heap[s]->val) s = r;
        if (s == i) break;
        swapNodes(s, i);
        i = s;
    }
    return top;
}

ListNode* mergeKLists(ListNode* lists[], int k) {
    heapSize = 0;
    for (int i = 0; i < k; i++)
        if (lists[i]) insertHeap(lists[i]);

    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (heapSize > 0) {
        ListNode* smallest = extractMin();
        tail->next = smallest;
        tail = smallest;
        if (smallest->next) insertHeap(smallest->next);
    }
    return dummy.next;
}

ListNode* build(const int arr[], int n) {
    ListNode dummy(0);
    ListNode* t = &dummy;
    for (int i = 0; i < n; i++) { t->next = new ListNode(arr[i]); t = t->next; }
    return dummy.next;
}

void printList(ListNode* h) {
    if (!h) { cout << "(empty)" << endl; return; }
    for (; h; h = h->next) cout << h->val << (h->next ? " -> " : "");
    cout << endl; }

int main() {
    int k;
    cout << "Enter number of linked lists (max " << MAX << "): ";
    cin >> k;

    ListNode* lists[MAX];
    for (int i = 0; i < k; i++) {
        int n;
        cout << "List " << i + 1 << " - enter size: ";
        cin >> n;
        int arr[MAX];
        cout << "List " << i + 1 << " - enter " << n << " elements in ascending order: ";
        for (int j = 0; j < n; j++) cin >> arr[j];
        lists[i] = build(arr, n); }

    cout << "\nInput lists:\n";
    for (int i = 0; i < k; i++) printList(lists[i]);

    ListNode* merged = mergeKLists(lists, k);
    cout << "\nMerged list:\n";
    printList(merged);

    while (merged) { ListNode* t = merged; merged = merged->next; delete t; }
    return 0;
}