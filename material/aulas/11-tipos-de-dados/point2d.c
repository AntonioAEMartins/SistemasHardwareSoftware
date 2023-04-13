#include "point2d.h"
#include <stdlib.h>

struct _p {
    double x, y;
};

typedef struct _p Point2D;


Point2D *point2D_new(double x, double y) {
    // Alocando Memoria para o tamanho da Struct
    Point2D *point = malloc(sizeof(Point2D));
    // Checando para ver se memoria foi alocada com sucesso
    if (point != NULL){
        point -> x = x; // Aloca X
        point -> y = y; // Aloca Y
    }
    return point;
}


void point2D_destroy(Point2D *p) {
    free(p);
}

double point2D_get_x(Point2D *p) {
    return p->x;
}

double point2D_get_y(Point2D *p) {
    return p->y;
}

Point2D *point2D_add(Point2D *p1, Point2D *p2) {
    // Criando p3
    Point2D *p3 = malloc(sizeof(Point2D));
    if (p3 != NULL){ //Se alocacao funcionou
        p3 -> x = p1->x + p2->x; // Soma X
        p3 -> y = p1->y + p2->y; // Soma Y
    }
    return p3;
}

double point2D_theta(Point2D *p1, Point2D *p2) {
    return (double) (p2->y - p1->y) / (p2->x - p1->x);
}

Point2D *point2D_scale(Point2D *p, double s) {
    Point2D *p3 = malloc(sizeof(Point2D));
    if (p3 != NULL){
        p3 -> x = p->x * s;
        p3 -> y = p->y * s;
    }
    return p3;
}

