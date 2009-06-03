// Copyright (C) 2007 EPITA Research and Development Laboratory
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

/*! \file tests/accu/histo.cc
 *
 * \brief Tests on mln::accu::histo.
 */

#include <mln/value/int_u8.hh>

#include <mln/accu/histo.hh>


int main()
{
  using namespace mln;
  using namespace mln::value;

  accu::histo<int_u8> a;

  a.take(1);
  a.take(1);
  a.take(1);


  a.take(2);
  a.take(2);
  a.take(2);

  a.take(234);
  a.take(234);
  a.take(234);
  a.take(234);
  a.take(234);
  a.take(234);

  mln_assertion(a[1] == 3);
  mln_assertion(a[2] == 3);
  mln_assertion(a[234] == 6);

  a.untake(234);
  mln_assertion(a[234] == 5);

  // Abort
  // a.untake(235);
}
