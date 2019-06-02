#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>  
#include <stdint.h>  

#define MAX_VERT 9
#define MAX_FACET 21
// The dimension of a polytope
#define DIM 5
// The maximal number of all faces of a polytope
#define MAX_FACES 65536
// The maximal length of a line in the input file
#define LINE_SIZE 1024 

FILE *logfile;

typedef struct Test_face Test_face;

struct Test_face{
	Test_face *next;
	int64_t vertices;
	int64_t facets;
};

int64_t face_arrays[2][MAX_FACES]; // list of faces for dim = k and for dim = k+1
int ref_to_cur_face_facets[MAX_FACES]; // references to cur_face facets

// Compare lexicographically minimal facet of the convex hull of new_face_vertices (new_face_facets) with cur_face_vertices (cur_face_facets)
// Return 1 if they are equal. Hence, we can add new_face_vertices to the list of (lexicographically minimal) faces
// new_face_facets contains facets for new_face_vertices; cur_face_facets contains facets for cur_face_vertices
inline int compare_min_facet (const int vertices, const int64_t new_face_vertices, const int64_t new_face_facets, const int64_t cur_face_vertices, const int64_t cur_face_facets, const int64_t *vertex_facet)
{
	int j, v;
	int64_t x;
	int64_t f_list[MAX_VERT]; 

	for (j = 0, x = 1; (new_face_vertices & x) == 0; j++, x <<= 1) ;

	f_list[0] = vertex_facet[j];
	for (v = 0; j < vertices; j++, x <<= 1)	{
		if (new_face_vertices & x) {
			f_list[v+1] = (f_list[v] & vertex_facet[j]);
			if (f_list[v+1] == new_face_facets)
				continue;
			if (cur_face_vertices&x == 0) // cur_face_vertices is not a minimal
				return 0;
			v++;
		}
	}
	
	return (f_list[v] == cur_face_facets);
}



