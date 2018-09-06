/*0이 아닌 원소들만 표현하는 자료구조를 활용한 전치행렬 구하기*/
#include<stdio.h>
#include<malloc.h>
#include<Windows.h>
#include<time.h>

int height = 0, width = 0;
int **arr;

typedef struct
{
	int row;		//행
	int col;		//열
	int value;		//그 위치 데이터 값
}element;
typedef struct 
{
	element *data;
	int rows;		//행의 개수
	int cols;		//열의 개수
	int terms = 0;		//항의 개수
}Sparse_Matix;

Sparse_Matix Make_Arr()
{
	printf("행렬의 사이즈를 지정하세요:");
	scanf("%d", &height);
	scanf("%d", &width);

	srand(time(NULL));
	int num;
	Sparse_Matix m1;
	m1.data = (element*)malloc(height*width * sizeof(element*));

	int k = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if(((num = rand()%10) % 2) != 0)
			{
				(m1.data + k)->value = num;
				(m1.data + k)->row = i;
				(m1.data + k)->col = j;
					printf("row:%d col:%d 값:%d terms:%d \n", i, j, (m1.data + k)->value, k);
				m1.terms = k++;
			}
		}
	}
	m1.rows = height;
	m1.cols = width;

	return m1;
}

Sparse_Matix TransForm_Arr(Sparse_Matix s)
{
	Sparse_Matix TSM;
	TSM.rows = s.cols;
	TSM.cols = s.rows;
	TSM.data = (element*)malloc(s.terms * sizeof(element*));
	for (int k = 0; k <= s.terms; k++)
	{
		(TSM.data + k)->value = (s.data + k)->value;
		(TSM.data + k)->row = (s.data + k)->col;
		(TSM.data + k)->col = (s.data + k)->row;
		printf("row:%d col:%d 값:%d terms:%d \n", (TSM.data + k)->row, (TSM.data + k)->col,(s.data + k)->value, k);
	}
	printf("변환완료");
	return TSM;
}

void PrintTransArr(Sparse_Matix t)
{
	arr = (int**)malloc(sizeof(int**) * t.rows);
	for (int i = 0; i<t.cols; i++) arr[i] = (int*)malloc(sizeof(int));
	
	for (int i = 0; i < t.rows; i++)
	{
		for (int j = 0; j < t.cols; j++)
		{
			for (int k; k < t.terms; k++)
			{
				if (i == (t.data + k)->row && j == (t.data + k)->col)
					arr[i][j] = (t.data + k)->value;
				else arr[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < t.rows; i++)
	{
		for (int j = 0; j < t.cols; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	free(arr);
}

void main()
{
	Sparse_Matix SM = Make_Arr();
	Sparse_Matix SM_Trans = TransForm_Arr(SM);
	PrintTransArr(SM_Trans);
	printf("완성");
	free(SM.data);
	free(SM_Trans.data);
	
}



