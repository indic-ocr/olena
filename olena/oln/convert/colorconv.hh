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

#ifndef OLENA_CONVERT_COLORCONV_HH
# define OLENA_CONVERT_COLORCONV_HH

# include <ntg/color/color.hh>
# include <oln/convert/conversion.hh>

namespace oln {
  namespace convert {

    namespace internal {

      /* Define this specialization separately to work around a bug
	 in gcc.  Specializing
	   conv_output<icomps,icolors,ocomps,ocolors,I>::output<T>
         for T = ntg::color<icomps,Q,colors> (Q generic) does not work.

	 See PR/4882.
	 http://gcc.gnu.org/cgi-bin/gnatsweb.pl?cmd=view&pr=4882&database=gcc
      */

      template< class T,
		unsigned icomps,
		template<unsigned> class icolor,
		unsigned ocomps,
		template<unsigned> class ocolor >
      struct _color_conversion {};

      template< unsigned qbits,
		unsigned icomps,
		template<unsigned> class icolor,
		unsigned ocomps,
		template<unsigned> class ocolor >
      struct _color_conversion<ntg::color<icomps, qbits, icolor>,
			       icomps, icolor, ocomps, ocolor >
      {
	typedef ntg::color<ocomps, qbits, ocolor> ret;
      };

    }

    template< unsigned icomps,
	      template<unsigned> class icolor,
	      unsigned ocomps,
	      template<unsigned> class ocolor,
	      class Exact = mlc::final >
    class color_conversion : public conversion< typename mlc::exact_vt<color_conversion<icomps, icolor, ocomps, ocolor, Exact>, Exact>::ret >
    {

    public:
      template <class T>
      struct output {
	typedef typename internal::_color_conversion<T,
						     icomps, icolor,
						     ocomps, ocolor>::ret ret;
      };
    };

  } // convert
} // oln


#endif // OLENA_CONVERT_COLORCONV_HH
