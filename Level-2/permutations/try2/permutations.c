#include <stdio.h>

/*
- Algoritmo (en resumen):
	Pasos del algoritmo (en resumen):
	Ordena la cadena (por ejemplo, con bubble sort).
	Usa una función recursiva para permutar:
	En cada llamada, intercambia el carácter actual por los siguientes, llama recursivamente para las siguientes posiciones, y luego deshace el swap.
	Cuando llegues al final, imprime la permutación.
	Imprime cada permutación con puts o write.
	
- ¿Qué funciones necesitas?
	Una para ordenar la cadena.
	Una función recursiva para permutar e imprimir.
	Un main que lo junte todo.
*/

// Intercambia dos caracteres
static void swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

// Ordena la cadena en orden alfabético (bubble sort recursivo)
static void sort_rec(char *str, int start, int len)
{
    if (start >= len - 1)
        return;
    if (str[start] > str[start + 1])
        swap(&str[start], &str[start + 1]);
    sort_rec(str, start + 1, len);
}

static void sort_string_rec(char *str, int len, int pass)
{
    if (pass >= len - 1)
        return;
    sort_rec(str, 0, len - pass);
    sort_string_rec(str, len, pass + 1);
}

// Esta función imprime todas las permutaciones de str desde l hasta r (sin bucles)
static void permute_rec(char *str, int l, int r, int i)
{
    if (l == r)
    {
        puts(str);
        return;
    }
    if (i > r)
        return;
    swap(&str[l], &str[i]);
    permute_rec(str, l + 1, r, l + 1);
    swap(&str[l], &str[i]);
    permute_rec(str, l, r, i + 1);
}

int main(int argc, char **argv)
{
    // Implementación aquí: imprimir todas las permutaciones en orden alfabético
    char *str;
    int len;
    if (argc != 2)
        return (1);
    len = strlen(argv[1]);
    str = malloc(len + 1);
    if (!str)
        return (1);
    strcpy(str, argv[1]);
    sort_string_rec(str, len, 0);     // Ordena la cadena recursivamente
    permute_rec(str, 0, len - 1, 0); // Genera permutaciones sin bucles
    free(str);
    return 0;
}
