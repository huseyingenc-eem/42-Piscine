#ifndef BSQ_H
# define BSQ_H

# include <unistd.h> // read, write, close
# include <stdlib.h> // malloc, free
# include <fcntl.h>  // open

/*
** t_map_info: Haritanın yapılandırmasını ve içeriğini tutar.
*/
typedef struct s_map_info
{
	int		lines;
	int		cols;
	char	empty;
	char	obstacle;
	char	full;
	char	**grid;
}	t_map_info;

/*
** t_square: Bulunan en büyük karenin bilgilerini tutar.
** x, y: Karenin sağ alt köşesinin koordinatları.
** size: Karenin kenar uzunluğu.
*/
typedef struct s_square
{
	int	x;
	int	y;
	int	size;
}	t_square;

// --- read_map.c Prototypeleri ---
t_map_info	*read_map(int fd);
void		free_grid(char **grid, int line_count);

// --- solve_bsq.c Prototypeleri ---
// Ana çözüm fonksiyonu, en büyük karenin bilgilerini döner.
t_square	solve_bsq(t_map_info *map_info);

// --- display_map.c Prototypeleri ---
// Sonucu (grid'i güncelleyip) yazdırır.
void		display_result(t_map_info *map_info, t_square bsq);

// --- Diğer Modüllerin Prototypeleri (Eklenecek) ---
// Örneğin: main.c

#endif