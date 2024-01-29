#include <stdio.h>
#include <stdlib.h>

struct UnionFind
{
    int *parent;
    int *size;
    int N;
};

//#define DEBUGG
#ifdef DFASTIO
#define scanf scanf_fastio
#define printf printf_fastio
#endif

void initUnionFind(struct UnionFind *uf, int n)
{
    uf->N = n;

    // Allocate memory for the parent array
    uf->parent = (int *)malloc(n * sizeof(int));
    if (uf->parent == NULL)
    {
        fprintf(stderr, "Error: Memory allocation for the parent array failed.\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the size array
    uf->size = (int *)malloc(n * sizeof(int));
    if (uf->size == NULL)
    {
        // Clean up memory allocated so far
        free(uf->parent);
        fprintf(stderr, "Error: Memory allocation for the size array failed.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize arrays
    for (int iii = 0; iii < n; iii++)
    {
        uf->parent[iii] = iii;
        uf->size[iii] = 1;
    }
}

int find(struct UnionFind *uf, int x)
{
    int root = x;
    while (uf->parent[root] != root)
    {
        uf->parent[root] = uf->parent[uf->parent[root]]; // Push up the node by one level
        root = uf->parent[root];
    }

    return root;
}

void merge(struct UnionFind *uf, int x, int y)
{
    int root_x = find(uf, x);
    int root_y = find(uf, y);
    if (uf->size[root_y] > uf->size[root_x])
    {
        uf->parent[root_x] = root_y;
        uf->size[root_y] += uf->size[root_x];
    }
    else
    {
        uf->parent[root_y] = root_x;
        uf->size[root_x] += uf->size[root_y];
    }
}

void destroyUnionFind(struct UnionFind *uf)
{
    free(uf->parent);
    free(uf->size);
}

#ifdef DFASTIO
#include <stdarg.h>

char buff[1 << 20]; // Adjust buffer size as needed

int scanf_fastio(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int result = vscanf(format, args);
    va_end(args);
    return result;
}

int printf_fastio(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int result = vsprintf(buff, format, args);
    va_end(args);
    return result;
}
#endif

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <num_lines> <num_students> <input_file>\n", argv[0]);
        return 1;
    }

    int num_lines = atoi(argv[1]);
    int num_students = atoi(argv[2]);
    const char *input_file = argv[3];

    struct UnionFind uf;
    initUnionFind(&uf, num_students);

    // Open the file
    FILE *file = fopen(input_file, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Read lines from the file
    for (int i = 0; i < num_lines; i++)
    {

        int value1, value2;
        char function;
        int result = fscanf(file, " %c %d %d", &function, &value1, &value2);
        if (result != 3)
        {
            fprintf(stderr, "Error reading input from file.\n");
            break; // or return 1; depending on your design
        }

#ifdef DEBUGG
        printf("%d\n", i);
        printf("%c ", function);
        printf("%d %d\n", value1, value2);
#endif

        if (function == 'j')
        {
            merge(&uf, value1, value2);

#ifdef DEBUGG
            printf("merged %d %d\n", value1, value2);
#endif
        }
        else if (function == '?')
        {
            int result1 = find(&uf, value1);
            int result2 = find(&uf, value2);

            if (result1 == result2)
            {
                printf("T\n");
            }
            else
            {
                printf("F\n");
            }
        }
        else
        {
            printf("Unknown function type '%c'\n", function);
        }
    }

    // Close the file
    fclose(file);

    destroyUnionFind(&uf);

#ifdef DEBUGG
    printf("%s", buff);
#endif

    return 0;
}
