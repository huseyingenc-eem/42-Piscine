/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_bsq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 05:54:13 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/30 06:20:56 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bsq.h"

/**
 * @brief Verilen üç tamsayının en küçüğünü bulur.
 * Dinamik programlama tablosunu doldururken kullanılır.
 *
 * @param a Birinci sayı.
 * @param b İkinci sayı.
 * @param c Üçüncü sayı.
 * @return int Üç sayı arasındaki minimum değer.
 */
static int	min_of_three(int a, int b, int c)
{
	int	min_val;

	min_val = a;
	if (b < min_val)
		min_val = b;
	if (c < min_val)
		min_val = c;
	return (min_val);
}

/**
 * @brief Dinamik programlama (DP) tablosundaki bir hücrenin değerini hesaplar.
 * Değer, o hücrede biten en büyük karenin kenar uzunluğunu temsil eder.
 *
 * @param map Harita bilgileri.
 * @param dp DP tablosu (o ana kadar doldurulmuş).
 * @param r Mevcut hücrenin satır indeksi.
 * @param c Mevcut hücrenin sütun indeksi.
 * @return int Hücrenin DP değeri (o hücrede biten karenin boyutu).
 */
static int	calculate_cell_value(t_map_info *map, int **dp, int r, int c)
{
	// Eğer mevcut hücre bir engel ise, burada kare bitemez.
	if (map->grid[r][c] == map->obstacle)
		return (0);
	// Eğer ilk satır veya ilk sütundaysak ve engel değilse, en büyük kare 1x1'dir.
	if (r == 0 || c == 0)
		return (1);
	// Eğer engel değilse ve ilk satır/sütun değilse, DP değeri:
	// 1 + solundaki, üstündeki ve sol üst çaprazındaki hücrelerin DP değerlerinin minimumu.
	// Bu, o noktada ne kadar büyük bir kare oluşturulabileceğini belirler.
	return (1 + min_of_three(dp[r - 1][c], dp[r][c - 1], dp[r - 1][c - 1]));
}

/**
 * @brief Bulunan mevcut kare boyutunu, şimdiye kadar bulunan en büyük kare (bsq)
 * ile karşılaştırır ve gerekirse bsq'yu günceller.
 *
 * @param current_val Mevcut hücre için hesaplanan DP değeri (kare boyutu).
 * @param r Mevcut hücrenin satır indeksi.
 * @param c Mevcut hücrenin sütun indeksi.
 * @param bsq Güncellenecek olan, şimdiye kadar bulunan en büyük kare bilgisi.
 */
static void	update_bsq(int current_val, int r, int c, t_square *bsq)
{
	// Eğer mevcut hücrede biten kare, şimdiye kadar bulunan en büyük kareden daha büyükse
	if (current_val > bsq->size)
	{
		bsq->size = current_val; // Yeni en büyük boyut
		bsq->x = c;             // Karenin bittiği sütun
		bsq->y = r;             // Karenin bittiği satır
	}
}

/**
 * @brief Dinamik programlama için 2 boyutlu bir tamsayı matrisi oluşturur ve belleğini ayırır.
 *
 * @param lines Matrisin satır sayısı (haritanın satır sayısı).
 * @param cols Matrisin sütun sayısı (haritanın sütun sayısı).
 * @return int** Başarıyla oluşturulan DP matrisi, bellek hatası olursa NULL.
 */
static int	**create_dp_matrix(int lines, int cols)
{
	int	**dp_table; // DP tablosu pointer'ı
	int	i;          // Döngü sayacı

	// Satır pointerları dizisi için yer ayır
	dp_table = (int **)malloc(sizeof(int *) * lines);
	if (!dp_table)
		return (NULL); // Malloc hatası

	// Her satır için sütunları içeren diziyi ayır
	i = 0;
	while (i < lines)
	{
		dp_table[i] = (int *)malloc(sizeof(int) * cols);
		if (!dp_table[i])
		{
			// Eğer bir satır için bellek ayrılamazsa, o ana kadar ayrılanları geri ver
			while (--i >= 0)
				free(dp_table[i]);
			free(dp_table); // Satır pointerları dizisini de serbest bırak
			return (NULL); // Malloc hatası
		}
		i++;
	}
	return (dp_table); // Başarıyla oluşturulan matrisi döndür
}

/**
 * @brief Verilen harita üzerinde en büyük kareyi (BSQ - Biggest Square) bulur.
 * Dinamik programlama yaklaşımını kullanır.
 *
 * @param map_info Harita bilgilerini içeren yapı.
 * @return t_square Bulunan en büyük karenin konumunu (sağ alt köşe) ve boyutunu içeren yapı.
 * Bellek hatası olursa {0, 0, 0} döndürür.
 */
t_square	solve_bsq(t_map_info *map_info)
{
	t_square	bsq;    // Sonucu (en büyük kare) tutacak yapı
	int			**dp;   // Dinamik programlama tablosu
	t_pos		pos;    // Harita üzerinde gezinmek için pozisyon yapısı

	// DP tablosu için bellek ayır
	dp = create_dp_matrix(map_info->lines, map_info->cols);
	if (!dp)
		// Bellek ayrılamazsa boş bir kare döndür (hata durumu)
		return ((t_square){.x = 0, .y = 0, .size = 0});

	// En büyük kare bilgilerini başlangıçta sıfırla
	bsq = (t_square){0, 0, 0};
	init_pos(&pos); // Pozisyonu başlat (-1, -1)

	// Haritanın her hücresi için DP değerini hesapla
	// Satır satır ilerle
	while (++pos.row < map_info->lines)
	{
		pos.col = -1; // Her yeni satır için sütunu sıfırla
		// Sütun sütun ilerle
		while (++pos.col < map_info->cols)
		{
			// Mevcut hücre için DP değerini hesapla
			dp[pos.row][pos.col] = calculate_cell_value(map_info, dp,
					pos.row, pos.col);
			// Hesaplanan değerle en büyük kareyi (bsq) güncelle
			update_bsq(dp[pos.row][pos.col], pos.row, pos.col, &bsq);
		}
	}

	// DP tablosu için ayrılan belleği serbest bırak
	pos.row = -1;
	while (++pos.row < map_info->lines)
		free(dp[pos.row]); // Önce her satırı serbest bırak
	free(dp); // Sonra satır pointerları dizisini serbest bırak

	// Bulunan en büyük karenin bilgilerini döndür
	return (bsq);
}
