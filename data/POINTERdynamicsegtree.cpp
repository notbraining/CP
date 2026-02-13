struct Node{
    int freq = 0;
    int lazy = -1;
    //lazy = -1 means no pending updates
    Node* left = nullptr;
    Node* right = nullptr;
};
struct sparse_segtree{
    Node* root = new Node;
    int sz = 1e18;
    void apply_lazy(Node* curr, int val, int len){
        curr->freq = val * len;
        curr->lazy = val;
    }
    void push_down(Node* curr, int l, int r){
        //getting ready to visit the children nodes

        if(curr->left == nullptr) curr->left = new Node;
        if(curr->right == nullptr) curr->right = new Node;
        if(curr->lazy == -1)
            return;
        int mid = (l + r) / 2;
        apply_lazy(curr->left, curr->lazy, mid - l + 1);
        apply_lazy(curr->right, curr->lazy, r - mid);
        curr->lazy = -1;
    }

    int range_sum(Node* curr, int l, int r, int ql, int qr){
        if(r < ql || qr < l){
            return 0;
        }
        if(ql <= l && r <= qr){
            return curr->freq;
        }
        int mid = (l + r) / 2;
        push_down(curr, l, r);
        return range_sum(curr->left, l, mid, ql, qr) + range_sum(curr->right, mid + 1, r, ql, qr);
    }
    void range_update(Node* curr, int l, int r, int ul, int ur, int val){
        if(r < ul || ur < l)
            return;
        if(ul <= l && r <= ur){
            apply_lazy(curr, val, r - l + 1);
            return;
        }
        int mid = (l + r) / 2;
        push_down(curr, l, r);
        range_update(curr->left, l, mid, ul, ur, val);
        range_update(curr->right, mid + 1, r, ul, ur, val);
        curr->freq = curr->left->freq + curr->right->freq;
    }
    int range_sum(int ql, int qr){
        return range_sum(root, 0LL, sz, ql, qr);
    }
    void range_update(int ul, int ur, int val){
        range_update(root, 0, sz, ul, ur, val);
    }
    sparse_segtree(int _){
        sz = _ + 10;
    }
};
