// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
//
// This file is part of Olena.
//
// Olena is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation, version 2 of the License.
//
// Olena is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Olena.  If not, see <http://www.gnu.org/licenses/>.
//
// As a special exception, you may use this file as part of a free
// software project without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to produce
// an executable, this file does not by itself cause the resulting
// executable to be covered by the GNU General Public License.  This
// exception does not however invalidate any other reasons why the
// executable file might be covered by the GNU General Public License.

#ifndef SCRIBO_FILTER_THIN_OBJECTS_HH
# define SCRIBO_FILTER_THIN_OBJECTS_HH

/// \file
///
/// Remove too thin objects.

# include <mln/core/concept/image.hh>
# include <mln/core/concept/neighborhood.hh>

# include <mln/util/array.hh>

# include <scribo/core/object_image.hh>
# include <scribo/extract/primitive/objects.hh>

namespace scribo
{

  namespace filter
  {

    using namespace mln;

    /// Remove objects thinner or equal to \p min_thickness.
    ///
    /// \param[in] input_ a binary image.
    /// \param[in] nbh_ a neighborhood used in labeling algorithms.
    /// \param[in] label_type the label type used for labeling.
    /// \param[in] min_thickness the minimum thickness value.
    ///
    /// \result A binary image without thin objects.
    //
    template <typename I, typename N, typename V>
    inline
    mln_concrete(I)
    thin_objects(const Image<I>& input_,
		 const Neighborhood<N>& nbh_,
		 const V& label_type,
		 unsigned min_thickness);

    /// Remove lines of text thinner or equal to \p min_thickness.
    ///
    /// \param[in] objects An object image.
    /// \param[in] min_thickness the minimum thickness value.
    ///
    /// \result An object image without too thin objects.
    //
    template <typename L>
    inline
    object_image(L)
    thin_objects(const object_image(L)& text,
		 unsigned min_thickness);


# ifndef MLN_INCLUDE_ONLY

    namespace internal
    {


      /// Filter Functor.
      /// Return false for all objects which are too large.
      template <typename L>
      struct thin_objects_filter
	: Function_v2b< thin_objects_filter<L> >
      {
	typedef accu::bbox<mln_psite(L)> box_accu_t;

	/// Constructor
	///
	/// \param[in] objects object bounding boxes.
	/// \param[in] min_thickness the minimum thickness allowed.
	thin_objects_filter(const object_image(L)& objects,
			    unsigned min_thickness)
	  : objects_(objects), min_thickness_(min_thickness)
	{
	}


	/// Return false if the objects is thinner than
	/// \p min_thickness_.
	///
	/// \param[in] l An image value.
	bool operator()(const mln_value(L)& l) const
	{
	  if (l == literal::zero)
	    return true;
	  return objects_.bbox(l).nrows() > min_thickness_
		&& objects_.bbox(l).ncols() > min_thickness_;
	}

	/// Component bounding boxes.
	object_image(L) objects_;

	/// The minimum thickness.
	unsigned min_thickness_;
      };


    } //  end of namespace scribo::filter::internal


    template <typename I, typename N, typename V>
    inline
    mln_concrete(I)
    thin_objects(const Image<I>& input_,
		 const Neighborhood<N>& nbh_,
		 const V& label_type,
		 unsigned min_thickness)
    {
      trace::entering("scribo::filter::thin_objects");

      const I& input = exact(input_);
      const N& nbh = exact(nbh_);

      mln_precondition(input.is_valid());
      mln_precondition(nbh.is_valid());

      V nlabels;
      typedef mln_ch_value(I,V) lbl_t;
      object_image(lbl_t) objects
	  = extract::primitive::objects(input, nbh, nlabels);

      typedef internal::thin_objects_filter<lbl_t> func_t;
      func_t fv2b(objects, min_thickness);
      objects.relabel(fv2b);

      mln_concrete(I) output = duplicate(input);
      data::fill((output | pw::value(objects) == pw::cst(literal::zero)).rw(),
		 false);

      trace::exiting("scribo::filter::thin_objects");
      return output;
    }


    template <typename L>
    inline
    object_image(L)
    thin_objects(const object_image(L)& objects,
		 unsigned min_thickness)
    {
      trace::entering("scribo::filter::thin_objects");

      mln_precondition(objects.is_valid());

      typedef internal::thin_objects_filter<L> func_t;
      func_t is_not_too_thin(objects, min_thickness);

      object_image(L) output;
      output.init_from_(objects);
      output.relabel(is_not_too_thin);

      trace::exiting("scribo::filter::thin_objects");
      return output;
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace scribo::filter

} // end of namespace scribo


#endif // ! SCRIBO_FILTER_THIN_OBJECTS_HH
