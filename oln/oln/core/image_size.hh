// Copyright (C) 2001, 2002  EPITA Research and Development Laboratory
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

#ifndef OLENA_CORE_IMAGE_SIZE_HH
# define OLENA_CORE_IMAGE_SIZE_HH

# include <oln/core/type.hh>


namespace oln {


  template<class Exact>
  struct image_size : public type::any< Exact >
  {

    static std::string name() { return std::string("image_size<") + Exact::name() + ">"; }
  protected:
    image_size() {}
  };

  /* Every dimension specializes this trait and define a ret typedef.  */
  template< unsigned Dim >
  struct image_size_for_dim {};

# define _ImageSizeForDim(DIM, TYPE)		\
  template<>					\
  struct image_size_for_dim<DIM> {		\
    typedef TYPE ret;				\
  };

} // end of oln


#endif // ! OLENA_CORE_IMAGE_SIZE_HH
