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

template <template <class,int...> class Vector, class T, int... Info>
T dot(Vector<T,Info...> a, Vector<T,Info...> b)
{
	return impl::dot<int,Vector,T,linalg_traits<Redux>::backend,Info...>::compute(a, b);
}

#ifdef HAVE_VIENNACL
template <template <class,unsigned int> class Vector, class T, unsigned int Info>
T dot(Vector<T,Info> a, Vector<T,Info> b)
{
	return impl::dot<unsigned int,Vector,T,linalg_traits<Redux>::backend,Info>::compute(a, b);
}
#endif // HAVE_VIENNACL

template <template <class,int...> class Matrix, class T, int... Info>
T sum(Matrix<T,Info...> m)
{
	return impl::sum<T, Matrix<T,Info...>, linalg_traits<Redux>::backend>::compute(m);
}

}
#endif // REDUX_H_
