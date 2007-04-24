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

#ifndef OLN_CORE_INTERNAL_WEIGHTED_WINDOW_BASE_HH
# define OLN_CORE_INTERNAL_WEIGHTED_WINDOW_BASE_HH

# include <oln/core/concept/weighted_window.hh>


namespace oln
{


  // Fwd decl.
  namespace internal { template <typename Exact> class weighted_window_base_; }


  // Super type.
  template <typename Exact>
  struct super_trait_< internal::weighted_window_base_<Exact> >
  {
    typedef Weighted_Window<Exact> ret;
  };


  /// Virtual types.
  template <typename Exact>
  struct vtypes< internal::weighted_window_base_<Exact> >
  {

//     typedef stc::abstract point;
//     typedef stc::abstract fwd_qiter;
//     typedef stc::abstract bkd_qiter;
//     typedef stc::abstract weight;

//     typedef stc_deferred(point)     point__;
//     typedef stc_deferred(fwd_qiter) fwd_qiter__;

//     typedef stc::final< oln_grid(point__) > grid;
//     typedef stc::final< fwd_qiter__ >       qiter;

    typedef stc::final< stc::is<Weighted_Window> >   category;
  };


  namespace internal
  {

    /// Base class for implementation of weighted_window classes.

    template <typename Exact>
    class weighted_window_base_ : public Weighted_Window<Exact>
    {
    public:

      stc_typename(point);
      stc_typename(weight);

    protected:
      weighted_window_base_();

    }; // end of class oln::internal::weighted_window_base_<Exact>



# ifndef OLN_INCLUDE_ONLY

    template <typename Exact>
    weighted_window_base_<Exact>::weighted_window_base_()
    {
    }

# endif // ! OLN_INCLUDE_ONLY

  } // end of namespace oln::internal

} // end of namespace oln


#endif // ! OLN_CORE_INTERNAL_WEIGHTED_WINDOW_BASE_HH
