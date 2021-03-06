#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 6031)
#endif

#include "functions.h"
#include "utility.h"

int main()
{
    FILE* f;
    f = fopen("file.txt", "r+");
    if (!f) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    fclose(f);
    int choice = menuInOut();
    while (choice != 5) {
        switch (choice) {
            case(1): {
                if (structWriteInFile(f))
                    return EXIT_FAILURE;
                break;
            }
            case(2): {
                if (filePrint(f))
                    return EXIT_FAILURE;
                printf_s("\nPress any key to proceed...");
                _getch();
                break;
            }
            case(3): {
                f = fopen("file.txt", "r+");
                if (!f) {
                    perror("File opening failed");
                    return EXIT_FAILURE;
                }
                int sortChoice = fieldToSortChoose();
                switch (sortChoice) {
                case 1: {
                    sortFile(f, compareByName);
                    break;
                }
                case 2: {
                    sortFile(f, compareByDeveloper);
                    break;
                }
                case 3: {
                    sortFile(f, compareByPublisher);
                    break;
                }
                case 4: {
                    sortFile(f, compareByRating);
                    break;
                }
                }
                filePrint(f);
                printf_s("\nPress any key to proceed...");
                _getch();
                fclose(f);
                break;
            }
            case(4): {
                if (filePrint(f))
                    return EXIT_FAILURE;
                if (removeElementFromFile(f))
                    return EXIT_FAILURE;
                if (filePrint(f))
                    return EXIT_FAILURE;
                break;
            }
        }
        choice = menuInOut();
    };
    return EXIT_SUCCESS;
}

/*
?????????? 11.2.
?????????????????? ???????????? ?????????? ???????? ?? ???????????????????? ???????????? ????????????????: 
1 - ???????????????? ?? ?????????? ?????????? ??????????/????????????/?????????? 
2 - ?????????????? ??????????/????????????/???????????? ???? ?????????? 
3 - ?????????????????????????? ??????????/????????????/???????????? (???? ?????????????????????? ???? ???????????? ???? ??????????) 
4 - ?????????????? ??????????/????????????/?????????? 
5 - ?????????? 

?????? ?????????????? ???????????????? ??????????????????/?????????????????? ???????? ?? ???????????????????????? ??????????????. 

????????????????: 
1 - Book. ???????????????? ???? ????????????, ???????????????????? ???? ?????????? 
2 - Music. ???????????????? ???? ??????????????????????, ???????????????????? ???? ???????????????? 
3 - Cinema. ???????????????? ???? ??????????????????, ???????????????????? ???? ????????????????
*/