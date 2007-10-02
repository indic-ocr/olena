// Copyright (C) 2006  EPITA Research and Development Laboratory
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

#ifndef MLN_TRAIT_OP_PLUS_HH
# define MLN_TRAIT_OP_PLUS_HH

# include <mln/trait/promote.hh>


# define mln_trait_op_plus(L, R)  typename mln::trait::op_plus< L , R >::ret
# define mln_trait_op_plus_(L, R)          mln::trait::op_plus< L , R >::ret



namespace mln
{

  namespace trait
  {


    template <typename L, typename R>
    struct op_plus : public solve_binary<op_plus, L, R>
    {
    };


    /// Default definition of op_plus is given by the promote trait.
    template <template <class> class Category_L, typename L,
	      template <class> class Category_R, typename R>
    struct set_binary_< op_plus, Category_L, L, Category_R, R >
      :
      public promote< L, R >
    {
    };


  } // end of namespace mln::trait

} // end of namespace mln


#endif // ! MLN_TRAIT_OP_PLUS_HH
