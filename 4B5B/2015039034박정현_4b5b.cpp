#include<stdio.h>
int buf0;                   //8��Ʈ
int buf1;                   //���ڸ���Ʈ
int buf2;                   //���ڸ���Ʈ
int buf3[1024];             //4b->5b | 5b->4b
int buf4[1280];             //���ڵ����� �þ ��Ʈ
/////���ڵ��Լ�//////////////////
void readfile_EN();         //Sample.bin���� �о����
int Change4b5b(int a);      //4b->5b��ȯ�Լ�
void Encoding(int n);       //���ڵ��Լ� �� EncodingSample.bin�� ����
void Encoding2();
/////���ڵ��Լ�//////////////////
void readfile_DE();         //EncodingSample.bin���� �о����
int Change5b4b(int a);      //5b->4b��ȯ
void Decoding();            //���ڵ��Լ� �� DecodingSample.bin�� ����

void Check(int n);          //���ڵ��� ���ڵ��� �� �Ǿ����� Ȯ���ϴ� �Լ�
/////�����Լ�//////////////////////////////////////////////////////////////////
void main()
{
    //���ڵ�
    readfile_EN();
    Encoding2();
    Check(1);
    //���ڵ�
    readfile_DE();
    Decoding();
    Check(0);
}

///////���ڵ��Լ�//////////////////////////////////////////////////////////////

void readfile_EN()
{
    //bin���� �о����
    int a;
    FILE* fp;           //bin ������ ����+�б���� ����
    if ((fp = fopen("Sample.bin", "rb")) == NULL)                                 //���������� ������ �������� �˻�
    {
        printf("Sample���� ���� ����");
    }

    //bin���Ͽ��� 8��Ʈ�� �����͸� �޾� �����Ѵ�
    for ( a = 0; a < 1024; a++)
    {
        buf0 = fgetc(fp);       //���Ͽ��� �о�� 8��Ʈ �����͸� buf0�� ����
        Encoding(a);            //�ٷ� ���ڵ�
    }

    //for (int j = 0; j < 1024; j++) printf("%3x", buf3[j]);
    fclose(fp);  
}
int Change4b5b(int a)
{
    //4��Ʈ�� 5��Ʈ�� ��ȯ�ϴ� �Լ�
    switch (a)
    {
        //4b->5b
    case 0x0:
        a = 0x1e;
        break;
    case 0x1:
        a = 0x09;
        break;
    case 0x2:
        a = 0x14;
        break;
    case 0x3:
        a = 0x15;
        break;
    case 0x4:
        a = 0x0a;
        break;
    case 0x5:
        a = 0x0b;
        break;
    case 0x6:
        a = 0x0e;
        break;
    case 0x7:
        a = 0x0f;
        break;
    case 0x8:
        a = 0x12;
        break;
    case 0x9:
        a = 0x13;
        break;
    case 0xa:
        a = 0x16;
        break;
    case 0xb:
        a = 0x17;
        break;
    case 0xc:
        a = 0x1a;
        break;
    case 0xd:
        a = 0x1b;
        break;
    case 0xe:
        a = 0x1c;
        break;
    case 0xf:
        a = 0x1d;
        break;
    }
    return a;
}
void Encoding(int n)
{
    buf1 = ((buf0 & 0xf0) >> 4);            //���� 4��Ʈ
    buf2 = (buf0 & 0x0f);                   //���� 4��Ʈ
    buf3[n] = (Change4b5b(buf1) << 5) | Change4b5b(buf2);       //��ȯ�� 5��Ʈ+5��Ʈ
}
void Encoding2()
{
    FILE* f;
    if ((f = fopen("EncodingSample.bin", "wb")) == NULL)  //������ ����� ����������� Ȯ��
    {
        printf("���� ���� ����");
    }

    for (int i = 0; i < 256; i++)
    {
        //��ȯ�� 10��Ʈ �����͸� �߸��� �ʵ��� 8��Ʈ ������ ������ ����
        //10��Ʈ���� 8��Ʈ ������ �������� ������ 1024������ 1280���� ��
        //�ٷ� �������Ͽ� ����
        fputc((buf3[4 * i]), f);
        fputc(((buf3[4 * i] >>8) | (buf3[4 * i + 1] <<2)), f);
        fputc(((buf3[4 * i + 1] >>6) | (buf3[4 * i + 2] <<4)), f);
        fputc(((buf3[4 * i + 2] >>4) | (buf3[4 * i + 3] <<6)), f);
        fputc((buf3[4 * i + 3] >>2), f);
    }

    fclose(f);
}
///////���ڵ��Լ�////////////////////////////////////////////////////////////
void readfile_DE()
{
    //bin���� �о����
    int a;
    FILE* fp;           //bin ������ ����+�б���� ����
    if ((fp = fopen("EncodingSample.bin", "rb")) == NULL)                                 //���������� ������ �������� �˻�
    {
        printf("EncodingSample���� ���� ����");
    }

    //bin���Ͽ��� 8��Ʈ�� �����͸� �޾� �����Ѵ�
    for (a = 0; a < 1280; a++)
    {
        buf4[a] = fgetc(fp);            //���Ͽ��� �о�� 8��Ʈ ������ 1280���� �迭�� ����
    }
    fclose(fp);
}
void Decoding()
{
    for (int i = 0; i < 256; i++)
    {
        //EncodingSample.bin���� �о�� 8��Ʈ���� 10��Ʈ ������ �ڸ���
        buf3[4 * i] = (buf4[5 * i]) | (buf4[5 * i + 1] <<8);
        buf3[4 * i + 1] = (buf4[5 * i + 1] >>2) | (buf4[5 * i + 2] <<6);
        buf3[4 * i + 2] = (buf4[5 * i + 2] >>4) | (buf4[5 * i + 3] <<4);
        buf3[4 * i + 3] = (buf4[5 * i + 3] >>6) | (buf4[5 * i + 4] <<2);
    }

    FILE* f;
    if ((f = fopen("DecodingSample.bin", "wb")) == NULL)  //������ ����� ����������� Ȯ��
    {
        printf("���� ���� ����");
    }
    for (int i = 0; i < 1024; i++)
    {
        buf1 = ((buf3[i] & 0x3e0) >> 5);            //�� 5��Ʈ
        buf2 = (buf3[i] & 0x1f);                    //�� 5��Ʈ
        buf0 = (Change5b4b(buf1) << 4) | Change5b4b(buf2);      //��ȯ�� 4��Ʈ+4��Ʈ
        fputc(buf0, f);         //���ڵ��� �����͸� DecodingSmaple.bin�� �Է�
    }
    fclose(f);
}
int Change5b4b(int a)
{
    //5��Ʈ�� 4��Ʈ�� ��ȯ�ϴ� �Լ�
    switch (a)
    {
    case 0x1e:
        //11110
        a = 0x0;
        break;
    case 0x09:
        //01001
        a = 0x1;
        break;
    case 0x14:
        //10100
        a = 0x2;
        break;
    case 0x15:
        //10101
        a = 0x3;
        break;
    case 0x0a:
        //01010
        a = 0x4;
        break;
    case 0x0b:
        //01011
        a = 0x5;
        break;
    case 0x0e:
        //01110
        a = 0x6;
        break;
    case 0x0f:
        //01111
        a = 0x7;
        break;
    case 0x12:
        //10010
        a = 0x8;
        break;
    case 0x13:
        //10011
        a = 0x9;
        break;
    case 0x16:
        //10110
        a = 0xa;
        break;
    case 0x17:
        //10111
        a = 0xb;
        break;
    case 0x1a:
        //11010
        a = 0xc;
        break;
    case 0x1b:
        //11011
        a = 0xd;
        break;
    case 0x1c:
        //11100
        a = 0xe;
        break;
    case 0x1d:
        //11101
        a = 0xf;
        break;
    }
    return a;
}

