#include <iostream>
using namespace std;
int main()
{
    int n;
    bool owerflowf = 0;
    cin >> n;
    int* array = new int[n];
    for (int i = 0; i < n; i++) 
        cin >> array[i];
    int d;
    cin >> d;
    _asm {
        mov ecx, n;             
        mov esi, 0;             
        mov ebx, array;         
        mov edx, d;
    loop_begin:
        mov eax, [ebx + esi * 4];   eax = array[esi]
        cmp eax, 0;             
        jge loop_end;           
        push edx;               
        mov edx, d;             
        cmp eax, edx;           
        jg loop_end;            
        pop edx;                
        add edx, eax;
        jo owerflow;            
    loop_end:
        inc esi;                
        loop loop_begin;        
        jmp ext;               
    owerflow:
        mov owerflowf, 1;
    ext:
        mov d, edx;
    }
    if (owerflowf) {
        cout << "Owerflow error!\n";
        return -1;
    }
    cout << d;
}