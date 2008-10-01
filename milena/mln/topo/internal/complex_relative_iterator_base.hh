// Copyright (C) 2008 EPITA Research and Development Laboratory (LRDE)
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
// License.  
// reasons why the executable file might be covered by the GNU General
// Public License.

#ifndef MLN_TOPO_INTERNAL_COMPLEX_RELATIVE_ITERATOR_BASE_HH
# define MLN_TOPO_INTERNAL_COMPLEX_RELATIVE_ITERATOR_BASE_HH

/** \file mln/topo/internal/complex_relative_iterator_base.hh
    \brief Definition of an implementation (factoring) class for
    iterators on mln::complex.

    The hierarchy of classes in this file is as follows
    
    \verbatim

                    complex_relative_iterator_base<F, E>
                                    ^
                                    |
                     ,--------------+--------------.
                     |                             |
   forward_complex_relative_iterator_base<F, E>    |
                                                   |
                              backward_complex_relative_iterator_base<F, E>

   \endverbatim
*/

# include <limits>

# include <mln/metal/equal.hh>

# include <mln/core/concept/iterator.hh>
# include <mln/topo/complex.hh>

/* FIXME: By moving iterator `i_' into
   internal::complex_relative_iterator_base, we'll be able to factor
   more methods (do_next_, update_f); this requires the type of this
   iterator be passed as an extra parameter to
   internal::complex_relative_iterator_base.  */


namespace mln
{

  namespace topo
  {

    namespace internal
    {

      /*-------------------------------------------------------.
      | topo::internal::complex_relative_iterator_base<F, E>.  |
      `-------------------------------------------------------*/

      /// \brief Factoring class for relative iterators on mln::complex.
      ///
      /// \arg \p F The type of the face handle.
      /// \arg \p E The type exact type of the iterator.
      template <typename F, typename E>
      class complex_relative_iterator_base : public Iterator<E>
      {
	typedef complex_relative_iterator_base<F, E> self_;

      public:
	typedef F face;
	// FIXME: Maybe we could just get the dimension D of the face's
	// complex, an define complex_type as mln::complex<D>?
	typedef typename F::complex_type complex_type;

	/// Construction and assignment.
	/// \{
	/* FIXME: Keep this non-const?  See a (big) comment about this in
	   milena/tests/complex_image.cc.   */
	complex_relative_iterator_base();
	/// \}

	/// Manipulation.
	/// \{
	/// Change the center face.
	void center_at(const F& c);

	/// Start an iteration.
	void start();
	/// Go to the next point.
	void next_();
	/// \}

	/// Conversion and accessors.
	/// \{
	/// Convert the iterator into an face handle.
	operator const face&() const;
	/// \}

      protected:
	/// A pointer to the center face around which this iterator
	/// moves.
	const face* c_;

	// The type of the set of vicinity sites (adjacent face handles).
	typedef std::vector<face> adj_faces_t;
	/// The set of faces adjacent to the reference face.
	adj_faces_t adj_faces_;

	/// The face handle this iterator is pointing to.
	face f_;
      };


      /* FIXME: This hand-made delegation is painful.  We should rely on
	 the general mechanism provided by Point_Site.  But then again, we
	 need to refine/adjust the interface of Point_Site w.r.t. the
	 mandatory conversions to points.  */
      template <typename F, typename E>
      inline
      std::ostream&
      operator<<(std::ostream& ostr, const complex_relative_iterator_base<F, E>& p);


      /*---------------------------------------------------------------.
      | topo::internal::forward_complex_relative_iterator_base<F, E>.  |
      `---------------------------------------------------------------*/

      /// \brief Factoring class for forward relative iterators on
      /// mln::complex.
      ///
      /// \arg \p F The type of the face handle.
      /// \arg \p E The type exact type of the iterator.
      template <typename F, typename E>
      class forward_complex_relative_iterator_base
	: public complex_relative_iterator_base<F, E>
      {
	typedef forward_complex_relative_iterator_base<F, E> self_;
	typedef complex_relative_iterator_base<F, E> super_;

      public:
	typedef F face;
	// FIXME: Maybe we could just get the dimension D of the face's
	// complex, an define complex_type as mln::complex<D>?
	typedef typename F::complex_type complex_type;

      public:
	/// Construction and assignment.
	/// \{
	/* FIXME: Keep this non-const?  See a (big) comment about this in
	   milena/tests/complex_image.cc.   */
	forward_complex_relative_iterator_base();
	/// \}

      public:
	/// Manipulation
	/// \{
	/// Test if the iterator is valid.
	bool is_valid() const;
	/// Invalidate the iterator.
	void invalidate();

	/// Start an iteration.
	void do_start_();
	/// Go to the next point.
	void do_next_();

	/// Update the target face.
	void update_f_();
	/// \}

      protected:
	/// An iterator on the set of adjacent edges.
	typename super_::adj_faces_t::const_iterator i_;
      };


      /*----------------------------------------------------------------.
      | topo::internal::backward_complex_relative_iterator_base<F, E>.  |
      `----------------------------------------------------------------*/

