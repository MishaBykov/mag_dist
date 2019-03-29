// This program reads polytopes from all4polytopes...txt,
// find the incidence matrices and some properties

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <windows.h>
#include <limits.h>

// Максимальная длина строки входного файла
#define LINE_SIZE 2048
// Размерность многогранников
#define DIM 4
// Максимальное число вершин
#define MAX_VERT 10
// Максимальной число фасет (гиперграней)
#define MAX_FACET 128

// Greatest common divisor
int gcd (int a, int b) {
    return b ? gcd(b, a % b) : a;
}

// Выясняем: верно ли, что все риджи -- треугольники?
// Ридж -- пересечение двух фасет
bool is_simplicial2(int64_t *matrix, int rows, int cols, FILE *outf){
    for (int i = 0; i < rows - 1; i++)
        for (int j = i+1; j < rows; j++){
            int x = matrix[i] & matrix[j];
            int num = 0;
            for (;x != 0; x >>= 1)
                num += x & 1;
            if (num > 3){
                //printf (" Not simplicial2: %d %d", i, j);
                //fprintf (outf, "Not simplicial2: %d %d\n", i, j);
                return false;
            }    
        }
    return true;        
}

// Транспонируем матрицу
void transpose(int64_t *source, int rows, int cols, int64_t *transposed){
    for (int j = 0; j < cols; j++){
        transposed[j] = 0;
        for (int i = 0; i < rows; i++)
            transposed[j] |= ((source[i] >> j) & 1) << i;
    }        
}

int read_firsching(char *buffer, int *fvector, int64_t **poly){
	char *pch = buffer;
	// Считываем f-вектор
    for (int i = 0; i <= DIM; i++)
        fvector[i] = strtol (pch+1, &pch, 10);
    // Сохраняем координаты вершин в массив poly
    pch--;
    int64_t lcm = 1; // The least common multiple for denominators of coordinates
    for (int i = 0; i < fvector[0]; i++){
        pch += 3;
        //printf (", (");
        for (int j = 0; j < DIM; j++){
            // Считываем числитель дроби
            poly[i][j] = strtol (pch+1, &pch, 10);
            //printf (" %2d", poly[i][j]);
            poly[i][j+DIM] = 1;
            if (pch[0] == '/'){
                // Считываем знаменатель дроби
                poly[i][j+DIM] = strtol (pch+1, &pch, 10);
                // Находим наименьшее общее кратное
				int mult = poly[i][j+DIM] / gcd(lcm, poly[i][j+DIM]);
				if (lcm >= LLONG_MAX / mult){
					printf ("ERROR: too big number!!!\n");
					return 1;
				}	
                lcm *= mult;
            }    
        }
        //printf (")");
    }
    //printf (" lcm = %d", lcm);
	// Делаем все числа целыми
    for (int i = 0; i < fvector[0]; i++){
        for (int j = 0; j < DIM; j++){
            poly[i][j] *= lcm / poly[i][j+DIM];
        }    
    }        
	return 0;
}

