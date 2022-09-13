#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>


int main()
{
	int data_size;
	FILE *fp;

	// Открываем файл с данными
	fp = fopen("source.b", "rb");

	// Определяем размер данных
	fseek(fp, 0, SEEK_END);
	data_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	printf("Data size file: %d\n", data_size);
	
	// Загружаем код
	char *binary_code;
	binary_code = malloc(data_size);
	fread(binary_code, data_size, 1, fp);
	fclose(fp);
	
	// Выделяем отдельный регион исполняемой памяти
	void *mem = mmap(NULL, data_size, PROT_WRITE | PROT_EXEC,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	memcpy(mem, binary_code, data_size);

	// Присваиваем адрес загруженного кода указателю на функцию
	int (*run_code_func) () = mem;

	printf("Run... (%d, %d) result is %d\n", 7, 5, run_code_func());
	
	// Очищаем данные
	free(binary_code);
	munmap(mem, data_size);

	return 0;
}
