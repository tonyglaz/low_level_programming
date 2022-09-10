#include <iostream>
#include<Windows.h>

using namespace std;

int Stirling(int n, int k) {
	int returnResPart1, returnResPart2;
	_asm {
		mov eax,n
		mov ebx,k
		cmp eax, ebx    //if n==k 
		je ifSame        //return 1
		cmp k, 0         //else if k==0 
		je ifKIsZero   // return 0
		//else
		dec n    //n-1
		dec k    //k-1
		push k
		push n
		call Stirling    //(Stirling(n-1,k-1)
		add esp, 8
		mov returnResPart1, eax
		inc k
		push k
		push n
		call Stirling    //Stirling(n-1,k)
		add esp, 8
		mov returnResPart2,eax
		mov eax,k
		mul returnResPart2 //k* Stirling(n - 1, k)
		add returnResPart1, eax    //Stirling(n-1,k-1) + k*Stirling(n-1,k)
		jmp endIf

		ifSame :       
		mov returnResPart1, 1 //return 1
		jmp endIf
		
		ifKIsZero :
		mov returnResPart1, 0    //return 0
		
		endIf :
	};
	return returnResPart1;
}

int main() {
	SetConsoleOutputCP(1251);
	int n, k;
	cout << "Enter n: ";
	cin >> n;
	cout << "Enter k: ";
	cin >> k;
	cout << "Количество неупорядоченных разбиений "<<n<<"-элементного множества на "<<k<<" непустых подмножеств = "<< Stirling(n,k)<< endl;
}