int eval_incmatrix (int *fvector, int64_t **poly, int64_t *facet_vertex, FILE *outf){
    // Сохраняем считанный многогранник в формате Avis-Fukuda в файл p.ext
    FILE *curf = fopen("p.ext", "w");
    fprintf (curf, "begin\n%d %d", fvector[0], DIM+1);
    for (int i = 0; i < fvector[0]; i++){
        fprintf (curf, "\n 1");
        for (int j = 0; j < DIM; j++){
            fprintf (curf, " %3d", poly[i][j]);
        }    
    }        
    fprintf (curf, "\nend\n");
    fclose(curf);
    // Обрабатываем p.ext с помощью программы skeleton64f.exe
    system("skeleton64f.exe p.ext --avisfukudaformat --silence --nologinfile --extinc --edges --ridges");
    // Открываем файл p.ext.out -- результат работы skeleton64f.exe
    FILE *skelf = fopen("p.ext.out", "r");
    if (skelf == NULL){
        fprintf (outf, "ERROR: Cann't open file p.ext.out\n");
        return 1;
    }
    // facet_vertex -- матрица инциденций фасет-вершин
    // Строка матрицы -- 64-битное целое (строка из 64-х нулей и единиц)
    //int64_t facet_vertex[MAX_FACET];
    // Считываем информацию из p.ext.out
	char buffer[LINE_SIZE];
	char *pch;
    while (fgets (buffer, LINE_SIZE, skelf) != NULL){
        if (memcmp(buffer, "* Extreme rays:", 15) == 0){
            fgets (buffer, LINE_SIZE, skelf);
            // Число фасет
            int facets = strtol (buffer, &pch, 10);
            if (facets != fvector[DIM-1]){
                fprintf (outf, "ERROR: skeleton facets = %d\n", facets);
                fvector[DIM-1] = facets;
            }
            continue;
        }
        if (memcmp(buffer, "* Edges:", 8) == 0){
            fgets (buffer, LINE_SIZE, skelf);
            // Число риджей
            int ridges = strtol (buffer, &pch, 10);
            if (ridges != fvector[DIM-2]){
                fprintf (outf, "ERROR: skeleton ridges = %d\n", ridges);
                fvector[DIM-2] = ridges;
            }
            continue;
        }
        if (memcmp(buffer, "* Rays-to-inequalities incidence:", 33) == 0){
            int incnum = 0;
            //fprintf (outf, "Incidence:\n");
            // Матрица инциденций фасет-вершин
            for (int i = 0; i < fvector[DIM-1]; i++){
                fgets (buffer, LINE_SIZE, skelf);
                int fnum = strtol (buffer, &pch, 10);
                if (fnum != i+1){
                    fprintf (outf, "ERROR: fnum = %d != %d\n", fnum, i);
                }
                pch++;
                facet_vertex[i] = 0;
                int vnum = 0;
                int v;
                while (v = strtol (pch, &pch, 10)){
                    facet_vertex[i] |= (int64_t)1 << (v-1);
                    vnum++;
                }
                incnum += vnum;
                // Является ли многогранник пирамидой?
                //if (vnum == fvector[0] - 1) is_pyramid = true;
                // Является ли многогранник симплициальным?    
                //if (vnum != DIM) is_simplicial = false;
                // Сохраняем одну строку матрицы инциденций в файл    
                //for (v = 0; v < fvector[0]; v++)
                //    fprintf (outf, " %d", ((facet_vertex[i]) >> v) & 1);
                //fprintf (outf, "\n");
            }    
            if (incnum != fvector[DIM])
                fprintf (outf, "ERROR: skeleton incnum = %d\n", incnum);
            continue;
        }
        if (memcmp(buffer, "* Ridges:", 9) == 0){
            fgets (buffer, LINE_SIZE, skelf);
            // Число ребер
            int edges = strtol (buffer, &pch, 10);
            if (edges != fvector[1]){
                fprintf (outf, "ERROR: skeleton edges = %d\n", edges);
                fvector[1] = edges;
            }
            continue;
        }
    }
    fclose(skelf);
	return 0;
}


// Write f-vector into file and some additional information
int write_fvec (FILE *outf, int *fvector, int simpliciality, int nincs, int minf_in_v, char *buffer){
	fprintf (outf, "%s", buffer);
	fprintf (outf, "v: %d, f: %d, d: %d, ", fvector[0], fvector[DIM-1], DIM);
    //if (is_pyramid) fprintf (outf, "pyramid, ");
    //if (simpliciality >= DIM - 1)
    //    fprintf (outf, "simplicial, ");
	//else
    fprintf (outf, "sc=%d, ", simpliciality);
    if (fvector[0] * (fvector[0] - 1) == 2 * fvector[1])
        fprintf (outf, "2-neighborly, ");
    fprintf (outf, "inc=%2d, ", nincs);
    fprintf (outf, "min(f in v)=%d\n", minf_in_v);
	fprintf (outf, "f-vector:");
	for (int i = 0; i < DIM; i++){
		fprintf (outf, " %d", fvector[i]);
	}
	fprintf (outf, "\n");

	return 0;
}

