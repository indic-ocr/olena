// Copyright (C) 2008 EPITA Research and Development Laboratory (LRDE)
//
// This file is part of Olena.
//
// Olena is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation, version 2 of the License.
//
// Olena is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Olena.  If not, see <http://www.gnu.org/licenses/>.
//
// As a special exception, you may use this file as part of a free
// software project without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to produce
// an executable, this file does not by itself cause the resulting
// executable to be covered by the GNU General Public License.  This
// exception does not however invalidate any other reasons why the
// executable file might be covered by the GNU General Public License.

#include <mln/core/image/image2d.hh>
#include <mln/core/alias/neighb2d.hh>
#include <mln/value/int_u8.hh>

#include <mln/debug/iota.hh>
#include <mln/debug/println.hh>

#include <mln/morpho/elementary/erosion.hh>


int main()
{
  using namespace mln;
  using value::int_u8;

//   trace::quiet = false;

  image2d<int_u8> ima(3, 3, 0);
  debug::iota(ima);
  debug::println(ima);
  {
    image2d<int_u8> ero = morpho::elementary::erosion(ima, c4());
    mln_assertion(ero.border() == 1);
    debug::println(ero);
  }

  image2d<bool> msk(3, 3, 0);
  data::fill(msk, pw::value(ima) >= pw::cst(5u));
  debug::println(msk);
  {
    image2d<bool> ero = morpho::elementary::erosion(msk, c4());
    mln_assertion(ero.border() == 1);
    debug::println(ero);
  }

}
