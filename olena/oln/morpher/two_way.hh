// Copyright (C) 2006 EPITA Research and Development Laboratory
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

#ifndef OLN_MORPHER_TWO_WAY_HH
# define OLN_MORPHER_TWO_WAY_HH

# include <oln/value/two_way.hh>
# include <oln/morpher/internal/image_value_morpher.hh>


namespace oln
{

  namespace morpher
  {
    // Forward declaration.
    template <typename Image, typename Fun> struct two_way;

  } // end of namespace oln::morpher


  /// Super type.
  template <typename Image, typename Fun>
  struct set_super_type< morpher::two_way<Image, Fun> >
  {
    typedef morpher::two_way<Image, Fun> self_t;
    typedef morpher::internal::image_value_morpher<Image, self_t> ret;
  };


  template <typename Image, typename Fun>
  struct vtypes< morpher::two_way<Image, Fun> >
  {
    typedef morpher::two_way<Image, Fun> self_t;
  public:
    typedef mlc::true_ is_computed_type;

    typedef typename Fun::result_type   value_type;
    typedef value::two_way<Image, Fun> lvalue_type;

    typedef typename Fun::result_type rvalue_type;
  };


  namespace morpher
  {

    /// 'Image thru Function' morpher.
    template <typename Image, typename Fun>
    class two_way : public internal::image_value_morpher< Image,
							   morpher::two_way<Image, Fun> >
    {
    private:

      typedef two_way<Image, Fun> self_t;

      typedef internal::image_value_morpher<Image, self_t> super_t;
      using super_t::image_;

      typedef oln_rvalue(self_t) rvalue_t;
      typedef oln_lvalue(self_t) lvalue_t;
      typedef oln_psite(self_t)  psite_t;

    public:

      two_way(Image& image, Fun fun);
      two_way(Image& image);

      two_way(oln::abstract::mutable_image<Image>& image,
	      const oln::abstract::fun_v2w2v<Fun>& fun);

      rvalue_t impl_op_read(const psite_t& p) const;
      lvalue_t impl_op_readwrite(const psite_t& p);

    protected:

      Fun fun_;
    };


    namespace ERROR
    {

      struct FIXME;

    } // end of namespace oln::morpher::ERROR

  } // end of namespace oln::morpher

} // end of namespace oln


# ifndef OLN_INCLUDE_ONLY
#  include "two_way.hxx"
# endif

# include <oln/value/two_way.hxx>


#endif // ! OLN_MORPHER_TWO_WAY_HH