// Evaluate f-vector of the incidence matrix 'facet_vertices'
// rows is the number of facets
// columns is the number of vertices
// the procedure uses the following global arrays:
// vert_facets, faces
int eval_fvector(int facets, int vertices, const int64_t *facet_vertex, const int64_t *vertex_facet, int64_t *fvector, int *dimension, int *simpliciality)
{
	memset (fvector, 0, sizeof(int64_t)*MAX_VERT);
    int64_t vertexincs[MAX_VERT], facetincs[MAX_VERT];
	memset (vertexincs, 0, sizeof(int64_t)*MAX_VERT);
	memset (facetincs, 0, sizeof(int64_t)*MAX_VERT);

	if (facets <= 2 || vertices <= 2) {
		fvector[0] = 2;
		*dimension = 1;
		return 0;
	}

	// Some variables
	int64_t x, y, begin_bit, intersection;
	int i, j, m, t, j_begin;

	// Temporary arrays for faces
	int64_t *faces = face_arrays[0];
	int64_t *new_faces = face_arrays[1], *buf_faces;
	
	// Initialize faces
	for (i = 1, x = 1; i <= vertices; i++, x <<= 1)
		faces[i] = x;
	faces[0] = vertices;
	fvector[0] = vertices;

	// current face
	int64_t cur_face_vertices, cur_face_facets;
	int num_cur_face_facets;

	// candidates will contain a list of new faces (candidates)
	Test_face candidates[MAX_VERT], *cur_candidate, *next_candidate, *prev_candidate;
	int num_candidates;


	// Main cycle
	for (*dimension = 1; ; (*dimension)++)
	{
		new_faces[0] = 0;
		// For all faces
		for (i = 1; i <= faces[0]; i++)
		{
			cur_face_vertices = faces[i];
			// Evaluate facets of closure for cur_face_vertices
			// Initializing of cur_face_facets
			for (j = 0, x = 1; (cur_face_vertices & x) == 0; x <<= 1, j++) ;
			begin_bit = x;
			j_begin = j;
			cur_face_facets = vertex_facet[j]; // Init
			// Evaluate closure
			j++;
			x <<= 1;
			for ( ; j < vertices; j++, x <<= 1)
				if (cur_face_vertices & x)
					cur_face_facets &= vertex_facet[j];

			// List of facets of cur_face
			num_cur_face_facets = 0;
			for (m = 0, y = 1; m < facets; m++, y <<= 1) {
				if (cur_face_facets & y) {
					ref_to_cur_face_facets[num_cur_face_facets] = m;
					num_cur_face_facets++;
				}
			}
			// End of evaluating of cur_face closure
			
			if (num_cur_face_facets == 1) // cur_face is a facet
				goto Exit;

			// candidates will contain a list of new faces
			num_candidates = 0;
			cur_candidate = candidates;
			// Choose vertex right after the smallest vertex in cur_face_vertices
			x = (begin_bit << 1);
			j = j_begin+1;
			// Adding new vertices
			for (; j < vertices; x <<= 1, j++)
			{
				if ((cur_face_vertices & x) == 0) // If this is a new vertex
				{
					// Init a new face closure
					cur_candidate->facets = cur_face_facets & vertex_facet[j];
					// Init vertices of a new face
					cur_candidate->vertices = ~((int64_t)0); // ATTENTION!!!
					for (t = 0; t < num_cur_face_facets; t++)
					{
						m = ref_to_cur_face_facets[t];
						//y = 1;
						//y <<= m;
						y = ((int64_t)1 << m); // ATTENTION!!!
						if ((cur_candidate->facets) & y)
							cur_candidate->vertices &= facet_vertex[m];
					}
					cur_candidate->next = cur_candidate+1;
					cur_candidate++;
					num_candidates++;
				}
			}
			if (cur_candidate != candidates)
			{
				cur_candidate--;
				cur_candidate->next = NULL;
			}
			else
				continue;
				
				

			//for (cur_candidate = candidates; ; )
			for (cur_candidate = candidates; cur_candidate != NULL; )
			{
				prev_candidate = cur_candidate;
				next_candidate = prev_candidate->next;
				// Comparing cur_candidate with the rest candidates
				for ( ; next_candidate != NULL; )
				{
					intersection = (cur_candidate->vertices) & (next_candidate->vertices);
					if (intersection == (cur_candidate->vertices))
					{
						// If next_candidate is greater, then exclude it
						prev_candidate->next = next_candidate->next;
						next_candidate = prev_candidate->next;
					}
					else if (intersection == (next_candidate->vertices))
						// If cur_candidate is greater, then skip to the next candidate
						goto Next;
					else
					{
						prev_candidate = next_candidate;
						next_candidate = prev_candidate->next;
					}
				}
				//printf ("end internal cycle candidate: %d\n", cur_candidate->vertices);
				//j = compare_min_facet(cur_candidate->vertices, cur_face_facets, cur_candidate->facets);
				// Testing: if the lexicographically smallest facet of cur_candidate
				// coincides with cur_face_vertices, then adding it to new_faces
			
				if (compare_min_facet (vertices, cur_candidate->vertices, cur_candidate->facets, cur_face_vertices, cur_face_facets, vertex_facet))
				{
					new_faces[0] += 1;
					new_faces[new_faces[0]] = cur_candidate->vertices;
					// __builtin_popcountll -- подсчитывает число единичек (суффикс ll - для 64-битных чисел)
                    vertexincs[*dimension] += __builtin_popcountll (cur_candidate->vertices);
					facetincs[*dimension] += __builtin_popcountll (cur_candidate->facets);
				}
				Next:
				cur_candidate = cur_candidate->next;
			}
		}
		fvector[*dimension] = new_faces[0];
		// Exchange faces and new_faces
		buf_faces = new_faces;
		new_faces = faces;
		faces = buf_faces;
	}	

	Exit:
/*	cur_polytope->proper_dim = dim+1; 
	cur_polytope->pyramid = is_pyramid(faces);
	cur_polytope->simplicial = is_simplicial(cur_polytope->proper_dim);
	cur_polytope->simplicial |= ((is_3nghb(cur_polytope)) << 1);
	cur_polytope->simplicial |= ((is_dual2nghb(cur_polytope)) << 7);*/
	// Вычисляем степень симплициальности многогранника
    for (i = 1; i <= *dimension; i++){
        if (fvector[i] * (i+1) != vertexincs[i])
            break;
    }
    *simpliciality = i - 1;
	/*
	// Вычисляем степень простоты многогранника
    for (i = *dimension-1; i > 0; i--){
        if (fvector[i] * (*dimension - i + 1) != facetincs[i])
            break;
    }
    if (i == 0 && (vertexincs[*dimension] == vertices * (*dimension + 1)))  i--;
    simplicity = *dimension - i - 1;
	*/
	return 0;
}


