#include<stdio.h>
int buf0;                   //8비트
int buf1;                   //앞자리비트
int buf2;                   //뒷자리비트
int buf3[1024];             //4b->5b | 5b->4b
int buf4[1280];             //인코딩으로 늘어난 비트
/////인코딩함수//////////////////
void readfile_EN();         //Sample.bin파일 읽어오기
int Change4b5b(int a);      //4b->5b변환함수
void Encoding(int n);       //인코딩함수 및 EncodingSample.bin에 저장
void Encoding2();
/////디코딩함수//////////////////
void readfile_DE();         //EncodingSample.bin파일 읽어오기
int Change5b4b(int a);      //5b->4b변환
void Decoding();            //디코딩함수 및 DecodingSample.bin에 저장

void Check(int n);          //인코딩과 디코딩이 잘 되었는지 확인하는 함수
/////메인함수//////////////////////////////////////////////////////////////////
void main()
{
    //인코딩
    readfile_EN();
    Encoding2();
    Check(1);
    //디코딩
    readfile_DE();
    Decoding();
    Check(0);
}

///////인코딩함수//////////////////////////////////////////////////////////////

void readfile_EN()
{
    //bin파일 읽어오기
    int a;
    FILE* fp;           //bin 파일을 이진+읽기모드로 열기
    if ((fp = fopen("Sample.bin", "rb")) == NULL)                                 //정상적으로 파일이 열리는지 검사
    {
        printf("Sample파일 열기 에러");
    }

    //bin파일에서 8비트씩 데이터를 받아 저장한다
    for ( a = 0; a < 1024; a++)
    {
        buf0 = fgetc(fp);       //파일에서 읽어온 8비트 데이터를 buf0에 저장
        Encoding(a);            //바로 인코딩
    }

    //for (int j = 0; j < 1024; j++) printf("%3x", buf3[j]);
    fclose(fp);  
}
int Change4b5b(int a)
{
    //4비트를 5비트로 변환하는 함수
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
    buf1 = ((buf0 & 0xf0) >> 4);            //앞의 4비트
    buf2 = (buf0 & 0x0f);                   //뒤의 4비트
    buf3[n] = (Change4b5b(buf1) << 5) | Change4b5b(buf2);       //변환된 5비트+5비트
}
void Encoding2()
{
    FILE* f;
    if ((f = fopen("EncodingSample.bin", "wb")) == NULL)  //파일이 제대로 만들어졌는지 확인
    {
        printf("파일 열기 에러");
    }

    for (int i = 0; i < 256; i++)
    {
        //변환된 10비트 데이터를 잘리지 않도록 8비트 단위로 나눠서 저장
        //10비트들을 8비트 단위로 나누었기 때문에 1024개에서 1280개가 됨
        //바로 이진파일에 저장
        fputc((buf3[4 * i]), f);
        fputc(((buf3[4 * i] >>8) | (buf3[4 * i + 1] <<2)), f);
        fputc(((buf3[4 * i + 1] >>6) | (buf3[4 * i + 2] <<4)), f);
        fputc(((buf3[4 * i + 2] >>4) | (buf3[4 * i + 3] <<6)), f);
        fputc((buf3[4 * i + 3] >>2), f);
    }

    fclose(f);
}
///////디코딩함수////////////////////////////////////////////////////////////
void readfile_DE()
{
    //bin파일 읽어오기
    int a;
    FILE* fp;           //bin 파일을 이진+읽기모드로 열기
    if ((fp = fopen("EncodingSample.bin", "rb")) == NULL)                                 //정상적으로 파일이 열리는지 검사
    {
        printf("EncodingSample파일 열기 에러");
    }

    //bin파일에서 8비트씩 데이터를 받아 저장한다
    for (a = 0; a < 1280; a++)
    {
        buf4[a] = fgetc(fp);            //파일에서 읽어온 8비트 데이터 1280개를 배열에 저장
    }
    fclose(fp);
}
void Decoding()
{
    for (int i = 0; i < 256; i++)
    {
        //EncodingSample.bin에서 읽어온 8비트들을 10비트 단위로 자르기
        buf3[4 * i] = (buf4[5 * i]) | (buf4[5 * i + 1] <<8);
        buf3[4 * i + 1] = (buf4[5 * i + 1] >>2) | (buf4[5 * i + 2] <<6);
        buf3[4 * i + 2] = (buf4[5 * i + 2] >>4) | (buf4[5 * i + 3] <<4);
        buf3[4 * i + 3] = (buf4[5 * i + 3] >>6) | (buf4[5 * i + 4] <<2);
    }

    FILE* f;
    if ((f = fopen("DecodingSample.bin", "wb")) == NULL)  //파일이 제대로 만들어졌는지 확인
    {
        printf("파일 열기 에러");
    }
    for (int i = 0; i < 1024; i++)
    {
        buf1 = ((buf3[i] & 0x3e0) >> 5);            //앞 5비트
        buf2 = (buf3[i] & 0x1f);                    //뒤 5비트
        buf0 = (Change5b4b(buf1) << 4) | Change5b4b(buf2);      //변환된 4비트+4비트
        fputc(buf0, f);         //디코딩한 데이터를 DecodingSmaple.bin에 입력
    }
    fclose(f);
}
int Change5b4b(int a)
{
    //5비트를 4비트로 변환하는 함수
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
        FILE* fp;           //bin 파일을 이진+읽기모드로 열기
        if ((fp = fopen("Sample.bin", "rb")) == NULL)                                 //정상적으로 파일이 열리는지 검사
        {
            printf("Sample파일 열기 에러");
        }
        FILE* f;           //bin 파일을 이진+읽기모드로 열기
        if ((f = fopen("DecodingSample.bin", "rb")) == NULL)                                 //정상적으로 파일이 열리는지 검사
        {
            printf("DeSample파일 열기 에러");
        }

        for (int i = 0; i < 1024; i++)
            if (fgetc(f) == fgetc(fp))
                count_DE++;
        if (count_DE == 1024)
            printf("디코딩성공!\n");
        else
            printf("디코딩 실패!!!!!\n");
        fclose(f);
        fclose(fp);
    }
    
    if (n == 1)
    {
        FILE* p;           //bin 파일을 이진+읽기모드로 열기
        if ((p = fopen("EncodingSample.bin", "rb")) == NULL)                                 //정상적으로 파일이 열리는지 검사
        {
            printf("EncodingSample파일 열기 에러");
        }

        while (fgetc(p) != EOF)
            count_EN++;
        if (count_EN == 1280)
            printf("인코딩 성공!\n");
        else
            printf("인코딩 실패!!!!!\n");

        fclose(p);
    }
}
