/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 05:52:55 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/30 05:53:16 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bsq.h"

/**
 * @brief Harita okuma sırasında bir hata oluştuğunda, o ana kadar
 * ızgara (grid) için ayrılmış olan satırların belleğini serbest bırakır.
 * Son olarak satır pointerları dizisini de serbest bırakır.
 *
 * @param grid Belleği serbest bırakılacak 2D karakter dizisi (ızgara).
 * @param lines_filled O ana kadar başarıyla doldurulmuş ve belleği ayrılmış satır sayısı.
 */
void	free_partial_grid(char **grid, int lines_filled)
{
	int	i;

	i = 0;
	// Doldurulmuş her satır için ayrılan belleği serbest bırak
	while (i < lines_filled)
	{
		free(grid[i]);
		i++;
	}
	// Satır pointerları dizisini serbest bırak
	free(grid);
}

/**
 * @brief Dosya tanıtıcısından (fd) bir sonraki '\n' karakterine kadar
 * veya buffer dolana kadar tek bir satır okur.
 *
 * @param fd Okunacak dosya tanıtıcısı.
 * @param buffer Okunan verinin yazılacağı karakter dizisi (buffer).
 * @param buffer_size Buffer'ın maksimum boyutu.
 * @return int Okunan byte sayısı. Hata durumunda -1, dosya sonunda ve hiç okuma yapılmadıysa -2 döndürür.
 * Buffer dolarsa da -1 döndürebilir (hata olarak işaretlenmeli).
 */
int	read_single_line(int fd, char *buffer, int buffer_size)
{
	int		bytes_read;   // read() fonksiyonunun dönüş değeri
	int		total_bytes;  // Bu satır için okunan toplam byte sayısı
	char	c;            // Okunan tek karakter

	total_bytes = 0;
	// İlk karakteri okumayı dene
	bytes_read = read(fd, &c, 1);
	// Okuma başarılı olduğu sürece devam et
	while (bytes_read > 0)
	{
		// Satır sonu karakterine ulaşıldıysa döngüyü kır
		if (c == '\n')
			break ;
		// Buffer'da yer varsa karakteri ekle
		if (total_bytes < buffer_size - 1) // -1 null terminator için yer ayırır
			buffer[total_bytes++] = c;
		else
			return (-1); // Buffer doldu, hata durumu
		// Sonraki karakteri oku
		bytes_read = read(fd, &c, 1);
	}
	// Okunan satırı null terminator ile sonlandır
	buffer[total_bytes] = '\0';

	// read() fonksiyonu hata verdiyse
	if (bytes_read < 0)
		return (-1); // Okuma hatası

	// Eğer dosya sonuna gelindiyse ve hiç byte okunmadıysa (boş dosya veya ardışık \n sonrası)
	if (bytes_read == 0 && total_bytes == 0)
		return (-2); // Dosya sonu ve boş satır durumu

	// Başarıyla okunan byte sayısını döndür
	return (total_bytes);
}

/**
 * @brief Harita yapılandırma satırından okunan karakterlerin (boş, engel, dolu)
 * geçerli olup olmadığını kontrol eder (birbirlerinden farklı olmalılar).
 *
 * @param map_info Kontrol edilecek karakterleri içeren harita yapısı.
 * @return int Karakterler geçerliyse 1, geçersizse (aynı karakterler varsa) 0.
 */
int	check_config_chars(t_map_info *map_info)
{
	// Karakterlerin birbirinden farklı olup olmadığını kontrol et
	if (map_info->empty == map_info->obstacle)
		return (0);
	if (map_info->empty == map_info->full)
		return (0);
	if (map_info->obstacle == map_info->full)
		return (0);
	// Tüm karakterler farklıysa geçerlidir
	return (1);
}

/**
 * @brief Haritanın ilk satırı olan yapılandırma satırını ayrıştırır.
 * Satır sayısını ve özel karakterleri (boş, engel, dolu) `map_info` yapısına işler.
 * Formatı doğrular (sayı + 3 karakter).
 *
 * @param buffer Ayrıştırılacak yapılandırma satırını içeren buffer.
 * @param len Buffer'daki verinin uzunluğu.
 * @param map_info Ayrıştırılan bilgilerin yazılacağı harita yapısı.
 * @return int Ayrıştırma ve doğrulama başarılıysa 1, hata olursa 0.
 */
int	parse_config_line(char *buffer, int len, t_map_info *map_info)
{
	int	i;
	int	num_part_len; // Satır sayısını içeren kısmın uzunluğu

	// Geçerli minimum uzunluk: 1 rakam + 3 karakter = 4
	if (len < 4)
		return (0); // Geçersiz uzunluk

	// Karakterleri sondan başlayarak al
	map_info->empty = buffer[len - 3];
	map_info->obstacle = buffer[len - 2];
	map_info->full = buffer[len - 1];

	// Karakterlerin geçerliliğini kontrol et (birbirinden farklı mı?)
	if (!check_config_chars(map_info))
		return (0); // Geçersiz karakterler

	// Sayı kısmının uzunluğunu hesapla
	num_part_len = len - 3;
	i = 0;
	map_info->lines = 0; // Satır sayısını sıfırla
	// Sayı kısmını oku ve tamsayıya çevir
	while (i < num_part_len)
	{
		// Sadece rakam içerdiğini kontrol et
		if (buffer[i] < '0' || buffer[i] > '9')
			return (0); // Sayı olmayan karakter bulundu
		// Sayıyı oluştur (atoi benzeri)
		map_info->lines = map_info->lines * 10 + (buffer[i] - '0');
		i++;
	}

	// Satır sayısı 0 veya daha küçük olamaz
	if (map_info->lines <= 0)
		return (0); // Geçersiz satır sayısı

	// Başlangıçta sütun sayısı bilinmiyor, ızgara NULL
	map_info->cols = 0;
	map_info->grid = NULL;

	// Başarılı ayrıştırma
	return (1);
}

/**
 * @brief Okunan bir harita satırının geçerliliğini kontrol eder.
 * İlk okunan satırsa sütun sayısını belirler, sonraki satırların bu sayıya
 * ve izin verilen karakterlere (boş, engel) uyup uymadığını kontrol eder.
 *
 * @param line Kontrol edilecek harita satırı.
 * @param len Satırın uzunluğu.
 * @param map Harita bilgilerini (beklenen sütun sayısı, karakterler) içeren yapı.
 * @return int Satır geçerliyse 1, geçersizse 0.
 */
int	validate_grid_line(char *line, int len, t_map_info *map)
{
	int	i;

	i = 0;
	// Eğer sütun sayısı henüz belirlenmemişse (ilk ızgara satırı)
	if (map->cols == 0)
	{
		// Satır boş olamaz
		if (len == 0)
			return (0);
		// Sütun sayısını bu satırın uzunluğu olarak belirle
		map->cols = len;
	}
	// Eğer sütun sayısı belirlenmişse, mevcut satırın uzunluğu eşleşmeli
	else if (len != map->cols)
		return (0); // Farklı satır uzunluğu hatası

	// Satırdaki her karakteri kontrol et
	while (i < len)
	{
		// Karakter sadece 'boş' veya 'engel' olabilir
		if (line[i] != map->empty && line[i] != map->obstacle)
			return (0); // Geçersiz karakter
		i++;
	}
	// Tüm kontrollerden geçerse satır geçerlidir
	return (1);
}
