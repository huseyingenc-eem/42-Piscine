#include <stdio.h>


#define N 10

int min(int a, int b, int c) {
    int m = a < b ? a : b;
    return m < c ? m : c;
}

void find_largest_square(int grid[N][N]) {
    int dp[N][N];
    int max_size = 0;
    int max_i = 0, max_j = 0;

    // İlk satır ve sütun doğrudan kopyalanır
    for (int i = 0; i < N; i++) {
        dp[i][0] = grid[i][0] == 0 ? 1 : 0;
        dp[0][i] = grid[0][i] == 0 ? 1 : 0;
    }

    // DP tablosunu doldur
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            if (grid[i][j] == 0) {
                dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]);
                if (dp[i][j] > max_size) {
                    max_size = dp[i][j];
                    max_i = i;
                    max_j = j;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    // Görsel çıktı:
    printf("En buyuk kare boyutu: %d\n", max_size);
    printf("Alt-sag kose: (%d, %d)\n", max_i, max_j);
    printf("Koordinatlar: (%d,%d) - (%d,%d)\n", max_i - max_size + 1, max_j - max_size + 1, max_i, max_j);
    printf("\nHarita:\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 1) {
                printf("o ");
            } else {
                if (
                    i >= max_i - max_size + 1 && i <= max_i &&
                    j >= max_j - max_size + 1 && j <= max_j
                )
                    printf("X ");
                else
                    printf("0 ");
            }
        }
        printf("\n");
    }
}


int main(void)
{
    int grid[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}
    };

    find_largest_square(grid);

    return 0;
}

