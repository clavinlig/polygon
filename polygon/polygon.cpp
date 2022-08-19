#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include < math.h >
#pragma warning(disable:4996)

int AMOUNT = 500;
double abscissa[500] = { 0 };
double ordinate[500] = { 0 };

double abscissaPolygon[1000] = { 0 };
double ordinatePolygon[1000] = { 0 };
int counter = 0;
int indexFirst = 0;

double newNum(void);
void printArray(double[]);
int findLower(double[], double[]);
void add(int);
int findNext(void);
double module(double, double);

int main()
{
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
    
    //поиск второй точки
    double cos = -1;
    int indexSecond = 0;
    for (int i = 0; i < AMOUNT; i++) {
        if (i == indexFirst) {
            continue;
        }
        double tmp = (abscissa[i] -abscissaPolygon[0]) / sqrt(pow(abscissa[i] -abscissaPolygon[0], 2) + pow(ordinate[i]- ordinatePolygon[0], 2));
        if (tmp > cos) {
            cos = tmp;
            indexSecond = i;
        }
    }
    
    add(indexSecond);
    printf("%d abscissa = %.1f, ordinate = %.1f\n", indexSecond, abscissa[indexSecond], ordinate[indexSecond]);
    printf("%d\n", counter);
    
    int next;
    do {
        next = findNext();
        add(next);
    } while (next != indexFirst);

    printArray(abscissaPolygon);
    printf("\n\n");
    printArray(ordinatePolygon);

    FILE* file1 = fopen("polygon.csv", "w");
    fprintf(file1, "x, y\n");
    for (int i = 0; i < AMOUNT; i++) {
        if (abscissaPolygon[i] == 0 && ordinatePolygon[i] ==0) {
            break;
        }
        fprintf(file1, "%.2f, %.2f\n", abscissaPolygon[i], ordinatePolygon[i]);
    }
    fprintf(file1, "%.2f, %.2f\n", abscissaPolygon[0], ordinatePolygon[0]);
    fclose(file1);
}

int findNext() {
    double cos = -1;
    double x_vector1 = abscissaPolygon[counter] - abscissaPolygon[counter - 1];
    double y_vector1 = ordinatePolygon[counter] - ordinatePolygon[counter - 1];
    double x_vector2, y_vector2;
    int indexNext = 0;
    for (int i = 0; i < AMOUNT; i++) {
        if (abscissa[i] == abscissaPolygon[counter] && ordinate[i] == ordinatePolygon[counter]) {
            continue;
        }
        x_vector2 = abscissa[i] - abscissaPolygon[counter];
        y_vector2 = ordinate[i] - ordinatePolygon[counter];
        double tmp = (x_vector1 * x_vector2 + y_vector1 * y_vector2) / (module(x_vector1, y_vector1) * module(x_vector2, y_vector2));
        if (tmp > cos) {
            cos = tmp;
            indexNext = i;
        }
    }
    return indexNext;
}

double module(double x, double y) {
    return sqrt(x * x + y * y);
}

void add(int index) {
    counter++;
    abscissaPolygon[counter] = abscissa[index];
    ordinatePolygon[counter] = ordinate[index];
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
    double r = (double)(rand() % 10) / (double) 10 + (double)(rand() % 10);
    return r;
}

void printArray(double a[]) {
    for (int i = 0; i < AMOUNT; i++) {
        printf(" %.3f", a[i]);
    }
}

