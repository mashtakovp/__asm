#include <iostream>

// (7-a*b/4)/(c-a+1)

using namespace std;
int main()
{
    double a, b, c;
    int seven = 7, four = 4;
    bool zero_flag = 0;
    cin >> a >> b >> c;
    _asm {
        fld c;      st(0) = c
        fld a;      st(0) = c, st(1) = a
        fsub;       st(0) = c-a
        fld1;       st(0) = 1, st(1) = c-a
        fadd;       st(0) = c-a+1
        fldz;       st(0) = 0, st(1) = c-a+1
        fcomp;      ?????????? ??????????? ? ?????
        fstsw ax;
        sahf;
        jz zero;    
        fild seven; st(0) = 7, st(1) = c - a + 1
        fld a;      st(0) = a, st(1) = 7, st(2) = c - a + 1
        fld b;      st(0) = b, st(1) = a, st(1) = 7, st(3) = c - a + 1
        fmul;       st(0) = a*b, st(1) = 7, st(2) = c - a + 1
        fild four;  st(0) = 4, st(1) = a*b, st(1) = 7, st(3) = c - a + 1
        fdiv;       st(0) = a*b/4, st(1) = 7, st(2) = c - a + 1     
        fsub;       st(0) = 7-a*b/4, st(1) = c - a + 1
        fxch st(1); st(1) = 7 - a * b / 4, st(0) = c - a + 1
        fdiv;       st(0) = (7 - a * b / 4) / (c - a + 1)
        fst a;      a = (7 - a * b / 4) / (c - a + 1)
        jmp ext;
    zero:
        mov zero_flag, 1;
    ext:

    }
    if (zero_flag) {
        cout << "Divivsion by zero error.";
        return -1;
    }
    cout << a;
}
