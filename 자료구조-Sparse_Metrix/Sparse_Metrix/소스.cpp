/*0�� �ƴ� ���ҵ鸸 ǥ���ϴ� �ڷᱸ���� Ȱ���� ��ġ��� ���ϱ�*/
#include<stdio.h>
#include<malloc.h>
#include<Windows.h>
#include<time.h>

typedef struct
{
	int row ;		//��
	int col ;		//��
	int value;		//�� ��ġ ������ ��
}element;
typedef struct
{
	element *data;
	int rows;		//���� ����
	int cols;		//���� ����
	int terms;		//���� ����
}Sparse_Matrix ;
Sparse_Matrix SM;
Sparse_Matrix TSM;

void Make_Arr()
{
	int height = 0, width = 0;
	printf("����� ����� �����ϼ���:");
	scanf("%d", &height);
	scanf("%d", &width);

	srand(time(NULL));
	int num;

	SM.data = (element*)malloc(height*width * sizeof(element*));

	int k = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (((num = rand() % 10) % 2) != 0)
			{
				(SM.data + k)->value = num;
				(SM.data + k)->row = i;
				(SM.data + k)->col = j;
				printf("row:%d col:%d ��:%d terms:%d \n", i, j, (SM.data + k)->value, k);
				SM.terms = k++;
			}
		}
	}
	SM.rows = height;
	SM.cols = width;
}

void TransForm_Arr()
{
	TSM.rows = SM.cols;
	TSM.cols = SM.rows;
	TSM.terms = SM.terms;
	TSM.data = (element*)malloc(TSM.terms * sizeof(element*));
	for (int k = 0; k <= SM.terms; k++)
	{
		(TSM.data + k)->value = (SM.data + k)->value;
		(TSM.data + k)->row = (SM.data + k)->col;
		(TSM.data + k)->col = (SM.data + k)->row;
		printf("row:%d col:%d ��:%d terms:%d \n", (TSM.data + k)->row, (TSM.data + k)->col, (SM.data + k)->value, k);
	}
	printf("��ȯ�Ϸ�\n");

	
}


void main()
{
	Make_Arr();
	printf("\n");
	TransForm_Arr();
	printf("�ϼ�");
	//free(SM.data);
	//free(TSM.data);

}



