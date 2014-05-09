/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2014 Soumyajit De
 */

#include <shogun/lib/Time.h>
#include <shogun/base/init.h>
#include <shogun/io/SGIO.h>
#include <linalg/linalg.h>
#include <Eigen/Eigen>

using namespace shogun;
using namespace Eigen;

void dot_test()
{
	auto size = 1000000;
	SGVector<float> a(size), b(size);
	auto iter = 1000;
	CTime* time = new CTime();
	double mean = 0, var = 0;
	for (auto i = 1; i <= iter; ++i)
	{
		SGVector<float>::random_vector(a.vector, a.vlen, 0, 1);
		SGVector<float>::random_vector(b.vector, b.vlen, 0, 1);
		time->start();
		linalg::dot(a, b);
		auto elapsed = time->cur_time_diff();
		auto delta = elapsed - mean;
		mean += delta/i;
		var += delta * (elapsed - mean);
	}
	var /= iter;
	SG_SPRINT("mean %.15f, var %.15lf\n", mean, var);
	SG_UNREF(time);
}

void sum_test()
{
	auto size = 1000;
	SGMatrix<float> m(size, size);
	auto iter = 1;
	CTime* time = new CTime();
	double mean = 0, var = 0;
	for (auto i = 1; i <= iter; ++i)
	{
		Map<MatrixXf> mat(m.matrix, m.num_rows, m.num_cols);
		mat=MatrixXf::Random(size, size);
		time->start();
		linalg::sum(m);
		auto elapsed = time->cur_time_diff();
		auto delta = elapsed - mean;
		mean += delta/i;
		var += delta * (elapsed - mean);
	}
	var /= iter;
	SG_SPRINT("mean %.15f, var %.15lf\n", mean, var);
	SG_UNREF(time);
}

void dot_explicit_backend()
{
	auto size = 1000000;
	SGVector<float> a(size), b(size);
	auto iter = 1000;
	CTime* time = new CTime();
	double mean = 0, var = 0;
	for (auto i = 1; i <= iter; ++i)
	{
		SGVector<float>::random_vector(a.vector, a.vlen, 0, 1);
		SGVector<float>::random_vector(b.vector, b.vlen, 0, 1);
		time->start();
		linalg::impl::dot<float, SGVector<float>, linalg::Backend::Eigen3>::compute(a, b);
		auto elapsed = time->cur_time_diff();
		auto delta = elapsed - mean;
		mean += delta/i;
		var += delta * (elapsed - mean);
	}
	var /= iter;
	SG_SPRINT("mean %.15f, var %.15lf\n", mean, var);
	SG_UNREF(time);
}

int main()
{
	init_shogun_with_defaults();
	dot_test();
	sum_test();
	dot_explicit_backend();
	exit_shogun();
	return 0;
}

