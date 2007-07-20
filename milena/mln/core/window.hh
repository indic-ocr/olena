// Copyright (C) 2007 EPITA Research and Development Laboratory
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

#ifndef MLN_CORE_WINDOW_HH
# define MLN_CORE_WINDOW_HH

/*! \file mln/core/window.hh
 *
 * \brief Definition of the generic window class mln::window_.
 */

# include <mln/core/concept/window.hh>
# include <mln/core/concept/genpoint.hh>
# include <mln/core/internal/set_of.hh>
# include <mln/core/dpoint.hh>
# include <mln/core/box.hh>

# include <mln/convert/to_dpoint.hh>
# include <mln/fun/all.hh>
# include <mln/norm/infty.hh>


namespace mln
{

  // fwd decls
  template <typename D> class dpoints_fwd_piter;
  template <typename D> class dpoints_bkd_piter;
 

  /*! \brief Generic window class.
   *
   * This type of window is just like a set of delta-points.  The
   * parameter is \c D, type of delta-point.
   */
  template <typename D>
  struct window_ : public Window< window_<D> >,
		   public internal::set_of_<D>
  {
    /// Point associated type.
    typedef mln_point(D) point;

    /// Dpoint associated type.
    typedef D dpoint;

    /*! \brief Piter type to browse the points of a generic window
     * w.r.t. the ordering of delta-points.
     */
    typedef dpoints_fwd_piter<D> fwd_qiter;

    /*! \brief Piter type to browse the points of a generic window
     * w.r.t. the reverse ordering of delta-points.
     */
    typedef internal::fixme bkd_qiter;

    /*! \brief Same as fwd_qiter.
     */
    typedef fwd_qiter qiter;


    /*! \brief Constructor without argument.
     *
     * The constructed window is empty. 
     */
    window_();

    /*! \brief Test if the window is centered.
     *
     * \return True if the delta-point 0 belongs to the window.
     */
    bool is_centered() const;

    /*! \brief Test if the window is symmetric.
     */
    bool is_symmetric() const;

    /*! \brief Give the maximum coordinate gap between the window
      center and a window point.
    */
    unsigned delta() const;

    /// Give the symmetrical window.
    window_<D> sym_() const;

  protected:
    
    box_<point> b_;
  };


  // FIXME: Move both ops below to mln/core/concept/window.hh

  /// Shift a window \p win with a delta-point \p dp.
  template <typename W>
  window_<mln_dpoint(W)> operator+(const Window<W>& win,
				   const mln_dpoint(W)& dp);

  /// Shift a window \p win with the delta-point (-\p dp).
  template <typename W>
  window_<mln_dpoint(W)> operator-(const Window<W>& win,
				   const mln_dpoint(W)& dp);

  /// Substract \p rhs from \p lhs.
  // FIXME: Give details!
  template <typename Wl, typename Wr>
  window_<mln_dpoint(Wl)> operator-(const Window<Wl>& lhs,
				    const Window<Wr>& rhs);



# ifndef MLN_INCLUDE_ONLY

  // window_<D>

  template <typename D>
  window_<D>::window_()
  {
  }

  template <typename D>
  bool window_<D>::is_centered() const
  {
    static const D origin = all(0);
    return this->has(origin);
  }

  template <typename D>
  bool window_<D>::is_symmetric() const
  {
    return this->sym_() == *this;
  }

  template <typename D>
  unsigned window_<D>::delta() const
  {
    unsigned d = 0;
    const unsigned n = this->nelements();
    for (unsigned i = 0; i < n; ++i)
      {
	unsigned dd = norm::infty(this->element(i).to_vec());
	if (dd > d)
	  d = dd;
      }
    return d;
  }

  template <typename D>
  window_<D>
  window_<D>::sym_() const
  {
    window_<D> tmp;
    const unsigned n = this->nelements();
    for (unsigned i = 0; i < n; ++i)
      tmp.insert(- this->element(i));
    return tmp;
  }

  // operators

  template <typename W>
  window_<mln_dpoint(W)> operator+(const Window<W>& win,
				   const mln_dpoint(W)& dp)
  {
    typedef mln_point(W) P;
    window_<mln_dpoint(W)> tmp;
    mln_qiter(W) q(win, P::zero);
    for_all(q)
      tmp.insert(convert::to_dpoint(q) + dp);
    return tmp;
  }

  template <typename W>
  window_<mln_dpoint(W)> operator-(const Window<W>& win,
				   const mln_dpoint(W)& dp)
  {
    return win + (-dp);
  }

  template <typename W, typename Wr>
  window_<mln_dpoint(W)> operator-(const Window<W>& lhs,
				   const Window<Wr>& rhs)
  {
    typedef mln_point(W) P;
    window_<mln_dpoint(W)> tmp;
    mln_qiter(W) q(lhs, P::zero);
    for_all(q)
      {
	mln_dpoint(W) dp = convert::to_dpoint(q);
	if (! exact(rhs).has(dp))
	  tmp.insert(dp);
      }
    return tmp;
  }

# endif // ! MLN_INCLUDE_ONLY

} // end of namespace mln


# include <mln/core/dpoints_piter.hh>


#endif // ! MLN_CORE_WINDOW_HH
