// Copyright (C) 2010, 2011 EPITA Research and Development Laboratory (LRDE)
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

#include "apps/bench/dilation-lena.hh"
#include "apps/data.hh"


// Shortcut macros for run.

#define DILATION_WITH_BUILTIN_WINDOW(Namespace, Suffix, Headline)	\
  do									\
    {									\
      d = lena;								\
      t.start();							\
      for (unsigned i = 0; i < niters; ++i)				\
	d = Namespace::dilation(d);					\
      t.stop();								\
      times.push_back(t.read());					\
    }									\
  while (0)

#define DILATION(Namespace, Win, Suffix, Headline)			\
  do									\
    {									\
      d = lena;								\
      t.start();							\
      for (unsigned i = 0; i < niters; ++i)				\
	d = Namespace::dilation(d, Win);				\
      t.stop();								\
      times.push_back(t.read());					\
    }									\
  while (0)


std::vector<float>
run(const std::string& filename, unsigned niters)
{
  using namespace mln;
  using value::int_u8;

  border::thickness = 1;
  image2d<int_u8> lena;
  io::pgm::load(lena, filename);

  image2d<int_u8> d;
  util::timer t;
  std::vector<float> times;

  DILATION_WITH_BUILTIN_WINDOW(nongen,      "nongen",      "nongen\t\t");
  DILATION_WITH_BUILTIN_WINDOW(nongen_2ptr, "nongen_2ptr", "nongen_2ptr\t");
# if 0
  // Disabled, not used in the paper's table.
  DILATION_WITH_BUILTIN_WINDOW(nongen_1ptr, "nongen_1ptr", "nongen_1ptr\t");
#endif

  DILATION(gen,           win_c4p(), "gen",           "gen\t\t");
  // FIXME: Introduce a new test case, gen_static, using a static window
  // and static_qiters.
  DILATION(fast,          win_c4p(), "fast",          "fast\t\t");
# if 0
  // Disabled, not used in the paper's table.
  DILATION(fast_noaccu,   win_c4p(), "fast_noaccu",   "fast_noaccu\t");
  DILATION(faster,        win_c4p(), "faster",        "faster\t\t");
  DILATION(faster_noaccu, win_c4p(), "faster_noaccu", "faster_noaccu\t");
#endif

  // Static windows and qixters.
  const unsigned n = 5;
  mln::dpoint2d dps[n] = { mln::dpoint2d( 0, -1),
			   mln::dpoint2d(-1,  0),
			   mln::dpoint2d( 0,  0),
			   mln::dpoint2d(+1,  0),
			   mln::dpoint2d( 0, +1) };
  mln::util::static_array<mln::dpoint2d, n> sa(dps, dps + n);
  mln::static_window<mln::dpoint2d, n> static_win_c4p (sa);

  DILATION(fast_static,   static_win_c4p, "fast_static",   "fast_static\t");
# if 0
  // Disabled, not used in the paper's table.
  DILATION(faster_static, static_win_c4p, "faster_static", "faster_static\t");
#endif

  return times;
}

int
main ()
{
  unsigned niters = 10;
  typedef std::vector<float> times_t;

  // Compute times.
  times_t times_512  = run(MLN_IMG_DIR "/lena.pgm",            niters);
  times_t times_1024 = run(MLN_APPS_DIR "/bench/lena1024.pgm", niters);
  times_t times_2048 = run(MLN_APPS_DIR "/bench/lena2048.pgm", niters);

  // Display times.
  times_t::const_iterator i_512  = times_512.begin();
  times_t::const_iterator i_1024 = times_1024.begin();
  times_t::const_iterator i_2048 = times_2048.begin();
  std::cout <<
    "\\begin{table}[tbp]\n"
    "  \\centering\n"
    "  \\begin{tabular}{lrrr}\n"
    "    \\hline\n"
    "    Implementation & \\multicolumn{3}{c}{Execution times (s)} \\\\\n"
    "                   & $512^2$ & $1024^2$ & $2048^2$ \\\\\n"
    "    \\hline\n"
    "    \\hline\n";

  /* Increment each iterator only once in each output statement to
     avoid non-determinism due to the successive uses of operator++ on
     a given iterator.  */

  // nongen.
  std::cout << 
    "    Non generic (\\algref{lst:non-gen-dilation}) & " <<
    *i_512++ << " & " << *i_1024++ << " & " << *i_2048++ << " \\\\\n"
    "    \\hline\n";

  // nongen_2ptr.
  std::cout << 
    "    Non generic, pointer-based\\footnotemark[1] & " <<
    *i_512++ << " & " << *i_1024++ << " & " << *i_2048++ << " \\\\\n"
    "    \\hline\n";

  // gen.
  std::cout << 
    "    Generic (\\algref{lst:gen-dilation}) & " <<
    *i_512++ << " & " << *i_1024++ << " & " << *i_2048++ << " \\\\\n"
    "    \\hline\n";

  // fast.
  std::cout << 
    "    Fast, partly generic (\\algref{lst:fast-dilation}) & " <<
    *i_512++ << " & " << *i_1024++ << " & " << *i_2048++ << " \\\\\n"
    "    \\hline\n";

  // fast_static.
  std::cout << 
    "    Fast, partly generic with & " <<
    *i_512++ << " & " << *i_1024++ << " & " << *i_2048++ << " \\\\\n"
    "    static window (\\algref{lst:fast-static-dilation}) & & & \\\\\n"
    "    \\hline\n";

  std::cout << 
    "  \\end{tabular}\n"
    "  \\caption{Execution times of various dilation implementations.}\n"
    "  \\label{tab:results}\n"
    "\\end{table}\n"
    "\\footnotetext[1]{Implementation not shown in this paper for space\n"
    "  reasons.}\n" << std::flush;
}
