#ifndef M_SET_HPP
#define M_SET_HPP
#include "rbtree.hpp"
#include "mutility.hpp"
#include <utility>

namespace sx {

template<typename Key, typename Compare = std::less<Key>, typename Alloc = sx::allocator<Key>>
class set;

template<typename Key, typename Compare, typename Alloc>
void swap(set<Key, Compare, Alloc> &first, set<Key, Compare, Alloc> &second) noexcept;


template<typename Key, typename Compare = std::less<Key>, typename Alloc = sx::allocator<Key>>
class multiset;

template<typename Key, typename Compare, typename Alloc>
void swap(multiset<Key, Compare, Alloc> &, multiset<Key, Compare, Alloc> &) noexcept;


template<typename Key,
	typename Compare, 
	typename Alloc>
class set : public sx::comparetor<set<Key, Compare, Alloc>> {
public:
	using key_type			= Key;
	using value_type		= Key;
	using key_compare		= Compare;
	using value_compare		= Compare;
private:
	using Container			= sx::rbtree<key_type, value_type, sx::identity<value_type>, Compare, Alloc>;
public:
	using pointer			= typename Container::pointer;
	using reference			= typename Container::reference;
	using const_pointer		= typename Container::const_pointer;
	using const_reference	= typename Container::const_reference;
	using difference_type	= typename Container::difference_type;
	using size_type			= typename Container::size_type;
	using iterator			= typename Container::const_iterator;
	using const_iterator	= typename Container::const_iterator;
private:
	Container container;			/* �ײ��������� */
public:
	set() : container(Compare{}) {}
	explicit set(Compare const &comp) : container(comp) {}

	template<typename InputIterator, 
		typename = std::enable_if_t<sx::is_input_iterator_v<InputIterator>>>
	set(InputIterator first, InputIterator last) {
		container.insert_unique(first, last);
	}

	set(set const &other) noexcept : container(other.container) { }

	set(set &&other) noexcept : container(std::move(other.container)) { }

	set &operator=(set const &other) {
		container = other.container;
		return *this;
	}

	set &operator=(set &&other) {
		container = std::move(other.container);
		return *this;
	}

	~set() { }
public:
	size_type size() const noexcept {
		return container.size();
	}

	bool empty() const noexcept {
		return container.empty();
	}

	void clear() {
		container.clear();
	}

	const_iterator begin() const noexcept {
		return cbegin();
	}

	const_iterator end() const noexcept {
		return cend();
	}

	const_iterator cbegin() const noexcept {
		return container.cbegin();
	}

	const_iterator cend() const noexcept {
		return container.cend();
	}

	std::pair<const_iterator, bool> insert(value_type const &val) {
		std::pair<typename Container::iterator, bool> ret = container.insert_unique(val);
		return std::pair<const_iterator, bool>(container.transform_const_iterator(ret.first), ret.second);
	}

	template<typename... Args>
	std::pair<const_iterator, bool> emplace(Args&&... args) {
		std::pair<typename Container::const_iterator, bool> ret = container.emplace_unique(std::forward<Args>(args)...);
		return std::pair<const_iterator, bool>(container.transform_const_iterator(ret.first), ret.second);
	}

	std::pair<const_iterator, bool> insert(const_iterator position, value_type const &val) {
		std::pair<typename Container::iterator, bool> ret = container.insert_unique(val);
		return std::pair<const_iterator, bool>(container.transform_const_iterator(ret.first), ret.second);
	}

	template<typename InputIterator,
		typename = std::enable_if_t<sx::is_input_iterator_v<InputIterator>>>
	void insert(InputIterator first, InputIterator last) {
		container.insert_unique(first, last);
	}

	void erase(const_iterator position) {
		container.erase(position);
	}

	void erase(value_type const &val) {
		container.erase(val);
	}

	const_iterator max() const noexcept{
		return container.max();
	}

	const_iterator min() const noexcept {
		return container.min();
	}