void Check(int n)
{
    int count_EN=0;
    int count_DE=0;
    if (n == 0)
    {
        FILE* fp;           //bin ������ ����+�б���� ����
        if ((fp = fopen("Sample.bin", "rb")) == NULL)                                 //���������� ������ �������� �˻�
        {
            printf("Sample���� ���� ����");
        }
        FILE* f;           //bin ������ ����+�б���� ����
        if ((f = fopen("DecodingSample.bin", "rb")) == NULL)                                 //���������� ������ �������� �˻�
        {
            printf("DeSample���� ���� ����");
        }

        for (int i = 0; i < 1024; i++)
            if (fgetc(f) == fgetc(fp))
                count_DE++;
        if (count_DE == 1024)
            printf("���ڵ�����!\n");
        else
            printf("���ڵ� ����!!!!!\n");
        fclose(f);
        fclose(fp);
    }
    
    if (n == 1)
    {
        FILE* p;           //bin ������ ����+�б���� ����
        if ((p = fopen("EncodingSample.bin", "rb")) == NULL)                                 //���������� ������ �������� �˻�
        {
            printf("EncodingSample���� ���� ����");
        }

        while (fgetc(p) != EOF)
            count_EN++;
        if (count_EN == 1280)
            printf("���ڵ� ����!\n");
        else
            printf("���ڵ� ����!!!!!\n");

        fclose(p);
    }
}
