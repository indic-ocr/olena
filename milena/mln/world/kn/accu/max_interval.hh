// Copyright (C) 2012 EPITA Research and Development Laboratory (LRDE)
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

#ifndef MLN_WORLD_KN_ACCU_MAX_INTERVAL_HH
# define MLN_WORLD_KN_ACCU_MAX_INTERVAL_HH

/// \file
///
/// \brief Define an accumulator that computes a max on a specific
/// interval.

# include <mln/core/concept/meta_accumulator.hh>
# include <mln/accu/internal/base.hh>
# include <mln/trait/value_.hh>
# include <mln/util/pix.hh>
# include <mln/value/interval.hh>


namespace mln
{


  // Forward declaration.
  namespace world {
    namespace kn {
      namespace accu {
	template <typename T> struct max_interval;
      }
    }
  }


  // Traits.

  namespace trait
  {

    template <typename T>
    struct accumulator_< world::kn::accu::max_interval<T> >
    {
      typedef accumulator::has_untake::no     has_untake;
      typedef accumulator::has_set_value::yes has_set_value;
      typedef accumulator::has_stop::no       has_stop;
      typedef accumulator::when_pix::use_v    when_pix;
    };

  } // end of namespace mln::trait


  namespace world
  {

    namespace kn
    {

      namespace accu
      {

	/// \brief Minimum accumulator restricted to a specific
	/// interval.
	///
	/// The parameter \c T is the type of values.
	///
	/// \ingroup modaccuvalues
	template <typename T>
	struct max_interval
	  : public mln::accu::internal::base< const T& , max_interval<T> >
	{
	  typedef T argument;

	  max_interval();
	  max_interval(const value::interval<T>& inter);
	  template <typename U, typename V>
	  max_interval(const U& first, const V& last);

	  /// Manipulators.
	  /// \{
	  void init();
	  void take_as_init_(const argument& t);
	  void take(const argument& t);
	  void take(const max_interval<T>& other);
	  /// \}

	  /// Force the value of the min to \a t.
	  void set_value(const T& t);

	  /// Get the value of the accumulator.
	  const T& to_result() const;

	  /// Check whether this accu is able to return a result.
	  /// Always true here.
	  bool is_valid() const;

	protected:

	  T t_;
	  value::interval<T> inter_;
	};


	template <typename I> struct max_interval< util::pix<I> >;


# ifndef MLN_INCLUDE_ONLY

	template <typename T>
	inline
	max_interval<T>::max_interval()
	{
	  inter_ = value::interval<T>(mln_min(T), mln_max(T));
	  init();
	}

	template <typename T>
	inline
	max_interval<T>::max_interval(const value::interval<T>& inter)
	{
	  inter_ = inter;
	  init();
	}

	template <typename T>
	template <typename U, typename V>
	max_interval<T>::max_interval(const U& first, const V& last)
	{
	  mlc_converts_to(U,T)::check();
	  mlc_converts_to(V,T)::check();
	  inter_ = value::interval<T>(first, last);
	  init();
	}

	template <typename T>
	inline
	void
	max_interval<T>::init()
	{
	  t_ = inter_.first();
	}

	template <typename T>
	inline
	void
	max_interval<T>::take_as_init_(const argument& t)
	{
	  t_ = t;
	}

	template <typename T>
	inline
	void
	max_interval<T>::take(const argument& t)
	{
	  if (t > t_)
	    t_ = t;
	}

	template <typename T>
	inline
	void
	max_interval<T>::take(const max_interval<T>& other)
	{
	  if (other.t_ > t_)
	    t_ = other.t_;
	}

	template <typename T>
	inline
	void
	max_interval<T>::set_value(const T& t)
	{
	  t_ = t;
	}

	template <typename T>
	inline
	const T&
	max_interval<T>::to_result() const
	{
	  return t_;
	}

	template <typename T>
	inline
	bool
	max_interval<T>::is_valid() const
	{
	  return true;
	}

# endif // ! MLN_INCLUDE_ONLY

      } // end of namespace mln::world::kn::accu

    } // end of namespace mln::world::kn

  } // end of namespace mln::world

} // end of namespace mln


#endif // ! MLN_WORLD_KN_ACCU_MAX_INTERVAL_HH