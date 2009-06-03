// Copyright (C) 2009 EPITA Research and Development Laboratory
// (LRDE)
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

#ifndef MLN_OPT_ELEMENT_HH
# define MLN_OPT_ELEMENT_HH

/// \file mln/opt/element.hh
///
/// Define the opt::element and opt::nelements routines.

# include <mln/core/concept/image.hh>
# include <mln/trait/images.hh>

namespace mln
{

  namespace opt
  {

    template <typename I>
    inline
    mln_rvalue(I) element(const Image<I>& ima, unsigned index);

    template <typename I>
    inline
    mln_lvalue(I) element(Image<I>& ima, unsigned index);

    template <typename I>
    inline
    unsigned nelements(const Image<I>& ima);


# ifndef MLN_INCLUDE_ONLY

    namespace impl
    {

      template <typename I>
      inline
      mln_rvalue(I) element_impl(trait::image::category::domain_morpher,
                                 const Image<I>& ima, unsigned index)
      {
        return element(*exact(ima).delegatee_());
      }

      template <typename I>
      inline
      mln_rvalue(I) element_impl(trait::image::category::any,
                                 const Image<I>& ima, unsigned index)
      {
        mlc_and(mlc_is(mln_trait_image_value_storage(I),
                       trait::image::value_storage::one_block),
                mlc_is(mln_trait_image_value_access(I),
                       trait::image::value_access::direct))::check();

        return exact(ima).element(index);
      }


      template <typename I>
      inline
      mln_lvalue(I) element_impl(trait::image::category::domain_morpher,
                                 Image<I>& ima, unsigned index)
      {
        return element(*exact(ima).delegatee_());
      }

      template <typename I>
      inline
      mln_lvalue(I) element_impl(trait::image::category::any,
                                 Image<I>& ima, unsigned index)
      {
        mlc_and(mlc_is(mln_trait_image_value_storage(I),
                       trait::image::value_storage::one_block),
                mlc_is(mln_trait_image_value_access(I),
                       trait::image::value_access::direct))::check();

        return exact(ima).element(index);
      }




      template <typename I>
      inline
      unsigned nelements_impl(trait::image::category::domain_morpher,
                              const Image<I>& ima)
      {
        return nelements(*exact(ima).delegatee_());
      }

      template <typename I>
      inline
      unsigned nelements_impl(trait::image::category::any,
                              const Image<I>& ima)
      {
        mlc_is(mln_trait_image_value_storage(I),
               trait::image::value_storage::one_block)::check();

        return exact(ima).nelements();
      }






    } // end of namespace mln::opt::impl


    template <typename I>
    inline
    mln_rvalue(I) element(const Image<I>& ima, unsigned index)
    {
      return impl::element_impl(mln_trait_image_category(I)(), ima, index);
    }

    template <typename I>
    inline
    mln_lvalue(I) element(Image<I>& ima, unsigned index)
    {
      return impl::element_impl(mln_trait_image_category(I)(), ima, index);
    }


    template <typename I>
    inline
    unsigned nelements(const Image<I>& ima)
    {
      return impl::nelements_impl(mln_trait_image_category(I)(), ima);
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::opt

} // end of namespace mln


#endif // ! MLN_OPT_VALUE_HH
