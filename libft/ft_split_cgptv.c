#include <stdlib.h>

// Función auxiliar para contar cuántas palabras hay en la cadena 's' delimitada por el carácter 'c'
static int count_words(const char *s, char c)
{
    int count = 0;
    int in_word = 0;

    while (*s)
    {
        if (*s != c && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if (*s == c)
            in_word = 0;
        s++;
    }
    return count;
}

// Función auxiliar para obtener la longitud de una palabra en la cadena 's' comenzando en un índice
static int word_len(const char *s, char c)
{
    int len = 0;

    while (s[len] && s[len] != c)
        len++;
    return len;
}

// Función auxiliar para liberar la memoria en caso de error
static void free_memory(char **result, int i)
{
    while (i > 0)
    {
        free(result[i - 1]);
        i--;
    }
    free(result);
}

// Función principal: ft_split
char **ft_split(char const *s, char c)
{
    int i = 0;
    int j;
    int len;
    char **result;

    if (!s)
        return NULL;

    // Reservar memoria para el array de punteros (cantidad de palabras + 1 para NULL final)
    result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
    if (!result)
        return NULL;

    // Iterar sobre la cadena y dividirla en palabras
    while (*s)
    {
        if (*s != c)
        {
            len = word_len(s, c);
            result[i] = (char *)malloc((len + 1) * sizeof(char));
            if (!result[i])
            {
                free_memory(result, i);
                return NULL;
            }
            j = 0;
            while (j < len)
                result[i][j++] = *s++;
            result[i++][j] = '\0'; // Terminar la cadena con un '\0'
        }
        else
            s++;
    }
    result[i] = NULL; // Terminar el array con un puntero NULL
    return result;
}
/*
Explicación del código:
count_words: Esta función cuenta cuántas palabras están presentes en la cadena s, delimitadas por el carácter c. Define una "palabra" como una secuencia de caracteres que no contiene el delimitador c.
word_len: Esta función retorna la longitud de una palabra (secuencia de caracteres no delimitada por c) desde una posición en la cadena s.
free_memory: Esta función libera la memoria previamente asignada si hay un error en alguna reserva, evitando fugas de memoria.
ft_split:
Primero cuenta cuántas palabras tendrá el array de strings.
Luego, itera sobre la cadena s, extrayendo cada palabra (los caracteres hasta encontrar el delimitador) y asignando memoria para esa palabra.
Al final, se asegura de que el array de strings termine con un puntero NULL.
*/

#include <stdio.h>

int main()
{
    char **result = ft_split("Hola esto es una prueba", ' ');

    for (int i = 0; result[i] != NULL; i++)
    {
        printf("Palabra %d: %s\n", i, result[i]);
        free(result[i]); // Liberar cada palabra después de usarla
    }
    free(result); // Liberar el array de punteros

    return 0;
}