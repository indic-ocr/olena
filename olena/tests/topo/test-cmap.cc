#include <ntg/int.hh>
#include <oln/basics2d.hh>
#include <oln/topo/combinatorial-map/cmap.hh>

#include <iostream>

#include "check.hh"
#include "data.hh"

using namespace oln;
using namespace topo;
using namespace tarjan;
using namespace inter_pixel;
using namespace combinatorial_map;

#define OK_OR_FAIL				\
      std::cout << "OK" << std::endl;		\
    else					\
      {						\
	std::cout << "FAIL" << std::endl;	\
	fail = true;				\
      }

bool
check()
{
  bool fail = false;

  typedef image2d<ntg::int_u8> input_t;

  input_t src = load(rdata("test-cmap"));

  std::cerr << "building inter pixel...";
  interpixel<input_t> ip(src);
  std::cerr << "OK" << std::endl;

  std::cerr << "building connected components...";
  flat_zone<input_t> cc(src);
  std::cerr << "OK" << std::endl;

  std::cerr << "building cmap...";
  cmap<input_t> cm(src, ip, cc);
  std::cerr << "OK" << std::endl;

  return fail;
}
