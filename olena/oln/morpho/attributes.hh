// Copyright (C) 2001, 2002, 2003, 2004  EPITA Research and Development Laboratory
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

#ifndef OLN_MORPHO_ATTRIBUTES_HH
# define OLN_MORPHO_ATTRIBUTES_HH
# include <mlc/type.hh>
# include <vector>

// attribute dedicated macros
# define attr_lambda_type(T)	typename oln::morpho::attr_traits<T>::lambda_type
# define attr_env_type(T)	typename oln::morpho::attr_traits<T>::env_type
# define attr_value_type(T)	typename oln::morpho::attr_traits<T>::value_type

# define attr_lambda_type_(T)	 oln::morpho::attr_traits<T>::lambda_type
# define attr_env_type_(T)	 oln::morpho::attr_traits<T>::env_type
# define attr_value_type_(T)	 oln::morpho::attr_traits<T>::value_type


# define attr_type_decl(self_type) \
      typedef mlc_exact_vt_type(self_type, Exact)	exact_type; \
      typedef attr_value_type(exact_type)		value_type; \
      typedef attr_env_type(exact_type)			env_type; \
      typedef attr_lambda_type(exact_type)		lambda_type

namespace oln {
  namespace morpho {
    /*!
    ** \brief oln::morpho::tools namespace
    */
    namespace tools {

      /*!
      ** \brief Absolute value of difference between v1 and v2.
      ** \warning Should be moved elsewhere.
      */
      template <class T>
      T diffabs(const T &v1, const T &v2)
      {
	return v1 > v2 ? v1 - v2 : v2 - v1;
      }
    } // !tools

    /*!
    ** \brief Top of environment hierarchy.
    */
    template <class Exact>
    struct env: public mlc_hierarchy::any<Exact>
    {
    };

    /*!
    ** \brief Useless environment.
    **
    ** This environment is an empty one.
    */
    struct NullEnv: public env<NullEnv>
    {
    };

    /*!
    ** \brief Environment containing image.
    **
    ** Used for image substitution in other_image attribute.
    */
    template <class I>
    struct OtherImageEnv: public env<OtherImageEnv<I> >
    {
      typedef abstract::image<I>	im_type;

      OtherImageEnv(const abstract::image<I> &im): im_(im)
      {};

      const im_type	&getImage() const
      {
	return im_;
      }

    protected:
      const im_type	&im_;
    };

    /*!
    ** \brief Environment containing point.
    **
    ** Used for point substitution in other_point attribute.
    */
    template <class I>
    struct OtherPointEnv: public env<OtherPointEnv<I> >
    {
      typedef abstract::image<I>	im_type;

//       OtherImageEnv(const abstract::image<I> &im): im_(im)
//       {};

      const oln_point_type(I)	&getPoint(const oln_point_type(I) &p) const
      {
	return p;
      }

//     protected:
//       const im_type	&im_;
    };

    // the traits fwd declaration
    /*!
    ** Traits  for attributes information.
    ** \param T: exact type of the attribute.
    */
    template <class T>
    struct attr_traits;

    /*!
    ** \brief Change the exact type of an attribute.
    **
    ** BE CAREFUL,  when you use specialization of  this traits, you
    ** say change_exact<In, Exact>::ret IS A In.
    ** Check this to avoid modeling problems.
    */
    template <class In, class Exact>
    struct change_exact;


      // the attributes hierarchy

      /*------------*
	| attribute |
	*-----------*/
    /*!
    ** \brief Attribute abstract class
    **
    ** Top of the attribute hierarchy.
    */
    template <class Exact>
    class attribute: public mlc_hierarchy::any<Exact>
    {
    public:
      typedef attribute<Exact>	self_type; /*< Self type of the class.*/
      attr_type_decl(self_type);

      /*!
      ** \brief += operator
      **
      ** This is a static dispatcher for the += operator.
      ** This method is abstract.
      */
      void operator+=(const exact_type &rhs)
      {
	mlc_dispatch(pe)(rhs);
      };

      /*!
      ** \brief >= operator
      **
      ** This is a static dispatcher for the >= operator.
      */
      bool operator>=(const lambda_type &lambda) const
      {
	mlc_dispatch(ge)(lambda);
      };

      /*!
      ** \brief < operator
      **
      ** This is a static dispatcher for the < operator.
      ** This method is abstract.
      */
      bool operator<(const lambda_type &lambda) const
      {
	mlc_dispatch(less)(lambda);
      };

      /*!
      ** \brief != operator
      **
      ** This is a static dispatcher for the != operator.
      ** This method is abstract.
      */
      bool operator!=(const lambda_type &lambda) const
      {
	mlc_dispatch(ne)(lambda);
      };

      /*!
      ** \brief >= operator implementation.
      **
      ** This is an implementation  of the >= operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T be called.
      */
      bool ge_impl(const lambda_type &lambda) const
      {
	return !(*this < lambda);
      };

    protected:
      attribute() {};

    };

      /*-----------*
	|   card    |
	*-----------*/