      /// \brief Factoring class for backward relative iterators on
      /// mln::complex.
      ///
      /// \arg \p F The type of the face handle.
      /// \arg \p E The type exact type of the iterator.
      template <typename F, typename E>
      class backward_complex_relative_iterator_base
	: public complex_relative_iterator_base<F, E>
      {
	typedef backward_complex_relative_iterator_base<F, E> self_;
	typedef complex_relative_iterator_base<F, E> super_;

      public:
	typedef F face;
	// FIXME: Maybe we could just get the dimension D of the face's
	// complex, an define complex_type as mln::complex<D>?
	typedef typename F::complex_type complex_type;

      public:
	/// Construction and assignment.
	/// \{
	/* FIXME: Keep this non-const?  See a (big) comment about this in
	   milena/tests/complex_image.cc.   */
	backward_complex_relative_iterator_base();
	/// \}

      public:
	/// Manipulation
	/// \{
	/// Test if the iterator is valid.
	bool is_valid() const;
	/// Invalidate the iterator.
	void invalidate();

	/// Start an iteration.
	void do_start_();
	/// Go to the next point.
	void do_next_();

	/// Update the target face.
	void update_f_();
	/// \}

      protected:
	/// An iterator on the set of adjacent edges.
	typename super_::adj_faces_t::const_reverse_iterator i_;
      };



# ifndef MLN_INCLUDE_ONLY

      /*-------------------------------------------------------.
      | topo::internal::complex_relative_iterator_base<F, E>.  |
      `-------------------------------------------------------*/

      template <typename F, typename E>
      inline
      complex_relative_iterator_base<F, E>::complex_relative_iterator_base()
	: c_(0)
      {
	// Ensure F and E are compatible.
	mlc_equal(F, typename E::face)::check();
	// Check for required methods in E.
	void (E::*m)() = & E::update_adj_faces_;
	m = 0;
      }

      template <typename F, typename E>
      inline
      void
      complex_relative_iterator_base<F, E>::center_at(const F& c)
      {
 	c_ = &c;
 	exact(this)->invalidate();
      }

      template <typename F, typename E>
      inline
      void
      complex_relative_iterator_base<F, E>::start()
      {
	exact(this)->do_start_();
	if (exact(this)->is_valid())
	  exact(this)->update_f_();
      }

      template <typename F, typename E>
      inline
      void
      complex_relative_iterator_base<F, E>::next_()
      {
	exact(this)->do_next_();
	if (exact(this)->is_valid())
	  exact(this)->update_f_();
      }

      template <typename F, typename E>
      inline
      complex_relative_iterator_base<F, E>::operator const F&() const
      {
	return f_;
      }


      template <typename F, typename E>
      inline
      std::ostream&
      operator<<(std::ostream& ostr,
		 const complex_relative_iterator_base<F, E>& p)
      {
	return ostr << F(p);
      }


      /*---------------------------------------------------------------.
      | topo::internal::forward_complex_relative_iterator_base<F, E>.  |
      `---------------------------------------------------------------*/

      template <typename F, typename E>
      inline
      forward_complex_relative_iterator_base<F, E>::forward_complex_relative_iterator_base()
      {
      }

      template <typename F, typename E>
      inline
      bool
      forward_complex_relative_iterator_base<F, E>::is_valid() const
      {
	return i_ != this->adj_faces_.end();
      }

      template <typename F, typename E>
      inline
      void
      forward_complex_relative_iterator_base<F, E>::invalidate()
      {
	i_ = this->adj_faces_.end();
      }

      template <typename F, typename E>
      inline
      void
      forward_complex_relative_iterator_base<F, E>::do_start_()
      {
	exact(this)->update_adj_faces_();
	i_ = this->adj_faces_.begin();
      }

      template <typename F, typename E>
      inline
      void
      forward_complex_relative_iterator_base<F, E>::do_next_()
      {
	++i_;
      }

      template <typename F, typename E>
      inline
      void
      forward_complex_relative_iterator_base<F, E>::update_f_()
      {
	this->f_ = *i_;
      }


      /*----------------------------------------------------------------.
      | topo::internal::backward_complex_relative_iterator_base<F, E>.  |
      `----------------------------------------------------------------*/

      template <typename F, typename E>
      inline
      backward_complex_relative_iterator_base<F, E>::backward_complex_relative_iterator_base()
      {
      }

      template <typename F, typename E>
      inline
      bool
      backward_complex_relative_iterator_base<F, E>::is_valid() const
      {
	return i_ != this->adj_faces_.rend();
      }

      template <typename F, typename E>
      inline
      void
      backward_complex_relative_iterator_base<F, E>::invalidate()
      {
	i_ = this->adj_faces_.rend();
      }

      template <typename F, typename E>
      inline
      void
      backward_complex_relative_iterator_base<F, E>::do_start_()
      {
	exact(this)->update_adj_faces_();
	i_ = this->adj_faces_.rbegin();
      }

      template <typename F, typename E>
      inline
      void
      backward_complex_relative_iterator_base<F, E>::do_next_()
      {
	++i_;
      }

      template <typename F, typename E>
      inline
      void
      backward_complex_relative_iterator_base<F, E>::update_f_()
      {
	this->f_ = *i_;
      }

# endif // ! MLN_INCLUDE_ONLY

    } // end of namespace mln::topo::internal

  } // end of namespace mln::topo

} // end of namespace mln

#endif // ! MLN_TOPO_INTERNAL_COMPLEX_RELATIVE_ITERATOR_BASE_HH
