/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2014 Soumyajit De
 */

#ifndef REDUX_H_
#define REDUX_H_

#include <linalg/impl/redux.h>

namespace linalg
{

template <class Scalar, class Vector>
Scalar dot(Vector a, Vector b)
{
	return impl::dot<Scalar, Vector, linalg_traits<Redux>::backend>::compute(a, b);
}

template <class Scalar, class Matrix>
Scalar sum(Matrix m)
{
	return impl::sum<Scalar, Matrix, linalg_traits<Redux>::backend>::compute(m);
}

}
#endif // REDUX_H_