    /*!
    ** \brief Cardinal attribute.
    **
    ** It is equivalent to an area in 2d, and a volume in 3D.
    */
    template <class T = unsigned, class Exact = mlc::final>
    class card_type:
      public attribute<mlc_2_exact_vt_type(card_type, T, Exact)>
    {
    public:
      typedef card_type<T, Exact>			self_type; /*!< Self type of the class. */
      attr_type_decl(self_type);

      /*!
      ** \brief Basic Ctor.
      **
      ** \warning  After this  call, the  object is  only instantiated
      ** (not initialized).
      */
      card_type()
	{
	};

      /*!
      ** \brief Ctor from a lambda_type value.
      */
      card_type(const lambda_type &lambda): value_(lambda)
	{
	};

      /*!
      ** \brief Ctor from a point and an image.
      **
      ** Every parameters are useless.
      */
      template <class I>
	card_type(const abstract::image<I>&,
		  const oln_point_type(I)&,
		  const env_type&):
	value_(ntg_unit_val(value_type))
	  {
	  };


      /*!
      ** \brief += operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T be called.
      */
      void pe_impl(const self_type &rhs)
	{
	  value_ += rhs.value_;
	};

      /*!
      ** \brief < operator implementation.
      **
      ** This is an implementation  of the < operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T be called.
      */
      bool less_impl(const lambda_type &lambda) const
	{
	  return value_ < lambda;
	};

      /*!
      ** \brief != operator implementation.
      **
      ** This is an implementation  of the != operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T be called.
      */
      bool ne_impl(const lambda_type &lambda) const
	{
	  return lambda != value_;
	};

    protected:
      value_type value_; /*!< Value used inside the class. */
    };


      /*-----------*
	|  integral   |
	*-----------*/

