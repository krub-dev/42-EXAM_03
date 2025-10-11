#include "broken_gnl.h"

char *ft_strchr(char *s, int c)
{
    int i = 0;
	if (!*s)
		return NULL;
    while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == c)
		return s + i;
	else
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
	return dest;
}

size_t ft_strlen(char *s)
{
    size_t i = 0;
	
	if(!s)
		return 0;
    while (s[i])
        i++;
    return (i);
}

char* str_append_mem(char *s1, char *s2, size_t size2)
{
    size_t size1 = ft_strlen(s1);
    char *tmp = malloc(size2 + size1 + 1);
    if (!tmp)
		return (NULL);

	if (s1)
		ft_memcpy(tmp, s1, size1);

    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
    free(s1);
    s1 = tmp;
    return s1;
}


void ft_memmove(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i + 1];
		i++;
	}
	
	while (dest[i])
	{
		dest[i] = '\0';
		i++;
	}
	dest[i] = '\0';
}

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = ""; // Resto
    char *ret = NULL;	// Línea a construir
    char *tmp = NULL;	// Puntero a salto
	int read_ret;

    tmp = ft_strchr(b, '\n');
	while (!tmp)
    {
		// Acumulamos lo que hay en b antes de leer mas o se pierde
        ret = str_append_mem(ret, b, ft_strlen(b));
		if (!ret)    
			return NULL;
        
		read_ret = read(fd, b, BUFFER_SIZE);
		
		if (read_ret < 0)
		{
			free(ret);
			return NULL;
		}
		else if (read_ret == 0)
		{
			b[0] = '\0'; // Limpia buffer
			// Si hay algo acumulado, lo devolvemos
			if (ft_strlen(ret) > 0)
				return ret;
			free(ret);
			return NULL;
		}
		
		// Sale del bucle porque tmp apunta a salto
		b[read_ret] = '\0';
		tmp = ft_strchr(b, '\n');
    }
    
	ret = str_append_mem(ret, b, tmp - b + 1);
	ft_memmove(b, tmp);
    
	if (!ret)
	{
		free(ret);
		return NULL;
    }
    return ret;
}

// Main provisional para testear, NO se entrega
int main(int argc, char** argv)
{
	int fd = open(argv[1], O_RDONLY);
	char *line;
	(void)argc;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}
