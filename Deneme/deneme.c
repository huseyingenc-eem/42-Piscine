#include <stdlib.h>
int main()
{   
    char src[]= "merhaba";
    int size= sizeof(src) / sizeof(src[0]);
    char *dest1 = malloc( sizeof(char) * size );
    char dest2[] = malloc( sizeof(char) * size );
}
/*
🔴 char dest2[] = malloc(...); neden hatalı?
dest2[] bir stack üzerinde tanımlanan dizidir ve 
derleyici bu diziye bir malloc sonucu dönen char * türündeki 
heap adresini atamanıza izin vermez.

char dest2[]; // bu şekilde tanımlanan bir dizi sabit boyutlu olmalı, dinamik değil.
Yani:

char dest2[] ifadesi derleyiciye "ben sabit boyutlu bir dizi tanımlıyorum" der.

Ama malloc(...) ifadesi derleyiciye "dinamik bellekten pointer veriyorum" der.

Bu ikisi uyumsuzdur. char[] tanımı compile-time'da boyut istemesine rağmen, malloc runtime'da bellek verir.
*/