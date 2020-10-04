#include "../utils.h"
int main() {
    Point p1 = {5, 0};
    Point p2 = {0, 4};
    Point rotatePoint = {0, 0};
    printf("p1: %d %d\n", p1.x, p1.y);
    printf("p2: %d %d\n", p2.x, p2.y);
    rotate(p1.x, p1.y, 90, rotatePoint);
    rotate(p2.x, p2.y, 90, rotatePoint);
    printf("rotate p1: %d %d\n", p1.x, p1.y);
    printf("totate p2: %d %d\n", p2.x, p2.y);

    Point p3 = {5, 0};
    Point p4 = {0, 4};
    translate(p3.x, p3.y, 2, 2);
    translate(p4.x, p4.y, 100, 100);
    printf("\ntranslate p1: %d %d\n", p3.x, p3.y);
    printf("translate p2: %d %d\n", p4.x, p4.y);   

    Point p5 = {5, 0};
    Point p6 = {0, 4};
    scale(p5.x, p5.y, 0.8);
    scale(p6.x, p6.y, 0.8);
    printf("\nscale p1: %d %d\n", p5.x, p5.y);
    printf("scale p2: %d %d\n", p6.x, p6.y); 
}