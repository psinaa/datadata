#define _CRT_SECURE_NO_DEPRECATE
#define CountScore 21
#define LeftT 1
#define RightT 11
#define LeftA 11
#define RightA 21
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <stdbool.h>

////Sorting functions
void sort(int Number, int UserScore[][CountScore], int Left, int Right);
int** rating(int Number, int UserScore[][CountScore]);
char* search_best(int Number, char* UserList[], int UserScore[][CountScore]);
char* search_worst(int Number, char* UserList[], int UserScore[][CountScore]);
char* search_mediana(int Number, char* UserList[], int UserScore[][CountScore]);
char* search_mesto(int Number, char* UserList[], int UserScore[][CountScore]);
char* search(int Number, char* UserList[], int UserScore[][CountScore]);
//
//
////File functions
int writefile(int Number, char* UserList[], int UserScore[][CountScore]);
int Load(int* Number, char* UserList[], int UserScore[][CountScore]);
//
////User functions
void PrintUser(int id, char* UserList[], int UserScore[][CountScore], bool);
void CreateUser(int* Number, char* UserList[], int UserScore[][CountScore]);

int search_index_score(int id, int Number, int UserScore[][CountScore]);

//Sub functions
char* concat(char* s1, char* s2);//Сложение строк
int SumElemArr(int array[][CountScore], int left, int right); // Суммирование периода в массиве
int* SwapElement(int UserScore[][CountScore], int array[], int id);
//
//commandline interface
void tabl();


int main() {
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);         // !!!
    SetConsoleOutputCP(1251);   // !!!
    int sum = 0, Number,UserID=0, n, d = 1, answercaseA = 0, answercaseT = 0, answercaseAT = 0;
    char* UserList[999];
    int UserScore[999][CountScore]; // 1 ID, технические первые 10, артистичные вторвые 10
    Load(&Number, UserList, UserScore);
    char id = Number;
    while (d != 0) {
        printf("База данных\n");
        printf("1)Создать пользователя\n");
        printf("2)Посмотреть таблицу\n");
        printf("3)Сумма за А\n");
        printf("4)Сумма за Т\n");
        printf("5)Сумма за всё\n");
        printf("6)Сортировка по А\n");
        printf("7)Сортировка по Т\n");
        printf("8)Рейтинг\n");
        printf("9)Поиск\n");
        printf("0)Выход\n");
        scanf("%i", &n);
        switch (n) {
        case 1:
            CreateUser(&Number, UserList, UserScore);
            writefile(Number, UserList, UserScore);
            break;
        case 2:
            tabl();
            for (int i = 0; i < Number; i++)
                PrintUser(i, UserList, UserScore, FALSE);
            break;
        case 3:
            printf("Выбрать пользователя по id - 1 Посмотреть всех - 2\n");
            scanf("%d", &answercaseA);
            switch (answercaseA) {
            case 1:
                printf("Введите ID пользователя");
                scanf("%d", &UserID);
                sum = SumElemArr(UserScore[search_index_score(UserID, Number, UserScore)], LeftA, RightA);
                printf("Сумма за A=%5i|%20s|\n", sum, UserList[UserID]);
                break;
            case 2:
                for (int i = 0; i < Number; i++) {
                    sum = SumElemArr(UserScore[i], LeftA, RightA);
                    printf("Сумма за A=%5i|%20s|\n", sum, UserList[UserScore[i][0]]);
                }
                break;
            default:
                break;
            }
            break;
        case 4:
            printf("Выбрать пользователя по id - 1 Посмотреть всех - 2\n");
            scanf("%d", &answercaseT);
            switch (answercaseT) {
            case 1:
                printf("Введите ID пользователя");
                scanf("%d", &UserID);
                sum = SumElemArr(UserScore[search_index_score(UserID, Number, UserScore)], LeftT, RightT);
                printf("Сумма за T=%5i|%20s|\n", sum, UserList[UserID]);
                break;
            case 2:
                for (int i = 0; i < Number; i++) {
                    sum = SumElemArr(UserScore[i], LeftT, RightT);
                    printf("Сумма за T=%5i|%20s|\n", sum, UserList[UserScore[i][0]]);
                }
                break;
            default:
                break;
            }
            break;
        case 5:
            printf("Выбрать пользователя по id - 1 Посмотреть всех - 2\n");
            scanf("%d", &answercaseAT);
            switch (answercaseAT) {
            case 1:
                printf("Введите ID пользователя");
                scanf("%d", &UserID);
                sum = SumElemArr(UserScore[search_index_score(UserID, Number, UserScore)], LeftT, RightA);
                printf("Сумма за A и T=%5i|%20s|\n", sum, UserList[UserID]);
                break;
            case 2:
                for (int i = 0; i < Number; i++) {
                    sum = SumElemArr(UserScore[i], LeftT, RightA);
                    printf("Сумма за A и T=%5i|%20s|\n", sum, UserList[UserScore[i][0]]);
                }
                break;
            default:
                break;
            }
            break;
        case 6:
            sort(Number, UserScore, LeftA, RightA);
            break;
        case 7:
            sort(Number, UserScore, LeftT, RightT);
            break;
        case 8:
            rating(Number, UserScore);
            puts("Фамилия имя          |Сумма очков|   Место  |");
            for (int i = 0; i < Number; i++) {
                int z = i + 1;
                sum = SumElemArr(UserScore[i], LeftT, RightA);
                printf("|%20s|%11d|%10d|\n", UserList[UserScore[i][0]], sum, z);
            }
            break;
        case 9:
            printf("Поиск\n");
            printf("1)По максимумy\n");
            printf("2)По минимуму\n");
            printf("3)По среднему\n");
            printf("4)По месту\n");
            printf("5)По фамилии и имени\n");
            int m, answ = 0;
            char* ret = NULL;
            scanf("%d", &m);
            switch (m) {
            case 1:
                search_best(Number, UserList, UserScore, TRUE);
                break;
            case 2:
                search_worst(Number, UserList, UserScore, TRUE);
                break;
            case 3:
                search_mediana(Number, UserList, UserScore, TRUE);
                break;
            case 4:
                search_mesto(Number, UserList, UserScore, TRUE);
                break;
            case 5:
                search(Number, UserList, UserScore,TRUE);
                break;
            default:
                break;
            }
        case 0:
            exit(1);
            break;
        default:
            break;
        }
    }
}

