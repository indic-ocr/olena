// Copyright (C) 2005 EPITA Research and Development Laboratory
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

#ifndef OLENA_CORE_ABSTRACT_IMAGE_WITH_DATA_HH
# define OLENA_CORE_ABSTRACT_IMAGE_WITH_DATA_HH


# include <mlc/tracked_ptr.hh>

# include <oln/core/abstract/entry.hh>


/*! \namespace oln
** \brief oln namespace.
*/
namespace oln {


  // fwd decl
  namespace abstract {
    template <typename E> class image_with_data;
  }

  // category
  template <typename E>
  struct set_category < abstract::image_with_data<E> >
  {
    typedef category::image ret;
  };

  // super_type
  template <typename E>
  struct set_super_type < abstract::image_with_data<E> >
  {
    typedef abstract::image_entry<E> ret;
  };

  // props
  template <typename E>
  struct set_props < category::image, abstract::image_with_data<E> > : public props_of<category::image>
  {
    // intrusive property:
    typedef is_a<abstract::readwrite_image> image_constness_type;
  };



  /*! \namespace oln::abstract
  ** \brief oln::abstract namespace.
  */
  namespace abstract {


    /*! \class abstract::image_with_data<E>
    **
    ** Class for images that contains data (a value per image point).
    **
    ** Parameter E is the exact type of image.
    */

    template <typename E>
    class image_with_data : public image_entry<E>
    {

    public:

      /// typedefs

      typedef oln_type_of(E, size)  size_type;
      typedef oln_type_of(E, point) point_type;
      typedef oln_type_of(E, value) value_type;
      typedef oln_type_of(E, storage) storage_type;


      /*! \brief Implement abstract::image<E>::size() so return the
      **  size of the current image.
      **
      ** \return An object deriving from abstract::size.  Ex: if the
      ** image is an image2d<something>, the returned object is a
      ** size2d.
      */

      const size_type& impl_size() const
      {
	precondition(this->has_data());
	return this->data_->size();
      }


      /*! \brief Implement abstract::image<E>::npoints() so return the
      **  size of the current image.
      **
      ** \return A positive value.  It can be 0 when the image size is
      ** not yet defined; ex: image2d<int> ima; cout << ima.npoints();
      */

      unsigned long impl_npoints() const
      {
	precondition(this->has_data());
	return this->data_->npoints();
      }


      /*! \brief Implement abstract::image<E>::hold(p) so test if the
      ** point \a p belongs to the current image.  Please note that a
      ** point of the outer boundary of an image does NOT belong to
      ** the image.
      **
      ** \return True if p belongs to the current image, false otherwise.
      */

      bool impl_hold(const point_type& p) const
      {
	precondition(this->has_data());
	return this->data_->hold(p);
      }

      bool impl_hold_large(const point_type& p) const
      {
	precondition(this->has_data());
	return this->data_->hold_large(p);
      }


      /*! \brief Implement both abstract::readonly_image<E>::get(p)
      ** and abstract::readwrite_image<E>::get(p) so read-only access
      ** to the value stored at \a p in the current image.
      **
      ** \return True if p belongs to the current image, false otherwise.
      */

      const value_type impl_get(const point_type& p) const
      {
	precondition(this->has_data());
	return this->data_->get(p);
      }


      /*! \brief Implement abstract::readwrite_image<E>::set(p, v) so
      ** write the value \a v at \a p in the current image.
      */

      template <typename V>
      void impl_set(const point_type& p, const V& v)
      {
	precondition(this->has_data());
	this->data_->set(p, v);
      }

      /*! \brief True if the image contains data.
      */
      bool has_data() const
      {
        return data_ != 0;
      }

      void resize_border(size_t new_border, bool copy_border = false)
      {
	this->data_->resize_border(new_border, copy_border);
      }


    protected:

      /*! \brief Constructor (protected) with no memory allocation for
      ** data.
      */
      image_with_data() :
	data_(0)
      {
      }


      /*! \brief Constructor (protected) with memory allocation for
      ** data.
      */
      image_with_data(const size_type& size) :
	data_(new storage_type(size))
      {
      }


      /*! \brief Copy constructor (protected) with shallow data copy.
      */
      image_with_data(image_with_data& rhs)
      {
	this->data_ = rhs.data_;
      }

      /*! \brief Data storage.
      */
      mlc::tracked_ptr<storage_type> data_;

    };


  } // end of namespace abstract


} // end of namespace oln


#endif // ! OLENA_CORE_ABSTRACT_IMAGE_WITH_DATA_HH
