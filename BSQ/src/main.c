/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 06:25:47 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/30 07:30:24 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bsq.h"

/**
 * @brief Tek bir girdi kaynağını (dosya veya standart girdi) işler.
 * Haritayı okur, çözer ve sonucu yazdırır.
 *
 * @param fd İşlenecek girdi kaynağının dosya tanıtıcısı (0: stdin).
 * @return int Başarılı olursa 0, hata olursa 1 döndürür.
 */
static int	process_single_input(int fd)
{
	t_map_info	*map_info;  // Harita bilgilerini tutacak yapı
	t_square	bsq_result; // Bulunan en büyük kareyi tutacak yapı

	// Haritayı oku ve doğrula
	map_info = read_map(fd);
	if (map_info == NULL)
	{
		// read_map zaten hata mesajı yazdırdı
		return (1); // Hata durumu
	}

	// Haritayı çöz (en büyük kareyi bul)
	bsq_result = solve_bsq(map_info);

	// Sonucu ekrana yazdır
	display_result(map_info, bsq_result);

	// Harita için ayrılan belleği serbest bırak
	free_map_info(map_info);
	return (0); // Başarı durumu
}

/**
 * @brief Verilen dosya adını açar ve process_single_input ile işler.
 *
 * @param filename İşlenecek dosyanın adı.
 * @return int Başarılı olursa 0, dosya açma veya işleme hatası olursa 1 döndürür.
 */
static int	process_file(char *filename)
{
	int	fd;         // Dosya tanıtıcısı
	int	status;     // İşlem durumu

	// Dosyayı salt okunur modda aç
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		// Dosya açılamazsa hata mesajı yazdır
		ft_putstr_error("map error\n");
		return (1); // Hata durumu
	}

	// Dosya içeriğini işle
	status = process_single_input(fd);

	// Dosyayı kapat
	close(fd);
	return (status); // İşlem sonucunu döndür
}

/**
 * @brief Komut satırından verilen birden fazla dosyayı sırayla işler.
 *
 * @param argc Argüman sayısı.
 * @param argv Argüman dizisi (dosya adları).
 * @return int Tüm dosyalar başarılı işlenirse 0, herhangi birinde hata olursa 1 döndürür.
 */
static int	process_multiple_files(int argc, char **argv)
{
	int	i;                  // Döngü sayacı
	int	overall_status;     // Genel işlem durumu
	int	current_status;     // Mevcut dosyanın işlem durumu

	i = 1; // İlk argüman program adı olduğu için 1'den başla
	overall_status = 0; // Başlangıçta hata yok varsayımı

	// Tüm dosya argümanlarını işle
	while (i < argc)
	{
		// İlk dosyadan sonraki dosyaların çıktıları arasına boşluk ekle
		if (i > 1)
			write(1, "\n", 1);

		// Mevcut dosyayı işle
		current_status = process_file(argv[i]);
		if (current_status != 0)
			overall_status = 1; // Herhangi bir hata olursa genel durumu güncelle
		i++;
	}
	return (overall_status); // Genel sonucu döndür
}

/**
 * @brief Programın ana giriş noktası.
 * Komut satırı argümanlarını kontrol eder ve ilgili işleme fonksiyonunu çağırır.
 *
 * @param argc Argüman sayısı.
 * @param argv Argüman dizisi.
 * @return int Programın çıkış durumu (0: başarı, 1: hata).
 */
int	main(int argc, char **argv)
{
	int	status; // Programın genel çıkış durumu

	status = 0;
	if (argc == 1)
	{
		// Argüman yoksa standart girdiden oku
		status = process_single_input(0); // 0: stdin dosya tanıtıcısı
	}
	else
	{
		// Argüman varsa dosyaları işle
		status = process_multiple_files(argc, argv);
	}
	return (status); // Programın durum koduyla çık
}
