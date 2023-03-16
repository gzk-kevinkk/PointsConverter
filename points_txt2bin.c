#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv)
{
    int i, j;
    char *filename = "case2";
    char *out_filename = "case2_bin";
    FILE *f;
    
    char buf[301], temp[101];
    double *points, x, y, z;
    int num = 0;
    int cnt, cnt_begin;

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
    f = fopen(filename, "r");
    assert(f != NULL);

    
    while (fgets(buf, 300, f))
    {
        if (strcmp(buf, "\n") == 0)
            continue;
        num = atoi(buf);
        break;
    }
    printf("Points num = %d\n", num);
    points = (double *)malloc(sizeof(double) * 3 * num);

    i = 0;
    while (i < num && fgets(buf, 300, f))
    {
        if (strcmp(buf, "\n") == 0)
            continue;
        cnt = 0;
        while (buf[cnt] == ' ' && (cnt < 300))
            cnt++;
        if (cnt == 300)
            continue;
        cnt_begin = cnt;
        while (buf[cnt] != ' ' && (cnt < 300))
        {
            temp[cnt - cnt_begin] = buf[cnt];
            cnt++;
        }
        temp[cnt - cnt_begin] = '\0';
        x = atof(temp);

        while (buf[cnt] == ' ' && (cnt < 300))
            cnt++;
        cnt_begin = cnt;
        while (buf[cnt] != ' ' && (cnt < 300))
        {
            temp[cnt - cnt_begin] = buf[cnt];
            cnt++;
        }
        temp[cnt - cnt_begin] = '\0';
        y = atof(temp);

        while (buf[cnt] == ' ' && (cnt < 300))
            cnt++;
        cnt_begin = cnt;
        while (buf[cnt] != ' ' && (cnt < 300))
        {
            temp[cnt - cnt_begin] = buf[cnt];
            cnt++;
        }
        temp[cnt - cnt_begin] = '\0';
        z = atof(temp);

        points[3 * i] = x;
        points[3 * i + 1] = y;
        points[3 * i + 2] = z;

        ++i;
    }
    fclose(f);

    f = fopen(out_filename, "wb");
    fwrite(&num, sizeof(int), 1, f);
    fwrite(points, sizeof(double), 3 * num, f);
    fclose(f);

    free(points);
    return 0;
}
