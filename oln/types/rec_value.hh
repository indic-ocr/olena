// Copyright 2001, 2002  EPITA Research and Development Laboratory
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

#ifndef OLENA_VALUE_REC_VALUE_HH_
# define OLENA_VALUE_REC_VALUE_HH_

# include <oln/types/type.hh>
# include <oln/types/global_ops_traits.hh>
# include <oln/types/typetraits.hh>
# include <oln/types/optraits.hh>

namespace oln
{
  
  //
  //   Value hierarchy, used for data storing
  //
  ////////////////////////////////////////////

  template <class Self>
  class rec_value : type::any_type<Self>
  {
    typedef typename typetraits<Self>::store store_type;

  public:

    // Hooks
    store_type& value() { return _value; }
    const store_type& value() const { return _value; }

    Self& self() { return static_cast<Self&>(*this); }
    const Self& self() const { return static_cast<const Self&>(*this); }

  protected:
    store_type _value;
  };

  
  //
  //  Scalar branch
  //
  //////////////////

  template <class Self>
  class rec_scalar : public rec_value<Self>
  {};
  

  //
  // int
  //  

  template <class Self>
  class rec_int : public rec_scalar<Self>
  {};

  // int_u
  template <class Self>
  class rec_int_u : public rec_int<Self>
  {};

  // int_s
  template <class Self>
  class rec_int_s : public rec_int<Self>
  {};


  //
  // float
  //

  template <class Self>
  class rec_float : public rec_scalar<Self>
  {};


  // 
  //  Enumerated branch
  //
  /////////////////////

  template <class Self>
  class rec_enum : public rec_value<Self>
  {};
  
} // namespace oln

#endif // ndef OLENA_VALUE_REC_VALUE_HH_
