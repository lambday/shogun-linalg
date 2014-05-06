/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2014 Soumyajit De
 */

#include <shogun/lib/config.h>
#include <shogun/lib/SGVector.h>
#include <shogun/lib/SGMatrix.h>

#ifdef HAVE_EIGEN3
#include <shogun/mathematics/eigen3.h>
#endif // HAVE_EIGEN3

#include <iostream>

namespace linalg
{

namespace impl
{
using namespace shogun;
using namespace linalg;
using namespace std;

template <class Scalar, class Vector, enum Backend>
struct dot
{
	static Scalar compute(Vector a, Vector b)
	{
		cout << "Generic dot()" << endl;
		return 0;
	}
};

template <class Scalar, class Matrix, enum Backend>
struct sum
{
	static Scalar compute(Matrix m)
	{
		cout << "Generic sum()" << endl;
		return 0;
	}
};

#if defined HAVE_EIGEN3 & (USE_EIGEN3_REDUX | USE_EIGEN3)
template <class Scalar>
struct dot<Scalar, SGVector<Scalar>, Backend::Eigen3>
{
	static Scalar compute(SGVector<Scalar> a, SGVector<Scalar> b)
	{
		cout << "Eigen3 cot()" << endl;
		typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> VectorXt;
		Eigen::Map<VectorXt> vec_a(a.vector, a.vlen);
		Eigen::Map<VectorXt> vec_b(b.vector, b.vlen);
		return vec_a.dot(vec_b);
	}
};

template <class Scalar>
struct sum<Scalar, SGMatrix<Scalar>, Backend::Eigen3>
{
	static Scalar compute(SGMatrix<Scalar> m)
	{
		cout << "Eigen3 sum()" << endl;
		typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> MatrixXt;
		Eigen::Map<MatrixXt> mat(m.matrix, m.num_rows, m.num_cols);
		return mat.sum();
	}
};
#endif // defined HAVE_EIGEN3 & USE_EIGEN3_REDUX

}
}
