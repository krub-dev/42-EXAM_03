#include "broken_gnl.h"
#include <stdbool.h>
// s = b
char *ft_strchr(char *s, int c)
{
    int i = 0;
	if (s == NULL)
		return NULL;
    while (s[i] != '\0')
	{
		if (s[i] == c)
			return &s[i];
		i++;
	}
	return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;
	
    while (i < n)
	{
        ((char*)dest)[i] = ((char*)src)[i];
		i++;
	}
	
	printf("HA LLEGADO MEMCPY\n");
    return dest;
}

size_t ft_strlen(char *s)
{
    size_t i = 0;
	if (!s)
		return 0;
    while (s[i])
	{
		i++;
	}
	printf("HA LLEGADO STRLEN\n");
    return (i);
}

// s1 = ret // s2 = b // size2 = size(b)
char  *str_append_mem(char *s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(s1);
    char *tmp = malloc(size2 + size1 + 1);
    if (!tmp)
	{
        return NULL;
	}
	if (s1)
	{
	    ft_memcpy(tmp, s1, size1);
	}
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
    free(s1);
	s1 = tmp;
	tmp = NULL;
	printf("\n\n%s\n", s1);
    return s1;
}

/*int str_append_str(char **s1, char *s2)
{
    return str_append_mem(s1, s2, ft_strlen(s2));
}*/
/*
void *ft_memmove(void *dest, const void *src, size_t n)
{
    if (dest > src)
        return ft_memcpy(dest, src, n);
    else if (dest == src)
        return dest;
    size_t i = ft_strlen((char*)src) - 1;
    while (i >= 0)
    {
        ((char*)dest)[i] = ((char*)src)[i];
        i--;
    }
    return dest;
}*/

char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE + 1];
    char *ret = NULL;
	int read_ret = 0;
	char *tmp = NULL;
	
	(void)fd;
	tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (b[0] == '\0')
		{
			read_ret = read(fd, b, BUFFER_SIZE);
			tmp = ft_strchr(b, '\n');
		}
		if (!tmp)
		{
			ret = str_append_mem(ret, b, ft_strlen(b));
			printf("ANTES DE RETURN\n%s", ret);
			return ret;
		}
	}
	/*while (!tmp)
    {

        if (!str_append_mem(&ret, b, ft_strlen(b)))
            return NULL;
        read_ret = read(fd, b, BUFFER_SIZE);
        if (read_ret == -1)
            return NULL;
        b[read_ret] = '\0';
    }
    if (!str_append_mem(&ret, b, (ft_strlen(tmp) - ft_strlen(b)) + 1))
    {
        free(ret);
        return NULL;
    }*/
    return ret;
}

int main(int argc, char **argv){

	int fd;
	char *buffer;
	(void)argv;
	(void)argc;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return 1;
	//get_next_line(fd);

	//if (argc != 2)
	//	return 1;

	buffer = get_next_line(fd);
	printf("%s", buffer);
	free(buffer);
	/*while (1)
	//{	
		buffer = get_next_line(fd);
		if (buffer == NULL)
		{
			close(fd);
			//break ;
		}
		else
			printf("%s", buffer);


	//}*/


	return 0;
}
