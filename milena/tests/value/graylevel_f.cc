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

#include <mln/value/graylevel.hh>
#include <mln/value/glf.hh>
#include <mln/literal/all.hh>


int main()
{
  using namespace mln;
  using value::glf;

  using literal::black;
  using literal::medium_gray;
  using literal::white;


  // Literals.
  {
    glf a = medium_gray;
    glf b = medium_gray;
    // a == 0.5f;
    mln_assertion(0.5f == a.to_enc());
    // a == b;
    mln_assertion(b == a);

    a *= 2;
    mln_assertion(a == glf(white));
    mln_assertion(a.to_enc() == 1.f);
  }
}