	const_iterator find(value_type const &val) const {
		return container.find(val);
	}

	const_iterator lower_bound(value_type const &val) const {
		return container.lower_bound(val);
	}

	const_iterator upper_bound(value_type const &val) const {
		return container.upper_bound(val);
	}

	void swap(set &other) noexcept {
		container.swap(other.container);
	}

	friend void swap(set &first, set &second) noexcept {
		first.swap(second);
	}
};


template<typename Key,
	typename Compare, 
	typename Alloc>
class multiset : public sx::comparetor<set<Key, Compare, Alloc>> {
public:
	using key_type			= Key;
	using value_type		= Key;
	using key_compare		= Compare;
	using value_compare		= Compare;
private:
	using Container			= sx::rbtree<key_type, value_type, sx::identity<value_type>, Compare, Alloc>;
public:
	using pointer			= typename Container::pointer;
	using reference			= typename Container::reference;
	using const_pointer		= typename Container::const_pointer;
	using const_reference	= typename Container::const_reference;
	using difference_type	= typename Container::difference_type;
	using size_type			= typename Container::size_type;
	using iterator			= typename Container::const_iterator;
	using const_iterator	= typename Container::const_iterator;
private:
	Container container;			/* �ײ��������� */
public:
	multiset() : container(Compare{}) {}

	explicit multiset(Compare const &comp) : container(comp) {}

	template<typename InputIterator, 
		typename = std::enable_if_t<sx::is_input_iterator_v<InputIterator>>>
		multiset(InputIterator first, InputIterator last) {
		container.insert_equal(first, last);
	}

	multiset(multiset const &other) noexcept : container(other.container) { }

	multiset(multiset &&other) noexcept : container(std::move(other.container)) { }

	multiset &operator=(multiset const &other) {
		container = other.container;
		return *this;
	}

	multiset &operator=(multiset &&other) {
		container = std::move(other.container);
		return *this;
	}

	~multiset() { }
public:
	size_type size() const noexcept {
		return container.size();
	}

	bool empty() const noexcept {
		return container.empty();
	}

	void clear() {
		container.clear();
	}

	const_iterator begin() const noexcept {
		return cbegin();
	}

	const_iterator end() const noexcept {
		return cend();
	}

	const_iterator cbegin() const noexcept {
		return container.cbegin();
	}

	const_iterator cend() const noexcept {
		return container.cend();
	}

	const_iterator insert(value_type const &val) {
		typename Container::iterator ret = container.insert_equal(val);
		return container.transform_const_iterator(ret);
	}

	template<typename... Args>
	const_iterator emplace(Args&&... args) {
		return container.emplace_equal(std::forward<Args>(args)...);
	}

	const_iterator insert(const_iterator position, value_type const &val) {
		typename Container::iterator ret = container.insert_equal(val);
		return container.transform_const_iterator(ret);
	}

	template<typename InputIterator,
		typename = std::enable_if_t<sx::is_input_iterator_v<InputIterator>>>
	void insert(InputIterator first, InputIterator last) {
		container.insert_equal(first, last);
	}

	void erase(const_iterator position) {
		container.erase(position);
	}

	void erase(value_type const &val) {
		container.erase(val);
	}

	const_iterator find(value_type const &val) const {
		return container.find(val);
	}

	const_iterator lower_bound(value_type const &val) const {
		return container.lower_bound(val);
	}

	const_iterator upper_bound(value_type const &val) const {
		return container.upper_bound(val);
	}

	const_iterator max() const noexcept {
		return container.max();
	}

	const_iterator min() const noexcept {
		return container.min();
	}

	std::pair<const_iterator, const_iterator> equal_range(value_type const &val) const {
		return std::pair<const_iterator, const_iterator>(lower_bound(val), upper_bound(val));
	}

	void swap(multiset &other) noexcept {
		container.swap(other.container);
	}

	friend void swap(multiset &first, multiset &second) noexcept {
		first.swap(second);
	}
};
}

#endif // !M_SET_HPP
