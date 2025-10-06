#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>



/*char *filter(char *str_Tofilter, char* s, size_t pos)
{
	size_t i = 0;
	size_t size_s = strlen(s);
	while(i < size_s)
	{
		str_Tofilter[pos + i] = '*';
		i++;
	}
	return (str_Tofilter);
}*/

int main(int argc, char **argv)
{
    // Aquí tu código.
    // Debes leer de stdin y reemplazar cada aparición de argv[1] por '*'
	char buffer[100000];
	int bytes_read;
//	size_t pos;
	char *ptr;
//	char *filtered;
	int i = 0;
	if (argc != 2)
	{	
		perror("ERROR");
		return 1;
	}
	
	//printf("%zu\n", sizeof(buffer));
	bytes_read = read(0, buffer, sizeof(buffer));
	if (bytes_read < 0)
	{
		perror("ERROR");
		return 1;
	}

	while (1)
	{
		if(!(ptr = (char*)memmem((void*)buffer, strlen(buffer), (void*)argv[1], strlen(argv[1]))))
			break ;
		while (argv[1][i])
		{
			ptr[i] = '*';
			i++;
		}
		i = 0;
		/*
		pos = strlen(buffer) - strlen(ptr);
		filtered = filter(buffer, argv[1], pos);*/
	}

		//*buffer = *ptr;
	printf("%s", buffer);
    return 0;
}
