// Copyright (C) 2007 EPITA Research and Development Laboratory (LRDE)
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

#ifndef MLN_MATH_ROUND_SAT_HH
# define MLN_MATH_ROUND_SAT_HH

/*! \file
 *
 * \brief Define round_sat routine.
 */

# include <cmath>

# include <mln/core/concept/function.hh>
# include <mln/trait/value_.hh>



namespace mln
{

  namespace math
  {


    template <typename R>
    struct round_sat_ : public Function_v2v< round_sat_<R> >
    {
      typedef R result;

      template <typename T>
      result operator()(const T& v) const;

    };


# ifndef MLN_INCLUDE_ONLY

    template <typename R>
    template <typename T>
    inline
    R round_sat_<R>::operator()(const T& v) const
    {
      long int l = (long int)(v + 0.49999); // FIXME: !!!
      return
	l < mln_min(R)
	? mln_min(R)
	: (l > mln_max(R)
	   ? mln_max(R)
	   : R(l));
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::math

} // end of namespace mln


#endif // ! MLN_MATH_ROUND_SAT_HH
