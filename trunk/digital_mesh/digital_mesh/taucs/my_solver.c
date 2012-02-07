#include <stdlib.h>
#include <memory.h>
#include "taucs.h"
#include "my_solver.h"

//
// functions for Cholesky Solver
//
DllExport struct Solver_tag * CreaterCholeskySolver
	(int n, int nnz, int *rowIndex, int *colIndex, double *value)
{
	int rc;
	char* options[] = {"taucs.factor.LLT=true", NULL};
	//char* options[] = {"taucs.factor.LLT=true", "taucs.factor.droptol=1e-2", "taucs.solve.cg=true", NULL};
	struct Solver_tag * s = (struct Solver_tag*) malloc(sizeof(struct Solver_tag));
	if (s == NULL) return NULL;
	s->n = n;
	s->matrix = NULL;
	s->factorization = NULL;

	 //open log file
	//taucs_logfile("c:/log2.txt");

	// create matrix
	s->matrix = taucs_ccs_create(n, n, nnz, TAUCS_DOUBLE|TAUCS_LOWER|TAUCS_SYMMETRIC);
	if (s->matrix == NULL) return NULL;
	
	// copy elements to matrix
 	memcpy(s->matrix->rowind, rowIndex, sizeof(int) * nnz);
 	memcpy(s->matrix->values.d, value, sizeof(double) * nnz);
 	memcpy(s->matrix->colptr, colIndex, sizeof(int) * (n+1));
	
	// factor matrix
	rc = taucs_linsolve(s->matrix, &s->factorization, 0, NULL, NULL, options, NULL);
	if (rc != TAUCS_SUCCESS) { FreeSolver(s); return NULL; }
	
	//taucs_logfile("none");

	return s;
}

DllExport int Solve( struct Solver_tag * sp, double *x, double *b )
{
	int rc;
	char* options [] = {"taucs.factor=false", NULL};
	//char* options [] = {"taucs.factor=false", "taucs.solve.cg=true", NULL};
	struct Solver_tag * s = (struct Solver_tag *) sp;
	void * F = NULL;

	if (s->matrix == NULL || s->factorization == NULL) return -1;

	rc = taucs_linsolve(s->matrix, &s->factorization, 1, x, b, options, NULL);
	if (rc != TAUCS_SUCCESS) return rc;

	return 0;
}

DllExport double SolveEx( struct Solver_tag * sp, double *x, int xIndex, double *b, int bIndex )
{
	int rc = -1;
	char* options [] = {"taucs.factor=false", NULL};
	struct Solver_tag * s = (struct Solver_tag *) sp;
	double time = taucs_ctime();

	rc = taucs_linsolve(s->matrix, &s->factorization, 1, x + xIndex, b + bIndex, options, NULL);
	time = taucs_ctime() - time;

	//return time;
	if (rc != TAUCS_SUCCESS) return rc;
	return 0;
}

DllExport int FreeSolver( struct Solver_tag * sp )
{
	struct Solver_tag * s = (struct Solver_tag *)sp;
	int rc = 0;

	if (sp == NULL)
	{
		return 0;
	}

	if (s->matrix != NULL) {
		taucs_ccs_free(s->matrix);
		s->matrix = NULL;
	}
	if (s->factorization != NULL) {
		rc = taucs_linsolve(NULL, &s->factorization, 0, NULL, NULL, NULL, NULL);
		s->factorization = NULL;
	}
	return rc;
}





//
// functions for symbolic solver
//
DllExport struct SymbolicSolver_tag * CreaterSymbolicSolver(int n, int nnz, int *rowIndex, int *colIndex, double *value)
{
	struct SymbolicSolver_tag * s = (struct SymbolicSolver_tag*) malloc(sizeof(struct SymbolicSolver_tag));
	s->n = n;
	s->matrix = taucs_ccs_create(n, n, nnz, TAUCS_DOUBLE|TAUCS_LOWER|TAUCS_SYMMETRIC);
	s->factorization = NULL;
	s->perm    = (int*) malloc(sizeof(int) * n);
	s->invperm = (int*) malloc(sizeof(int) * n);
	s->tmp_b = (double*) malloc(sizeof(double) * n);
	s->tmp_x = (double*) malloc(sizeof(double) * n);

	if (s->matrix == NULL) return NULL;
	if (s->perm == NULL) return NULL;

	memcpy(s->matrix->colptr, colIndex, sizeof(int)*(n+1));
	memcpy(s->matrix->rowind, rowIndex, sizeof(int)*nnz);
	memcpy(s->matrix->values.d, value, sizeof(double)*nnz);

	taucs_ccs_order(s->matrix, &s->perm, &s->invperm, "metis");
	s->matrix = taucs_ccs_permute_symmetrically(s->matrix, s->perm, s->invperm);
	s->factorization = taucs_ccs_factor_llt_symbolic(s->matrix);

	return s;
}

