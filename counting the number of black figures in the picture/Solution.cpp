// task2_5.0.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

//int countAnglesOnCPLusPLus(int arr[], int w, int h) {
//	int mainCounter = 0;
//	int counterX = 0;
//	int counterY = 0;
//	for (int y = 0; y < h - 3; y++) {
//		for (int x = 0; x < w - 3; x++) {
//			counterX = 0;
//			counterY = 0;
//			if (arr[y * w + x] == 0) goto skip;
//
//			while (arr[y * w + x + counterX] == 1 && x + counterX < w) counterX++;
//			while (arr[(y + counterY) * w + x] == 1 && y + counterY < h) counterY++;
//			if (counterX != counterY) goto skip; // должны быть равной длины
//			if (counterX < 4) goto skip; // меньше 4 пикселей не получится
//
//			for (int i = 0; i < counterX; i++) {
//				//if (x != 0)
//				//    if (arr[(y + i) * w + x - 1] != 0) goto skip; // проверка белого слева
//				//if (y != 0)
//				//    if (arr[(y - 1) * w + x + i] != 0) goto skip; // проверка белого сверху
//				if (y + i + 1 != h)
//					if (arr[(y + i + 1) * w + x + 1] != 0) goto skip; // проверка вертикального белого внутри
//				if (x + 1 + i != w)
//					if (arr[(y + 1) * w + x + 1 + i] != 0) goto skip; // проверка горизонтального белого внутри
//			}
//			//if (y + counterX != h) {
//			//    if (arr[(y + counterX) * w + x] != 0) goto skip; // проверка белого под линиями
//			//    if (arr[(y + counterX) * w + x + 2] != 0) goto skip; // проверка белого под линиями
//			//}
//			//if (x + counterX != w) {
//			//    if (arr[y * w + x + counterX] != 0) goto skip;  // проверка справа от линий
//			//    if (arr[(y + 2) * w + x + counterX] != 0) goto skip;  // проверка справа от линий
//			//}
//
//			for (int i = 0; i < counterX - 2; i++) { // проверка внутреннего уголка
//				if (arr[(y + i + 2) * w + x + 2] != 1) goto skip; // проверка внутреннего уголка (вертикально)
//				if (arr[(y + 2) * w + x + i + 2] != 1) goto skip; // проверка внутреннего уголка (горизонтально)
//				if (y + i + 3 != h)
//					if (arr[(y + i + 3) * w + x + 3] != 0) goto skip; // проверка справа от внутреннего уголка
//				if (x + i + 3 != w)
//					if (arr[(y + 3) * w + x + i + 3] != 0) goto skip; // проверка белого под внутренним уголком
//			}
//			mainCounter++;
//		skip:;
//		}
//	}
//	cout << counterX << counterY;
//	return mainCounter;
//}

