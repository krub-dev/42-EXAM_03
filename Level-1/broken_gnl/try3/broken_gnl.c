#include "broken_gnl.h"

// Comprueba que s exista y la iteracion es de s[i] != '\0'
char *ft_strchr(char *s, int c)
{
	int i = 0;
	if(!s)
		return NULL;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == c)
		return s + i;
	else
		return NULL;
}

// Se recorre hacia adelante
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

// Funciona de por si pero la hice mas legible
size_t ft_strlen(char *s)
{
	size_t i = 0;
	while (s[i])
		i++;
	return (i);
}

// NO cambia nada, porque tmp[0] = 0 es lo mismo que te tmp[0] = '\0'
int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 0;
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return 1;
}

int str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

// Cambia: ahora copia exactamente 'n' bytes (no usa strlen), 
// y copia hacia atrás si hay solapamiento.
void *ft_memmove(void *dest, const void *src, size_t n)
{

	/*
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
	*/

	char *tmp;
	size_t i;

	// Si el origen y el destino son iguales, o n es 0, no hay nada que mover
	if (dest == src || n == 0)
		return dest;

	// Reservamos memoria temporal para copiar los datos
	tmp = malloc(n);
	if (!tmp) // Si falla malloc, devolvemos NULL
		return NULL;

	// Copiamos los n bytes desde src a la memoria temporal
	i = 0;
	while (i < n)
	{
		tmp[i] = ((char *)src)[i];
		i++;
	}

	// Copiamos los n bytes desde la memoria temporal al destino
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = tmp[i];
		i++;
	}

	// Liberamos la memoria temporal
	free(tmp);

	// Devolvemos el puntero al destino
	return dest;
}

char *get_next_line(int fd)
{
	// Buffer estatico para guardar el resto
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = malloc(1); // Lo que devolvemos, lo iniciamos como string vacio
	int read_ret;
	char *tmp;

	// Si el malloc falla, salimos on NULL
	if (!ret)
		return NULL;
	// Hacemos que sea un string vacio, primer char
	ret[0] = '\0';

	while (1)
	{
		// Busca si hay salto de linea en buffer b
		tmp = ft_strchr(b, '\n');
		if (tmp)
		{
			// Si hay salto de line, a;ade a ret desde b hasta el salto de linea incluido
			if (!str_append_mem(&ret, b, tmp - b + 1))
			{
				free(ret); // Libera memoria en caso de error
				return NULL;
			}
			// Mueve el contenido despues de salto de linea de buffer b
			ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
			// Si ret sigue siendo cadena vac'ia, lo liberamos y devolvemos NULL
			if (ret[0] == '\0')
			{
				free(ret); // Lbera memoria en caso de error
				return NULL;
			}
			return ret;
		}
		// Si no hay salto de línea en b, añade todo el buffer a ret
		if (!str_append_str(&ret, b))
		{
			free(ret); // Libera memoria en caso de error
			return NULL;
		}
		// Lee más datos del descriptor de fichero
		read_ret = read(fd, b, BUFFER_SIZE);
		// Si read devuelve -1 (error) o 0 (EOF)
		if (read_ret <= 0)
		{	
			// Limpia buffer estatico
			b[0] = '\0';
			// Si hay error de lectura o ret sigue vacío (no hay más líneas), libera y sale
			if (read_ret == -1 || !*ret)
			{
				free(ret);
				return NULL;
			}
			// Devuelve lo que queda en ret (última línea sin salto de línea)
			return ret;
		}
		// Añade el final de string al buffer leído
		b[read_ret] = 0;

	}
}

// Main provisional para testear, NO se entrega
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}
