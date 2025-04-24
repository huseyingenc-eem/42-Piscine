#include <stdio.h>

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char	reversed;
	int				i;

	reversed = 0;
	i = 0;
	while (i < 8)
	{
		if ((octet >> i) & 1)
		{
			reversed |= (1 << (7 - i));
		}
		i++;
	}
	return (reversed);
}

int	main(void)
{
	unsigned char	original;
	unsigned char	reversed_octet;

	original = 0b00100110; // Örnek girdi (38 onluk)
	reversed_octet = reverse_bits(original);
	printf("Orijinal: 0b%08u (%d)\n", original, original);
	printf("Ters çevrilmiş: 0b%08u (%d)\n", reversed_octet, reversed_octet);
	return (0);
}