// Read combinatorial type of polytope from the format
// http://www-imai.is.s.u-tokyo.ac.jp/~hmiyata/oriented_matroids/
// For example: http://www-imai.is.s.u-tokyo.ac.jp/~hmiyata/oriented_matroids/polytope_n8d5.txt
int read_miyata (char *buffer, int &vertices, int &facets, int64_t *facet_vertex, int64_t *vertex_facet, bool &is_pyramid, bool &is_simplicial){
	int f, v, read;
	for (v = 0; v < MAX_VERT; v++)
		vertex_facet[v] = 0;
    is_pyramid = false;
    is_simplicial = true;
    char *endptr = buffer;
	int64_t x;
    vertices = 0;
	for (f = 0, x = 1; (*endptr) == '['; f++, x <<= 1){
        if (f > MAX_FACET)
            break;
		facet_vertex[f] = 0;
        //printf("%c", *endptr);
		for (v = 0; (*endptr) != ']'; v++){
			read = strtol (endptr+1, &endptr, 10);
			if (read < 0 || read >= MAX_VERT){
				printf ("ERROR: Wrong format 2 in line %s\n", buffer);
				return 2;
			}
            if (read >= vertices)
                vertices = read+1;
            //printf(" %d", read);
			facet_vertex[f] |= (1 << read);
			vertex_facet[read] |= x;
		}
        if (v == MAX_VERT - 1)
            is_pyramid = true;
        if (v != DIM)
            is_simplicial = false;
        //printf("%c", *endptr);
        endptr += 2;
    }    
	facets = f;
	return 0;
}

// Write incidence matrices into file
int write_inc (FILE *incfile, int facets, int vertices, int64_t *facet_vertex, int64_t *vertex_facet){
//	FILE *incfile = fopen(filename, "w");
	if (incfile == NULL ){
		printf ("ERROR: Cann't open file %s\n");
		return 1;
	}

	int i, j;
	int64_t x;
	fprintf (incfile, "begin\n%d %d\n", facets, vertices);
	for (i = 0; i < facets; i++){
		for (j = 0, x = 1; j < vertices; j++, x <<= 1){
			fprintf (incfile, " %d", (facet_vertex[i]&x)/x);
		}
		fprintf (incfile, "\n");
	}
	fprintf (incfile, "end\n");

//	fprintf (incfile, "\nbegin\n%d %d\n", vertices, facets);
//	for (i = 0; i < vertices; i++){
//		for (j = 0, x = 1; j < facets; j++, x <<= 1){
//			fprintf (incfile, " %d", (vertex_facet[i]&x)/x);
//		}
//		fprintf (incfile, "\n");
//	}
//	fprintf (incfile, "end\n");
//	fclose (incfile);
	return 0;
}