int countAngles(int arr[], int w, int h) {
	int mainCounter = 0, counterX = 0, counterY = 0; int x, y, i, i2 = 0;
	//int test1 = 0, test2 = 0;
	_asm {
		/*    mov         mainCounter,
		  mov        counterX, 0
			mov         counterY, 0*/
			// for (int y = 0; y < h - 3; y++) {
		mov        y, 0
		jmp         is_y_less_than_h_minus_3
		nextForY :
		mov         eax, y
			add         eax, 1
			mov     y, eax
			is_y_less_than_h_minus_3 :
		mov         eax, h
			sub         eax, 3
			cmp       y, eax
			jge          end_first_for
			//    for (int x = 0; x < w - 3; x++) {
			mov       x, 0
			jmp          is_x_less_than_w_minus_3
			nextForX :
		mov         eax, x
			add         eax, 1
			mov        x, eax
			is_x_less_than_w_minus_3 :
		mov         eax, w
			sub         eax, 3
			cmp       x, eax
			jge         end_second_for
			//   counterX = 0;
			mov         counterX, 0
			//      counterY = 0;
			mov         counterY, 0
			//  if (arr[y * w + x] == 0) goto skip;
			mov         eax, y
			mul  w
			add         eax, x
			mov         ebx, eax
			shr eax, 5
			and ebx, 31
			bt[edi + eax * 4], ebx
			/* setc al
			 cmp al,0*/
			jc         if_first_if_not_zero
			jmp         skip

			//   while (arr[y * w + x + counterX] == 1 && x + counterX < w) counterX++;
			if_first_if_not_zero :
		mov         eax, y
			mul w
			add         eax, x
			add         eax, counterX
			mov         ebx, eax
			shr eax, 5
			and ebx, 31
			bt[edi + eax * 4], ebx
			// setc al
			//cmp         al, 1//arr[y * w + x + counterX] == 1?
			jnc       second_while_begin
			mov         eax, x
			add         eax, counterX
			cmp         eax, w //x + counterX < w?
			jge        second_while_begin
			mov         eax, counterX
			add         eax, 1
			mov         counterX, eax
			jmp         if_first_if_not_zero
			//    while (arr[(y + counterY) * w + x] == 1 && y + counterY < h) counterY++;
			second_while_begin :
		mov         eax, y
			add         eax, counterY
			mul w
			add         eax, x
			mov         ebx, eax
			shr eax, 5
			and ebx, 31
			bt[edi + eax * 4], ebx
			//setc al
			//cmp         al, 1//arr[(y + counterY) * w + x] == 1?
			jnc         end_second_while
			mov         eax, y
			add         eax, counterY
			cmp         eax, h// y + counterY < h?
			jge         end_second_while
			mov         eax, counterY
			add         eax, 1
			mov         counterY, eax
			jmp        second_while_begin
			//  if (counterX != counterY) goto skip; // должны быть равной длины
			end_second_while :
		mov         eax, counterX
			mov ebx, counterY
		//	mov test1,eax
		//	mov test2,ebx
			cmp         eax, ebx
			je          if_counters_equals
			jmp         skip
			//  if (counterX < 4) goto skip; // меньше 4 пикселей не получится
			if_counters_equals :
	     	cmp         counterX, 4

			jge        end_first_for
			jmp        	if_more_than_4

			//    //    for (int i = 0; i < counterX; i++) {
			if_more_than_4 :
		mov      i, 0
			jmp        is_i_less_than_counterX
			next_i_in_frist_forI :
		mov         eax, i
			add         eax, 1
			mov        i, eax
			is_i_less_than_counterX :
		mov         eax, i
			cmp         eax, counterX
			jge        end_for_counterX

			//   if (y + i + 1 != h)
			mov         eax, i
			add         eax, y
			inc eax
			cmp         eax, h

			je          if_y_plus_i_plus_1_not_equals_h
			//  if (arr[(y + i + 1) * w + x + 1] != 0) goto skip; // проверка вертикального белого внутри

			mov         eax, i
			add eax, y
			inc eax
			mul w
			add         eax, x
			inc eax
			mov         ebx, eax
			shr eax, 5
			and ebx, 31
			bt[edi + eax * 4], ebx

			jnc        if_y_plus_i_plus_1_not_equals_h
			jmp         skip
			//       if (x + 1 + i != w)
			if_y_plus_i_plus_1_not_equals_h :
		mov         eax, i
			add eax, x
			inc eax
			cmp         eax, w
			je           if_x_plus_i_plus_1_not_equals_w
			//      if (arr[(y + 1) * w + x + 1 + i] != 0) goto skip; // проверка горизонтального белого внутри
			mov         eax, y
			add         eax, 1
			mul w
			add         eax, x
			add eax, i
			inc eax
			mov         ebx, eax
			shr eax, 5
			and ebx, 31
			bt[edi + eax * 4], ebx
			/*  setc al
			  cmp         al, 0*/
			jnc          if_x_plus_i_plus_1_not_equals_w
			jmp         skip

			if_x_plus_i_plus_1_not_equals_w :
		jmp          next_i_in_frist_forI

			//    for (int i = 0; i < counterX - 2; i++) { // проверка внутреннего уголка
			end_for_counterX :
		mov        i2, 0
			jmp         is_i_less_than_counterX_minus_2
			nextI2 :
		mov         eax, i2
			add         eax, 1
			mov        i2, eax
			is_i_less_than_counterX_minus_2 :
		mov         eax, counterX
			sub         eax, 2
			cmp        i2, eax
			jge         end_forI2
			//     if (arr[(y + i + 2) * w + x + 2] != 1) goto skip; // проверка внутреннего уголка (вертикально)
			mov         eax, i2
			add eax, y
			add eax, 2
			mul w
			add         eax, x
			add eax, 2
			mov         ebx, eax
			shr eax, 5
			and ebx, 31
			bt[edi + eax * 4], ebx
			/* setc al
			 cmp         al, 1*/
			jc          inner_angle
			jmp         skip
			//  if (arr[(y + 2) * w + x + i + 2] != 1) goto skip; // проверка внутреннего уголка (горизонтально)
			inner_angle :
		mov         eax, y
			add         eax, 2
			mul w
			add         eax, x
			add         eax, i2
			mov         ecx, arr
			mov         ebx, eax
			shr eax, 5
			and ebx, 31
			bt[edi + eax * 4], ebx
			/* setc al
			 cmp         al, 1*/
			jc            if_inner_angle_horizontal
			jmp         skip
			//       if (y + i + 3 != h)
			if_inner_angle_horizontal :
		mov         eax, i2
			mov         ecx, y
			lea         edx, [ecx + eax + 3]
			cmp         edx, h
			je          if_y_plus_i_plus_3_equals_h
			//           if (arr[(y + i + 3) * w + x + 3] != 0) goto skip; // проверка справа от внутреннего уголка
			mov         eax, i2
			add eax, y
			add eax, 3
			mul w
			add         eax, x
			add eax, 3
			mov         ebx, eax
			shr eax, 5
			and ebx, 31
			bt[edi + eax * 4], ebx
			/* setc al
			 cmp         al, 0*/
			jnc           if_y_plus_i_plus_3_equals_h
			jmp         skip
			//  if (x + i + 3 != w)
			if_y_plus_i_plus_3_equals_h :
		mov         eax, i2
			mov         ecx, x
			lea         edx, [ecx + eax + 3]
			cmp         edx, w
			je          if_x_plus_i_plus_3_equals_w
			//    if (arr[(y + 3) * w + x + i + 3] != 0) goto skip; // проверка белого под внутренним уголком
			mov         eax, y
			add         eax, 3
			mul w
			add         eax, x
			add         eax, i2
			add eax, 3
			mov         ebx, eax
			shr eax, 5
			and ebx, 31
			bt[edi + eax * 4], ebx
			/*  setc al
			  cmp         al, 0*/
			jnc           if_x_plus_i_plus_3_equals_w
			jmp         skip

			if_x_plus_i_plus_3_equals_w :
		jmp         nextI2
			//  mainCounter++;
			end_forI2 : mov         eax, mainCounter
			add         eax, 1
			mov         mainCounter, eax

			skip :
		jmp        nextForX

			end_second_for :
		jmp        nextForY
			//   return mainCounter;
			end_first_for :
	}
	//cout << test1 << "\t" << test2;
	return mainCounter;

}

int main()
{
	setlocale(LC_ALL, "ru");
	const int W = 10;
	const int H = 10;
	int arr[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 1, 0, 1, 0
	};
	cout << "Количество черных фигур (уголков): " << countAngles(arr, W, H) << endl;
//работает неправильно

}
