/* 
Summary del flujo lógico del código ft_scanf

1 - El usuario llama a ft_scanf
Ejemplo: ft_scanf("%d%c%s", &d, &c, s);
Se le pasa un string de formato y variables donde guardar los resultados.

2 - Se inicializa el sistema de argumentos variables
Usa va_list para poder acceder a los argumentos que vienen después del formato.

3 - Se llama a ft_vfscanf para procesar el formato y leer la entrada
Siempre lee desde stdin (el teclado).

4 - Recorre el string de formato carácter a carácter
Si encuentra un %, determina qué tipo de conversión es (d, c, s).
Si hay espacios en el formato, los salta en la entrada.
Si hay caracteres literales, los espera en el input (por ejemplo, un guion o coma).

5 - Cuando encuentra una conversión:
%d: Salta espacios, lee caracteres que formen un entero (con posible signo), y guarda el valor en la variable pasada.
%c: Lee exactamente un carácter y lo guarda en la variable pasada.
%s: Salta espacios, lee una palabra (hasta espacio), y la guarda en el array pasado.
Cada conversión exitosa suma 1 al contador de conversiones.

6 - Si ocurre un error de lectura o una conversión falla, se detiene
Por ejemplo, si esperas un número y el usuario teclea una letra, no se suma esa conversión.

7 - Devuelve el número de conversiones exitosas
Igual que el comportamiento estándar de scanf.

8 - Las variables que pusiste como argumentos ahora contienen los valores leídos del input

Puedes usarlas para lo que necesites en tu programa.
¿Qué hace cada parte?
- match_space: Salta espacios en el input antes de leer valores.
- match_char: Comprueba si el siguiente carácter coincide con uno esperado (del formato).
- scan_char: Lee y guarda un carácter.
- scan_int: Lee y guarda un entero con signo.
- scan_string: Lee y guarda una palabra (string sin espacios).
- match_conv: Decide qué función de lectura usar según la conversión detectada en el formato.
- ft_vfscanf: Recorre el formato, llama a las funciones de lectura y cuenta las conversiones.
- ft_scanf: Interfaz pública que prepara los argumentos variables y llama a la función principal.

En resumen:
- ft_scanf interpreta el formato, lee datos de la entrada estándar según ese formato, almacena los valores en variables y devuelve cuántas conversiones ha hecho correctamente.
*/

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

// Salta espacios en el input (entrada estándar)
int match_space(FILE *f)
{
	int c;
	while ((c = fgetc(f)) != EOF)
	{
		if (!isspace(c)) // Si no es espacio
		{
			ungetc(c, f); // Devuelve el carácter leído para procesarlo más adelante
			break;
		}
	}
    return (0);
}

// Comprueba si el siguiente carácter en el input es igual a 'c'
int match_char(FILE *f, char c)
{
	int ch = fgetc(f); // Lee un carácter
	if (ch == c)
		return (1); // Es igual al esperado
	if (ch != EOF)
		ungetc(ch, f); // Si no es igual, lo devuelve al buffer
    return (0);
}

// Lee exactamente un carácter y lo guarda en la variable correspondiente
int scan_char(FILE *f, va_list ap)
{
	int c = fgetc(f);
	if (c == -1)
		return (0); // Error de lectura
	char *dest = va_arg(ap, char *); // Siguiente argumento (donde guardar el char)
	*dest = c; // Guarda el carácter leído
    return (1); // Conversión exitosa
}

// Lee un número entero (con signo) y lo guarda en la variable correspondiente
int scan_int(FILE *f, va_list ap)
{
	int value = 0;
	int sign = 1;
	int c = fgetc(f);
	if (c == EOF)
		return (0); // Error de lectura
	if (c == '-' || c == '+') // Detecta signo
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f); // Lee el siguiente carácter después del signo
	}
	if (c == EOF)
		return (0);
	if (!isdigit(c)) // Si lo siguiente no es un dígito, no es válido
	{
		ungetc(c, f);
		return (0);
	}
	while (isdigit(c)) // Procesa todos los dígitos
	{
		value = 10 * value + c - '0'; // Acumula el valor
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f); // Devuelve el último carácter leído si no era dígito
	int *dst = va_arg(ap, int *); // Siguiente argumento (donde guardar el int)
	*dst = value * sign; // Guarda el valor leído con el signo
    return (1); // Conversión exitosa
}

// Lee una palabra (string sin espacios) y la guarda en la variable correspondiente
int scan_string(FILE *f, va_list ap)
{
	int i = 0;
	char *dst = va_arg(ap, char *); // Siguiente argumento (donde guardar el string)
	int c = fgetc(f);

	if (c == -1)
		return (0); // Error de lectura
	dst[i++] = (char)c; // Guarda el primer carácter
	while ((c = fgetc(f)) != EOF && !isspace(c)) // Sigue leyendo mientras no haya espacio
	{
		dst[i++] = (char)c; // Guarda cada carácter
	}
	if (c != EOF)
		ungetc(c, f); // Si termina por espacio, lo devuelve
	dst[i] = 0; // Termina el string con '\0'
	return (1); // Conversión exitosa
}

// Realiza la conversión según el tipo (%c, %d, %s)
int match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap); // Lee un carácter
		case 'd':
			match_space(f); // Salta espacios antes de leer el número
			return scan_int(f, ap); // Lee un entero
		case 's':
			match_space(f); // Salta espacios antes de leer la palabra
			return scan_string(f, ap); // Lee un string
		case EOF:
			return -1;
		default:
			return -1;
	}
}

// Procesa el formato y aplica las conversiones correspondientes
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0; // Número de conversiones exitosas

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%') // Encuentra conversión
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break; // Si falla, termina
			else
				nconv++; // Conversión exitosa
		}
		else if (isspace(*format)) // Si hay espacio en el formato
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1) // Si debería haber un carácter literal
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv; // Devuelve el número de conversiones exitosas
}

// Versión pública: inicializa la lista de argumentos variables y llama a ft_vfscanf sobre stdin
int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

#include <stdio.h>

// Ejemplo de uso
int main(void)
{
	printf("Enter a character: ");
	int d;
	char c;
	char s[100];
	ft_scanf("%d%c%s", &d, &c, s); // Lee un entero, un carácter y un string
	printf("d: %d\nc: %c\ns: %s\n", d, c, s); // Muestra lo leído
}
