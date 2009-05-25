// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
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

#ifndef MLN_FUN_I2V_VALUE_AT_INDEX_HH
# define MLN_FUN_I2V_VALUE_AT_INDEX_HH

/// \file mln/fun/i2v/value_at_index.hh
///
/// \brief File that define a function that gives an index per value.

#include <mln/core/concept/function.hh>
#include <mln/trait/value_.hh>


namespace mln
{

  namespace fun
  {

    namespace i2v
    {

      template <typename T>
      struct value_at_index : Function_v2v< value_at_index<T> >,
			      private metal::bool_<(mln_dim(T) == 1)>::check_t
      {
	typedef T result;
	T operator()(unsigned i) const;
      };

      template <>
      struct value_at_index<bool> : Function_v2v< value_at_index<bool> >
      {
	typedef bool result;
	bool operator()(unsigned i) const;
      };


# ifndef MLN_INCLUDE_ONLY

      template <typename T>
      inline
      T
      value_at_index<T>::operator()(unsigned i) const
      {
	return T( int(mln_min(T)) + int(i) );
      }

      inline
      bool
      value_at_index<bool>::operator()(unsigned i) const
      {
	mln_precondition(i < 2);
	return i == 1u ? true : false;
      }

# endif // ! MLN_INCLUDE_ONLY

    } // end of namespace mln::fun::i2v

  } // end of namespace mln::fun

} // end of namespace mln

#endif // ! MLN_FUN_I2V_VALUE_AT_INDEX_HH