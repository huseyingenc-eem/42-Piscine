
ex00

#include <stdio.h>

int main()
{
    char *original = "Merhaba Dünya!";
    char *copy;

    copy = ft_strdup(original);

    if (copy != NULL)
    {
        printf("Orijinal: %s\n", original);
        printf("Kopya: %s\n", copy);
        free(copy); // Ayrılan belleği serbest bırakmayı unutmayın!
    }
    else
    {
        printf("Bellek ayırma başarısız oldu.\n");
    }

    char *empty = "";
    char *empty_copy = ft_strdup(empty);

    if (empty_copy != NULL)
    {
        printf("Orijinal (boş): %s\n", empty);
        printf("Kopya (boş): %s\n", empty_copy);
        free(empty_copy);
    }
    else
    {
        printf("Boş string kopyalama başarısız oldu.\n");
    }

    char *null_src = NULL;
    char *null_copy = ft_strdup(null_src);

    if (null_copy == NULL)
    {
        printf("NULL kaynak string doğru şekilde ele alındı.\n");
    }
    else
    {
        printf("NULL kaynak string beklenmedik bir şekilde kopyalandı.\n");
        free(null_copy); // Hata durumunda serbest bırakma
    }

    return 0;
}


ex01


#include <stdio.h>

int main()
{
    int *arr1;
    int size1;
    int i;

    arr1 = ft_range(2, 7); // Beklenen çıktı: [2, 3, 4, 5, 6]
    if (arr1)
    {
        printf("Aralık (2, 7):\n");
        for (i = 0; i < (7 - 2); i++)
            printf("%d ", arr1[i]);
        printf("\n");
        free(arr1);
    }
    else
    {
        printf("Aralık (2, 7) için bellek ayırma başarısız oldu veya boş aralık.\n");
    }

    int *arr2;
    int size2;

    arr2 = ft_range(5, 5); // Beklenen çıktı: NULL
    if (arr2)
    {
        printf("Aralık (5, 5):\n");
        for (i = 0; i < (5 - 5); i++) // Döngü hiç çalışmamalı
            printf("%d ", arr2[i]);
        printf("\n");
        free(arr2); // Bu satıra ulaşılmamalı
    }
    else
    {
        printf("Aralık (5, 5) için doğru şekilde boş dizi döndürüldü.\n");
    }

    int *arr3;
    int size3;

    arr3 = ft_range(7, 2); // Beklenen çıktı: NULL
    if (arr3)
    {
        printf("Aralık (7, 2):\n");
        for (i = 0; i < (2 - 7); i++) // Döngü hiç çalışmamalı
            printf("%d ", arr3[i]);
        printf("\n");
        free(arr3); // Bu satıra ulaşılmamalı
    }
    else
    {
        printf("Aralık (7, 2) için doğru şekilde boş dizi döndürüldü.\n");
    }

    return 0;
}


ex02

int main()
{
    int *my_range;
    int min = 5;
    int max = 15;
    int result_size;

    result_size = ft_ultimate_range(&my_range, min, max);

    if (result_size == -1)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }
    else if (result_size == 0)
    {
        printf("Range is empty (min >= max).\n");
        return 0;
    }
    else
    {
        printf("Range: ");
        for (int i = 0; i < result_size; i++)
        {
            printf("%d ", my_range[i]);
        }
        printf("\nSize of range: %d\n", result_size);
    }
    free(my_range);
    return 0;
}

ex03

#include <stdlib.h>
#include <stdio.h>


int main(void)
{
    char *strings[] = {"Hello", "World", "42", "Istanbul"};
    char *separator = "---";
    int size = sizeof(strings) / sizeof(strings[0]);
    char *result;

    result = ft_strjoin(size, strings, separator);
    if (result)
    {
        printf("Joined string: %s\n", result);
        free(result); // Don't forget to free the allocated memory!
    }
    else
    {
        printf("Failed to join strings.\n");
    }

    // Example with size 0
    char *empty_result = ft_strjoin(0, strings, separator);
    if (empty_result) {
        printf("Joined string (size 0): %s\n", empty_result); // Should print an empty string
        free(empty_result);
    }
    else
    {
        printf("Failed to join string (size 0).\n");
    }
    return (0);
}
