#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>


int main()
{
	int data_size;
	FILE *fp;

	fp = fopen("source.b", "rb");

	fseek(fp, 0, SEEK_END);
	data_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	printf("Data size file: %d\n", data_size);
	
	char *binary_code;
	binary_code = malloc(data_size);
	fread(binary_code, data_size, 1, fp);
	fclose(fp);
		
	void *mem = mmap(NULL, data_size, PROT_WRITE | PROT_EXEC,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	memcpy(mem, binary_code, data_size);

	int (*run_code_func) () = mem;

	printf("Run... (%d, %d) result is %d\n", 7, 5, run_code_func());	
	free(binary_code);
	munmap(mem, data_size);

	return 0;
}
