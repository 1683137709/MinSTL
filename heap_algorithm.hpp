#ifndef M_HEAP_ALGORITHM_HPP
#define M_HEAP_ALGORITHM_HPP
#include "miterator.hpp"
#include <utility>

namespace sx {

template<typename RandomIterator> 
void push_heap(RandomIterator const &, RandomIterator const &);

template<typename RandomIterator, typename Compare> 
void push_heap(RandomIterator const &, RandomIterator const &, Compare const &);

template<typename RandomIterator, typename Compare> 
void push_heap_aux(RandomIterator, RandomIterator, Compare, sx::random_access_iterator_tag);

template<typename RandomIterator>
void pop_heap(RandomIterator const &first, RandomIterator const &end);

template<typename RandomIterator, typename Compare>
void pop_heap(RandomIterator const &, RandomIterator const &, Compare const &);

template<typename RandomIterator, typename Compare>
void pop_heap_aux(RandomIterator const &, RandomIterator const &, Compare const &, sx::random_access_iterator_tag);

template<typename RandomIterator>
void sort_heap(RandomIterator first, RandomIterator end);

template<typename RandomIterator, typename Compare>
void sort_heap(RandomIterator first, RandomIterator end, Compare comp);

template<typename RandomIterator, typename Compare>
void make_heap(RandomIterator const &first, RandomIterator const &, Compare const &);

template<typename RandomIterator, typename Compare>
void make_heap(RandomIterator const &first, RandomIterator const &);

template<typename RandomIterator, typename Compare>
void make_heap_aux(RandomIterator, RandomIterator, Compare, sx::random_access_iterator_tag);

template<typename RandomIterator, typename Compare>
void adjust_heap(RandomIterator first, int hole_index, int len, Compare comp);


template<typename RandomIterator>
void push_heap(RandomIterator const &first, RandomIterator const &end) {
	using iterator_category = typename iterator_traits<RandomIterator>::iterator_category;
	sx::push_heap_aux(first, end, std::greater<>{}, iterator_category{});
}

template<typename RandomIterator, typename Compare>
void push_heap(RandomIterator const &first, RandomIterator const &end, Compare const &comp) {
	using iterator_category = typename iterator_traits<RandomIterator>::iterator_category;
	sx::push_heap_aux(first, end, comp, iterator_category{});
}

template<typename RandomIterator, typename Compare> inline
void push_heap_aux(RandomIterator begin, RandomIterator end, Compare comp, sx::random_access_iterator_tag) {
	using distance_type = typename iterator_traits<RandomIterator>::difference_type;
	using value_type = typename iterator_traits<RandomIterator>::value_type;

	distance_type hole_index = end - begin - 1;
	distance_type parent_index = (hole_index - 1) / 2;
	value_type value = std::move(begin[hole_index]);
	while (hole_index >= 1) {
		/* �����������, ������ƶ����� */
		if (comp(value, begin[parent_index])) {
			begin[hole_index] = std::move(begin[parent_index]);
			hole_index = parent_index;
			parent_index = (parent_index - 1) / 2;
		}
		else
			break;
	}
	begin[hole_index] = std::move(value);
}


template<typename RandomIterator>
void pop_heap(RandomIterator const &first, RandomIterator const &end) {
	using iterator_category = typename iterator_traits<RandomIterator>::iterator_category;
	sx::pop_heap_aux(first, end, std::greater<>{}, iterator_category{});
}

template<typename RandomIterator, typename Compare> inline 
void pop_heap(RandomIterator const &first, RandomIterator const &end, Compare const &comp) {
	using iterator_category = typename iterator_traits<RandomIterator>::iterator_category;
	sx::pop_heap_aux(first, end, comp, iterator_category{});
}

template<typename RandomIterator, typename Compare> inline
void pop_heap_aux(RandomIterator const &first, RandomIterator const &end, Compare const &comp, sx::random_access_iterator_tag) {
	if (first == end || first + 1 == end)
		return;

	using std::swap;
	using difference_type = typename iterator_traits<RandomIterator>::difference_type;

	difference_type len = sx::distance(first, end);
	swap(first[0], first[len - 1]);
	sx::adjust_heap(first, 0, --len, comp);
}


template<typename RandomIterator, typename Compare>
void adjust_heap(RandomIterator first, int hole_index, int len, Compare comp) {
	using difference_type = typename iterator_traits<RandomIterator>::difference_type;
	using value_type = typename iterator_traits<RandomIterator>::value_type;

	value_type value = std::move(*(first + hole_index));
	difference_type child;
	
	for (; (2 * hole_index + 1) < len; hole_index = child) {
		child = (2 * hole_index) + 1;
		if (child != len - 1 && comp(first[child + 1], first[child]))
			++child;
		if (comp(first[child], value))
			first[hole_index] = std::move(first[child]);
		else
			break;
	}
	first[hole_index] = std::move(value);
}



template<typename RandomIterator>
void sort_heap(RandomIterator first, RandomIterator end) {
	while (end - first > 1)
		sx::pop_heap(first, end--);
}


template<typename RandomIterator, typename Compare>
void sort_heap(RandomIterator first, RandomIterator end, Compare comp) {
	while (end - first > 1)
		sx::pop_heap(first, end--, comp);
}


template<typename RandomIterator, typename Compare>
void make_heap(RandomIterator const &first, RandomIterator const &end, Compare const &comp) {
	using iterator_category = typename iterator_traits<RandomIterator>::iterator_category;
	sx::make_heap_aux(first, end, comp, iterator_category{});
}

template<typename RandomIterator>
void make_heap(RandomIterator const &first, RandomIterator const &end) {
	using iterator_category = typename iterator_traits<RandomIterator>::iterator_category;
	sx::make_heap_aux(first, end, std::greater<>{}, iterator_category{});
}

template<typename RandomIterator, typename Compare>
void make_heap_aux(RandomIterator first, RandomIterator end, Compare comp, sx::random_access_iterator_tag) {
	using difference_type = typename iterator_traits<RandomIterator>::difference_type;

	difference_type len = sx::distance(first, end);
	difference_type hole_index = (len - 1) / 2;			/* �ҵ���һ����Ҷ�ӽ�� */
	while (hole_index >= 0) {
		sx::adjust_heap(first, hole_index, len, comp);
		--hole_index;
	}
}

}	// !namespace sx

#endif // !M_HEAP_ALGORITHM_HPP

