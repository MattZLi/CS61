#include<stdio.h>
inline double* melt2(matrix* m, unsigned i, unsigned j) {
    return &m->elt[i + j * m->N];
}

#define	m 1000
#define	j 1000
// struct matrix {
//     unsigned N;
//     unsigned M;
//     double elt[0];
// };
int main(){
	printf("%p", &m->elt[10 * 200 + 100]);
	printf("%p", &m->elt[10 * 200 + 101]);
	printf("%p", &m->elt[10 * 200 + 102]);
	printf("%p", &m->elt[10 * 200 + 103]);
	printf("%p", &m->elt[10 * 200 + 104]);
	printf("%p", &m->elt[11 * 200 + 105]);
	printf("column")
	printf("%p", &m->elt[10 * m->M + 100]);
	printf("%p", &m->elt[11 * m->M + 100]);
	printf("%p", &m->elt[12 * m->M + 100]);
	printf("%p", &m->elt[13 * m->M + 100]);
	printf("%p", &m->elt[14 * m->M + 100]);
	printf("%p", &m->elt[15 * m->M + 100]);
}
