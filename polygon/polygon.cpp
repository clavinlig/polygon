#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include < math.h >
#pragma warning(disable:4996)

int AMOUNT = 100;
double abscissa[100] = { 0 };
double ordinate[100] = { 0 };

double abscissaPolygon[100] = { 0 };
double ordinatePolygon[100] = { 0 };
int counter = 0;
int indexFirst = 0;

double newNum(void);
void printArray(double[]);
int findLower(double[], double[]);
void add(int);
int findNext(void);

int main()
{
    /*int main() {
        
        
    }
    */

    srand(time(NULL));
    for (int i = 0; i < AMOUNT; i++) {
        abscissa[i] = newNum();
        ordinate[i] = newNum();
    }
    FILE* file = fopen("allPoints.csv", "w");
    fprintf(file, "x, y\n");
    for (int i = 0; i < AMOUNT; i++) {
        fprintf(file, "%.2f, %.2f\n", abscissa[i], ordinate[i]);
    }
    fclose(file);


    printArray(abscissa);
    printf("\n\n");
    printArray(ordinate);

    //нашли самую нижнюю точку
    indexFirst = findLower(abscissa, ordinate);
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
    //зануляем точку
    abscissa[indexSecond] = 0;
    ordinate[indexSecond] = 0;

    int next;
    do {
        next = findNext();
        add(next);

        abscissa[next] = 0;
        ordinate[next] = 0;

    } while (next != indexFirst);


    printArray(abscissaPolygon);
    printf("\n\n");
    printArray(ordinatePolygon);

    FILE* file1 = fopen("polygon.csv", "w");
    fprintf(file1, "x, y\n");
    for (int i = 0; i < AMOUNT; i++) {
        if (abscissaPolygon[i] == 0 && ordinatePolygon[i]) {
            break;
        }
        fprintf(file1, "%.2f, %.2f\n", abscissaPolygon[i], ordinatePolygon[i]);
    }
    fclose(file1);
}

int findNext() {
    double cos = -1;
    int indexNext = 0;

    for (int i = 0; i < AMOUNT; i++) {
        if (abscissa[i] == 0 && ordinate[i] == 0 || indexFirst == i) {
            continue;
        }
        
        double tmp = (abscissa[i] - abscissaPolygon[counter - 1])/ sqrt(pow(abscissa[i] - abscissaPolygon[counter - 1], 2) + pow(ordinate[i] -ordinatePolygon[counter - 1], 2));
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

