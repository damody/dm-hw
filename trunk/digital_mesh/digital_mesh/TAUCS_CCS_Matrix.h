#pragma once
#pragma warning(disable:4819)

extern "C" {
#include "taucs.h"
};
#include "shared_ptr.h"
#include "imath.h"
#include "log_define.h"

SHARE_PTR(taucs_ccs_matrix);
// auto release functor
static struct 
{
	void operator()( taucs_ccs_matrix* t_css_mat )
	{
		taucs_ccs_free(t_css_mat);
	}
}release_taucs_ccs_matrix;
taucs_ccs_matrix_sptr make_t_ccs_matrix_shared_ptr(taucs_ccs_matrix* src);

taucs_ccs_matrix* Clone_taucs_ccs_matrix(taucs_ccs_matrix* src, size_t datatype_size);
taucs_ccs_matrix* Clone_taucs_ccs_matrix_double(taucs_ccs_matrix* src);
taucs_ccs_matrix_sptr Clone_taucs_ccs_matrix_sptr(taucs_ccs_matrix* src, size_t datatype_size);
taucs_ccs_matrix_sptr Clone_taucs_ccs_matrix_sptr_double(taucs_ccs_matrix* src);

class TAUCS_CCS_Matrix_Double
{
public:
	TAUCS_CCS_Matrix_Double();
	TAUCS_CCS_Matrix_Double(const MMatrix& mat);
	TAUCS_CCS_Matrix_Double(const taucs_ccs_matrix* mat);
	TAUCS_CCS_Matrix_Double(int m, int n);

	//建立一個新的taucs_ccs_matrix需要自己free
	taucs_ccs_matrix*	Get_taucs_ccs_matrix();
	taucs_ccs_matrix_sptr	Get_taucs_ccs_matrix_sptr()  
	{return taucs_ccs_matrix_sptr(Get_taucs_ccs_matrix(), release_taucs_ccs_matrix);} //sptr型別的轉換
	MMatrix			Get_ublas_Matrix();
	
	MVector	Compute_x_By_Slover_Ax_B(const MVector& B); //解Vector的線性系統
	MMatrix	Compute_x_By_Slover_Ax_B(const MMatrix& B); //解矩陣的 
	// resize matrix size
	void	Resize(int m, int n);				
	// auto-cast for taucs_ccs_matrix
	operator taucs_ccs_matrix*() 
	{return Get_taucs_ccs_matrix();}			
	operator taucs_ccs_matrix_sptr()
	{return Get_taucs_ccs_matrix_sptr();}
	// auto-cast for Matrix
	operator MMatrix()
	{return Get_ublas_Matrix();}
	TAUCS_CCS_Matrix_Double& operator=(const taucs_ccs_matrix* mat);//轉換
	TAUCS_CCS_Matrix_Double& operator=(const MMatrix& mat);
	//void PreMultiply(std::vector <double> xIn,std::vector <double> xOut);
	int_vector2d GetRowIndex();
	int_vector2d GetColIndex();
public:
	MMatrix	m_Matrix;
};

struct Solver {
	int m_n;
	TAUCS_CCS_Matrix_Double m_t_ccs_matrix;
	void * m_factorization;
	Solver():m_factorization(NULL){}
	Solver(const MMatrix& mat):m_t_ccs_matrix(mat)
	{
		// check ATA m==n
		assert(mat.size1() == mat.size2());
		int rc;
		char* options[] = {"taucs.factor.LLT=true", NULL};
		//char* options[] = {"taucs.factor.LLT=true", "taucs.factor.droptol=1e-2", "taucs.solve.cg=true", NULL};
		m_n = mat.size1();
		// factor matrix
		rc = taucs_linsolve(m_t_ccs_matrix.Get_taucs_ccs_matrix_sptr().get(),
			&m_factorization, 0, NULL, NULL, options, NULL);
		if (rc != TAUCS_SUCCESS) { m_factorization = NULL; }
	}
	Solver(taucs_ccs_matrix* t_ccs_matrix):m_t_ccs_matrix(t_ccs_matrix)
	{
		taucs_ccs_matrix_sptr t_ccs_mat_sptr = m_t_ccs_matrix.Get_taucs_ccs_matrix_sptr();
		// check ATA m==n
		assert(t_ccs_mat_sptr->m == t_ccs_mat_sptr->n);
		int rc;
		char* options[] = {"taucs.factor.LLT=true", NULL};
		//char* options[] = {"taucs.factor.LLT=true", "taucs.factor.droptol=1e-2", "taucs.solve.cg=true", NULL};
		m_n = t_ccs_mat_sptr->m;
		// factor matrix
		rc = taucs_linsolve(t_ccs_mat_sptr.get(),
			&m_factorization, 0, NULL, NULL, options, NULL);
		if (rc != TAUCS_SUCCESS) { m_factorization = NULL; }
	}
	int Solve(Vector& x, Vector& b) {
		int rc;
		char* options [] = {"taucs.factor=false", NULL};
		//char* options [] = {"taucs.factor=false", "taucs.solve.cg=true", NULL};
		void * F = NULL;
		if (m_factorization == NULL) return -1;
		double_vector tx, tb;
		tx.resize(x.size());
		tb.resize(b.size());
		copy(b.begin(), b.end(), tb.begin());
		rc = taucs_linsolve(m_t_ccs_matrix.Get_taucs_ccs_matrix_sptr().get(), 
			&m_factorization, 1, &tx[0], &tb[0], options, NULL);
		copy(tx.begin(), tx.end(), x.begin());
		if (rc != TAUCS_SUCCESS) return rc;
		return 0;
	}
	int Solve(double_vector& x, double_vector& b) {
		int rc;
		char* options [] = {"taucs.factor=false", NULL};
		//char* options [] = {"taucs.factor=false", "taucs.solve.cg=true", NULL};
		void * F = NULL;
		if (m_factorization == NULL) return -1;

		rc = taucs_linsolve(m_t_ccs_matrix.Get_taucs_ccs_matrix_sptr().get(), 
			&m_factorization, 1, &x[0], &b[0], options, NULL);
		if (rc != TAUCS_SUCCESS) return rc;
		return 0;
	}
	int Solve(double *x, double *b) {
		int rc;
		char* options [] = {"taucs.factor=false", NULL};
		//char* options [] = {"taucs.factor=false", "taucs.solve.cg=true", NULL};
		void * F = NULL;
		if (m_factorization == NULL) return -1;

		rc = taucs_linsolve(m_t_ccs_matrix.Get_taucs_ccs_matrix_sptr().get(), 
			&m_factorization, 1, x, b, options, NULL);
		if (rc != TAUCS_SUCCESS) return rc;
		return 0;
	}
};

