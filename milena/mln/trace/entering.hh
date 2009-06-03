// Copyright (C) 2007, 2008 EPITA Research and Development Laboratory
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
// software library without restriction.  Specificenteringy, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to
// produce an executable, this file does not by itself cause the
// resulting executable to be covered by the GNU General Public
// License.  This exception does not however invalidate any other
// reasons why the executable file might be covered by the GNU General
// Public License.

#ifndef MLN_TRACE_ENTERING_HH
# define MLN_TRACE_ENTERING_HH

/// \file mln/trace/entering.hh
///
/// Definition of the trace entering procedure.

# include <string>
# include <iostream>
# include <stack>
# include <ctime>

# include <mln/trace/quiet.hh>


namespace mln
{

  namespace trace
  {

    void entering(const std::string& scope);

    extern std::stack<std::clock_t> start_times;
    extern std::stack<std::string>  scopes;      // For testing purpose
                                                 // (entering/exiting scope matching).


# ifndef MLN_INCLUDE_ONLY

    std::stack<std::clock_t> start_times;
    std::stack<std::string>  scopes;


    inline
    void entering(const std::string& scope)
    {
      if (quiet)
	return;

      start_times.push(std::clock());
      scopes.push(scope);

      if ((tab != 0) && (internal::max_tab == tab))
	std::cout << std::endl;

      for (unsigned i = 0; i < tab; ++i)
	std::cout << "  ";
      std::cout << scope << " {";

      internal::max_tab = ++tab;
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::trace

} // end of namespace mln


#endif // ! MLN_TRACE_ENTERING_HH
