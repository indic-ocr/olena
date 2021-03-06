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

#include <mln/core/alias/point2d.hh>
#include <mln/core/site_set/p_priority.hh>
#include <mln/core/site_set/p_queue.hh>
#include <mln/geom/bbox.hh>
#include <mln/make/box2d.hh>
#include <mln/set/has.hh>
#include <mln/set/get.hh>


int main()
{
  using namespace mln;

  typedef p_queue<point2d> Q;
  p_priority<unsigned, Q> q;
  point2d p1(6, 9);
  point2d p2(5, 1);
  point2d p3(4, 2);

  mln_assertion(q.is_empty());

  mln_assertion(q.nsites() == 0);

  q.push(0, p3);
  q.push(3, p1);
  q.push(5, p2);

  mln_assertion(geom::bbox(q) == make::box2d(4,1, 6,9));

  mln_assertion(! q.is_empty());

  mln_assertion(set::has(q, p1));
  mln_assertion(set::has(q, p2));
  mln_assertion(set::has(q, p3));

  mln_assertion(q.nsites() == 3);
  mln_assertion(q.front() == p2);
  q.pop();

  mln_assertion(set::has(q, p1));
  mln_assertion(! set::has(q, p2));
  mln_assertion(set::has(q, p3));

  mln_assertion(q.nsites() == 2);
  mln_assertion(q.front() == p1);
  q.pop();

  mln_assertion(! set::has(q, p1));
  mln_assertion(! set::has(q, p2));
  mln_assertion(set::has(q, p3));

  mln_assertion(q.nsites() == 1);
  mln_assertion(q.front() == p3);
  q.pop();

  mln_assertion(! set::has(q, p1));
  mln_assertion(! set::has(q, p2));
  mln_assertion(! set::has(q, p3));
  mln_assertion(q.nsites() == 0);

  mln_assertion(q.is_empty());

  q.push(0, p3);
  q.push(5, p2);
  q.push(3, p1);

  mln_assertion(set::get(q, 2) == p3);
  mln_assertion(set::get(q, 0) == p2);
  mln_assertion(set::get(q, 1) == p1);
  q.clear();
  mln_assertion(q.is_empty());
}
