#include <iostream>
#include <Windows.h>

using namespace std;
void convert(bool f[], int result[], int n) {
	for (int i = 0; i < (1 << n); i++) {
		result[i / 32] |= f[i] << (i % 32);
	}
}

//void equalAsm(){
//	const int N = 3;
//	const int sizee = 1 << N; //2^n byte
//	int countSDNF = 0, countSKNF = 0;
//	bool normalArr[sizee] = { 1,1,1,1,1,0,0,0 };
//	int arr[(sizee + 31) / 32] = { 0 };
//	convert(normalArr, arr, N);
//	int numOfOne = 0;
//	for (int i = 0; i < sizee; i++)
//		if (normalArr[i] == 1)
//			numOfOne++;
//	for (int j = 0; j < N ; j++)
//		for (int i = 0; i < (1 << N); i++)
//			if (!(((i >> j) & 1) == normalArr[i]))
//				if (((i >> j) & 1) == 0) {
//					countSDNF++;
//					break;
//				}
//	for (int j = 0; j < N; j++)
//		for (int i = 0; i < (1 << N); i++)
//			if (!(((i >> j) & 1) == normalArr[i]))
//				if (((i >> j) & 1) != 0) {
//					countSKNF++;
//					break;
//				}
//				
//	countSDNF += numOfOne * N - 1;
//	countSKNF += (sizee - numOfOne) * N - 1;
//	cout << "СКНФ:" << countSKNF << "\tСДНФ:" << countSDNF << "\nдля столбца значений функции:\n";
//	for (int i = 0; i < sizee; i++)
//		cout << normalArr[i] << endl;
//}

int main(){
	SetConsoleOutputCP(1251);
     const int N = 3;
	const int sizee = 1 << N; //2^n byte
	int countSDNF = 0, countSKNF = 0;
	bool normalArr[sizee] = { 1,1,1,1,1,0,0,0 };
	//{1,1,1,1};
		/*{ 0,0,0,0,0,0,0,1 };*/
	//{ 0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
	int arr[(sizee + 31) / 32] = { 0 };
	convert(normalArr, arr, N);
	int numOfOne=0;
	int i, j;
	equalAsm();
	
	_asm {
		  mov         numOfOne, 0
		//	for (int i = 0; i < sizee; i++)
		mov        i, 0
		jmp         is_i_in_first_for_less_than_arr_size
	next_i_in_first_for :
		mov         eax, i
		add         eax, 1
		mov         i, eax
	is_i_in_first_for_less_than_arr_size :
		mov eax, i
		cmp       eax, sizee
		 jae         inside_forJ//переход, если больше или равно

		//	if (arr[i] == 1)
		mov ecx, i
		mov edx, ecx
		shr ecx, 5
		and edx, 31
		bt arr[ecx * 4], edx
		jnc   is_i_equals_1//Перейти при отсутствии переноса

		//numOfOne++;
		mov         eax, numOfOne
		add         eax, 1
		mov       numOfOne, eax

	is_i_equals_1 ://if not
		jmp        next_i_in_first_for

		//for (int j = 0; j < N - 1; j++)
	inside_forJ :
		mov        j, 0
		 jmp         is_j_less_than_N
	next_j_in_second_for :
		mov         eax, j
		add         eax, 1
		mov        j, eax
	is_j_less_than_N :
		mov eax, N
		cmp        j, eax
		jge         end_second_forJ

		//		for (int i = 0; i < (1 << N); i++)
		mov       i, 0
		jmp         size_byte
	next_i_in_second_for :
		mov         eax, i
		add         eax, 1
		mov        i, eax
		size_byte:
		mov eax,i
		cmp       eax, sizee
		jge         end_second_if_in_second_for 

		//		if (!(((i >> j) & 1) == arr[i]))
		mov         eax, i
		mov         ecx, j
		sar         eax, cl
		and eax, 1
		mov ecx, i
		mov edx, ecx
		shr ecx, 5
		and edx, 31
		bt arr[ecx * 4], edx
		setc dl
		cmp         al, dl  //al- самый младший байт eax(and eax, 1)

		jnc          end_if_in_second_for
		//	if (((i >> j) & 1) == 0) {
		mov         eax, i
		mov         ecx, j
		sar         eax, cl
		and eax, 1
		cmp eax,0
		je         else_if //Переход, если не равно

		jmp         end_second_if_in_second_for	//		break;

		jmp          end_if_in_second_for

	else_if:
		mov         eax, countSKNF
		add         eax, 1	//	countSKNF++;
		mov         countSKNF, eax
		jmp          end_second_if_in_second_for//			break;

	end_if_in_second_for :
		jmp         next_i_in_second_for

	end_second_if_in_second_for :
		jmp         next_j_in_second_for
			end_second_forJ :


		//for (int j = 0; j < N - 1; j++)
	inside_for2:
		mov        j, 0
			jmp         is_j_less_than_N2
			next_j_in_second_for2 :
		mov         eax, j
			add         eax, 1
			mov        j, eax
			is_j_less_than_N2 :
		mov eax, N
			cmp        j, eax
			jge         end_second_forJ2

			//		for (int i = 0; i < (1 << N); i++)
			mov       i, 0
			jmp         size_byte2
			next_i_in_second_for2 :
		mov         eax, i
			add         eax, 1
			mov        i, eax
			size_byte2 :
		mov eax, i
			cmp       eax, sizee
			jge         end_second_if_in_second_for2

			//		if (!(((i >> j) & 1) == arr[i]))
			mov         eax, i
			mov         ecx, j
			sar         eax, cl
			and eax, 1
			mov ecx, i
			mov edx, ecx
			shr ecx, 5
			and edx, 31
			bt arr[ecx * 4], edx
			setc dl
			cmp         al, dl  //al- самый младший байт eax(and eax, 1)

			jnc          end_if_in_second_for2
			//	if (((i >> j) & 1) == 0) {
			mov         eax, i
			mov         ecx, j
			sar         eax, cl
			and eax, 1
			cmp eax, 0
			jne         else_if2 //Переход, если не равно

			mov         eax, countSDNF
			add         eax, 1	//countSDNF++;
			mov         countSDNF, eax
			jmp         end_second_if_in_second_for2	//		break;

			jmp          end_if_in_second_for2

			else_if2 :

			end_if_in_second_for2 :
		jmp         next_i_in_second_for2

			end_second_if_in_second_for2 :
		jmp         next_j_in_second_for2
			end_second_forJ2 :

		//	countSDNF += numOfOne * N - 1;
		mov eax,numOfOne
		mul        N//numOfOne*N 
		mov         ecx, countSDNF 
		add ecx, eax 
		cmp ecx, 0
		jbe withoutDec//Перейти, если меньше или равно
		dec ecx
	withoutDec :
		mov         countSDNF, ecx

		//  countSKNF += (N - numOfOne) * N - 1;
		mov         eax, sizee
		sub         eax, numOfOne
		mul         N
		mov         ecx, countSKNF
		add ecx, eax
		cmp ecx,0
		jbe withoutDecAgain
		dec ecx
	withoutDecAgain:
		mov         countSKNF, ecx
	}
	
		cout << "СКНФ:" << countSKNF << "\tСДНФ:" << countSDNF <<"\nдля столбца значений функции:\n";
		for (int i = 0; i < sizee; i++)
			cout << normalArr[i] << endl;
}
