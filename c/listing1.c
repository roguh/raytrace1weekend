#include <stdio.h>

int main(void) {
    int w = 256, h = 256;
    printf("P3\n%d %d\n255\n", w, h);
    for (int j = 0; j < w; j++) {
        for (int i = 0; i < h; i++) {
            double r = (double)(i) / (w - 1);
            double g = (double)(j) / (h - 1);
            double b = 0.0;
            int ir = (int)(255.999 * r);
            int ig = (int)(255.999 * g);
            int ib = (int)(255.999 * b);
            printf("%d %d %d\n", ir, ig, ib);
        }
    }
}