//Чтение файла
int Load(int* Number, char* UserList[], int UserScore[][CountScore])
{
    FILE* F;

    if ((F = fopen("my.txt", "rt")) == NULL)
    {
        fprintf(stderr, "Невозможно открыть для чтения файл 'my.dta'\n");
        return 0;
    }

    fscanf(F, "%i", &*Number);
    for (int i = 0; i < *Number; i++) {
        char surname[50];
        char name[50];
        char* string3;
        fscanf(F, "%s", &surname);
        fscanf(F, "%s", &name);

        string3 = concat(surname, name);
        UserList[i] = string3;
        UserScore[i][0] = i;
        for (int j = 1; j < CountScore; j++)
        {
            fscanf(F, "%d", &UserScore[i][j]);
        }
    }
    fclose(F);
    int g = *Number;
    return g;
}

void PrintUser(int id, char* UserList[], int UserScore[][CountScore], bool flgheader) {
    if (flgheader)
    {
        tabl();
    }
    for (int i = 1; i < CountScore - 10; i++) {
        int j = i + 10;
        printf(" %d %d    ", UserScore[id][i], UserScore[id][j]);
    }
    printf(" %s ", UserList[UserScore[id][0]]);
    puts("\n");
}

//Создание пользователя
void CreateUser(int* Number, char* UserList[], int UserScore[][CountScore]) {
    char surname[50];
    char name[50];
    char* string3;
    int w,u;

    printf("Введите фамилию\n");
    getchar();
    scanf("%s", &surname);
    printf("Введите имя\n");
    getchar();
    scanf("%s", &name);
    string3 = concat(surname, name);
    UserList[*Number] = string3;
    UserScore[*Number][0] = *Number;
    printf("Выберите пункт\n");
    printf("1)Ввести баллы вручную\n");
    printf("2)Сгенерировать рандомные баллы\n");
    scanf("%d", &w);
    if (w == 1) {
        printf("Введите баллы нового участника\n");
        for (int j = 1; j < CountScore; j++) {
            scanf("%d", &u);
            UserScore[*Number][j] = u;
        }
    }
    if (w==2){
        for (int j = 1; j < CountScore; j++) {
            UserScore[*Number][j] = (rand() % 9) + 1;
        }
    }
    *Number += 1;
}

//Сложение строк
char* concat(char* s1, char* s2) {
    const char* s3 = " ";
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t len3 = strlen(s3);

    char* result = (char*)malloc(len1 + len3 + len2 + 1);
    if (!result) {
        fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }

    memcpy(result, s1, len1);
    memcpy(result + len1, s3, len3);
    memcpy(result + len1 + len3, s2, len2 + 1);
    return result;
}

//Сумма
int SumElemArr(int array[], int left, int right)
{
    int sum = 0;
    for (int i = left; i < right; i++) {
        sum += array[i];
    }
    return sum;
}

int* SwapElement(int UserScore[][CountScore], int array[], int id)
{

    for (int i = 0; i < CountScore; i++)
    {
        UserScore[id][i] = array[i];
    }
    return UserScore[id];
}

//Добавление элеменетов в файл
int writefile(int Number, char* UserList[], int UserScore[][CountScore])
{
    FILE* F;
    if ((F = fopen("my.txt", "w")) == NULL)
    {
        fprintf(stderr, "Невозможно открыть для чтения файл 'fail.dta'\n");
        return 0;
    }

    fprintf(F, "%d\n", Number);

    for (int i = 0; i < Number; i++) {

        int n = 0;
        for (int j = 0; j < Number; j++)
        {
            if (UserScore[j][0] == i) n = j;
        }

        fprintf(F, "%s", UserList[i]);
        for (int k = 1; k < CountScore; k++)
        {
            fprintf(F, "% d", UserScore[n][k]);
        }
        fputs("\n", F);
    }
    fclose(F);
    return Number;
}

