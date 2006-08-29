// Copyright (C) 2006  EPITA Research and Development Laboratory
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

#ifndef OLENA_LRDE_UFMT_HPX_MAXTREE_HH
# define OLENA_LRDE_UFMT_HPX_MAXTREE_HH

# include <oln/level/fill.hh>
# include <oln/lrde/ufmt/utils.hh>
# include <oln/lrde/ufmt/ap_maxtree.hh>
# include <oln/lrde/ufmt/attributes.hh>



namespace oln
{

  namespace lrde
  {

    namespace ufmt
    {

      // FIXME: doc.

      template <class I>
      struct hpx_maxtree : public ap_maxtree<I>
      {
	typedef ap_maxtree<I> super;
	using super::f;
	using super::nbh;
	using super::par;
	oln_lrde_ufmt_import_ap_maxtree_typedefs;

	// aux data
	std::vector<point> S;
	std::vector<size_t> H;
	std::vector<dpoint> dp_pre, dp_post;
	unsigned nb;
	unsigned nnodes;
	typename mute<I, unsigned>::ret label;
	typename mute<I, point>::ret cpar;


	// ctor

	hpx_maxtree(const abstract::image<I>& f,
		   const oln_neighborhood_type(I)& nbh)
	  :
	  super(f, nbh),
	  label(f.size()),
	  cpar(f.size())
	{
	}

	template <class A> // void if no attributes
	void go()
	{
	  init();
	  compute_parent();  // 1st pass
// 	  extract_maxtree<A>(); // 2nd pass
	}

	void init()
	{
	  S = histogram_reverse_sort_p(f, H);
	  nb = split<I>(nbh, dp_pre, dp_post);
	  nnodes = 1;
	}

	void compute_parent()
	{
	  int i = 0;
	  for (int h = uint_nvalues(f) - 1; h >= 0; --h)
	    {
	      int i_first = i;
	      int i_last  = i_first + H[h];

	      // union-find

	      for (i = i_first; i < i_last; ++i)
		{
		  point p = S[i];
		  make_x_set(p);
		  // pre
		  for (unsigned j = 0; j < nb; ++j)
		    {
		      point n = p + dp_pre[j];
		      if (f.hold(n) and f[n] >= h)
			do_x_union(n, p);
		    }
		  // post
		  for (unsigned j = 0; j < nb; ++j)
		    {
		      point n = p + dp_post[j];
		      if (f.hold(n) and f[n] > h)
			do_x_union(n, p);
		    }
		}

	      // enhancing level compression:
	      //   we compress within 'level h' but we can end up with:
	      //   p' @ h+ --> p @ h --> lr @ h
	      //   so we have p -> lr for all p at level h
	      //   but p' --> p cannot be compressed by the code below
	      for (int k = i_last - 1; k >= i_first; --k)
		{
		  point p = S[k];
// 		  if (is_root(p))
// 		    ++nnodes;
// 		  else
		    cpar[p] = cpar[cpar[p]];
		}
	      
	    } // end of "for all h"
	}


	void make_x_set(const point& x)
	{
	  par[x] = x;
	  cpar[x] = x;
	}

	point find_x_root(point x)
	{
	  if (cpar[x] == x)
	    return x;
	  else
	    return cpar[x] = find_x_root(cpar[x]);
	}

	void do_x_union(const point& n, const point& p)
	{
	  point r = find_x_root(n);
	  if (r != p)
	    {
	      par[r] = p;
	      cpar[r] = p;
	      if (f[p] < f[r])
		++nnodes;
	    }
	}


      }; // end of class hpx_maxtree



    } // end of namespace oln::lrde::ufmt

  } // end of namespace oln::lrde

} // end of namespace oln


#endif // ! OLENA_LRDE_UFMT_HPX_MAXTREE_HH
