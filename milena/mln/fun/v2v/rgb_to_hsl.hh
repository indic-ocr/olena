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
// License.
// reasons why the executable file might be covered by the GNU General
// Public License.

#ifndef MLN_FUN_V2V_RGB_TO_HSL_HH
# define MLN_FUN_V2V_RGB_TO_HSL_HH

# include <cmath>

# include <mln/math/round.hh>
# include <mln/math/max.hh>
# include <mln/math/min.hh>

# include <mln/trait/value_.hh>

# include <mln/value/rgb.hh>

namespace mln
{

  // Forward declaration
  namespace value
  {
    template <typename H, typename S, typename L> class hsl_;
    typedef hsl_<float, float, float> hsl_f;
  }

  namespace fun
  {

    namespace v2v
    {

      template <typename T_hsl>
      struct f_rgb_to_hsl_ : public Function_v2v< f_rgb_to_hsl_<T_hsl> >
      {
	typedef T_hsl result;

	template <typename T_rgb>
	T_hsl operator()(const T_rgb& rgb) const;

      };

      typedef f_rgb_to_hsl_<value::hsl_f> f_rgb_to_hsl_f_t;

      extern f_rgb_to_hsl_f_t f_rgb_to_hsl_f;


# ifndef MLN_INCLUDE_ONLY

      /// Global variables.
      /// \{
      f_rgb_to_hsl_f_t f_rgb_to_hsl_f;
      /// \}


      template <typename T_hsl>
      template <typename T_rgb>
      inline
      T_hsl
      f_rgb_to_hsl_<T_hsl>::operator()(const T_rgb& rgb) const
      {
	// Locals.
	T_hsl hsl;

	typename T_rgb::red_t rmax = math::max(rgb.red(), math::max(rgb.green(), rgb.blue()));
	typename T_rgb::red_t rmin = math::min(rgb.red(), math::min(rgb.green(), rgb.blue()));

	if (rmin == rmax)
	  hsl.hue() = 0;
	else
	  if (rmax == rgb.red())
	    {
	      hsl.hue() = (60. * (rgb.green() - rgb.blue()) / (rmax - rmin));
	      if (hsl.hue() < 0)
		hsl.hue() += 360.;
	    }
	  else
	    if (rmax == rgb.green())
	      hsl.hue() = (60. * (rgb.blue() - rgb.red()) / (rmax - rmin)) + 120.;
	    else
	      hsl.hue() = (60. * (rgb.red() - rgb.green()) / (rmax - rmin)) + 240;

	hsl.lum() = ((double) rmax + rmin) / 2;

	// We want min and max between 0 and 1
	rmax -= mln_min(typename T_rgb::red_t);
	rmin -= mln_min(typename T_rgb::red_t);
	double nmax = (double) rmax / (mln_max(typename T_rgb::red_t) - mln_min(typename T_rgb::red_t));
	double nmin = (double) rmin / (mln_max(typename T_rgb::red_t) - mln_min(typename T_rgb::red_t));

	if (rmin == rmax)
	  hsl.sat() = 0;
	else
	  if (hsl.lum() <= 0.5)
	    hsl.sat() = (nmax - nmin) / (nmax + nmin);
	  else
	    hsl.sat() = (nmax - nmin) / (2 - nmax - nmin);

	return hsl;
      }


# endif // !MLN_INCLUDE_ONLY

    } // end of namespace fun::v2v

  } // end of namespace fun

} // end of namespace mln

#endif // ! MLN_FUN_V2V_RGB_TO_HSL_HH
