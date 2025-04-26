#include "../includes/bsq.h"

// Bellek serbest bırakma
void	free_grid(char **grid, int line_count)
{
	int	i;

	i = 0;
	if (!grid)
		return ;
	while (i < line_count)
	{
		if (grid[i])
			free(grid[i]);
		i++;
	}
	free(grid);
}

// Yardımcı: Tek bir satırı okur (\n'e kadar), buffer'a yazar.
static int	read_single_line(int fd, char *buffer, int buffer_size)
{
	int		bytes_read;
	int		total_bytes;
	char	c;

	total_bytes = 0;
	bytes_read = read(fd, &c, 1);
	while (bytes_read > 0)
	{
		if (c == '\n')
			break ;
		if (total_bytes < buffer_size - 1)
			buffer[total_bytes++] = c;
		else
			return (-1); // Buffer dolu (hata)
		bytes_read = read(fd, &c, 1);
	}
	buffer[total_bytes] = '\0';
	if (bytes_read < 0) // Okuma hatası
		return (-1);
	if (bytes_read == 0 && total_bytes == 0) // Dosya sonu ve hiç okunmadı
		return (-2); // EOF
	return (total_bytes);
}

// Yardımcı: İlk satırı (konfigürasyon) parse eder ve map_info'yu doldurur.
static int	parse_config_line(char *buffer, int len, t_map_info *map_info)
{
	int	i;
	int	num_part_len;

	// Karakter kontrolü
	if (len < 4 || buffer[len - 3] == buffer[len - 2]
		|| buffer[len - 3] == buffer[len - 1]
		|| buffer[len - 2] == buffer[len - 1])
		return (0);
	map_info->empty = buffer[len - 3];
	map_info->obstacle = buffer[len - 2];
	map_info->full = buffer[len - 1];
	num_part_len = len - 3;
	i = 0;
	map_info->lines = 0;
	// Satır sayısını al
	while (i < num_part_len)
	{
		if (buffer[i] < '0' || buffer[i] > '9')
			return (0);
		map_info->lines = map_info->lines * 10 + (buffer[i] - '0');
		i++;
	}
	if (map_info->lines <= 0) // Satır sayısı pozitif olmalı
		return (0);
	map_info->cols = 0; // Sütun sayısı henüz bilinmiyor
	map_info->grid = NULL;
	return (1);
}

// DÜZENLENMİŞ FONKSİYON: Grid'i (haritanın geri kalanını) okur ve doğrular.
// Hata kontrolleri ve iç döngü sadeleştirildi.
// Başarı: 1, Hata: 0
static int	read_and_validate_grid(int fd, t_map_info *map)
{
	char	buffer[4096]; // Buffer boyutu ayarlanabilir
	int		line_idx;
	int		len;
	int		i; // Döngü sayacı dışarı alındı

	map->grid = (char **)malloc(sizeof(char *) * map->lines);
	if (!map->grid)
		return (0); // Grid satırları için malloc hatası
	line_idx = 0;
	while (line_idx < map->lines)
	{
		len = read_single_line(fd, buffer, 4096);
		if (len < 0) // Okuma hatası veya buffer taştı
			return (free_grid(map->grid, line_idx), 0);
		if (line_idx == 0) // İlk grid satırı
		{
			if (len == 0) return (free(map->grid), 0); // İlk satır boş olamaz
			map->cols = len;
		}
		else if (len != map->cols) // Satır uzunlukları eşleşmeli
			return (free_grid(map->grid, line_idx), 0);
		map->grid[line_idx] = (char *)malloc(sizeof(char) * (map->cols + 1));
		if (!map->grid[line_idx]) // Satır için malloc hatası
			return (free_grid(map->grid, line_idx), 0);
		i = -1;
		while (++i < map->cols) // Satırı kopyala ve doğrula
		{
			if (buffer[i] != map->empty && buffer[i] != map->obstacle)
				return (free_grid(map->grid, line_idx + 1), 0); // Geçersiz karakter
			map->grid[line_idx][i] = buffer[i];
		}
		map->grid[line_idx][i] = '\0'; // Satırı sonlandır
		line_idx++;
	}
	// Opsiyonel: Dosyanın sonunda fazladan veri olup olmadığını kontrol et
	// len = read_single_line(fd, buffer, 4096);
	// if (len > 0 || len == -1) return (free_grid(map->grid, line_idx), 0);
	return (1);
}

// Ana okuma fonksiyonu
t_map_info	*read_map(int fd)
{
	t_map_info	*map_info;
	char		buffer[1024]; // İlk satır için buffer
	int			len;

	map_info = (t_map_info *)malloc(sizeof(t_map_info));
	if (!map_info)
	{
		write(2, "map error\n", 10); // Malloc hatası
		return (NULL);
	}
	// İlk satırı oku
	len = read_single_line(fd, buffer, 1024);
	if (len <= 0 || !parse_config_line(buffer, len, map_info))
	{
		free(map_info);
		write(2, "map error\n", 10); // Geçersiz ilk satır
		return (NULL);
	}
	// Grid'i oku ve doğrula
	if (!read_and_validate_grid(fd, map_info))
	{
		// read_and_validate_grid hata durumunda grid'i serbest bırakır
		free(map_info);
		write(2, "map error\n", 10); // Geçersiz grid
		return (NULL);
	}
	return (map_info);
}