// Write f-vector into file and some additional information
int write_fvec (FILE *outf, int facets, int vertices, int dimension, int64_t *fvector, bool is_pyramid, int simpliciality, int nincs, int minf_in_v, char *buffer){
	fprintf (outf, "%s", buffer);
	fprintf (outf, "v: %d, f: %d, d: %d, ", vertices, facets, dimension);
    if (is_pyramid)
        fprintf (outf, "pyramid, ");
    if (simpliciality >= dimension - 1)
        fprintf (outf, "simplicial, ");
	else
        fprintf (outf, "sc=%d, ", simpliciality);
    if (fvector[0] * (fvector[0] - 1) == 2 * fvector[1])
        fprintf (outf, "2-neighborly, ");
    fprintf (outf, "inc=%2d, ", nincs);
    fprintf (outf, "min(f in v)=%d\n", minf_in_v);
	fprintf (outf, "f-vector:");
	for (int i = 0; i < dimension; i++){
		fprintf (outf, " %d", fvector[i]);
	}
	fprintf (outf, "\n");

	return 0;
}



///////////////////////////////////
//  MAIN
///////////////////////////////////

// The argument of a program -- file with combinatorial types of 5-polytopes from
// http://www-imai.is.s.u-tokyo.ac.jp/~hmiyata/oriented_matroids/
// For example: http://www-imai.is.s.u-tokyo.ac.jp/~hmiyata/oriented_matroids/polytope_n8d5.txt
int main(int argc, char *argv[]) {

	if (argc < 2){
		printf("Usage: fvector [inc-file]\n");
		return 1;
	}

	FILE *infile = fopen(argv[1], "r");
	if (infile == NULL){
		printf ("ERROR: Cann't open file %s\n", argv[1]);
		return 1;
	}
	char filename[255];
	sprintf(filename, "%s.fvec", argv[1]);
	FILE *outfile = fopen(filename, "w");
	if (outfile == NULL){
		printf ("ERROR: Cann't open file %s\n", filename);
		return 1;
	}
    
	int facets, vertices = MAX_VERT;
	int64_t facet_vertex[MAX_FACET], vertex_facet[MAX_VERT];
    bool is_pyramid, is_simplicial;
	char buffer[LINE_SIZE];
    
	int64_t fvector[MAX_VERT];
    int dimension;
    int min_facets = MAX_FACET;
    int max_facets = 0;
    while(fgets (buffer, LINE_SIZE, infile) != NULL){
        // Read combinatorial type of a polytope
        if (read_miyata (buffer, vertices, facets, facet_vertex, vertex_facet, is_pyramid, is_simplicial) != 0)
            break;
        //printf ("v = %d, f = %d\n", vertices, facets);
        if (facets > MAX_FACET){
            fprintf (outfile, "ERROR: %d facets > %d\n", facets, MAX_FACET);
            printf ("ERROR: %d facets > %d\n", facets, MAX_FACET);
            continue;
        }        
        // Evaluate f-vector
		int simpliciality;
        eval_fvector(facets, vertices, facet_vertex, vertex_facet, fvector, &dimension, &simpliciality);
		
//        if (fvector[0] * (fvector[0] - 1) == 2 * fvector[1])// Write only 2-neighborly polytopes
//        if (simpliciality > 1 && facets < 11) // Write only 2-simplicial polytopes
        if (simpliciality < 2) // Write only 2-simplicial polytopes
			continue;
        if (min_facets > fvector[dimension - 1])
            min_facets = fvector[dimension - 1];
        if (max_facets < fvector[dimension - 1])
            max_facets = fvector[dimension - 1];
		int i, nincs, minf_in_v;
		for (i = 0, nincs = 0; i < facets; i++)
			nincs += __builtin_popcountll (facet_vertex[i]); // Подсчитываем число единичек
		for (i = 0, minf_in_v = facets; i < vertices; i++){
			int f_in_v = __builtin_popcountll (vertex_facet[i]); // Подсчитываем число фасет в вершине
			if (minf_in_v > f_in_v) minf_in_v = f_in_v;
		}
        write_fvec (outfile, facets, vertices, dimension, fvector, is_pyramid, simpliciality, nincs, minf_in_v, buffer);
        write_inc (outfile, facets, vertices, facet_vertex, vertex_facet);
    }
    
	fprintf (outfile, "MIN facets: %d\nMAX facets: %d\n", min_facets, max_facets);
    fclose (infile);
    fclose (outfile);
	return 0;
}