//Сортировка пузырьком по артистизму
void sort(int Number, int UserScore[][CountScore], int Left, int Right)
{
    for (int i = 0; i < Number - 1; i++)
    {
        // сравниваем два соседних элемента.
        for (int j = 0; j < Number - i - 1; j++)
        {
            int one = SumElemArr(UserScore[j], Left, Right);
            int two = SumElemArr(UserScore[j + 1], Left, Right);
            if (one < two) {

                int tmp[CountScore];
                for (int k = 0; k < CountScore; k++) tmp[k] = UserScore[j][k];
                int* tmp2 = UserScore[j + 1];
                SwapElement(UserScore, tmp2, j);
                SwapElement(UserScore, tmp, j + 1);
            }
        }
    }
    printf("_____________________________________________________________\nДля просмотра отсортированной таблицы в общем виде нажмите 2|\n_____________________________________________________________\n");
}

//Рейтинг, сорировка пузырьком по всем очкам
int** rating(int Number, int UserScore[][CountScore])
{
    for (int i = 0; i < Number - 1; i++)
    {
        // сравниваем два соседних элемента.
        for (int j = 0; j < Number - i - 1; j++)
        {
            int one = SumElemArr(UserScore[j], 1, 21); //суммируем все очки первого элемента
            int two = SumElemArr(UserScore[j + 1], 1, 21); //суммируем все очки второго элемента
            if (one < two) {

                //замены в массиве очков
                int tmp[CountScore]; //обявление статического массива для временнного хранения очков UserScore[j], не указатель так как при замене элементов в UserScore[j] изменились бы элементы и здесь
                for (int k = 0; k < CountScore; k++) tmp[k] = UserScore[j][k]; // заполнение массива tmp

                int* tmp2 = UserScore[j + 1];  //объявление указателя, чтобы взять значения UserScore[j + 1] для замены UserScore[j]
                SwapElement(UserScore, tmp2, j); //функция SwapElement выполняет UserScore[j] = tmp2 (она же UserScore[j+1]), напрямую это не работало для двумерного массива
                SwapElement(UserScore, tmp, j + 1);//функция SwapElement выполняет UserScore[j+1] = tmp (она же UserScore[j]), напрямую это не работало для двумерного массива
            }
        }
    }
}

char* search_best(int Number, char* UserList[], int UserScore[][CountScore]) {
    char* ret = NULL;
    rating(Number, UserScore);
    PrintUser(0, UserList, UserScore, TRUE);
    ret = UserList[0];
    return ret;
}
char* search_worst(int Number, char* UserList[], int UserScore[][CountScore]) {
    char* ret = NULL;
    rating(Number, UserScore);
    PrintUser(Number - 1, UserList, UserScore, TRUE);
    ret = UserList[Number - 1];
    return ret;
}
char* search_mediana(int Number, char* UserList[], int UserScore[][CountScore]) {
    char* ret = NULL;
    rating(Number, UserScore);
    PrintUser(Number/2, UserList, UserScore, TRUE);
    ret = UserList[Number / 2];
    return ret;
}

char* search_mesto(int Number, char* UserList[], int UserScore[][CountScore]) {
    char* ret = NULL;
    int answ;
    printf("Введите место\n");
    scanf("%d", &answ);
    rating(Number, UserScore);
    PrintUser(answ - 1, UserList, UserScore, TRUE);
    ret = UserList[answ - 1];
    return ret;
}
//Функция поиска по имени и фамилиии
char* search(int Number, char* UserList[], int UserScore[][CountScore]) {
    char surname[50];
    char name[50];
    char* string3;
    char* ret = NULL;
    printf("Введите фамилию\n");
    getchar();
    scanf("%s", surname);

    printf("Введите имя\n");
    getchar();
    scanf("%s", name);

    string3 = concat(surname, name);
    for (int i = 0; i < Number; i++) {
        if (strcmp(UserList[i], string3) == 0) {
            PrintUser(search_index_score(i, Number, UserScore), UserList, UserScore, TRUE);
        }
    }
    ret = string3;
    return ret;
}

//Оформление таблицы
void tabl() {
    puts("\t\t    Таблица результатов по фехтованию");
    puts("\t\t\t\tСудьи\t\t\t\t\t\t");
    puts("\t Бригада судей A\t\t\t Бригада судей B\t\t\t\t\t");
    puts(" 1\t 2\t 3\t 4\t 5\t 1\t 2\t 3\t 4\t 5\t");
    puts(" т а \t т а \t т а \t т а \t т а \t т а \t т а \t т а \t т а \t т а       Участники");
}
int search_index_score(int id, int Number, int UserScore[][CountScore]) {
    int v = 0;
    for (int i = 0; i < Number; i++) {
        if (UserScore[i][0] == id)
            v = i;
    }
    return v;
}