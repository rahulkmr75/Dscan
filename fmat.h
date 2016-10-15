#ifndef FMAT_H_
#define FMAT_H_
/************************************************************************
*	given a matrix and a file name it writes to permanent storage	*
*	with the format row: <row>					*
*			col: <col>					*
*			data:						*
*				<R1>					*
*				<R2>					*
*	Similarly readmat reads the matrix from a given file and loads	*
*	it into RAM.							*
************************************************************************/
template <typename Tp1>void writemat(mat<Tp1> &m,char *name);
template <typename Tp1>void readmat(mat<Tp1> &m,char *name);
#endif
