// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
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

/// \file tests/topo/skeleton/is_simple_point.cc
///
/// Test mln::topo::skeleton::is_simple_point.

#include <mln/make/image2d.hh>
#include <mln/topo/skeleton/is_simple_point.hh>
#include <mln/make/image.hh>

#include <mln/debug/println.hh>

static const unsigned ref[] = { 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0 };

int main()
{
  using namespace mln;

  bool vals[][6] = { { 0, 1, 0, 0, 1, 1 },
                     { 0, 0, 0, 0, 1, 1 } };

  image2d<bool> ima = make::image(vals);

  unsigned i = 0;
  mln_piter_(image2d<bool>) p(ima.domain());
  for_all(p)
    mln_assertion(ref[i++] == topo::skeleton::is_simple_point(ima, c8(), p));
}
