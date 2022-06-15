#include <iostream>

// (7-a*b/4)/(1+c/a-b)

int main()
{
	int a, b, c;
	std::cin >> a >> b >> c;
	bool owf_err_flag = 0;
	bool zero_dev_flag = 0;
	_asm {
		mov eax, c;		// eax = c
		mov ecx, a;		// ecx = a
		cmp ecx, 0;		// if a==0 then zero division error
		je zerodev;
		cdq;
		idiv ecx;		// eax = c/a
		inc eax;		// eax = 1+c/a
		jo owf;
		mov ebx, b;		// ebx = b
		sub eax, ebx;	// eax = 1+c/a-b
		cmp eax, 0;
		je zerodev;		// if eax==0 then zero devision error
		push eax;		// put eax to stack top
		mov eax, a;		// eax = a
		imul eax, ebx;	// eax = a*b
		jo owf;			// cheking if owerflow
		mov ebx, 4;		// ebx = 4
		cdq;
		idiv ebx;		// eax = a*b/4
		mov ebx, 7;		// ebx = 7
		sub ebx, eax;	// ebx = 7-a*b/4 
		mov eax, ebx;	// eax = 7-a*b/4 
		pop ebx;		// taking divider form stack top
		cdq;
		idiv ebx;		// eax = (7-a*b/4)/(1+c/a-b)
		mov a, eax;
		jmp ext;
	owf:
		mov owf_err_flag, 1;
		jmp ext;
	zerodev:
		mov zero_dev_flag, 1;
	ext:
	}
	if (zero_dev_flag) {
		std::cout << "Error: divide by zero!\n";
		return -1;
	}
	if (owf_err_flag) {
		std::cout << "Error: integer owerflow!\n";
		return -1;
	}
	std::cout << a;
	return 0;
}
