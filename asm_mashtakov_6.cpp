#include <iostream>

using namespace std;
int main()
{
    double a, b;
    cin >> a >> b;
    bool zero_error_flag = 0;
    int c10 = -10, c100 = 100, c5 = -5;
    _asm {
        fld a;
        fld b;
        fcomi st, st(1);
        jb a_g;
        ja a_l;
        fild c10;
        fst a;
        jmp ext;
    a_g:
        fxam;
        fstsw ax;
        sahf;
        jz zero_error;
        fdivp st(1), st;
        fild c100;
        fadd;
        fst a;
        jmp ext;
    a_l:
        fild c5;
        fadd;
        fdiv st, st(1);
        fst a;
        jmp ext;
    zero_error:
        mov zero_error_flag, 1;
    ext:
    }
    if (zero_error_flag) {
        cout << "zero error" << endl;
        return -1;
    }
    cout << a << endl;
    return 0;
}
