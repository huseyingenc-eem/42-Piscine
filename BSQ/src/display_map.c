/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 05:51:50 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/30 06:54:04 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bsq.h"

/**
 * @brief Bulunan en büyük kareyi (bsq) harita ızgarası üzerinde
 * map->full karakteri ile işaretler/boyar.
 *
 * @param map İşaretlenecek harita bilgilerini ve ızgarayı içeren yapı.
 * @param bsq İşaretlenecek karenin bilgileri (konum, boyut).
 */
static void	paint_square_on_grid(t_map_info *map, t_square bsq)
{
	int	start_y; // Karenin başlangıç satırı
	int	start_x; // Karenin başlangıç sütunu
	int	y;       // Döngü için satır indeksi
	int	x;       // Döngü için sütun indeksi

	// Eğer kare bulunamadıysa (boyut 0), işlem yapma
	if (bsq.size == 0)
		return ;

	// Karenin sol üst köşesinin koordinatlarını hesapla
	// bsq.y ve bsq.x sağ alt köşeyi gösterir.
	start_y = bsq.y - bsq.size + 1;
	start_x = bsq.x - bsq.size + 1;

	// Karenin kapladığı alandaki hücreleri 'full' karakteri ile doldur
	y = start_y;
	while (y <= bsq.y) // Karenin son satırına kadar
	{
		x = start_x;
		while (x <= bsq.x) // Karenin son sütununa kadar
		{
			// Sınır kontrolü (gereksiz olabilir ama garanti için iyi)
			if (y >= 0 && y < map->lines && x >= 0 && x < map->cols)
				map->grid[y][x] = map->full; // Hücreyi doldur
			x++;
		}
		y++;
	}
}

/**
 * @brief Haritanın son halini (ızgarayı) standart çıktıya yazdırır.
 *
 * @param map Yazdırılacak harita bilgilerini ve ızgarayı içeren yapı.
 */
static void	print_final_grid(t_map_info *map)
{
	int	y; // Satır döngü indeksi

	y = 0;
	// Tüm satırları yazdır
	while (y < map->lines)
	{
		// Satırı yazdır (write daha verimli olabilir)
		write(1, map->grid[y], map->cols);
		// Satır sonuna yeni satır karakteri ekle
		write(1, "\n", 1);
		y++;
	}
}

/**
 * @brief BSQ çözümünün sonucunu görüntüler.
 * Önce bulunan kareyi harita üzerinde işaretler, sonra haritayı yazdırır.
 *
 * @param map_info Harita bilgileri.
 * @param bsq Bulunan en büyük karenin bilgileri.
 */
void	display_result(t_map_info *map_info, t_square bsq)
{
	// Kareyi harita üzerinde boya/işaretle
	paint_square_on_grid(map_info, bsq);
	// Sonucu (işaretlenmiş haritayı) ekrana yazdır
	print_final_grid(map_info);
}