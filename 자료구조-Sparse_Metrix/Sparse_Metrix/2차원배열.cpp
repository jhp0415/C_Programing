/*2차원배열을 가지고 희소행렬의 전치행렬 구하기*/

#include<stdio.h>
#include<malloc.h>
#include<Windows.h>
#include<time.h>

void main()
{
	int size = 0;
	printf("행렬의 사이즈를 지정하세요:");
	scanf("%d", &size);

	srand(time(NULL));
	int num;
	int **arr;
	arr = (int**)malloc(sizeof(int*) * size);
	for (int i = 0; i<size; i++) {
		arr[i] = (int*)malloc(sizeof(int) * size);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if ((num = rand() % 2) == 0)
				arr[i][j] = 0;
			else
				arr[i][j] = rand()%10;
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
	printf("\n\n\n");


	//전치행렬 바꾸기
	int** arr_T = (int**)calloc(size, sizeof(int*));
	for (int i = 0; i < size; i++) arr_T[i] = (int*)calloc(size, sizeof(int));


	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			arr_T[j][i] = arr[i][j];
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d ", arr_T[i][j]);
		printf("\n");
	}


	system("pause");
}