#include <iostream>
#include<Windows.h>

const int N = 6;

using Graph = int[N][N];

using namespace std;
//
//bool is_digraphOnCPlusPlus(unsigned int graph[N][N]) {
//	unsigned int marks[N] = { };  
//	for (int i = 0; i < N; i++) { 
//		for (int j = i + 1; j < N; j++) { 
//			if (graph[i][j] == 1) { 
//				if (marks[i] % 2 == marks[j] % 2 && marks[j] == 1) {
//				}
//				else { 
//					marks[j] = marks[i] + 1;
//				}
//			}
//		}
//	}
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			if (marks[i] % 2 != marks[j] % 2 && graph[i][j] == 0)
//				return false;
//		}
//	}
//	return true;  
//}

void convert(const Graph& g, int out[]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int index = i * N + j;
			out[index / 32] |= g[i][j] << (index % 32);
		}
	}
}


bool is_digraph(int graph[]) {
	unsigned int marks[N] = {};//пустой инициализатор заполняет массив нулями 
	int i, j;
	bool isIt;
	_asm {
		xor eax, eax
		mov        marks, eax
		mov        i, 0//int i = 0
		jmp         is_i_inFirstcicle_less_then_N

		next_i_in_first_for :
		mov         eax, i//
			add         eax, 1//i++
			mov         i, eax//

		is_i_inFirstcicle_less_then_N :
		    mov eax, i
			cmp        eax, N//i<N?
			jge         endFirstForI
			mov         eax, i//
			add         eax, 1//j=i+1
			mov         j, eax//
			jmp          is_j_inFirstcicle_less_then_N
			add         eax, 1
				next_j_in_first_for :
		mov        j, eax
		is_j_inFirstcicle_less_then_N :
		   mov eax, j
			cmp         eax, N//j<N?
			jge        endFirstForJ
			////////////////////

			mov ecx, i
			mul N
			add ecx, j//i*N + j

			mov ebx, ecx
			shr ecx, 5
			and ebx, 31
			bt graph[ecx * 4], ebx
			setc cl

			cmp cl, 1//graph[i][j] == 1?
			jne         end_if_in_first_forI//if not graph[i][j] == 1

			mov         eax, i
			mov         eax, marks[eax * 4]
			xor edx, edx
			mov         ecx, 2
			div          ecx
			mov         ecx, edx
			mov         edx, j
			mov         eax, marks[edx * 4]
			xor edx, edx
			mov         esi, 2
			div          esi
			cmp         ecx, edx// marks[i] % 2 == marks[j] % 2?
			jne         firstElse

			mov         eax, j
			cmp          marks[eax * 4], 1// marks[j] == 1?
			jne         firstElse

			xor al, al
			jmp         isthisreturn


			firstElse ://marks[j] = marks[i] + 1;
		mov         eax, i
			mov         ecx, marks[eax * 4]
			add         ecx, 1
			mov         edx, j
			mov          marks[edx * 4], ecx

			end_if_in_first_forI :
		jmp         next_j_in_first_for

			endFirstForJ :
		jmp         next_i_in_first_for



			endFirstForI ://второй вложенный цикл
		mov        i, 0
			jmp         is_i_inSecondcicle_less_then_N

			next_i_in_second_for :
		mov         eax, i
			add         eax, 1
			mov         i, eax

			is_i_inSecondcicle_less_then_N :
		mov eax, i
			cmp         eax, N
			jge        endSecondForI
			mov         j, 0
			jmp        is_j_inSecondcicle_less_then_N

			next_j_in_second_for :
		mov         eax, j
			add         eax, 1
			mov         j, eax


			is_j_inSecondcicle_less_then_N :// if (marks[i] % 2 != marks[j] % 2 && graph[i][j] == 0)
		mov eax, j
			cmp         eax, N
			jge         endSecondForJ
			mov         eax, i
			mov         eax, marks[eax * 4]
			xor edx, edx
			mov         ecx, 2
			div         ecx
			mov         ecx, edx
			mov         edx, j
			mov         eax, marks[edx * 4]
			xor edx, edx
			mov         esi, 2
			div         esi
			cmp         eax, edx //marks[i] % 2 != marks[j] % 2?

			je          end_if_in_second_forI
			mov ebx, eax
			shr eax, 5//альтернативОчка
			and ebx, 31
			bt graph[eax * 4], ebx
			setc cl

			cmp cl, 0//graph[i][j] == 0?
			jne         end_if_in_second_forI
			xor al, al
			jmp         isthisreturn

			end_if_in_second_forI :
		jmp         next_j_in_second_for

			endSecondForJ :
		jmp         next_i_in_second_for

			endSecondForI :
		mov         al, 1

			isthisreturn :
			mov isIt, al
	}
	return isIt;
}

int main() {
	SetConsoleOutputCP(1251);
	Graph graph =
		

	{ { 0,1,1 },
	{ 1,0,0 }, //полный двудольный
	{ 1,0,0 }, };

	//{ { 0,1,0 },
	//{ 1,0,1 }, //полный двудольный
	//{ 0,1,0 }, };

	//{ { 0, 1, 1, 0, 0, 0, 1 },
//  { 1, 0, 1, 1, 0, 0, 0 },
//  { 1, 1, 0, 0, 0, 0, 0 },
//  { 0, 1, 0, 0, 1, 0, 0 }, //не (полный двудольный)
//  { 0, 0, 0, 1, 0, 1, 0 },
//  { 0, 0, 0, 0, 1, 0, 1 },
//  { 1, 0, 0, 0, 0, 1, 0 } };
	int arr[5] = { 0 };
	convert(graph, arr);
	cout << "Граф оказался " << (is_digraph(arr) ? "" : "НЕ ") << "полным двудольным" << endl;
}
