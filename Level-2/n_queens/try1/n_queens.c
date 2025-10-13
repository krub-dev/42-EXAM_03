#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Funcion llamada en solve que determina si la posicion donde colocar la reina es valida o no (estudiar)
int is_safe(int *positions, int current_col, int current_row)
{
	int prev_col = 0;
	while (prev_col < current_col)
	{
		int prev_row = positions[prev_col];
		if (prev_row == current_row ||
				prev_row - prev_col == current_row - current_col ||
				prev_row + prev_col == current_row + current_col)
			return 0; // No es valida
		prev_col++;
	}
	return 1; // Es valida
}

// Imprime las posiciones de las n queens posibles en cada "tablero"
void print_positions(int *positions, int n)
{
	int i = 0;
	while (i < n)
	{
		if (i > 0) // Para que no imprima el espacio al principio
			printf(" "); 
		printf("%d", positions[i]); // Pos de queen valida
		i++;
	}
	printf("\n"); // Salto entre soluciones
}

// Funcion recursiva que prueba cada posibilidad, haciendo backtracking si no es valido
void solve(int *positions, int col, int n)
{
	if (col == n) // CASO BASE, todo comprobado, printamos
	{
		print_positions(positions, n);
		return;
	}
	int row = 0; // Reiniciamos fila a 0 para comprobar otra columna (col + 1 recursiva)
	while (row < n)
	{
		if (is_safe(positions, col, row)) // Devuelve 1 si es valida (al ser if 1 = true)
		{
			positions[col] = row; // Si es valida, guardamos la posicion en el array a printar (positions)
			solve(positions, col + 1, n); // Llamamos a la siguiente posibilidad, col + 1
		}
		row++; // Iteramos comprobando
	}
}

int main(int argc, char **argv)
{
	if (argc != 2 && argv[1][0] == '-') // Cubre negativo, en principio no hace falta
		return 1;
	
	int n = atoi(argv[1]); // atoi usado, permitido
	if (n == 1 || n == 0) // Casos especificos (Printan 0, no se por que)
		return 1;
	int *positions = malloc(sizeof(int) * n); // Alocamos n * 4 (sizeof de int)	
	if (!positions)
		return 1;

	solve(positions, 0, n); // Llamada a func. recursiva, backtracking
	free(positions); // Liberamos antes de salir

	return 0;
}
