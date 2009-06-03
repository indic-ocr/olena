// Copyright (C) 2007, 2008 EPITA Research and Development Laboratory
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

/*! \file tests/arith/diff_abs.cc
 *
 * \brief Tests on mln::arith::diff_abs.
 */

#include <mln/core/image/image2d.hh>
#include <mln/debug/iota.hh>
#include <mln/arith/diff_abs.hh>
#include <mln/data/compare.hh>

int main()
{
  using namespace mln;

  trace::quiet = false;

  {
    image2d<int> ima(3,3);

    int vs1[3][3] = {
      {0, 1, 2},
      {3, 4, 5},
      {6, 7, 8}
    };


    int vs2[3][3] = {
      {1, 0, 5},
      {8, 5, 6},
      {9, 5, 2}
    };

    int vs_ref[3][3] = {
      {1, 1, 3},
      {5, 1, 1},
      {3, 2, 6}
    };

    image2d<int> ima1 = make::image(vs1);
    image2d<int> ima2 = make::image(vs2);
    image2d<int> ref = make::image(vs_ref);

    mln_assertion (arith::diff_abs(ima1, ima2) == ref);
  }

}
