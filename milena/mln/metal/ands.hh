// Copyright (C) 2008 EPITA Research and Development Laboratory (LRDE)
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

#ifndef MLN_METAL_ANDS_HH
# define MLN_METAL_ANDS_HH

/// \file mln/metal/ands.hh
///
/// Definition of a multiple-"and"s Boolean expression.

# include <mln/metal/bool.hh>


namespace mln
{

  namespace metal
  {
    
    /// Ands type.
    template < typename E1,
	       typename E2,
	       typename E3,
	       typename E4 = true_,
	       typename E5 = true_,
	       typename E6 = true_,
	       typename E7 = true_,
	       typename E8 = true_ >
    struct ands : bool_<( E1::value &&
			  E2::value &&
			  E3::value &&
			  E4::value &&
			  E5::value &&
			  E6::value &&
			  E7::value &&
			  E8::value )>
    {};


  } // end of namespace mln::metal

} // end of namespace mln


#endif // ! MLN_METAL_ANDS_HH
