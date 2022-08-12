#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include < math.h >

int AMOUNT = 100;
double abscissa[100] = { 0 };
double ordinate[100] = { 0 };

double abscissaPolygon[100] = { 0 };
double ordinatePolygon[100] = { 0 };
int counter = 0;

double newNum(void);
void printArray(double[]);
int findLower(double[], double[]);
void add(int);
int findNext(void);

int main()
{
    srand(time(NULL));
    for (int i = 0; i < AMOUNT; i++) {
        abscissa[i] = newNum();
        ordinate[i] = newNum();
    }
    
    printArray(abscissa);
    printf("\n\n");
    printArray(ordinate);

    //нашли самую нижнюю точку
    int indexFirst = findLower(abscissa, ordinate);
    printf("\n\n%d,first point. abscissa = %.1f, ordinate = %.1f\n", indexFirst, abscissa[indexFirst], ordinate[indexFirst]);
    //добавили во множество вершин многоугольника
    abscissaPolygon[0] = abscissa[indexFirst];
    ordinatePolygon[0] = ordinate[indexFirst];
    counter++;

    //поиск второй точки
    double cos = -1;
    int indexSecond = 0;
    for (int i = 0; i < AMOUNT; i++) {
        if (i == indexFirst) {
            continue;
        }
        double tmp = abscissa[i] / sqrt(pow(abscissa[i], 2) + pow(ordinate[i], 2));
        if (tmp > cos) {
            cos = tmp;
            indexSecond = i;
        }
    }
    add(indexSecond);
    printf("%d abscissa = %.1f, ordinate = %.1f\n", indexSecond, abscissa[indexSecond], ordinate[indexSecond]);

    do {
        

    } while (abscissa[counter]) != ;
}

int findNext() {
    double cos = -1;
    double x_vector1 = abscissa[counter - 1] - abscissa[counter - 2];
    double y_vector1 = ordinate[counter -1] - ordinate[counter - 2];
    double x_vector2, y_vector2;
    int indexNext = 0;

    for (int i = 0; i < AMOUNT; i++) {
        if (abscissa[i] == abscissa[counter] && ordinate[i] == ordinate[counter]) {
            continue;
        }
        double x_vector2 = abscissa[i] - abscissa[counter - 1];
        double y_vector2 = ordinate[i] - ordinate[counter -1];
        double tmp = (x_vector1 * x_vector2 + y_vector1 * y_vector2) / (sqrt((pow(x_vector1, 2) + pow(y_vector1, 2))) * sqrt((pow(x_vector2, 2) + pow(y_vector2, 2))));
        if (tmp > cos) {
            cos = tmp;
            indexNext = i;
        }
    }
    return indexNext;
}

void add(int index) {
    abscissaPolygon[counter] = abscissa[index];
    ordinatePolygon[counter] = ordinate[index];
    counter++;

}

int findLower(double x[], double y[]) {
    double minX = x[0];
    double minY = y[0];
    int index = 0;

    for (int i = 1; i < AMOUNT; i++) {
        if (minY >= y[i]) {
            minX = x[i];
            minY = y[i];
            index = i;
        }
    }
    return index;
}

double newNum() {
    //
    double r = (double)(rand() % 10) / (double) 10 + (double)(rand() % 10);
    return r;
}

void printArray(double a[]) {
    for (int i = 0; i < AMOUNT; i++) {
        printf(" %.3f", a[i]);

    }
}

