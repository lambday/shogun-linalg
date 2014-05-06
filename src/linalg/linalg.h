/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2014 Soumyajit De
 */

#ifndef LINALG_H_
#define LINALG_H_

#include <shogun/lib/config.h>

namespace linalg
{
using namespace shogun;

enum class Backend
{
	Default,
	Eigen3,
	ViennaCL
};

// general purpose linalg_traits for compile time information
// about backends
template <class T>
struct linalg_traits : T
{
};

// define the modules
#ifndef SET_MODULE_BACKEND
#define SET_MODULE_BACKEND(MODULE, BACKEND) \
struct MODULE \
{ \
	const static Backend backend = Backend::BACKEND; \
};
#endif // SET_MODULE_BACKEND

#ifndef SET_GLOBAL_BACKEND
#define SET_GLOBAL_BACKEND(BACKEND) \
SET_MODULE_BACKEND(Redux, BACKEND) \
SET_MODULE_BACKEND(Linsolver, BACKEND) \
SET_MODULE_BACKEND(Eigsolver, BACKEND)
#endif // SET_GLOBAL_BACKEND

#ifdef USE_EIGEN3
SET_GLOBAL_BACKEND(Eigen3)
#elif USE_VIENNACL
SET_GLOBAL_BACKEND(ViennaCL)
#else // USE_EIGEN3 AND USE_VIENNACL
// Reduction module
#ifdef USE_EIGEN3_REDUX
SET_MODULE_BACKEND(Redux, Eigen3)
#elif USE_VIENNACL_REDUX
SET_MODULE_BACKEND(Redux, ViennaCL)
#else // the default case
SET_MODULE_BACKEND(Redux, Default)
#endif // USE_EIGEN3_REDUX

// Linear solver module
#ifdef USE_EIGEN3_LINSLV
SET_MODULE_BACKEND(Linsolver, Eigen3)
#elif USE_VIENNACL_LINSLV
SET_MODULE_BACKEND(Linsolver, ViennaCL)
#else // the default case
SET_MODULE_BACKEND(Linsolver, Default)
#endif // USE_EIGEN3_Linsolver

// Eigen solver module
#ifdef USE_EIGEN3_EIGSLV
SET_MODULE_BACKEND(Eigsolver, Eigen3)
#elif USE_VIENNACL_EigSLV
SET_MODULE_BACKEND(Eigsolver, ViennaCL)
#else // the default case
SET_MODULE_BACKEND(Eigsolver, Default)
#endif // USE_EIGEN3_EIGSLV

#endif // USE_EIGEN3;

#undef SET_MODULE_BACKEND
}

// include all the modules
#include <linalg/redux.h>
// #include <linalg/eigsolver.h> .. and so on

#endif // LINALG_H_
