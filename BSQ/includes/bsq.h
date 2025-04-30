/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 06:26:22 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/30 06:26:49 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <unistd.h> // write, read, close için
# include <stdlib.h> // malloc, free için
# include <fcntl.h>  // open için

// Harita bilgilerini (boyutlar, karakterler, ızgara) tutan yapı.
typedef struct s_map_info
{
	int		lines;      // Haritadaki satır sayısı
	int		cols;       // Haritadaki sütun (kolon) sayısı
	char	empty;      // Boş alanı temsil eden karakter
	char	obstacle;   // Engeli temsil eden karakter
	char	full;       // Bulunan karenin doldurulacağı karakter
	char	**grid;     // Haritayı temsil eden 2 boyutlu karakter dizisi (ızgara)
}	t_map_info;

// Bulunan en büyük karenin bilgilerini (konum, boyut) tutan yapı.
typedef struct s_square
{
	int	x;          // Karenin sağ alt köşesinin sütun (kolon) indeksi
	int	y;          // Karenin sağ alt köşesinin satır indeksi
	int	size;       // Karenin kenar uzunluğu
}	t_square;

// Harita üzerinde pozisyon (satır, sütun) tutmak için kullanılan yardımcı yapı.
typedef struct s_pos
{
	int	row;        // Satır indeksi
	int	col;        // Sütun (kolon) indeksi
}	t_pos;

// Fonksiyon prototipleri

// t_pos yapısını başlatır (-1 değerleriyle).
void		init_pos(t_pos *p);
// Verilen dosya tanıtıcısından (fd) haritayı okur, ayrıştırır ve doğrular.
// Başarılı olursa t_map_info yapısını, hata olursa NULL döndürür.
t_map_info	*read_map(int fd);
// t_map_info yapısı ve içindeki ızgara için ayrılan belleği serbest bırakır.
void		free_map_info(t_map_info *map_info);
// Standart hataya (stderr) bir hata mesajı yazar.
void		ft_putstr_error(char *str);
// Verilen string'in uzunluğunu döndürür.
int			ft_strlen(char *str);
// Verilen harita bilgisi üzerinde BSQ algoritmasını çalıştırarak en büyük kareyi bulur.
// Bulunan karenin bilgilerini t_square yapısı olarak döndürür.
t_square	solve_bsq(t_map_info *map_info);
// Sonucu (haritayı ve üzerine işaretlenmiş en büyük kareyi) standart çıktıya yazdırır.
void		display_result(t_map_info *map_info, t_square bsq);

// read_map_utils.c içindeki statik olmayan fonksiyonların prototipleri (eğer dışarıdan erişim gerekmiyorsa burada olmaları şart değil)
int		read_single_line(int fd, char *buffer, int buffer_size);
int		parse_config_line(char *buffer, int len, t_map_info *map_info);
int		validate_grid_line(char *line, int len, t_map_info *map);
void	free_partial_grid(char **grid, int lines_filled);
int		check_config_chars(t_map_info *map_info);


#endif