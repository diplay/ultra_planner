

#ifndef UltraCore_complex_queue_h
#define UltraCore_complex_queue_h

#include "streamer.h"
#include <stxxl/queue>
#include <stdexcept>

template<typename T, typename S = base_type_streamer<T>, unsigned int BlockSize = 8192>
class complex_queue
{
	using value_type = T;
	using streamer_t = S;


	struct block_t
	{
		static const unsigned int DataSize = BlockSize - 2 * sizeof(unsigned int);

		block_t()
			:first(0), last(0)
		{}

		unsigned int first, last;
		char data[DataSize];
	};

	typedef stxxl::queue<block_t> base_container_t;

public:
	complex_queue(const streamer_t & streamer)
		:m_streamer(streamer), m_valsPerBlock(block_t::DataSize / streamer.serialized_size())
	{

	}

	complex_queue(const streamer_t & streamer, const value_type & first_val)
		:m_streamer(streamer), m_valsPerBlock(block_t::DataSize / streamer.serialized_size())
	{
		push(first_val);
	}

	void push(const value_type & val)
	{
		if (m_baseContainer.empty())
			m_baseContainer.push(block_t());

		block_t & last_el = m_baseContainer.back();
		m_streamer.serialize(last_el.data + last_el.last * m_streamer.serialized_size(), val);
		++last_el.last;

		if (last_el.last == m_valsPerBlock)
			m_baseContainer.push(block_t());
	}

	value_type top() const
	{
		if (m_baseContainer.empty())
			throw out_of_range("Queue is empty");

		const block_t & first_el = m_baseContainer.front();

		value_type val;
		m_streamer.deserialize(first_el.data + first_el.first * m_streamer.serialized_size(), val);
		return val;
	}

	void pop()
	{
		block_t & first_el = m_baseContainer.front();
		++first_el.first;

		if (first_el.first == first_el.last)
			m_baseContainer.pop();
	}

	bool empty() const
	{
		return m_baseContainer.empty();
	}
private:
	const streamer_t & m_streamer;
	base_container_t m_baseContainer;
	size_t m_valsPerBlock;
};

#endif
