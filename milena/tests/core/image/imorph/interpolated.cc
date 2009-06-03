// Copyright (C) 2007, 2008, 2009 EPITA Research and Development
// Laboratory (LRDE)
//
// This file is part of the Milena Library.  This library is free
// software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License version 2 as published by the
// Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this library; see the file COPYING.  If not, write to
// the Free Software Foundation, 51 Franklin Street, Fifth Floor,
// Boston, MA 02111-1307, USA.
//
// As a special exception, you may use this file as part of a free
// software library without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to
// produce an executable, this file does not by itself cause the
// resulting executable to be covered by the GNU General Public
// License.  This exception does not however invalidate any other
// reasons why the executable file might be covered by the GNU General
// Public License.

/// \file tests/core/image/imorph/interpolated.cc
///
/// Tests on mln::interpolated.


#include <iostream>
#include <mln/core/image/image2d.hh>
#include <mln/core/image/imorph/interpolated.hh>

#include <mln/algebra/vec.hh>

#include <mln/data/fill.hh>

#include <mln/debug/println.hh>

#include <mln/fun/x2v/bilinear.hh>



int main()
{
  using namespace mln;

  float tab[] = {1.,  3.,  5.,  7.,
		 4.,  7.,  10., 13.,
		 7.,  11., 15., 19.,
		 10., 15., 20., 25.};
  image2d<float> f = make::image2d(tab);

  interpolated<image2d<float>, fun::x2v::bilinear> inter(f);

  algebra::vec<2, float> v1 = make::vec(2.3, 0.6);
  algebra::vec<2, float> v2 = make::vec(3.2, 1.8);

  debug::println(f);

  std::cout << v1 << " : " << inter(v1) << std::endl;
  std::cout << v2 << " : " << inter(v2) << std::endl;
}