DllExport void FreeSymbolicSolver(void *sp)
{
	struct SymbolicSolver_tag * s = (struct SymbolicSolver_tag *) sp;
	if (s == NULL) return;
	if (s->matrix) taucs_ccs_free(s->matrix);
	if (s->factorization) taucs_supernodal_factor_free(s->factorization);
	if (s->perm) free(s->perm);
	if (s->invperm) free(s->invperm);
	if (s->tmp_b) free (s->tmp_b);
	if (s->tmp_x) free (s->tmp_x);
	s->matrix = s->factorization = NULL;
	s->perm = s->invperm = NULL;
	s->tmp_b = s->tmp_x = NULL;
}

DllExport int NumericFactor( struct SymbolicSolver_tag *sp, int n, int nnz, int *rowIndex, int *colIndex, double *value )
{
	int ret = -1;
	struct SymbolicSolver_tag * s = (struct SymbolicSolver_tag *) sp;
	taucs_ccs_matrix * m = taucs_ccs_create(n, n, nnz, TAUCS_DOUBLE|TAUCS_LOWER|TAUCS_SYMMETRIC);
	if (m == NULL) return -1;

	// copy elements to matrix
	memcpy(m->rowind, rowIndex, sizeof(int) * nnz);
	memcpy(m->values.d, value, sizeof(double) * nnz);
	memcpy(m->colptr, colIndex, sizeof(int) * (n+1));
	m = taucs_ccs_permute_symmetrically(m, s->perm, s->invperm);

	ret = taucs_ccs_factor_llt_numeric(m, s->factorization);
	taucs_ccs_free(m);

	return ret;
}

DllExport void FreeNumericFactor( struct SymbolicSolver_tag *sp )
{
	struct SymbolicSolver_tag * s = (struct SymbolicSolver_tag *) sp;
	taucs_supernodal_factor_free_numeric(s->factorization);
}

DllExport int NumericSolve( struct SymbolicSolver_tag * sp, double *x, double *b )
{
	int rc = -1;
	struct SymbolicSolver_tag * s = (struct SymbolicSolver_tag *) sp;
	taucs_vec_permute(s->n, TAUCS_DOUBLE, b, s->tmp_b, s->perm);
 	rc = taucs_supernodal_solve_llt(s->factorization, s->tmp_x, s->tmp_b);
 	taucs_vec_permute(s->n, TAUCS_DOUBLE, s->tmp_x, x, s->invperm);
	return rc;
}

//
// functions for symbolic solver
//
DllExport void * CreaterCGSolver
(int n, int nnz, int *rowIndex, int *colIndex, double *value)
{
	int currCol = -1;
	char* options[] = {"taucs.factor.LLT=true", NULL};
	struct CGSolver_tag * s = (struct CGSolver_tag*) malloc(sizeof(struct CGSolver_tag));
	if (s == NULL) return NULL;
	s->n = n;
	s->matrix = NULL;

	//open log file
	taucs_logfile("c:/log.txt");

	// create matrix
	s->matrix = taucs_ccs_create(n, n, nnz, TAUCS_DOUBLE|TAUCS_LOWER|TAUCS_SYMMETRIC);
	if (s->matrix == NULL) return NULL;

	// copy elements to matrix
	memcpy(s->matrix->rowind, rowIndex, sizeof(int) * nnz);
	memcpy(s->matrix->values.d, value, sizeof(double) * nnz);
	memcpy(s->matrix->colptr, colIndex, sizeof(int) * (n+1));

	taucs_logfile("none");

	return s;
}

DllExport int SolveCG(void * sp, double *x, double *b) {
	int rc;
	char* options [] = {"taucs.solve.cg=true", NULL};
	struct Solver_tag * s = (struct Solver_tag *) sp;
	void * F = NULL;

	if (s->matrix == NULL || s->factorization == NULL) return -1;

	//open log file
	taucs_logfile("c:/log.txt");

	rc = taucs_linsolve(s->matrix, &F, 1, x, b, options, NULL);
	if (rc != TAUCS_SUCCESS) return rc;

	taucs_logfile("none");

	return 0;
}

DllExport int FreeCGSolver(void * sp) {
	struct CGSolver_tag * s = (struct CGSolver_tag *)sp;
	int rc = 0;

	if (sp == NULL)
	{
		return 0;
	}

	if (s->matrix != NULL) {
		taucs_ccs_free(s->matrix);
		s->matrix = NULL;
	}
	return rc;
}
