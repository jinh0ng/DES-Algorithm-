//#include "des.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)
//학번_이름
char SUBMISSION_INFO[256] = "2020350218_홍예진";

//Initial Permutation table
int IP[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
                60, 52, 44, 36, 28, 20, 12, 4,
                62, 54, 46, 38, 30, 22, 14, 6,
                64, 56, 48, 40, 32, 24, 16, 8,
                57, 49, 41, 33, 25, 17, 9, 1,
                59, 51, 43, 35, 27, 19, 11, 3,
                61, 53, 45, 37, 29, 21, 13, 5,
                63, 55, 47, 39, 31, 23, 15, 7 };
//Expansion D-box Table
int ED[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
              6, 7, 8, 9, 8, 9, 10, 11,
              12, 13, 12, 13, 14, 15, 16, 17,
              16, 17, 18, 19, 20, 21, 20, 21,
              22, 23, 24, 25, 24, 25, 26, 27,
              28, 29, 28, 29, 30, 31, 32, 1 };
//S- BOX table(S1~S8)
int s_box_table[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                     0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                     4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                     15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
                   { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                     3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                     0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                     13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },

                   { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                     13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                     13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                     1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
                   { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                     13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                     10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                     3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
                   { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                     14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                     4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                     11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
                   { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                     10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                     9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                     4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
                   { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                     13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                     1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                     6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
                   { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                     1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                     7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                     2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };
// p_box Table
int p_box_table[32] = { 16, 7, 20, 21,
                29, 12, 28, 17,
                1, 15, 23, 26,
                5, 18, 31, 10,
                2, 8, 24, 14,
                32, 27, 3, 9,
                19, 13, 30, 6,
                22, 11, 4, 25 };
// Final Permutation Table
int FP[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
               39, 7, 47, 15, 55, 23, 63, 31,
               38, 6, 46, 14, 54, 22, 62, 30,
               37, 5, 45, 13, 53, 21, 61, 29,
               36, 4, 44, 12, 52, 20, 60, 28,
               35, 3, 43, 11, 51, 19, 59, 27,
               34, 2, 42, 10, 50, 18, 58, 26,
               33, 1, 41, 9, 49, 17, 57, 25 };
//16진수를 2진수로 변환 param : 16진수 string                             
char* hex2bin(const char s[])
{
    char* str;
    str = (char*)malloc(64);
    str[0] = '\0';


    for (int i = 0; i < strlen(s); i++)
    {

        switch (s[i])
        {
        case '0':
            strcat(str, "0000");
            break;
        case '1':
            strcat(str, "0001");
            break;
        case '2':
            strcat(str, "0010");
            break;
        case '3':
            strcat(str, "0011");
            break;
        case '4':
            strcat(str, "0100");
            break;
        case '5':
            strcat(str, "0101");
            break;
        case '6':
            strcat(str, "0110");
            break;
        case '7':
            strcat(str, "0111");
            break;
        case '8':
            strcat(str, "1000");
            break;
        case '9':
            strcat(str, "1001");
            break;
        case 'a':
        case 'A':
            strcat(str, "1010");
            break;
        case 'b':
        case 'B':
            strcat(str, "1011");
            break;
        case 'c':
        case 'C':
            strcat(str, "1100");
            break;
        case 'd':
        case 'D':
            strcat(str, "1101");
            break;
        case 'e':
        case 'E':
            strcat(str, "1110");
            break;
        case 'f':
        case 'F':
            strcat(str, "1111");
            break;
        default:
            printf("Invalid hexadecimal input.");
        }
    }
    return str;
}
//2진수를 16진수로 변환 param : 2진수 string 
char* bin2hex(char s[]) {
    char* hexstr;
    hexstr = (char*)malloc(64);
    hexstr[0] = '\0';


    //char hexstr[strlen(s)];
    int hexnum;
    char four[4];
    int i, j;
    for (i = 0; i < strlen(s) / 4; ++i)
    {
        hexnum = 0;

        strncpy(four, s + (i * 4), 4);
        for (j = 0; j < 4; ++j)
            hexnum += (four[j] - '0') << (3 - j);

        sprintf(hexstr + i, "%X", hexnum);
    }
    return hexstr;
}
//해당 talble (arr[]) 을 n bit만큼 k를 치환 
char* permute(const char k[], int arr[], int n)
{
    char* str;
    str = (char*)malloc(n + 2);
    str[0] = '\0';
    memset(str, 0, n + 2);
    for (int i = 0; i < n; i++) {
        str[i] = k[arr[i] - 1];
    }
    return str;
}
//string 잘라내기 param: input 자르고자하는 string, i_begin 시작점, i_end 종료점  
char* substring(const char* input, int i_begin, int i_end)
{
    int cnt = 0;
    int size = (i_end - i_begin) + 2;
    char* str = (char*)malloc(size);

    memset(str, 0, size);

    for (int i = i_begin; i <= i_end; i++)
    {
        str[cnt] = input[i];
        cnt++;
    }
    return str;
}
//xor 함수 param: a 와 b를 xor연산  
char* xor_(const char* a, char* b)
{
    char* str;
    str = (char*)malloc(strlen(a) + 2);
    str[0] = '\0';
    memset(str, 0, strlen(a) + 2);

    for (int i = 0; i < strlen(a); i++) {
        if (a[i] == b[i]) {
            strcat(str, "0");
        }
        else {
            strcat(str, "1");
        }
    }
    return str;
}
//주어진 s_box 표를 찾아 해독  
char* cal_s_box(char* x) {
    char* str;
    str = (char*)malloc(32 + 2);
    str[0] = '\0';
    memset(str, 0, 32 + 2);
    int cnt = 0;
    for (int i = 0; i < 8; i++) {
        int r1 = x[i * 6] - '0';
        int r2 = x[i * 6 + 5] - '0';
        int row = 2 * r1 + r2;
        int c1 = x[i * 6 + 1] - '0';
        int c2 = x[i * 6 + 2] - '0';
        int c3 = x[i * 6 + 3] - '0';
        int c4 = x[i * 6 + 4] - '0';
        //int col = 8 * int(x[i * 6 + 1] - '0') + 4 * int(x[i * 6 + 2] - '0') + 2 * int(x[i * 6 + 3] - '0') + int(x[i * 6 + 4] - '0');
        int col = 8 * c1 + 4 * c2 + 2 * c3 + c4;
        int val = s_box_table[i][row][col];
        char v1 = val / 8 + '0';
        //str[cnt++] = char(val / 8 + '0');
        str[cnt++] = v1;
        val = val % 8;
        char v2 = val / 4 + '0';
        //str[cnt++] = char(val / 4 + '0');
        str[cnt++] = v2;
        val = val % 4;
        char v3 = val / 2 + '0';
        //str[cnt++] = char(val / 2 + '0');
        str[cnt++] = v3;
        val = val % 2;
        char v4 = val + '0';
        //str[cnt++] = char(val + '0');
        str[cnt++] = v4;
    }
    return str;
}
// str1과 str2를 스왑  
void swap(char** str1_ptr, char** str2_ptr)
{
    char* temp = *str1_ptr;
    *str1_ptr = *str2_ptr;
    *str2_ptr = temp;
}

char* DES_enc(const char* P)
{
    const char* key;
    //입력받은 16진수를 2진수로 변환  
    P = hex2bin(P);
    //입력받은 64bit의 평문을 IP table을 거친다.
    P = permute(P, IP, 64);

    // 32bit씩 왼쪽과 오른쪽으로 나눈다.
    char* left = substring(P, 0, 31);
    char* right = substring(P, 32, 63);

    for (int i = 0; i < 16; i++) { //1~16라운드 반복

         //오른쪽32-bit를 48bit로 확장
        char* right_expanded = permute(right, ED, 48);

        //0~15라운드이므로 i가 짝수일 때 홀수라운드, i가 홀수일 때 짝수라운드이다.
        if (i % 2 == 0)key = "000000000000"; //홀수라운드
        else key = "FFFFFFFFFFFF";//짝수라운드

        key = hex2bin(key);

        //확장해 얻은 48-bit와 키를 XOR-> 48-bit를 얻는다.
        char* x = xor_(key, right_expanded);
        //printf("xor_x: %s\n",x);

        //위에서 얻은 48-bit를 S-box table을 거쳐 다시 32-bit로 되돌린다.      
        char* op = cal_s_box(x);
        //printf("op: %s\n",op);

        // S-box를 거쳐 나온 32-bit를 p-box table을 거친다.
        op = permute(op, p_box_table, 32);
        //printf("op: %s\n",op);

        // 위에서 나온것과 처음에 나눈 왼쪽 32-bit를 xor하면 다음 라운드의 오른쪽이 된다.
        left = xor_(op, left);
        //printf("left: %s\n",left);

        // 다음 라운드의 왼쪽은 이전 라운드의 오른쪽 32-bit가 그대로 들어간다.
        if (i != 15) {
            swap(&left, &right);
        }
        //printf("left: %s\n",left);
    }
    // 합치기  
    char* com;
    com = (char*)malloc(64 + 2);
    com[0] = '\0';
    memset(com, 0, 64 + 2);
    strcat(com, left);
    strcat(com, right);
    //printf("com: %s\n",com);

    // 지금까지 과정이 한 라운드인데 이를 16번 반복한다. 
    //단 16번째 라운드에서는 마지막에FP table을 거친다.
    char* cipher = bin2hex(permute(com, FP, 64));
    //printf("code: %s\n",cipher);

    char* str;
    str = (char*)malloc(64 + 2);
    str[0] = '\0';
    memset(str, 0, 64 + 2);
    strcpy(str, cipher);

    return str;
}

char* DES_dec(const char* C)
{
    const char* key;
    //입력받은 16진수를 2진수로 변환  
    C = hex2bin(C);
    //입력받은 64bit의 평문을 IP(initial permutation)라는 table을 거친 뒤
    C = permute(C, IP, 64);

    char* left = substring(C, 0, 31);
    char* right = substring(C, 32, 63);

    for (int i = 0; i < 16; i++) { //DES_enc 함수와 마찬가지로 16라운드 반복

         //오른쪽32-bit를 48bit로 확장
        char* right_expanded = permute(right, ED, 48);

        if (i % 2 == 1)key = "000000000000";
        else key = "FFFFFFFFFFFF";

        key = hex2bin(key);

        //위에서 얻은 48-bit와  키를 XOR-> 48-bit의 출력을 얻는다.
        char* x = xor_(key, right_expanded);
        //printf("xor_x: %s\n",x);

        //4. 위에서 얻은 48-bit를 S-box table을 거쳐 다시 32-bit로      
        char* op = cal_s_box(x);
        //printf("op: %s\n",op);

        //S-box를 거쳐 나온 32-bit를 p-box table을 거쳐 뒤섞는다.
        op = permute(op, p_box_table, 32);
        //printf("op: %s\n",op);

        // 위에서 나온것과 처음에 나눈 왼쪽 32-bit를 xor하면 다음 라운드의 오른쪽
        left = xor_(op, left);
        //printf("left: %s\n",left);

        // 다음 라운드의 왼쪽은 이전 라운드의 오른쪽 32-bit가 그대로 들어감.
        if (i != 15) {
            swap(&left, &right);
        }
        //printf("left: %s\n",left);
    }
    // 합치기  
    char* com;
    com = (char*)malloc(64 + 2);
    com[0] = '\0';
    memset(com, 0, 64 + 2);
    strcat(com, left);
    strcat(com, right);
    //printf("com: %s\n",com);

    // 지금까지의 과정이 한 라운드인데 이를 16번 반복. 
    //16번째 라운드에서는 마지막에FP table을 거친다.
    char* cipher = bin2hex(permute(com, FP, 64));
    //printf("code: %s\n",cipher);

    char* str;
    str = (char*)malloc(64 + 2);
    str[0] = '\0';
    memset(str, 0, 64 + 2);
    strcpy(str, cipher);

    return str;
}

int main() {
    const char* P = "1111111111111111";//P:평문
    printf("입력평문: %s\n", P)
        ;
    char* p = DES_enc(P); //p: 암호화
    printf("암호: %s\n", p);

    char* d = DES_dec(p);//d: 복호화
    printf("복호화: %s\n", d);

    return 0;
}