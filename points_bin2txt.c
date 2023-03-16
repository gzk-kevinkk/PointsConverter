#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv)
{
    int i;
    char *filename = "case2_bin";
    char *out_filename = "case2_txt";
    FILE *f;
    
    double *points;
    int num = 0;

    if (argc >= 3){
        for (i = 1; i < argc - 1; i++){
            if (strcmp(argv[i], "-in") == 0){
                filename = argv[i + 1];
            }
            else if(strcmp(argv[i], "-out") == 0){
                out_filename = argv[i + 1];
            }
        }
    }
    printf("Input file: %s\n", filename);
    printf("Output file: %s\n", out_filename);
    f = fopen(filename, "rb");
    assert(f != NULL);

    fread(&num, sizeof(int), 1, f);
    printf("Coefs num = %d\n", num);
    points = (double *)malloc(sizeof(double) * 3 * num);
    fread(points, sizeof(double), 3 * num, f);
    fclose(f);

    f = fopen(out_filename, "w");
    fprintf(f, "%d\n", num);
    for (i = 0; i < num; i++)
    {
        fprintf(f, "%16.15le %16.15le %16.15le\n", points[3 * i], points[3 * i + 1], points[3 * i + 2]);
    }
    fclose(f);

    free(points);
    return 0;
}