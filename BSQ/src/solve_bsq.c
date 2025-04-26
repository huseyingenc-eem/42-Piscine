#include "../includes/bsq.h"

// Yardımcı: Üç tamsayının minimumunu bulur.
// a, b, c: Karşılaştırılacak sayılar.
// min_val: Bulunan minimum değer.
static int	min_of_three(int a, int b, int c)
{
	int	min_val; // Minimum değeri tutar

	min_val = a;
	if (b < min_val)
		min_val = b;
	if (c < min_val)
		min_val = c;
	return (min_val);
}

// Yardımcı: DP (Dinamik Programlama) matrisini (int**) başlatır.
// map: Harita bilgilerini içeren struct.
// bsq_result: En büyük kare bilgilerini tutacak struct (başlangıç değerleri atanır).
// dp_table: Oluşturulan DP tablosu.
// row, col: Matris indeksleri (satır, sütun).
static int	**init_dp_matrix(t_map_info *map, t_square *bsq_result)
{
	int	**dp_table;
	int	row;
	int	col;

	// Satırlar için yer ayır
	dp_table = (int **)malloc(sizeof(int *) * map->lines);
	if (!dp_table)
		return (NULL);
	row = 0;
	while (row < map->lines)
	{
		// Her satır için sütunları ayır
		dp_table[row] = (int *)malloc(sizeof(int) * map->cols);
		if (!dp_table[row]) // Malloc hatası durumunda öncekileri serbest bırak
		{
			while (--row >= 0)
				free(dp_table[row]);
			free(dp_table);
			return (NULL);
		}
		col = 0;
		while (col < map->cols) // Başlangıç değeri olarak 0 ata
		{
			dp_table[row][col] = 0;
			col++;
		}
		row++;
	}
	// Başlangıçta en büyük kare boyutu 0, koordinatlar 0
	bsq_result->size = 0;
	bsq_result->x = 0;
	bsq_result->y = 0;
	return (dp_table);
}

// Yardımcı: DP matrisini hesaplar ve en büyük kareyi bulur.
// map: Harita bilgileri.
// dp_table: Doldurulacak DP tablosu.
// bsq_result: Bulunan en büyük kare bilgilerini günceller.
// row, col: Matris indeksleri.
static void	calculate_dp_and_find_bsq(t_map_info *map, int **dp_table,
										t_square *bsq_result)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->lines)
	{
		col = 0;
		while (col < map->cols)
		{
			if (map->grid[row][col] == map->obstacle)
				dp_table[row][col] = 0; // Engel varsa kare bitemez
			else // Boşluk karakteri ise
			{
				if (col == 0 || row == 0) // İlk satır veya sütun durumu
					dp_table[row][col] = 1;
				else // Diğer durumlar: sol, üst, sol-üst minimumunun 1 fazlası
					dp_table[row][col] = 1 + min_of_three(dp_table[row - 1][col], \
								dp_table[row][col - 1], dp_table[row - 1][col - 1]);
				// En büyük kareyi güncelle
				if (dp_table[row][col] > bsq_result->size)
				{
					bsq_result->size = dp_table[row][col];
					bsq_result->x = col; // Sağ alt köşe sütun
					bsq_result->y = row; // Sağ alt köşe satır
				}
			}
			col++;
		}
		row++;
	}
}

// Yardımcı: DP matrisini serbest bırakır.
// dp_table: Serbest bırakılacak matris.
// line_count: Matrisin satır sayısı.
// row_idx: Döngü indeksi.
static void	free_dp_matrix(int **dp_table, int line_count)
{
	int	row_idx;

	row_idx = 0;
	if (!dp_table)
		return ;
	while (row_idx < line_count)
	{
		if (dp_table[row_idx])
			free(dp_table[row_idx]);
		row_idx++;
	}
	free(dp_table);
}

// Ana çözüm fonksiyonu (bsq.h'de prototipi var)
// map_info: İşlenecek harita bilgileri.
// bsq_result: Bulunan en büyük karenin bilgileri.
// dp_matrix: Dinamik programlama için kullanılan matris.
t_square	solve_bsq(t_map_info *map_info)
{
	t_square	bsq_result;
	int			**dp_matrix;

	// DP matrisini başlat
	dp_matrix = init_dp_matrix(map_info, &bsq_result);
	if (!dp_matrix)
	{
		// Malloc hatası durumunda boş kare döndür
		bsq_result.size = 0;
		bsq_result.x = 0;
		bsq_result.y = 0;
		return (bsq_result); // Hata dönüşü
	}
	// Matrisi doldur ve en büyük kareyi bul
	calculate_dp_and_find_bsq(map_info, dp_matrix, &bsq_result);
	// DP matrisini temizle
	free_dp_matrix(dp_matrix, map_info->lines);
	// Bulunan en büyük karenin bilgilerini döndür
	return (bsq_result);
}