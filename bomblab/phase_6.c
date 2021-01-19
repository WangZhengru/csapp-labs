extern void explode();

struct Node
{
    int          idx, val;
    struct Node* next;
};

void phase_6(char* input)
{
    int          rsp[6];
    struct Node* arr[6];
    int          r12d = 0;
    for (int* r13 = rsp;; ++r13) {
        int eax = r13[r12d];
        --eax;
        if (eax > 5) explode();
        if (++r12d == 6) break;
        for (int ebx = r12d; ebx <= 5; ++ebx)
            if (eax == rsp[ebx]) explode();
    }
    for (int* rax = rsp; rax != rsp + 6; ++rax) { *rax = 7 - *rax; }
    for (int rsi = 0; rsi != 6; ++rsi) {
        int ecx = rsp[rsi];
        if (ecx <= 1) {
            // impossible
        }
        else {
            struct Node* rdx = 0x6032d0;                               // list head
            for (int eax = 1; eax != ecx; ++eax) { rdx = rdx->next; }  // link list
            arr[rsi] = rdx;
        }
    }
    struct Node *rbx = arr[0], *rcx = rbx;
    for (int i = 1; i != 6; ++i) {
        struct Node* rdx = arr[i];
        rcx->next        = rdx;
        rcx              = rdx;
    }  // last next == NULL
    for (int ebp = 5; ebp != 0; --ebp) {
        if (rbx->val < rbx->next->val) explode();
        rbx = rbx->next;
    }
}