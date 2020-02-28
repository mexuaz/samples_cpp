#include "foo.hpp"

template
		__device__
		__host__
		void assign<nid_t, nid_t>(Policy_t,
								   const vec<nid_t> &,
								   const vec<nid_t> &,
								   vec<nid_t> &);
