#nclude <stdio.h>
include <string.h>
include <ctype.h> 

define MAX_BOOKS 100
define MAX_LENGTH 100

typedef struct {
    char title[MAX_LENGTH];
    char author[MAX_LENGTH];
    float price;
    int pages;        
    char publisher[MAX_LENGTH];  
    int year;          
    char city[MAX_LENGTH];  
} Book;
int isAuthorValid(const char *author) {
    for (int i = 0; author[i] != '\0'; i++) {
        if (!isalpha(author[i]) && author[i] != ' ' && author[i] != '-') {
            return 0;  // false
        }
    }
    return 1;  // true
}
int isPriceValid(const char *priceStr) {
    int dotCount = 0;  
    for (int i = 0; priceStr[i] != '\0'; i++) {
        if (!isdigit(priceStr[i]) && priceStr[i] != '.') {
            return 0;  
        }
        if (priceStr[i] == '.') {
            dotCount++;
        }
    }
    return dotCount <= 1;
}
float stringToFloat(const char *str) {
    float result = 0.0;
    float fraction = 1.0;
    int isFraction = 0; 
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            isFraction = 1;
            continue;
        }
        if (isdigit(str[i])) {
            if (isFraction) {
                fraction *= 0.1;
                result += (str[i] - '0') * fraction;
            } else {
                result = result * 10.0 + (str[i] - '0');
            }
        }
    }
    return result;
}

void inputBooks(Book books[], int *n) {
    printf("Введите количество книг: ");
    scanf("%d", n);
    getchar(); 

    for (int i = 0; i < *n; i++) {
        printf("Книга %d:\n", i + 1);

       
        printf("  Название: ");
        fgets(books[i].title, MAX_LENGTH, stdin);
        books[i].title[strcspn(books[i].title, "\n")] = '\0';       
        int validAuthor = 0;
        do {
            printf("  Автор: ");
            fgets(books[i].author, MAX_LENGTH, stdin);
            books[i].author[strcspn(books[i].author, "\n")] = '\0';
            if (isAuthorValid(books[i].author)) {
                validAuthor = 1;  // true
            } else {
                printf("Ошибка: автор должен состоять только из букв, пробелов и дефисов.\n");
            }
        } while (!validAuthor);
        int validPrice = 0;
        char priceStr[MAX_LENGTH];
        do {
            printf("  Цена: ");
            fgets(priceStr, MAX_LENGTH, stdin);
            priceStr[strcspn(priceStr, "\n")] = '\0';  // Удаляем символ новой строки
            if (isPriceValid(priceStr)) {
                books[i].price = stringToFloat(priceStr);  // Преобразуем строку в число
                validPrice = 1;  // true
            } else {
                printf("Ошибка: цена должна состоять только из цифр и одной точки.\n");
            }
        } while (!validPrice);

        printf("  Число страниц: ");
        scanf("%d", &books[i].pages);
        getchar();  // Убираем символ новой строки после scanf

        printf("  Издательство: ");
        fgets(books[i].publisher, MAX_LENGTH, stdin);
        books[i].publisher[strcspn(books[i].publisher, "\n")] = '\0';  // Удаляем символ новой строки

        printf("  Год издания: ");
        scanf("%d", &books[i].year);
        getchar();  // Убираем символ новой строки после scanf

        printf("  Город издания: ");
        fgets(books[i].city, MAX_LENGTH, stdin);
        books[i].city[strcspn(books[i].city, "\n")] = '\0';  // Удаляем символ новой строки
    }
}

void outputBooks(Book books[], int n, const char *author) {
    float minPrice = -1;
    int found = 0;
    int minIndex = -1;  

    // Находим минимальную цену для книг указанного автора
    for (int i = 0; i < n; i++) {
        if (strcmp(books[i].author, author) == 0) {
            if (minPrice == -1 || books[i].price < minPrice) {
                minPrice = books[i].price;
                minIndex = i;  
            }
            found = 1;
        }
    }

    if (!found) {
        printf("Книги автора %s не найдены.\n", author);
        return;
    }
    printf("Книга автора %s с самой низкой ценой (%.2f):\n", author, minPrice);
    printf("  Название: %s\n", books[minIndex].title);
    printf("  Число страниц: %d\n", books[minIndex].pages);
    printf("  Издательство: %s\n", books[minIndex].publisher);
    printf("  Год издания: %d\n", books[minIndex].year);
    printf("  Город издания: %s\n", books[minIndex].city);
}

int main() {
    Book books[MAX_BOOKS];
    int n;
    char author[MAX_LENGTH];

    inputBooks(books, &n);

    printf("Введите автора для поиска: ");
    fgets(author, MAX_LENGTH, stdin);
    author[strcspn(author, "\n")] = '\0'; 

    outputBooks(books, n, author);

    return 0;
}
