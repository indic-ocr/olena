// Copyright 2001  EPITA Research and Development Laboratory
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


#ifndef OLENA_CONVERT_NRGBYIQ_HH
# define OLENA_CONVERT_NRGBYIQ_HH

# include "convert/colorconv.hh"
# include "value/nrgb.hh"
# include "value/yiq.hh"

/*--------------------------------------------------------------.
| The formulas used here come from ``Digital Image Processing   |
| Algorithms and Applications'', I. Pitas; Wiley-Interscience.  |
`--------------------------------------------------------------*/

namespace oln {
  namespace convert {

    struct nrgb_to_yiq
      : public color_conversion<3, nrgb_traits,
				3, yiq_traits, nrgb_to_yiq>
    {
      typedef type::bottom inferior;

      template <unsigned qbits>
      color<3, qbits, yiq_traits>
      operator() (const color<3, qbits, nrgb_traits>& v) const
      {
	vec<3, float> in = v.to_float();
	vec<3, float> out;
	out[yiq_Y] =
	  0.299 * in[nrgb_R] + 0.587 * in[nrgb_G] + 0.114 * in[nrgb_B];
	out[yiq_I] =
	  0.596 * in[nrgb_R] - 0.274 * in[nrgb_G] - 0.322 * in[nrgb_B];
	out[yiq_Q] =
	  0.211 * in[nrgb_R] - 0.523 * in[nrgb_G] + 0.312 * in[nrgb_B];
	return out;
      }

      static std::string name() { return "nrgb_to_yiq"; }
    };

    struct yiq_to_nrgb
      : public color_conversion<3, yiq_traits,
				3, nrgb_traits, yiq_to_nrgb>
    {
      typedef type::bottom inferior;

      template <unsigned qbits>
      color<3, qbits, nrgb_traits>
      operator() (const color<3, qbits, yiq_traits>& v) const
      {
	vec<3, float> in = v.to_float();
	vec<3, float> out;
	out[nrgb_R] = in[yiq_Y] + 0.95617 * in[yiq_I] + 0.62143 * in[yiq_Q];
	out[nrgb_G] = in[yiq_Y] - 0.27269 * in[yiq_I] - 0.64681 * in[yiq_Q];
	out[nrgb_B] = in[yiq_Y] - 1.10374 * in[yiq_I] + 1.70062 * in[yiq_Q];
	return out;
      }

      static std::string name() { return "yiq_to_nrgb"; }
    };

  } // convert
} // oln

#endif // OLENA_CONVERT_NRGBYIQ_HH
