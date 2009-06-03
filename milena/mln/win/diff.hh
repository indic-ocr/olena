// Copyright (C) 2008 EPITA Research and Development Laboratory
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

#ifndef MLN_WIN_DIFF_HH
# define MLN_WIN_DIFF_HH

/*! \file mln/win/diff.hh
 *
 * \brief Set difference between a couple of windows or neighborhoods.
 */

# include <mln/core/window.hh>
# include <mln/core/neighb.hh>



namespace mln
{

  /// Set difference between a couple of windows \p win1 and \p win2.
  template <typename W1, typename W2>
  mln_regular(W1)
  operator-(const Window<W1>& win1, const Window<W2>& win2);


  /// Set difference between a couple of neighborhoods \p nbh1 and \p nbh2.
  template <typename N1, typename N2>
  neighb<mln_deduce(N1, window, regular)>
  operator-(const Neighborhood<N1>& nbh1, const Neighborhood<N2>& nbh2);


# ifndef MLN_INCLUDE_ONLY

  template <typename W1, typename W2>
  inline
  mln_regular(W1)
  operator-(const Window<W1>& win1_, const Window<W2>& win2_)
  {
    trace::entering("win::diff");

    mln_is_simple_window(W1)::check();
    mln_is_simple_window(W2)::check();

    const W1& win1 = exact(win1_);
    const W2& win2 = exact(win2_);
    mln_regular(W1) tmp;

    const unsigned n = win1.size();
    for (unsigned i = 0; i < n; ++i)
      {
	if (win2.has(win1.dp(i)))
	  continue;
	tmp.insert(win1.dp(i));
      }

    trace::exiting("win::diff");
    return tmp;
  }


  template <typename N1, typename N2>
  neighb<mln_deduce(N1, window, regular)>
  operator-(const Neighborhood<N1>& nbh1, const Neighborhood<N2>& nbh2)
  {
    typedef mln_deduce(N1, window, regular) W1;
    W1 win = diff(exact(nbh1).win(), exact(nbh2).win());
    neighb<W1> tmp(win);
    return tmp;
  }

# endif // ! MLN_INCLUDE_ONLY

} // end of namespace mln


#endif // ! MLN_WIN_DIFF_HH