class SymbolicSolver {
public:
	int m_n;
	TAUCS_CCS_Matrix_Double m_t_ccs_matrix;
	void*		m_factorization;
	int_vector	m_perm;
	int_vector	m_invperm;
	double_vector	m_tmp_b;
	double_vector	m_tmp_x;
	SymbolicSolver():m_factorization(NULL){}
	SymbolicSolver(const MMatrix& mat):
	m_t_ccs_matrix(mat),m_perm(mat.size1()), m_invperm(mat.size1())
	{
		LOG_TRACE << "SymbolicSolver start";
		// check ATA m==n
		assert(mat.size1() == mat.size2());
		const int n = mat.size1();
		// get taucs_ccs_matrix form TAUCS_CCS_Matrix_Double
		LOG_TRACE << "Matrix " << mat.size1() << " " << mat.size2() << " nnz: " << mat.nnz();
		taucs_ccs_matrix_sptr matrix = m_t_ccs_matrix;
		LOG_TRACE << "get taucs_ccs_matrix";
		int *perm=0, *invperm=0;
		taucs_ccs_order(matrix.get(), &perm, &invperm, "metis");
		LOG_TRACE << "perm: " << perm;
		LOG_TRACE << "taucs_ccs_order finish";
		std::copy(perm, perm+n, m_perm.begin());
		std::copy(invperm, invperm+n, m_invperm.begin());
		taucs_ccs_permute_symmetrically(matrix.get(), &m_perm[0], &m_invperm[0]);
		LOG_TRACE << "taucs_ccs_permute_symmetrically finish";
		m_factorization = taucs_ccs_factor_llt_symbolic(matrix.get());
		LOG_TRACE << "taucs_ccs_factor_llt_symbolic finish";
		free(perm);
		free(invperm);
	}
	SymbolicSolver(taucs_ccs_matrix* t_ccs_matrix):
	m_perm(t_ccs_matrix->n), m_invperm(t_ccs_matrix->n), m_t_ccs_matrix(t_ccs_matrix)
	{
		// check ATA m==n
		assert(t_ccs_matrix->m == t_ccs_matrix->n);
		const int n = t_ccs_matrix->n;
		taucs_ccs_matrix_sptr matrix = m_t_ccs_matrix;
		int *perm, *invperm;
		taucs_ccs_order(matrix.get(), &perm, &invperm, "metis");
		std::copy(perm, perm+n, m_perm.begin());
		std::copy(invperm, invperm+n, m_invperm.begin());
		taucs_ccs_permute_symmetrically(matrix.get(), &m_perm[0], &m_invperm[0]);
		m_factorization = taucs_ccs_factor_llt_symbolic(matrix.get());
		free(perm);
		free(invperm);
	}
	int NumericFactor(taucs_ccs_matrix* input)
	{
		taucs_ccs_matrix_sptr t_ccs_mat = 
			make_t_ccs_matrix_shared_ptr(
			taucs_ccs_permute_symmetrically(input, &m_perm[0], &m_invperm[0])
			);
		//td::cout << TAUCS_CCS_Matrix_Double(t_ccs_mat.get()).Get_ublas_Matrix()  << std::endl;
		return taucs_ccs_factor_llt_numeric(t_ccs_mat.get(), m_factorization);
	}
	int NumericSolve(Vector& x, const Vector& b)
	{
		x.resize(0);
		int_vector tb;
		tb.reserve(b.size());
		std::copy(b.begin(), b.end(), tb.begin());
		int_vector tx(b.size());
		int rc = -1;

		taucs_vec_permute(m_n, TAUCS_DOUBLE, &tb[0], &m_tmp_b[0], &m_perm[0]);
		rc = taucs_supernodal_solve_llt(m_factorization, &m_tmp_x[0], &m_tmp_b[0]);
		taucs_vec_permute(m_n, TAUCS_DOUBLE, &m_tmp_x[0], &tx[0], &m_invperm[0]);
		std::copy(tx.begin(), tx.end(), x.begin());
		return rc;
	}
};


