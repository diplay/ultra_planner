
#ifndef UltraSolver_dfs_engine_h
#define UltraSolver_dfs_engine_h

#include "queued_engine.h"

/*
Depth first search.
*/

template<class E>
struct dfs_node_priority_cmp
{
	typedef E element_t;

	bool operator()(const element_t & lhs, const element_t & rhs) const
	{
		return get<1>(lhs) < get<1>(rhs);
	}
};

template<typename Gr>
class dfs_engine : public blind_engine<Gr, dfs_node_priority_cmp>
{
	using _Base = blind_engine<Gr, dfs_node_priority_cmp>;
public:
	//template<typename Gr>
	dfs_engine(Gr & graph, const typename Gr::vertex_streamer_t & vstreamer)
		:_Base(graph, vstreamer)
	{}
};

#endif
