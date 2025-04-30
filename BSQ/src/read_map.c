/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 05:53:48 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/30 05:53:53 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bsq.h"

// Diğer dosyalardaki yardımcı fonksiyonların prototipleri (header'da zaten var ama burada da belirtilebilir)
int		read_single_line(int fd, char *buffer, int buffer_size);
int		parse_config_line(char *buffer, int len, t_map_info *map_info);
int		validate_grid_line(char *line, int len, t_map_info *map);
void	free_partial_grid(char **grid, int lines_filled);

/**
 * @brief Verilen buffer'daki veriyi yeni bir string'e kopyalar.
 *
 * @param buffer Kopyalanacak veriyi içeren buffer.
 * @param len Kopyalanacak karakter sayısı.
 * @return char* Yeni ayrılmış ve kopyalanmış string, hata olursa NULL.
 */
static char	*copy_line(char *buffer, int len)
{
	char	*line_copy;
	int		i;

	line_copy = (char *)malloc(sizeof(char) * (len + 1)); // +1 null terminator için
	if (!line_copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line_copy[i] = buffer[i];
		i++;
	}
	line_copy[i] = '\0'; // String'i sonlandır
	return (line_copy);
}

/**
 * @brief Haritanın ızgara (grid) satırlarını dosyadan okur, doğrular ve map->grid içine atar.
 *
 * @param fd Okunacak dosya tanıtıcısı.
 * @param map Harita bilgilerini içeren ve ızgarası doldurulacak yapı.
 * @return int Başarılı olursa 1, hata olursa 0.
 */
static int	process_grid_lines(int fd, t_map_info *map)
{
	char	buffer[4096]; // Satır okumak için geçici buffer (makul bir boyut)
	int		line_idx;     // Mevcut satır indeksi
	int		len;          // Okunan satırın uzunluğu
	char	*current_line;// Geçerli satırın kopyasını tutacak pointer

	line_idx = 0;
	// Beklenen satır sayısı kadar oku
	while (line_idx < map->lines)
	{
		// Tek bir satırı oku
		len = read_single_line(fd, buffer, 4096);
		// Satır okuma hatası veya geçersiz satır kontrolü
		if (len < 0 || !validate_grid_line(buffer, len, map))
		{
			// Hata durumunda o ana kadar ayrılan ızgara satırlarını serbest bırak
			free_partial_grid(map->grid, line_idx);
			return (0); // Hata
		}
		// Geçerli satırı kopyala (map->cols kullanılarak doğru uzunlukta)
		current_line = copy_line(buffer, map->cols);
		if (!current_line)
		{
			// Kopyalama (malloc) hatası durumunda belleği temizle
			free_partial_grid(map->grid, line_idx);
			return (0); // Hata
		}
		// Kopyalanan satırı haritanın ızgarasına ata
		map->grid[line_idx] = current_line;
		line_idx++;
	}
	// Dosyada beklenenden fazla satır var mı diye kontrol edilebilir (isteğe bağlı)
	// len = read_single_line(fd, buffer, 1); // Sonraki okumayı dene
	// if (len != -2) { // -2: dosya sonu değilse hata
	//     free_partial_grid(map->grid, map->lines); return (0);
	// }
	return (1); // Başarılı
}

/**
 * @brief Haritanın ızgarası (grid) için bellek ayırır (satır pointerları için).
 *
 * @param map Bellek ayrılacak ızgarayı içeren harita yapısı.
 * @return int Başarılı olursa 1, malloc hatası olursa 0.
 */
static int	allocate_grid(t_map_info *map)
{
	// Satır pointerları dizisi için yer ayır
	map->grid = (char **)malloc(sizeof(char *) * map->lines);
	if (!map->grid)
		return (0); // malloc hatası
	return (1); // Başarılı
}

/**
 * @brief t_map_info yapısı ve içindeki ızgara için ayrılan tüm belleği serbest bırakır.
 *
 * @param map_info Belleği serbest bırakılacak yapı. NULL ise işlem yapmaz.
 */
void	free_map_info(t_map_info *map_info)
{
	if (!map_info)
		return ;
	// Eğer ızgara için bellek ayrılmışsa, önce satırları sonra pointer dizisini serbest bırak
	if (map_info->grid)
		free_partial_grid(map_info->grid, map_info->lines); // Satırları serbest bırakır
	free(map_info); // Ana yapıyı serbest bırak
}

/**
 * @brief Verilen dosya tanıtıcısından (fd) haritayı okur, yapılandırır ve doğrular.
 * Önce yapılandırma satırını, sonra ızgarayı okur.
 *
 * @param fd Haritanın okunacağı dosya tanıtıcısı.
 * @return t_map_info* Başarıyla okunan ve doğrulanmış harita bilgileri. Hata durumunda NULL döndürür ve hata mesajı basar.
 */
t_map_info	*read_map(int fd)
{
	t_map_info	*map_info;  // Döndürülecek harita yapısı
	char		buffer[1024];// Yapılandırma satırını okumak için buffer
	int			len;        // Okunan yapılandırma satırının uzunluğu

	// Ana harita yapısı için bellek ayır
	map_info = (t_map_info *)malloc(sizeof(t_map_info));
	if (!map_info)
	{
		ft_putstr_error("map error\n"); // Bellek hatası
		return (NULL);
	}

	// İlk satırı (yapılandırma satırı) oku
	len = read_single_line(fd, buffer, 1024);
	// Yapılandırma satırını oku, ayrıştır ve doğrula
	if (len <= 0 || !parse_config_line(buffer, len, map_info))
	{
		free(map_info); // Başarısız olursa ayrılan belleği geri ver
		ft_putstr_error("map error\n"); // Hata mesajı
		return (NULL);
	}

	// Harita ızgarası için bellek ayır
	if (!allocate_grid(map_info))
	{
		free(map_info);
		ft_putstr_error("map error\n"); // Bellek hatası
		return (NULL);
	}

	  // Izgara satırlarını oku ve doğrula
	  if (!process_grid_lines(fd, map_info))
	  {
		  // process_grid_lines başarısız oldu. Kendi içinde map_info->grid'i
		  // ve ilgili satırları free_partial_grid ile temizledi.
		  // Bizim burada sadece map_info yapısını free etmemiz yeterli.
		  free(map_info); // Sadece ana yapıyı free et.
		  ft_putstr_error("map error\n"); // Hata mesajını yazdır.
		  return (NULL); // NULL döndürerek hatayı bildir.
	  }

	// Her şey başarılıysa harita bilgilerini döndür
	return (map_info);
}