// The argument of a program -- file with combinatorial types of 4-polytopes from
// https://page.mi.fu-berlin.de/moritz/polytopes
// For example: ftp://ftp.imp.fu-berlin.de/pub/moritz/classification/all4polytopes8vertices.txt
int main (int argc, char *argv[])
{
 	if (argc < 2){
		printf("Usage: 4poly [file name]\n");
		return 0;
	}

    FILE *inf = fopen(argv[1], "r");
	if (inf == NULL){
		printf ("ERROR: Cann't open file %s\n", argv[1]);
		return 1;
	}
	printf ("Input from %s\n", argv[1]);

    // Результаты работы сохраняем в файл с расширением out
	char outfname[64];
	sprintf (outfname, "%s.out", argv[1]);
	FILE *outf = fopen(outfname, "w");
	if (outf == NULL){
		printf ("ERROR: Cann't open file %s\n", outfname);
		return 1;
	}
	printf ("Open file %s for writing\n", outfname);
    
	char buffer[LINE_SIZE];
	char *pch;
    int fvector[DIM+1];
    int64_t arr[MAX_VERT][2*DIM];
    int64_t *poly[MAX_VERT];
	for (int k = 0; k < MAX_VERT; k++) poly[k] = arr[k];
    int min_facets = MAX_FACET;
    int max_facets = 0;
    
    // Читаем входной файл построчно
    while (fgets (buffer, LINE_SIZE, inf) != NULL){
		if (read_firsching(buffer, fvector, poly)){
			fprintf (outf, "ERROR: too big least common divisor in %s!!!\n", buffer);
		}
        /*    
        if (fvector[1] + fvector[2] + 2 * (fvector[0] + fvector[3]) == 2 * fvector[4]){
            fprintf (outf, "Ziegler's condition is true!\n");
            printf ("Ziegler's condition is true!\n");
            Sleep(1000); // sleep for 1 sec
        }
        */
        // Если нас интересуют только 2-смежностные многогранники
//        if (fvector[0] * (fvector[0] - 1) != 2 * fvector[1])
//            continue;
        
        // Записываем считанную строку в выходной файл
 //       fprintf (outf, "%s", buffer);
 //       fprintf (outf, "This is 2-neighborly polytope!\n");

		// Находим матрицу инциденций с помощью skeleton
		int64_t facet_vertex[MAX_FACET];
		eval_incmatrix (fvector, poly, facet_vertex, outf);
        // Результаты тестирования сохраняем в файл .out
//        if (2*fvector[1] == fvector[0]*(fvector[0] - 1))
//            fprintf (outf, "2-neighborly\n");
//        if (2*fvector[DIM-2] == fvector[DIM-1]*(fvector[DIM-1] - 1))
//            fprintf (outf, "Dual 2-neighborly\n");
        //if (is_simplicial) fprintf (outf, "Simplicial\n");
        //if (is_pyramid) fprintf (outf, "Pyramid\n");
        // Проверяем, являются ли все риджи треугольниками    
        bool is_s2 = is_simplicial2(facet_vertex, fvector[DIM-1], fvector[0], outf);
		if (!is_s2)
			continue;
			
        if (min_facets > fvector[DIM - 1])
            min_facets = fvector[DIM - 1];
        if (max_facets < fvector[DIM - 1])
            max_facets = fvector[DIM - 1];
		int i, j, nincs, minf_in_v;
		for (i = 0, nincs = 0; i < fvector[DIM-1]; i++)
			nincs += __builtin_popcountll (facet_vertex[i]); // Подсчитываем число единичек (вершин в фасете)
		if (nincs != fvector[DIM])
			fprintf (outf, "ERROR: nincs == %d\n", nincs);
		// Подсчитываем число фасет в вершинах
		int f_in_v[MAX_VERT];
		for (j = 0; j < fvector[0]; j++){
			f_in_v[j] = 0;
			for (i = 0; i < fvector[DIM-1]; i++)
				f_in_v[j] += ((facet_vertex[i] >> j) & 1);
		}        
		for (i = 0, minf_in_v = fvector[DIM-1]; i < fvector[0]; i++){
			if (minf_in_v > f_in_v[i]) minf_in_v = f_in_v[i];
		}	
		write_fvec (outf, fvector, 2, nincs, minf_in_v, buffer);
		/*
        bool is_ss2 = false;
        if (fvector[DIM-1] <= 64){    
            int64_t vertex_facet[MAX_VERT];
            // Транспонируем матрицу
            transpose(facet_vertex, fvector[DIM-1], fvector[0], vertex_facet);
            // Верно ли, что каждое ребро является пересечением ровно трех фасет?
            is_ss2 = is_simplicial2(vertex_facet, fvector[0], fvector[DIM-1], outf);
            fprintf (outf, "Dual 2-simplicial\n");
        }
        else{
            fprintf (outf, "Cann't test dual 2-simpliciality (%d facets > 64)\n", fvector[DIM-1]);
        }
		*/
    }
    fclose(inf);
	fprintf (outf, "MIN facets: %d\nMAX facets: %d\n", min_facets, max_facets);
    fclose(outf);
	return 0;
}
