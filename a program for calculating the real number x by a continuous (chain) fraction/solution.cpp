#include <iostream>
using namespace std;

int main() {
	const int N = 7;
	int arr[N] = { 1,2,2,2,2,2,2 };
	double x = 0;
	int i = N - 1;
	/*for (; i > 0; i--)
		x = 1 / (arr[i] + x);
	cout << x + arr[0] << endl;*/
	_asm {
		lea esi,arr
		fldz
		mov eax, i
		cmp eax, 0
	nextI :
		mov         eax, i
		fiadd[esi + eax * 4]//x+arr[i]
		fld1
		fdivrp st(1),st(0)
		mov         eax, i
		dec eax
		mov         i, eax
		cmp eax, 0
		jne        nextI
	sThisEnd :
		fiadd [esi]
		fstp x
	}
       cout.precision(10);
	cout << x << endl;
}
