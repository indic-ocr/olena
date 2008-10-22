// Copyright (C) 2008 EPITA Research and Development Laboratory
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

#ifndef MLN_SET_UNI_HH
# define MLN_SET_UNI_HH

/*! \file mln/set/uni.hh
 *
 * \brief Several routines to compute the union of a couple of sets.
 */

# include <mln/convert/to_std_set.hh>
# include <mln/convert/to_window.hh>
# include <mln/convert/to_p_set.hh>
# include <mln/metal/equal.hh>
# include <mln/util/ord.hh>


namespace mln
{

  namespace set
  {

    /*! \brief Union of a couple of windows.
     *
     * \relates mln::Window
     */
    template <typename Wl, typename Wr>
    window<mln_dpoint(Wl)>
    uni(const Window<Wl>& lhs, const Window<Wr>& rhs);

    /*! \brief Union of a couple of point sets.
     *
     * \relates mln::Site_Set
     */
    template <typename Wl, typename Wr>
    p_set<mln_point(Wl)>
    uni(const Site_Set<Wl>& lhs, const Site_Set<Wr>& rhs);


# ifndef MLN_INCLUDE_ONLY

    template <typename Wl, typename Wr>
    inline
    window<mln_dpoint(Wl)>
    uni(const Window<Wl>& lhs, const Window<Wr>& rhs)
    {
      trace::entering("set::uni");
      mln::metal::equal<mln_dpoint(Wl), mln_dpoint(Wr)>::check();
      typedef mln_dpoint(Wl) D;
      std::set<D, util::ord<D> >
	sl = convert::to_std_set(lhs),
	sr = convert::to_std_set(rhs),
	s;
      std::set_union(sl.begin(), sl.end(),
		     sr.begin(), sr.end(),
		     std::inserter(s, s.begin()));
      trace::exiting("set::uni");
      return convert::to_window(s);
    }

    template <typename Wl, typename Wr>
    inline
    p_set<mln_point(Wl)>
    uni(const Site_Set<Wl>& lhs, const Site_Set<Wr>& rhs)
    {
      trace::entering("set::uni");
      mln::metal::equal<mln_point(Wl), mln_point(Wr)>::check();
      typedef mln_point(Wl) P;
      std::set<P, util::ord<P> >
	sl = convert::to_std_set(lhs),
	sr = convert::to_std_set(rhs),
	s;
      std::set_union(sl.begin(), sl.end(),
		     sr.begin(), sr.end(),
		     std::inserter(s, s.begin()));
      trace::exiting("set::uni");
      return convert::to_p_set(s);
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::set

} // end of namespace mln


#endif // ! MLN_SET_UNI_HH
