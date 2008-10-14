// Copyright (C) 2007, 2008 EPITA Research and Development Laboratory
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

#ifndef MLN_ACCU_MAX_H_HH
# define MLN_ACCU_MAX_H_HH

/*! \file mln/accu/max_h.hh
 *
 * \brief Define a generic max accumulator class based on histogram.
 */

# include <mln/accu/internal/base.hh>
# include <mln/accu/histo.hh>
# include <mln/util/pix.hh>


namespace mln
{

  namespace accu
  {


    /*! \brief Generic max function based on histogram over a value set with
     * type \c V.
     */
    template <typename V>
    struct max_h : public mln::accu::internal::base< V, max_h<V> >
    {
      typedef V argument;
      typedef argument result;

      max_h();

      /// Manipulators.
      /// \{
      void init();
      void   take(const argument& t);
      void   take_as_init(const argument& t);
      void   take(const max_h<V>& other);
      void untake(const argument& t);
      /// \}

      unsigned card() const { return h_.sum(); }

      /// Get the value of the accumulator.
      argument to_result() const;

      const accu::histo<V>& histo() const;

      /// Check whether this accu is able to return a result.
      /// Always true here.
      bool is_valid() const;

      void debug_print_() const;

    protected:

      mutable accu::histo<V> h_;
      const value::set<V>& s_; // derived from h_

      mutable std::size_t sum_;
      mutable bool valid_;
      mutable std::size_t i_; // the max index
      mutable argument t_;       // the max argument

      // Auxiliary methods
      void update_() const;
      void go_minus_() const;
      void go_plus_() const;
    };



    template <typename I> struct max_h< util::pix<I> >;


    namespace meta
    {

      /*!
       * \brief Meta accumulator for max.
       */
      struct max_h : public Meta_Accumulator< max_h >
      {
	template <typename T>
	struct with
	{
	  typedef accu::max_h<T> ret;
	};
      };

    } // end of namespace mln::meta



# ifndef MLN_INCLUDE_ONLY

    template <typename V>
    inline
    max_h<V>::max_h()
      : h_(),
	s_(h_.vset())
    {
      init();
    }

    template <typename V>
    inline
    void
    max_h<V>::take(const argument& t)
    {
      if (h_.sum() == 0)
	{
	  this->take_as_init(t);
	  return;
	}
      h_.take(t);
      if (t > t_)
	{
	  ++sum_;
	  valid_ = false;
	}
    }

    template <typename V>
    inline
    void
    max_h<V>::take(const max_h<V>& other)
    {
      // h_
      h_.take(other.h_);
      for (unsigned i = this->card() - 1; i > i_; --i)
	sum_ += other.h_[i];
      valid_ = false;
      // FIXME: Optimize.
    }

    template <typename V>
    inline
    void
    max_h<V>::untake(const argument& t)
    {
      mln_precondition(h_(t) != 0);
      h_.untake(t);
      if (h_.sum() == 0)
	{
	  init();
	  return;
	}
      if (t > t_)
	{
	  mln_invariant(sum_ >= 1);
	  --sum_;
	  valid_ = false;
	}
      else
	if (t == t_ && h_[i_] == 0)
	  valid_ = false;
    }

    template <typename V>
    inline
    void
    max_h<V>::update_() const
    {
      if (sum_ != 0)
	go_plus_();
      else
	if (h_[i_] == 0)
	  go_minus_();
      valid_ = true;
    }

    template <typename V>
    inline
    void
    max_h<V>::go_plus_() const
    {
      do
	{
	  ++i_;
	  if (h_[i_] != 0)
	    sum_ -= h_[i_];
	}
      while (sum_ != 0);
      t_ = s_[i_];
    }

    template <typename V>
    inline
    void
    max_h<V>::go_minus_() const
    {
      do
	--i_;
      while (h_[i_] == 0);
      t_ = s_[i_];
    }

    template <typename V>
    inline
    void
    max_h<V>::init()
    {
      h_.init();
      sum_ = 0;
      i_ = mln_min(argument);
      t_ = s_[i_];
      valid_ = true;
    }

    template <typename V>
    inline
    void
    max_h<V>::take_as_init(const argument& t)
    {
      h_.take(t);
      sum_ = 0;
      i_ = s_.index_of(t);
      t_ = t;
      valid_ = true;
    }

    template <typename V>
    inline
    typename max_h<V>::argument
    max_h<V>::to_result() const
    {
      if (! valid_)
	update_();
      return t_;
    }

    template <typename V>
    inline
    const accu::histo<V>&
    max_h<V>::histo() const
    {
      return h_;
    }

    template <typename V>
    inline
    bool
    max_h<V>::is_valid() const
    {
      return true;
    }

    template <typename V>
    inline
    void
    max_h<V>::debug_print_() const
    {
      std::cout << "h={" << h_ << "} ";
      std::cout << "sum=" << sum_ << ' '
		<< "valid=" << valid_ << ' '
		<< "i=" << i_ << ' '
		<< "t=" << t_ << std::endl;
    }

    template <typename V>
    inline
    std::ostream& operator<<(std::ostream& ostr, const max_h<V>& m)
    {
      return ostr << m.to_result();
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::accu

} // end of namespace mln


#endif // ! MLN_ACCU_MAX_H_HH