    /*!
    ** \brief Integral attribute.
    **
    ** It is equivalent to volume in 2D, and weight in 3D.
    */
    template <class T = unsigned, class Exact = mlc::final>
    class integral_type:
      public attribute<mlc_2_exact_vt_type(integral_type, T, Exact)>
    {
    public:
      typedef integral_type<T, Exact>			self_type; /*!< Self type of the class. */
      attr_type_decl(self_type);

      /*!
      ** \brief Basic Ctor.
      **
      ** \warning  After this  call, the  object is  only instantiated
      ** (not initialized).
      */
      integral_type()
	{
	};

      /*!
      ** \brief Ctor from a lambda_type value.
      */
      integral_type(const lambda_type &lambda): value_(lambda)
	{
	};

      /*!
      ** \brief Ctor from a point and an image.
      */
      template <class I>
	integral_type(const abstract::image<I> &input,
		      const oln_point_type(I) &p,
		      const env_type &) :
	reflevel_(input[p]),
	area_(ntg_unit_val(value_type)),
	value_(ntg_unit_val(value_type))
	{
	};

      // interface part
      /*!
      ** \brief Accessor to value_.
      **
      ** Virtual method.
      ** \see getValue_impl()
      */
      const value_type &getValue() const
	{
	  mlc_dispatch(getValue)();
	};

      /*!
      ** \brief Accessor to the reference level.
      **
      ** \see getReflevel_impl()
      */
      const value_type &getReflevel() const
	{
	  mlc_dispatch(getReflevel)();
	};

      /*!
      ** \brief Accessor to the current area.
      **
      ** \see getArea_impl()
      */
      const value_type &getArea() const
	{
	  mlc_dispatch(getArea)();
	};

      // impl part
      /*!
      ** \brief Implementation of getValue().
      **
      ** Override this  method in  order to provide  a new  version of
      ** getValue().
      **
      ** \warning Do not call this method, use getValue() instead.
      */
      const value_type &getValue_impl() const
	{
	  return value_;
	};

      /*!
      ** \brief Implementation of getReflevel().
      **
      ** Override this  method in  order to provide  a new  version of
      ** getReflevel().
      **
      ** \warning Do not call this method, use getReflevel() instead.
      */
      const value_type &getReflevel_impl() const
	{
	  return reflevel_;
	};

      /*!
      ** \brief Implementation of getArea().
      **
      ** Override this  method in  order to provide  a new  version of
      ** getArea().
      **
      ** \warning Do not call this method, use getArea() instead.
      */
      const value_type &getArea_impl() const
	{
	  return area_;
	};

      /*!
      ** \brief += operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      void pe_impl(const self_type &rhs)
	{
	  value_ += rhs.getValue() + area_ * tools::diffabs(reflevel_, rhs.getReflevel());
	  area_ += rhs.getArea();
	};

      /*!
      ** \brief < operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool less_impl(const lambda_type &lambda) const
	{
	  return value_ < lambda;
	};

      /*!
      ** \brief != operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool ne_impl(const lambda_type &lambda) const
	{
	  return lambda != value_;
	};

      protected:
      value_type reflevel_; ///< Reference level.
      value_type area_; ///< Current area.
      value_type value_; ///< Current value (deduced from area and level).
      };

    /*-------------------*
      | other image_type |
      ------------------*/
    /*!
    ** \class other_image
    **
    ** \brief Metaclass used to change attribute behavior.
    **
    ** This class do the same job  that its Dad parameter, but force it
    ** to work on other data.
    */
    template <class Dad, class I, class Exact = mlc::final>
    class other_image:
      public change_exact<Dad, typename mlc::exact_vt<other_image<Dad, I, Exact>, Exact>::ret >::ret
    {
    public:
      typedef other_image<Dad, I,  Exact>						self_type; /*< Self type of the class.*/
      typedef typename abstract::image<mlc_exact_type(I)>				im_type; /*< Type of substituted image.*/
      attr_type_decl(self_type);
      typedef typename change_exact<Dad,
				    typename mlc::exact_vt<other_image<Dad, I, Exact>,
							   Exact>::ret >::ret		super_type; /*< Mother class type.*/

      /*!
      ** \brief Constructor.
      **
      ** Dispatch to Dad constructor.
      */
      other_image(): super_type()
      {
      };

      /*!
      ** \brief lambda_type Constructor.
      **
      ** Dispatch to Dad constructor.
      */
      other_image(const lambda_type &lambda): super_type(lambda)
      {
      };

      /*!
      ** \brief Image Constructor.
      **
      ** Dispatch to Dad constructor but substitute image argument with
      ** the image contained in the environment.
      */
      template <typename IM>
      other_image(const abstract::image<IM> &,
		  const oln_point_type(I) &p,
		  const env_type & e): super_type(e.getImage(), p, e)
      {
      };
    };

    /*--------------*
      | other_point |
      *------------*/
//     /*!
//     ** \class other_point
//     **
//     ** \brief Metaclass used to change attribute behavior.
//     **
//     ** This class do the same job  that its Dad parameter, but force it
//     ** to work on other data.
//     */
//     template <class Dad, class I, class Exact = mlc::final>
//     class other_point:
//       public change_exact<Dad, typename mlc::exact_vt<other_point<Dad, I, Exact>, Exact>::ret >::ret
//     {
//     public:
//       typedef other_image<Dad, I,  Exact>						self_type; /*< Self type of the class.*/
//       typedef typename abstract::image<mlc_exact_type(I)>				im_type; /*< Type of substituted image.*/
//       attr_type_decl(self_type);
//       typedef typename change_exact<Dad,
// 				    typename mlc::exact_vt<other_point<Dad, I, Exact>,
// 							   Exact>::ret >::ret		super_type; /*< Mother class type.*/

//       /*!
//       ** \brief Constructor.
//       **
//       ** Dispatch to Dad constructor.
//       */
//       other_point(): super_type()
//       {
//       };

//       /*!
//       ** \brief lambda_type Constructor.
//       **
//       ** Dispatch to Dad constructor.
//       */
//       other_point(const lambda_type &lambda): super_type(lambda)
//       {
//       };

//       /*!
//       ** \brief Image Constructor.
//       **
//       ** Dispatch to Dad constructor but substitute image argument with
//       ** the image contained in the environment.
//       */
//       template <typename IM>
//       other_point(const abstract::image<IM> &im,
// 		  const oln_point_type(I) &p,
// 		  const env_type &e): super_type(im, e.getPoint(p), e)
//       {
//       };
//     };

      /*-----------*
	|  height   |
	*-----------*/
    /*!
    ** \brief Attribute working on height between components.
    */
    template <class T = unsigned, class Exact = mlc::final>
    class height_type:
      public attribute<mlc_2_exact_vt_type(height_type, T, Exact)>
    {
    public:
      typedef height_type<T, Exact>			self_type;
      attr_type_decl(self_type);

      /*!
      ** \brief Basic Ctor.
      **
      ** \warning  After this  call, the  object is  only instantiated
      ** (not initialized).
      */
      height_type()
	{
	};

      /*!
      ** \brief Ctor from a lambda_type value.
      */
      height_type(const lambda_type &lambda):
	value_(lambda),
	min_(ntg_zero_val(value_type)),
	max_(lambda)
	{
	};

      /*!
      ** \brief Ctor from a point and an image.
      */
      template <class I>
	height_type(const abstract::image<I> &input,
		    const oln_point_type(I) &p,
		    const env_type&):
	value_(ntg_zero_val(value_type)),
	min_(input[p]),
	max_(input[p])
	{
	};

      /*!
      ** \brief Accessor to min value.
      **
      ** Virtual method.
      ** \see getMin_impl()
      */
      const value_type &getMin() const
	{
	  mlc_dispatch(getMin)();
	};

      /*!
      ** \brief Accessor to max value.
      **
      ** Virtual method.
      ** \see getMax_impl()
      */
      const value_type &getMax() const
	{
	  mlc_dispatch(getMax)();
	};

      // impl part
      /*!
      ** \brief Implementation of getMin().
      **
      ** Override this  method in  order to provide  a new  version of
      ** getMin().
      **
      ** \warning Do not call this method, use getMin() instead.
      */
      const value_type &getMin_impl() const
	{
	  return min_;
	};

      /*!
      ** \brief Implementation of getMax().
      **
      ** Override this  method in  order to provide  a new  version of
      ** getMax().
      **
      ** \warning Do not call this method, use getMax() instead.
      */
      const value_type &getMax_impl() const
	{
	  return max_;
	};

      /*!
      ** \brief += operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      void pe_impl(const height_type &rhs)
	{
	  min_ = ntg::min(min_, rhs.getMin());
	  max_ = ntg::max(max_, rhs.getMax());
	  value_ = max_ - min_;
	};

      /*!
      ** \brief < operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool less_impl(const lambda_type &lambda) const
	{
	  return value_ < lambda;
	};

      /*!
      ** \brief != operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool ne_impl(const lambda_type &lambda) const
	{
	  return lambda != value_;
	};

      protected:
      value_type	value_; ///< Current value.
      value_type	min_; ///< Current minimum.
      value_type	max_; ///< Current maximum.
    };


    /*-----------*
      | maxvalue  |
      *-----------*/
    /*!
    ** \brief Max value attribute.
    ** \param T: data type.
    ** \param Exact: the exact type.
    */
    template <class T = unsigned, class Exact = mlc::final>
    class maxvalue_type:
      public attribute<mlc_2_exact_vt_type(maxvalue_type, T, Exact)>
    {
    public:
      typedef maxvalue_type<T, Exact>			self_type; ///< Self type of the class.
      attr_type_decl(self_type);

      /*!
      ** \brief Basic Ctor.
      **
      ** \warning  After this  call, the  object is  only instantiated
      ** (not initialized).
      */
      maxvalue_type()
	{
	};

      /*!
      ** \brief Ctor from a lambda_type value.
      **
      ** \arg lambda: value of the attribute.
      */
      maxvalue_type(const lambda_type &lambda): value_(lambda)
	{
	};

      /*!
      ** \brief Ctor from a point and an image.
      **
      ** \param I: image exact type.
      **
      ** \arg input: input image.
      ** \arg p: point to consider in the image.
      */
      template <class I>
	maxvalue_type(const abstract::image<I> &input,
		      const oln_point_type(I) &p,
		      const env_type &):
	value_(input[p])
	{
	};

      /*!
      ** \brief Accessor to value_.
      **
      ** Virtual method.
      ** \see getValue_impl()
      */
      const value_type &getValue() const
	{
	  mlc_dispatch(getValue)();
	};

      /*!
      ** \brief Implementation of getValue().
      **
      ** Override this  method in  order to provide  a new  version of
      ** getValue().
      **
      ** \warning Do not call this method, use getValue() instead.
      */
      const value_type &getValue_impl() const
	{
	  return value_;
	};

      /*!
      ** \brief += operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      void pe_impl(const maxvalue_type &rhs)
	{
	  value_ = ntg::max(value_, rhs.getValue());
	};

      /*!
      ** \brief < operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool less_impl(const lambda_type &lambda) const
	{
	  return value_ < lambda;
	};

      /*!
      ** \brief != operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool ne_impl(const lambda_type &lambda) const
	{
	  return lambda != value_;
	};

    protected:
      value_type value_; ///< Value of the attribute.
    };


    /*-----------*
      | minvalue  |
      *-----------*/
    /*!
    ** \brief Min value attribute.
    ** \param T: data type.
    ** \param Exact: the exact type.
    */
    template <class T = unsigned, class Exact = mlc::final>
    class minvalue_type:
      public attribute<mlc_2_exact_vt_type(minvalue_type, T, Exact)>
    {
    public:
      typedef minvalue_type<T, Exact>			self_type;
      attr_type_decl(self_type);

      /*!
      ** \brief Basic Ctor.
      **
      ** \warning  After this  call, the  object is  only instantiated
      ** (not initialized).
      */
      minvalue_type()
	{
	};

      /*!
      ** \brief Ctor from a lambda_type value.
      **
      ** \arg lambda: value of the attribute.
      */
      minvalue_type(const lambda_type &lambda): value_(lambda)
	{
	};

      /*!
      ** \brief Ctor from a point and an image.
      **
      ** \param I: image exact type.
      **
      ** \arg input: input image.
      ** \arg p: point to consider in the image.
      */
      template <class I>
	minvalue_type(const abstract::image<I> &input,
		      const oln_point_type(I) &p,
		      const env_type &) :
	value_(input[p])
	{
	};

      /*!
      ** \brief Accessor to value_.
      **
      ** Virtual method.
      ** \see getValue_impl()
      */
      const value_type &getValue() const
	{
	  mlc_dispatch(getValue)();
	};

      /*!
      ** \brief Implementation of getValue().
      **
      ** Override this  method in  order to provide  a new  version of
      ** getValue().
      **
      ** \warning Do not call this method, use getValue() instead.
      */
      const value_type &getValue_impl() const
	{
	  return value_;
	};

      /*!
      ** \brief += operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      void pe_impl(const minvalue_type &rhs)
	{
	  value_ = ntg::min(value_, rhs.getValue());
	};

      /*!
      ** \brief < operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool less_impl(const lambda_type &lambda) const
	{
	  return value_ > lambda;
	};

      /*!
      ** \brief != operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool ne_impl(const lambda_type &lambda) const
	{
	  return lambda != value_;
	};

    protected:
      value_type value_; ///< Value of the attribute.
    };


      /*-----------*
	|   ball    |
	*-----------*/
    /*!
    ** \brief Ball attribute.
    ** \param I: exact type of images to process.
    ** \param Exact: the exact type.
    */
    template <class I, class Exact = mlc::final>
    class ball_type:
      public attribute<mlc_2_exact_vt_type(ball_type, I, Exact)>
    {
    public:
      typedef ball_type<I, Exact>			self_type; ///< Self type of the class.
      attr_type_decl(self_type);
      typedef abstract::image<mlc_exact_type(I)>	im_type; ///< Image type.
      typedef oln_point_type(im_type)			point_type; ///< Point type associated to im_type.
      typedef oln_dpoint_type(im_type)			dpoint_type; ///< Dpoint type associated to im_type.
      typedef std::vector<point_type>			pts_type; ///< Point vector type.
      typedef typename pts_type::const_iterator		cst_iter_type; ///< const iterator on Point vector.

      /*!
      ** \brief Basic Ctor.
      **
      ** \warning  After this  call, the  object is  only instantiated
      ** (not initialized).
      */
      ball_type()
	{
	};

      /*!
      ** \brief Ctor from a lambda_type value.
      **
      ** \arg lambda: value of the attribute.
      */
      ball_type(const lambda_type &lambda): value_(lambda), pts_()
	{
	};


      /*!
      ** \brief Ctor from a point and an image.
      **
      ** \arg p: point to consider in the image.
      */
      ball_type(const im_type&, const point_type &p, const env_type &) :
	value_(ntg_zero_val(value_type)), pts_()

	{
	  pts_.push_back(p);
	};

      /*!
      ** \brief Accessor to value_.
      **
      ** Virtual method.
      ** \see getValue_impl()
      */
      const value_type &getValue() const
	{
	  mlc_dispatch(getValue)();
	};


      /*!
      ** \brief Accessor to pts_.
      **
      ** Virtual method.
      ** \see getPts_impl()
      */
      const pts_type &getPts() const
	{
	  mlc_dispatch(getPts)();
	};

      // impl
      /*!
      ** \brief Implementation of getValue().
      **
      ** Override this  method in  order to provide  a new  version of
      ** getValue().
      **
      ** \warning Do not call this method, use getValue() instead.
      */
      const value_type &getValue_impl() const
	{
	  return value_;
	};

      /*!
      ** \brief Implementation of getValue().
      **
      ** Override this  method in  order to provide  a new  version of
      ** getPts().
      **
      ** \warning Do not call this method, use getPts() instead.
      */
      const pts_type &getPts_impl() const
	{
	  return pts_;
	};

      /*!
      ** \brief += operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      void pe_impl(const ball_type &rhs)
	{
	  value_type	last = value_;
	  std::copy(rhs.getPts().begin(),
		    rhs.getPts().end(),
		    std::back_inserter(pts_));
	  value_ = ntg_zero_val(value_type);
	  for (cst_iter_type p1 = pts_.begin(); p1 != pts_.end(); ++p1)
	    for (cst_iter_type p2 = pts_.begin(); p2 != pts_.end(); ++p2)
	      {
		unsigned d = 0;
		dpoint_type	p = *p1 - *p2;
		for (int i = 0; i < point_traits<point_type>::dim; ++i)
		  d += p.nth(i) * p.nth(i);
		if (d > value_)
		  value_ = d;
	      }
	  value_ /= 2;
	  value_ = ntg::max(value_, last);
	  value_ = ntg::max(value_, rhs.getValue());
	};

      /*!
      ** \brief < operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool less_impl(const lambda_type &lambda) const
	{
	  return value_ < lambda;
	};

      /*!
      ** \brief != operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool ne_impl(const lambda_type &lambda) const
	{
	  return lambda != value_;
	};

      protected:
      value_type	value_; ///< Value of the attribute.
      pts_type		pts_; ///< List of point in the ball.
    };



      /*-----------*
	|   dist    |
	*-----------*/
    /*!
    ** \brief Dist attribute.
    ** \param I: exact type of images to process.
    ** \param Exact: the exact type.
    */
    template <class I, class Exact = mlc::final>
    class dist_type:
      public attribute<mlc_2_exact_vt_type(dist_type, I, Exact)>
    {
    public:
      typedef dist_type<I, Exact>			self_type; ///< Self type of the class.
      attr_type_decl(self_type);
      typedef abstract::image<mlc_exact_type(I)>	im_type; ///< Image type.
      typedef oln_point_type(im_type)			point_type; ///< Point type associated to im_type.
      typedef oln_dpoint_type(im_type)			dpoint_type; ///< Dpoint type associated to im_type.

      /*!
      ** \brief Basic Ctor.
      **
      ** \warning  After this  call, the  object is  only instantiated
      ** (not initialized).
      */
      dist_type()
	{
	};

      /*!
      ** \brief Ctor from a point and an image.
      **
      ** \arg p: point to consider in the image.
      */
      dist_type(const im_type&,
		const point_type &p,
		const env_type &) :
	value_(ntg_zero_val(value_type)),
	center_(p)
	{
	};

      /*!
      ** \brief Accessor to value_.
      **
      ** Virtual method.
      ** \see getValue_impl()
      */
      const value_type &getValue() const
	{
	  mlc_dispatch(getValue)();
	};

      /*!
      ** \brief Ctor from a lambda_type value.
      **
      ** \arg lambda: value of the attribute.
      */
      dist_type(const lambda_type lambda): value_(lambda)
	{
	};

      /*!
      ** \brief Accessor to center_.
      **
      ** Virtual method.
      ** \see getCenter_impl()
      */
      const point_type &getCenter() const
	{
	  mlc_dispatch(getCenter)();
	};

      // impl
      /*!
      ** \brief Implementation of getCenter().
      **
      ** Override this  method in  order to provide  a new  version of
      ** getCenter().
      **
      ** \warning Do not call this method, use getCenter() instead.
      */
      const point_type &getCenter_impl() const
	{
	  return center_;
	};

      /*!
      ** \brief Implementation of getValue().
      **
      ** Override this  method in  order to provide  a new  version of
      ** getValue().
      **
      ** \warning Do not call this method, use getValue() instead.
      */
      const value_type &getValue_impl() const
	{
	  return value_;
	};

      /*!
      ** \brief += operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      void pe_impl(const dist_type &rhs)
	{
	  value_type	last = value_;
	  dpoint_type	p = center_ - rhs.getCenter();

	  value_ = ntg_zero_val(value_type);
	  for (int i = 0; i < point_traits<point_type>::dim; ++i)
	    value_ += p.nth(i) * p.nth(i);
	  value_ = sqrt(value_);
	  value_ = ntg::max(value_, last);
	  value_ = ntg::max(value_, rhs.getValue());
	};

      /*!
      ** \brief < operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool less_impl(const lambda_type &lambda) const
	{
	  return value_ < lambda;
	};

      /*!
      ** \brief != operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool ne_impl(const lambda_type &lambda) const
	{
	  return value_ != lambda;
	};

    protected:
      value_type value_; ///< Current value of the attribute.
      point_type center_; ///< Center of the attribute.

    };



      /*-----------*
	|  cube   |
	*-----------*/
    /*!
    ** \brief Cube attribute.
    ** \param I: exact type of images to process.
    ** \param Exact: the exact type.
    */
    template <class I, class Exact = mlc::final>
    class cube_type:
      public attribute<mlc_2_exact_vt_type(cube_type, I, Exact)>
    {
    public:
      typedef cube_type<I, Exact>			self_type; ///< Self type of the class.
      attr_type_decl(self_type);
      typedef abstract::image<mlc_exact_type(I)>	im_type; ///< Image type.
      typedef oln_point_type(im_type)			point_type; ///< Point type associated to im_type.
      typedef oln_dpoint_type(im_type)			dpoint_type; ///< Dpoint type associated to im_type.

      enum {dim = point_traits<point_type>::dim};

      /*!
      ** \brief Basic Ctor.
      **
      ** \warning  After this  call, the  object is  only instantiated
      ** (not initialized).
      */
      cube_type()
	{
	}

      /*!
      ** \brief Ctor from a lambda_type value.
      **
      ** \arg lambda: value of the attribute.
      */
      cube_type(const lambda_type &lambda):
	mins_(dim),
	maxs_(dim),
	value_(lambda)
	  {
	    for (int i = 0; i < point_traits<point_type>::dim; ++i)
	      {
		maxs_[i] = lambda;
		mins_[i] = ntg_zero_val(coord);
	      }
	  };

      /*!
      ** \brief Ctor from a point and an image.
      **
      ** \arg p: point to consider in the image.
      */
      cube_type(const im_type&,
		const point_type &p,
		const env_type &):
	mins_(dim), maxs_(dim), value_(ntg_zero_val(value_type))
	{
	  for (int i = 0; i < dim; ++i)
	    mins_[i] = maxs_[i] = p.nth(i);
	}

      /*!
      ** \brief Accessor to minimums.
      **
      ** Virtual method.
      ** \arg i: index of the minimum wanted.
      ** \return the i th minimum.
      ** \see getMin_impl()
      */
      int getMin(int i) const
	{
	  mlc_dispatch(getMin)(i);
	};

      /*!
      ** \brief Accessor to maximums.
      **
      ** Virtual method.
      ** \arg i: index of the minimum wanted.
      ** \return the i th maximum.
      ** \see getMax_impl()
      */
      int getMax(int i) const
	{
	  mlc_dispatch(getMax)(i);
	};

      // impl
      /*!
      ** \brief Implementation of getMin(int i).
      **
      ** Override this  method in  order to provide  a new  version of
      ** getMin(int i).
      **
      ** \warning Do not call this method, use getMin() instead.
      */
      int getMin_impl(int i) const
	{
	  precondition(i < dim);
	  return mins_[i];
	};

      /*!
      ** \brief Implementation of getMax(int i).
      **
      ** Override this  method in  order to provide  a new  version of
      ** getMax(int i).
      **
      ** \warning Do not call this method, use getMax() instead.
      */
      int getMax_impl(int i) const
	{
	  precondition(i < dim);
	  return maxs_[i];
	};

      /*!
      ** \brief += operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      void pe_impl(const cube_type &rhs)
	{
	  for (int i = 0; i < dim; ++i)
	    {
	      mins_[i] = ntg::min(mins_[i], rhs.getMin(i));
	      maxs_[i] = ntg::max(maxs_[i], rhs.getMax(i));
	    }
	  value_ = maxs_[0] - mins_[0];
	  for (int i = 1; i < dim; ++i)
	    if (value_ < value_type(maxs_[i] - mins_[i]))
	      value_ = maxs_[i] - mins_[i];
	}

      /*!
      ** \brief < operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool less_impl(const lambda_type &lambda) const
	{
	  return value_ < lambda;
	}

      /*!
      ** \brief != operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool ne_impl(const lambda_type &lambda) const
	{
	  return value_ != lambda;
	};

    protected:
      std::vector<coord>	mins_;
      std::vector<coord>	maxs_;
      value_type		value_;
    };



      /*------*
	| box |
	*-----*/
    /*!
    ** \brief Box attribute.
    ** \param I: exact type of images to process.
    ** \param Exact: the exact type.
    */
    template <class I, class Exact = mlc::final>
    class box_type:
      public attribute<mlc_2_exact_vt_type(box_type, I, Exact)>
    {
    public:
      typedef box_type<I, Exact>			self_type; ///< Self type of the class.
      attr_type_decl(self_type);
      typedef abstract::image<mlc_exact_type(I)>	im_type; ///< Image type.
      typedef oln_point_type(im_type)			point_type; ///< Point type associated to im_type.
      typedef oln_dpoint_type(im_type)			dpoint_type; ///< Dpoint type associated to im_type.
      enum {dim = point_traits<point_type>::dim };

      /*!
      ** \brief Ctor from a lambda_type value.
      **
      ** \arg lambda: value of the attribute.
      */
      box_type(const lambda_type &lambda): maxs_(dim), mins_(dim)
	{
	  for (int i = 0; i < dim; ++i)
	    {
	      mins_[i] = ntg_zero_val(value_type);
	      maxs_[i] = lambda[i];
	    }
	};

      /*!
      ** \brief Basic Ctor.
      **
      ** \warning  After this  call, the  object is  only instantiated
      ** (not initialized).
      */
      box_type()
	{
	};

      /*!
      ** \brief Ctor from a point and an image.
      **
      ** \arg p: point to consider in the image.
      */
      box_type(const im_type&, const point_type &p, const env_type &): maxs_(dim), mins_(dim)
	{
	  for (int i = 0; i < dim; ++i)
	    mins_[i] = maxs_[i] = p.nth(i);
	};

      /*!
      ** \brief Accessor to minimums.
      **
      ** Virtual method.
      ** \arg i: index of the minimum wanted.
      ** \return the i th minimum.
      ** \see getMin_impl()
      */
      value_type getMin(int i) const
	{
	  mlc_dispatch(getMin)(i);
	};


      /*!
      ** \brief Accessor to maximums.
      **
      ** Virtual method.
      ** \arg i: index of the minimum wanted.
      ** \return the i th maximum.
      ** \see getMax_impl()
      */
      value_type getMax(int i) const
	{
	  mlc_dispatch(getMax)(i);
	};

      // impl
      /*!
      ** \brief Accessor to minimums.
      **
      ** Virtual method.
      ** \arg i: index of the minimum wanted.
      ** \return the i th minimum.
      ** \see getMin_impl()
      */
      value_type getMin_impl(int i) const
	{
	  precondition(i < point_traits<point_type>::dim);
	  return mins_[i];
	};

      /*!
      ** \brief Accessor to maximums.
      **
      ** Virtual method.
      ** \arg i: index of the minimum wanted.
      ** \return the i th maximum.
      ** \see getMax_impl()
      */
      value_type getMax_impl(int i) const
	{
	  precondition(i < point_traits<point_type>::dim);
	  return maxs_[i];
	};

      /*!
      ** \brief += operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      void pe_impl(const box_type &rhs)
	{
	  for (int i = 0; i < dim; ++i)
	    {
	      mins_[i] = ntg::min(mins_[i], rhs.getMin(i));
	      maxs_[i] = ntg::max(maxs_[i], rhs.getMax(i));
	    }
	}

      /*!
      ** \brief < operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool less_impl(const lambda_type &lambda) const
	{
	  for (int i = 0; i < dim; ++i)
	    if ((maxs_[i] - mins_[i]) >= lambda[i])
	      return false;
	  return true;
	}

      /*!
      ** \brief != operator implementation.
      **
      ** This is an implementation  of the += operator.  Override this
      ** method to provide a new implementation of this operator.
      ** \warning This method SHOULDN'T directly be called.
      */
      bool ne_impl(const lambda_type &lambda) const
	{
	  for (int i = 0; i < dim; ++i)
	    if ((maxs_[i] - mins_[i]) == lambda[i])
	      return false;
	  return true;
	};

    protected:
      std::vector<value_type>	maxs_; ///< List of minimums.
      std::vector<value_type>	mins_; ///< List of maximums.
    };

      /*-------------------------
	| traits specializations |
	\------------------------*/


      // integral traits
      template <class T, class Exact>
      struct attr_traits<integral_type<T, Exact> >
      {
	typedef T		value_type;
	typedef value_type	lambda_type;
	typedef NullEnv		env_type;
      };

      // height traits
      template <class T, class Exact>
      struct attr_traits<height_type<T, Exact> >
      {
	typedef T		value_type;
	typedef value_type	lambda_type;
	typedef NullEnv		env_type;
      };

      // card traits
      template <class T, class Exact>
      struct attr_traits<card_type<T, Exact> >
      {
	typedef T		value_type;
	typedef value_type	lambda_type;
	typedef NullEnv		env_type;
      };

      // maxvalue traits
      template <class T, class Exact>
      struct attr_traits<maxvalue_type<T, Exact> >
      {
	typedef T		value_type;
	typedef value_type	lambda_type;
	typedef NullEnv		env_type;
      };

      // minvalue traits
      template <class T, class Exact>
      struct attr_traits<minvalue_type<T, Exact> >
      {
	typedef T		value_type;
	typedef value_type	lambda_type;
	typedef NullEnv		env_type;
      };

      // ball traits
      template <class I, class Exact>
      struct attr_traits<ball_type<I, Exact> >
      {
	typedef unsigned	value_type;
	typedef value_type	lambda_type;
	typedef NullEnv		env_type;
      };

      // dist traits
      template <class I, class Exact>
      struct attr_traits<dist_type<I, Exact> >
      {
	typedef float		value_type;
	typedef value_type	lambda_type;
	typedef NullEnv		env_type;
      };

      // cube traits
      template <class I, class Exact>
      struct attr_traits<cube_type<I, Exact> >
      {
	typedef unsigned	value_type;
	typedef value_type	lambda_type;
	typedef NullEnv		env_type;
      };

      // box traits
      template <class I, class Exact>
      struct attr_traits<box_type<I, Exact> >
      {
	typedef unsigned					value_type;
	typedef ntg::vec<I::dim, value_type, mlc::final>	lambda_type;
	typedef NullEnv						env_type;
      };

      // other_image traits
      template <class Dad, class I, class Exact>
      struct attr_traits<other_image<Dad, I, Exact> >
      {
	//typedef typename change_exact<Dad, other_image<Dad, I, Exact> >::ret	super_type;
	typedef typename change_exact<Dad,
				      typename mlc::exact_vt<other_image<Dad, I, Exact>,
							     Exact>::ret>::ret		super_type;
	typedef attr_value_type(super_type)						value_type;
	typedef attr_lambda_type(super_type)						lambda_type;
	typedef OtherImageEnv<I>							env_type;
      };

//       // other_point traits
//       template <class Dad, class I, class Exact>
//       struct attr_traits<other_point<Dad, I, Exact> >
//       {
// 	//typedef typename change_exact<Dad, other_image<Dad, I, Exact> >::ret	super_type;
// 	typedef typename change_exact<Dad,
// 				      typename mlc::exact_vt<other_point<Dad, I, Exact>,
// 							     Exact>::ret>::ret		super_type;
// 	typedef attr_value_type(super_type)						value_type;
// 	typedef attr_lambda_tye(super_type)						lambda_type;
// 	typedef OtherPointEnv<I>							env_type;
//       };

    // traits for other_image derivation

    /*!
    ** \brief Change the exact type of an attribute.
    **
    ** Traits to change integral_type exact type.
    */
    template <class NewExact, class OldExact, class T>
    struct change_exact<integral_type<T, OldExact>, NewExact>
    {
      typedef integral_type<T, NewExact>	ret;
    };

//     /*!
//     ** \brief Change the exact type of an attribute.
//     **
//     ** Traits to change dist_type exact type.
//     */
//     template <class NewExact, class OldExact, class T>
//     struct change_exact<dist_type<T, OldExact>, NewExact>
//     {
//       typedef dist_type<T, NewExact>	ret;
//     };

  } // !morpho
} //!oln

/*-----------*
  |  diamond  |
  *-----------*/

// FIXME: to be written...


#endif // !OLN_MORPHO_ATTRIBUTES

