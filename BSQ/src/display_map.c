#include "../includes/bsq.h"

// Yardımcı: Bulunan kareyi grid üzerine 'full' karakteri ile çizer.
static void	paint_square_on_grid(t_map_info *map, t_square bsq)
{
	int	start_x;
	int	start_y;
	int	end_y;
	int	end_x;
	int	y;
	int	x;

	if (bsq.size == 0) // Çizilecek kare yoksa çık
		return ;
	// Karenin başlangıç koordinatlarını hesapla (sağ alt -> sol üst)
	start_y = bsq.y - bsq.size + 1;
	start_x = bsq.x - bsq.size + 1;
	end_y = bsq.y;
	end_x = bsq.x;
	y = start_y;
	while (y <= end_y)
	{
		x = start_x;
		while (x <= end_x)
		{
			// Koordinatların geçerli olduğundan emin ol (ekstra kontrol)
			if (y >= 0 && y < map->lines && x >= 0 && x < map->cols)
				map->grid[y][x] = map->full;
			x++;
		}
		y++;
	}
}

// Yardımcı: Grid'i standart çıktıya yazdırır.
// Norminette write içinde döngüye izin vermeyebilir, gerekirse
// her satırı ayrı write ile yazdıracak şekilde düzenlenmeli.
static void	print_final_grid(t_map_info *map)
{
	int	y;
	int	write_len; // Her satırın uzunluğu (\n dahil değil)

	y = 0;
	write_len = map->cols; // Satır uzunluğu
	while (y < map->lines)
	{
		// Satırı yazdır
		write(1, map->grid[y], write_len);
		// Satır sonu karakterini yazdır
		write(1, "\n", 1);
		y++;
	}
}

// Ana yazdırma fonksiyonu (bsq.h'de prototipi var)
void	display_result(t_map_info *map_info, t_square bsq)
{
	// Önce kareyi grid üzerine çiz
	paint_square_on_grid(map_info, bsq);
	// Sonra güncellenmiş grid'i yazdır
	print_final_grid(map_info);
}

// Bu dosyada şimdilik 3 fonksiyon var, Norm'a uygun.