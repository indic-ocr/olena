// Copyright (C) 2008 EPITA Research and Development Laboratory
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

#ifndef MLN_FUN_X2X_NNEIGHBOR_HH
# define MLN_FUN_X2X_NNEIGHBOR_HH

# include <mln/core/concept/function.hh>
# include <mln/fun/internal/selector.hh>
# include <mln/algebra/vec.hh>
# include <mln/convert/to.hh>

/*! \file mln/fun/x2v/nneighbor.hh
 *
 * \brief Define a nneighbor interpolation of values from an underlying image
 */

namespace mln
{

  namespace fun
  {

    namespace x2x
    {

        template < typename I >
        struct nneighbor
          : public fun::internal::selector_<const algebra::vec<3,float>,
                                            // 3,float is a dummy parameter (real is n,T)
                                            mln_value(I), nneighbor<I> >::ret
        {
          typedef mln_value(I) result;

          nneighbor(const I& ima);

          template < unsigned n, typename T >
          mln_value(I)
          operator()(const algebra::vec<n,T>& x) const;

          const I& ima;
        };


# ifndef MLN_INCLUDE_ONLY

        template < typename I >
        nneighbor<I>::nneighbor(const I& ima) : ima(ima)
        {
        }

        template < typename I >
        template < unsigned n, typename T >
        mln_value(I)
        nneighbor<I>::operator()(const algebra::vec<n,T>& x) const
        {
          mln_psite(I) p =  convert::to<mln_psite(I)>(x);
          return ima(p);
        }


# endif // ! MLN_INCLUDE_ONLY

    } // end of namespace mln::fun::x2x

  } // end of namespace mln::fun

} // end of namespace mln


#endif // ! MLN_FUN_X2X_NNEIGHBOR_HH
