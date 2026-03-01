#include "common.h"
#include "lib/hsluv.h"

int main(void) {
    srand((unsigned int)time(NULL));
    int W = 256, H = 256;
    printf("P3\n%d %d\n255\n", W, H);
    int ir, ig, ib;
    double hue = RAND_D * 360.0;
    for (int j = 0; j < W; j++) {
        for (int i = 0; i < H; i++) {
            double sat = 100.0 * (double)(i) / (W - 1);
            double lum = 100.0 * (double)(j) / (H - 1);
            hsluv2rgb255(hue, sat, lum, &ir, &ig, &ib);
            printf("%d %d %d\n", ir, ig, ib);
        }
    }
}
