// Copyright (C) 2001, 2002, 2003  EPITA Research and Development Laboratory
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


#ifndef OLENA_CONVERT_BOUND_HH
# define OLENA_CONVERT_BOUND_HH

# include <oln/convert/abstract/conversion.hh>
# include <ntg/utils/cast.hh>

namespace oln {
  namespace convert {

    // FIXME: is this really useful with new types ?

    /* Like convert::force, but with saturation.  */
    template<class Output, class Exact = mlc::final>
    struct bound : public abstract::conversion_to_type< Output, typename mlc::exact_vt<bound<Output, Exact>, Exact>::ret >
    {
 
      template< class Input >
      Output 
      doit(const Input& v) const 
      {
	return ntg::cast::bound<Output>(v);
      }

      static std::string
      name()
      {
	// FIXME: ntg_name(Exact) will not work for mlc::final !
	return std::string("bound<")
	  + ntg_name(Output) + ", "
	  + "FIXME: ntg_name(Exact)" + ">";
      }
    };
    
  } // convert
} // oln

#endif // OLENA_CONVERT_BOUND_HH
