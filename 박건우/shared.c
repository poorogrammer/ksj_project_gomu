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
        return 0; // 디렉토리면 0 반환
    else
        return 1; // 그밖의 경우는 "존재하는 파일"이기에 1 반환

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

        check = isFileOrDir();    //파일인지 디렉토리 인지 식별

        if (check == 0 && fd.name[0] != '.')
        {
            FileSearch(file_pt);    //하위 디렉토리 검색 재귀함수
        }
        else if (check == 1 && fd.size != 0 && fd.name[0] != '.')
        {
            printf("파일명 : %s, 크기:%d\n", file_pt, fd.size);
        }
    }
    _findclose(handle);
}

int main()
{
    char file_path[_MAX_PATH] = "c:";    //C:\ 경로 탐색

    FileSearch(file_path);

    return 0;
}

// 식별
/*
#pragma warning ( disable : 4996 )
#include <stdio.h>
#include <io.h>

int isFileOrDir(char* s);

int main(void) {
    char* filename = "C:\\test";

    int result = isFileOrDir(filename);

    if (result == 1)
        puts("파일입니다.");

    else if (result == 0)
        puts("디렉토리입니다.");
    else    //result == -1
        puts("그런 파일 또는 디렉토리는 없습니다.");

    return 0;
}

int isFileOrDir(char* s) {
    _finddatai64_t c_file;
    intptr_t hFile;
    int result;


    if ((hFile = _findfirsti64(s, &c_file)) == -1L)
        result = -1; // 파일 또는 디렉토리가 없으면 -1 반환
    else
        if (c_file.attrib & _A_SUBDIR)
            result = 0; // 디렉토리면 0 반환
        else
            result = 1; // 그밖의 경우는 "존재하는 파일"이기에 1 반환

    _findclose(hFile);
    return result;
}


출처: https://gyeongje.tistory.com/259?category=925558 [Gyeongje's Blog]
*/