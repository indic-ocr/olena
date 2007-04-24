// Copyright (C) 2006, 2007 EPITA Research and Development Laboratory
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

#ifndef OLN_CORE_2D_WEIGHTED_WINDOW2D_HH
# define OLN_CORE_2D_WEIGHTED_WINDOW2D_HH

# include <cmath>
# include <oln/core/internal/weighted_window.hh>
# include <oln/core/2d/dpoint2d.hh>



namespace oln
{


  // Fwd decl.
  template <typename W> class weighted_window2d;


# define current weighted_window2d<W>
# define super   internal::weighted_window_< current >


  // Super type.
  template <typename W>
  struct super_trait_< current >
  {
    typedef super ret;
  };


  // Virtual types.
  template <typename W>
  struct vtypes< current >
  {
    typedef W       weight;
    typedef point2d point;
  };


  /// Generic classical weighted_window2d class.

  template <typename W>
  class weighted_window2d : public super
  {
  public:
    stc_using(weight);
    
    weighted_window2d();

    template <unsigned n>
    void impl_fill_with(const weight (&values)[n]);

  }; // end of class oln::weighted_window2d<W>



# ifndef OLN_INCLUDE_ONLY

  template <typename W>
  weighted_window2d<W>::weighted_window2d()
  {
  }

  template <typename W>
  template <unsigned n>
  void
  weighted_window2d<W>::impl_fill_with(const weight (&values)[n])
  {
    int h = int(std::sqrt(n)) / 2;
    precondition((2 * h + 1) * (2 * h + 1) == n);
    unsigned i = 0;
    for (int drow = -h; drow <= h; ++drow)
      for (int dcol = -h; dcol <= h; ++dcol)
	{
	  if (values[i] != 0)
	    this->take(values[i], dpoint2d(drow, dcol));
	  ++i;
	}
  }

# endif // ! OLN_INCLUDE_ONLY

# undef super
# undef current

} // end of namespace oln


#endif // ! OLN_CORE_2D_WEIGHTED_WINDOW2D_HH
