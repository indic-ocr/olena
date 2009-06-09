// Copyright (C) 2007, 2008, 2009 EPITA Research and Development Laboratory (LRDE)
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

#include <iterator>

#include <mln/core/image/image2d.hh>
#include <mln/core/image/image1d.hh>

#include <mln/value/int_u8.hh>

#include <mln/debug/iota.hh>
#include <mln/accu/histo.hh>
#include <mln/histo/compute.hh>

#include <mln/debug/println.hh>

#include <mln/convert/to_image.hh>

int main()
{
  using namespace mln;
  using value::int_u8;

  {
    accu::histo<bool> h;

    for (unsigned i = 0; i < 5; ++i)
      h.take(false);
    for (unsigned i = 0; i < 2; ++i)
      h.take(true);
    h.untake(true);

    mln_assertion(h[0] * 10 + h[1] == 51);
    mln_assertion(h(false) * 10 + h(true) == 51);
  }

  {
    image2d<int_u8> ima(3, 3);
    debug::iota(ima);
    ima(point2d(0,1)) = 255;
    debug::println(ima);
    histo::array<int_u8> h = histo::compute(ima);
    std::cout << h << std::endl;

    image1d<unsigned> ima2 = convert::to_image(h);
    debug::println(ima2);
  }
}
