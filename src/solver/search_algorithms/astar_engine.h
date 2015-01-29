
#ifndef UltraSolver_astar_engine_h
#define UltraSolver_astar_engine_h

#include "serial_engine.h"

template<class E>
struct astar_node_priority_cmp
{
	typedef E element_t;

	bool operator()(const element_t & lhs, const element_t & rhs) const
	{
		float sum1 = get<1>(lhs) + get<0>(lhs),
			sum2 = get<1>(rhs) + get<0>(rhs);
		return sum1 < sum2;

		/*if (sum1 == sum2)
		{
			return get<1>(lhs) > get<1>(rhs);
		}
		else
			return sum1 < sum2;*/
	}
};

#define ASTAR_BASE buffered_heuristic_engine
//#define ASTAR_BASE heuristic_engine

template<typename Gr, typename H, bool ExtMemory>
class astar_engine : public ASTAR_BASE<Gr, astar_node_priority_cmp, H, ExtMemory>
{
	using _Base = ASTAR_BASE<Gr, astar_node_priority_cmp, H, ExtMemory>;
public:
	astar_engine(Gr & graph, const typename Gr::vertex_streamer_t & vstreamer)
		:_Base(graph, vstreamer)
	{}
};

#endif
