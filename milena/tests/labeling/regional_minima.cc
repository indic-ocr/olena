// Copyright (C) 2007, 2008 EPITA Research and Development Laboratory (LRDE)
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

/*! \file tests/labeling/regional_minima.cc
 *
 * \brief Test on mln::labeling::regional_minima.
 */

#include <mln/core/image/image2d.hh>
#include <mln/value/int_u8.hh>
#include <mln/core/alias/neighb2d.hh>
#include <mln/io/pgm/load.hh>
#include <mln/pw/all.hh>
#include <mln/labeling/regional_minima.hh>

#include "tests/data.hh"


int main()
{
  using namespace mln;
  using value::int_u8;

  image2d<int_u8> lena = io::pgm::load<int_u8>(MLN_IMG_DIR "/tiny.pgm");

  unsigned n;
  labeling::regional_minima((pw::cst(255) - pw::value(lena)) | lena.domain(),
			    c4(), n);
  mln_assertion(n == 25);
}
