#pragma warning ( disable : 4996 )
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <Windows.h>

struct _finddata_t fd;

int isFileOrDir()
{
    if (fd.attrib & _A_SUBDIR)
        return 0; // ���丮�� 0 ��ȯ
    else
        return 1; // �׹��� ���� "�����ϴ� ����"�̱⿡ 1 ��ȯ

}

void FileSearch(char file_path[])
{
    intptr_t handle;
    int check = 0;
    char file_path2[_MAX_PATH];

    strcat(file_path, "\\");
    strcpy(file_path2, file_path);
    strcat(file_path, "*");

    if ((handle = _findfirst(file_path, &fd)) == -1)
    {
        printf("No such file or directory\n");
        return;
    }

    while (_findnext(handle, &fd) == 0)
    {
        char file_pt[_MAX_PATH];
        strcpy(file_pt, file_path2);
        strcat(file_pt, fd.name);

        check = isFileOrDir();    //�������� ���丮 ���� �ĺ�

        if (check == 0 && fd.name[0] != '.')
        {
            FileSearch(file_pt);    //���� ���丮 �˻� ����Լ�
        }
        else if (check == 1 && fd.size != 0 && fd.name[0] != '.')
        {
            printf("���ϸ� : %s, ũ��:%d\n", file_pt, fd.size);
        }
    }
    _findclose(handle);
}

int main()
{
    char file_path[_MAX_PATH] = "c:";    //C:\ ��� Ž��

    FileSearch(file_path);

    return 0;
}

// �ĺ�
/*
#pragma warning ( disable : 4996 )
#include <stdio.h>
#include <io.h>

int isFileOrDir(char* s);

int main(void) {
    char* filename = "C:\\test";

    int result = isFileOrDir(filename);

    if (result == 1)
        puts("�����Դϴ�.");

    else if (result == 0)
        puts("���丮�Դϴ�.");
    else    //result == -1
        puts("�׷� ���� �Ǵ� ���丮�� �����ϴ�.");

    return 0;
}

int isFileOrDir(char* s) {
    _finddatai64_t c_file;
    intptr_t hFile;
    int result;


    if ((hFile = _findfirsti64(s, &c_file)) == -1L)
        result = -1; // ���� �Ǵ� ���丮�� ������ -1 ��ȯ
    else
        if (c_file.attrib & _A_SUBDIR)
            result = 0; // ���丮�� 0 ��ȯ
        else
            result = 1; // �׹��� ���� "�����ϴ� ����"�̱⿡ 1 ��ȯ

    _findclose(hFile);
    return result;
}


��ó: https://gyeongje.tistory.com/259?category=925558 [Gyeongje's Blog]
*/