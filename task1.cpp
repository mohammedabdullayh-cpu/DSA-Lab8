#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

class MinHeap {
    vector<Node*> h;
    void siftUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (h[p]->freq <= h[i]->freq) break;
            swap(h[p], h[i]);
            i = p; }
    }
    void siftDown(int i) {
        int n = h.size();
        while (true) {
            int l = 2 * i + 1, r = 2 * i + 2, s = i;
            if (l < n && h[l]->freq < h[s]->freq) s = l;
            if (r < n && h[r]->freq < h[s]->freq) s = r;
            if (s == i) break;
            swap(h[s], h[i]);
            i = s;
        }
    }
public:
    void push(Node* n) { h.push_back(n); siftUp(h.size() - 1); }
    Node* pop() {
        Node* top = h[0];
        h[0] = h.back();
        h.pop_back();
        if (!h.empty()) siftDown(0);
        return top;
    }
    int size() const { return h.size(); }
};

void preorder(Node* root, string code, vector<string>& out) {
    if (!root) return;
    if (!root->left && !root->right) {
        out.push_back(code);
        return; }
    preorder(root->left, code + "0", out);
    preorder(root->right, code + "1", out);
}

void freeTree(Node* r) {
    if (!r) return;
    freeTree(r->left);
    freeTree(r->right);
    delete r; }

vector<string> huffmanCodes(const string& S, const vector<int>& f) {
    MinHeap heap;
    for (size_t i = 0; i < S.size(); i++) heap.push(new Node(S[i], f[i]));
    if (heap.size() == 1) {            
        Node* only = heap.pop();
        freeTree(only);
        return {"0"};
    }
    while (heap.size() > 1) {
        Node* a = heap.pop();
        Node* b = heap.pop();
        Node* m = new Node('$', a->freq + b->freq);
        m->left = a;                   
        m->right = b;
        heap.push(m);
    }
    Node* root = heap.pop();
    vector<string> out;
    preorder(root, "", out);
    freeTree(root);
    return out;
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    string S;
    vector<int> f(n);

    cout << "Enter " << n << " distinct characters (no spaces, e.g. abcdef): ";
    cin >> S;

    cout << "Enter " << n << " frequencies (space separated): ";
    for (int i = 0; i < n; i++) cin >> f[i];

    cout << "\nHuffman codes (preorder): ";
    for (auto& c : huffmanCodes(S, f)) cout << c << " ";
    cout << endl;
    return 0; }