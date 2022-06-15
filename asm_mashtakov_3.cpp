#include <iostream>

int main()
{
    int a, b;
    bool owf_flag = 0;
    bool zerodev_flag = 0;
    std::cin >> a >> b;
    _asm {
        mov ebx, a;     // ebx = a
        mov eax, b;     // eax = b
        cmp ebx, eax;   // comparing a and b
        jl less;       
        jg greater;   
        mov a, -10;     // if a==b
        jmp ext;
    less:               // if a<b
        cmp ebx, 0;
        je zerodev;
        sub eax, 5;     // eax = b-5
        cdq;
        idiv ebx;       // eax = (b-5)/a
        mov a, eax;     
        jmp ext;
    greater:            // if a>b
        cmp eax, 0;
        je zerodev;
        imul ebx, ebx;  // ebx = a^2
        jo owf; 
        cdq;    
        mov eax, ebx;   // eax = a^2
        mov ebx, b;
        idiv ebx;       // eax = a^2/b
        add eax, 100;   // eax = a^2/b+100
        mov a, eax;
        jmp ext;
    owf:
        mov owf_flag, 1;
        jmp ext;
    zerodev:
        mov zerodev_flag, 1;
    ext:

    }
    if (zerodev_flag) {
        std::cout << "Error: divide by zero!\n";
        return -1;
    }
    if (owf_flag) {
        std::cout << "Error: integer owerflow!\n";
        return -1;
    }
    std::cout << a;
    return 0;
}

