// Copyright (C) 2004  EPITA Research and Development Laboratory
//
// This file is part of the Olena Library.  This library is free
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
// the Free Software Foundation, 59 Temple Place - Suite 330, Boston,
// MA 02111-1307, USA.


namespace oln {
  namespace abstract {

    /// Give the value of the nth coordinate of the point.
    template<class Exact>
    coord point_nd<Exact>::nth_impl(const unsigned			dim) const
    {
      assert(0 <= dim);
      assert(dim < oln_dim_val(Exact));
      return coord_[dim];
    }

    /// Return a reference to the nth coordinate of the point.
    template<class Exact>
    coord&
    point_nd<Exact>::nth_impl(const unsigned dim)
    {
      assert(0 <= dim);
      assert(dim < oln_dim_val(Exact));
      return coord_[dim];
    }


    /// Add a delta point \a dp to the current point
    template<class Exact>
    Exact &
    point_nd<Exact>::op_plus_assign_impl(const oln_dpoint_type(Exact)& dp)
    {
      for(unsigned dim = 0; dim < oln_dim_val(Exact); ++dim)
	coord_[dim] += dp.nth(dim);
      return this->exact();
    }

    /// Subtract a delta point \a dp from the current point.
    template<class Exact>
    Exact&
    point_nd<Exact>::op_minus_assign_impl(const oln_dpoint_type(Exact)	&dp)
    {
      for(unsigned dim = 0; dim < oln_dim_val(Exact); ++dim)
	coord_[dim] -= dp.nth(dim);
      return this->exact();
    }

    /// Subtract a point \a p from the current point.
    template<class Exact>
    oln_dpoint_type(Exact)
      point_nd<Exact>::op_minus_impl(const Exact			&p) const
    {
      oln_dpoint_type(Exact) res;
      for(unsigned dim = 0; dim < oln_dim_val(Exact); ++dim)
	res.nth(dim) = coord_[dim] - p.nth(dim);
      return res;
    }


    /// Addition of a delta point \a dp and the current point.
    template<class Exact>
    Exact
    point_nd<Exact>::op_plus_impl(const oln_dpoint_type(Exact)	&dp) const
    {
      Exact res;
      for(unsigned dim = 0; dim < oln_dim_val(Exact); ++dim)
	res.nth(dim) = coord_[dim] + dp.nth(dim);
      return res;
    }


    /// Subtraction of a delta point \a dp and the current point.
    template<class Exact>
    Exact
    point_nd<Exact>::op_minus_impl(const oln_dpoint_type(Exact)	&dp) const
    {
      Exact res;
      for(unsigned dim = 0; dim < oln_dim_val(Exact); ++dim)
	res.nth(dim) = coord_[dim] - dp.nth(dim);
      return res;
    }


    /// Opposite of the current point coordinates
    template<class Exact>
    Exact
    point_nd<Exact>::op_minus_impl() const
    {
      Exact res;
      for(unsigned dim = 0; dim < oln_dim_val(Exact); ++dim)
	res.nth(dim) = - coord_[dim];
      return res;
    }

    /// Points equal.
    template<class Exact>
    bool
    point_nd<Exact>::op_equal_impl(const Exact			&p) const
    {
      for(unsigned dim = 0; dim < oln_dim_val(Exact); ++dim)
	if (coord_[dim] != p.nth(dim))
	  return false;
      return true;
    }


    /// Points not equal.
    template<class Exact>
    bool
    point_nd<Exact>::op_not_equal_impl(const Exact			&p) const
    {
      for(unsigned dim = 0; dim < oln_dim_val(Exact); ++dim)
	if (coord_[dim] == p.nth(dim))
	  return true;
      return false;
    }
  } // end namespace abstract
} // end namespace abstract

