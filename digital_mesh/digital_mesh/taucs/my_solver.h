//#define DllExport   __declspec( dllexport )
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
#define DllExport
struct Solver_tag {
	int n;
	taucs_ccs_matrix * matrix;
	void * factorization;
};

DllExport struct Solver_tag * CreaterCholeskySolver(int n, int nnz, int *rowIndex, int *colIndex, double *value);
DllExport int FreeSolver(struct Solver_tag * sp);
DllExport int Solve(struct Solver_tag * sp, double *x, double *b);
DllExport double SolveEx(struct Solver_tag * sp, double *x, int xIndex, double *b, int bIndex);

struct SymbolicSolver_tag {
	int n;
	taucs_ccs_matrix * matrix;
	void * factorization;
	int  * perm;
	int  * invperm;
	double *tmp_b;
	double *tmp_x;
};

DllExport struct SymbolicSolver_tag * CreaterSymbolicSolver(int n, int nnz, int *rowIndex, int *colIndex, double *value);
DllExport void FreeSymbolicSolver(void * sp);
DllExport int NumericFactor(struct SymbolicSolver_tag *sp, int n, int nnz, int *rowIndex, int *colIndex, double *value);
DllExport void FreeNumericFactor(struct SymbolicSolver_tag *sp);
DllExport int NumericSolve(struct SymbolicSolver_tag * sp, double *x, double *b);

struct CGSolver_tag {
	int n;
	taucs_ccs_matrix * matrix;
};

DllExport void * CreaterCGSolver(int n, int nnz, int *rowIndex, int *colIndex, double *value);
DllExport int FreeCGSolver(void * sp);
DllExport int SolveCG(void * sp, double *x, double *b);
#ifdef __cplusplus
};
#endif // __cplusplus
