#include "../includes/bsq.h"

// Yardımcı: Tek bir girdi kaynağını (dosya veya stdin) işler.
// Başarı: 0, Hata: 1
// (Bu fonksiyonun içeriği öncekiyle aynı, sadece yorum satırı eklendi)
static int	process_single_input(int fd)
{
	t_map_info	*map_info;
	t_square	bsq_result;

	map_info = read_map(fd);
	if (map_info == NULL)
	{
		// read_map zaten "map error" yazdırdı.
		return (1); // Hata durumu
	}
	bsq_result = solve_bsq(map_info);
	display_result(map_info, bsq_result);
	free_grid(map_info->grid, map_info->lines);
	free(map_info);
	return (0); // Başarı durumu
}

// YARDIMCI: Birden fazla dosya argümanını işler.
// Genel durumu döner (0: hepsi başarılı, 1: en az bir hata oluştu)
static int	process_multiple_files(int argc, char **argv)
{
	int	fd;
	int	i;
	int	first_output_done;
	int	overall_status; // Daha anlaşılır olması için process_status yerine

	i = 1;
	first_output_done = 0;
	overall_status = 0;
	while (i < argc)
	{
		// Eğer bu ilk işlem değilse, önceki çıktıdan ayır
		if (first_output_done)
			write(1, "\n", 1);
		fd = open(argv[i], O_RDONLY);
		if (fd == -1) // Dosya açma hatası
		{
			write(2, "map error\n", 10);
			overall_status = 1; // Hata oluştu
		}
		else // Dosya başarıyla açıldı
		{
			// Dosyayı işle ve durumunu kontrol et
			if (process_single_input(fd) != 0)
				overall_status = 1; // Hata oluştu
			close(fd); // Dosyayı kapat
		}
		first_output_done = 1; // En az bir işlem (başarılı veya hatalı) yapıldı
		i++;
	}
	return (overall_status);
}

// Düzenlenmiş Ana program fonksiyonu
int	main(int argc, char **argv)
{
	int	status; // process_status yerine

	status = 0;
	if (argc == 1)
	{
		// Argüman yoksa standart girdiden oku (fd = 0)
		status = process_single_input(0);
	}
	else
	{
		// Dosya argümanlarını işle
		status = process_multiple_files(argc, argv);
	}
	// Programın genel çıkış durumu
	return (status);
}