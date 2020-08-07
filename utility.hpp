#ifndef M_UTILITY_HPP
#define M_UTILITY_HPP

namespace sx {


/* 容器比较器, 为派生类提供 比较操作符 */
template<typename Derived>
struct comparetor {
	friend bool operator==(Derived const &first, Derived const &second) noexcept {
		if (first.size() != second.size())
			return false;

		auto begin1 = first.cbegin();
		auto begin2 = second.cbegin();
		auto end1 = first.cend();
		auto end2 = second.cend();

		for (; begin1 != end1 && begin2 != end2; ++begin1, ++begin2) {
			if (*begin1 != *begin2)
				return false;
		}

		return true;
	}

	friend bool operator!=(Derived const &first, Derived const &second) noexcept {
		return !(first == second);
	}

	friend bool operator<(Derived const &first, Derived const &second) noexcept {
		auto begin1 = first.cbegin();
		auto begin2 = second.cbegin();
		auto end1 = first.cend();
		auto end2 = second.cend();

		for (; begin1 != end1 && begin2 != end2; ++begin1, ++begin2) {
			if (*begin1 < *begin2)
				return true;
		}

		return first.size() < second.size();
	}

	friend bool operator<=(Derived const &first, Derived const &second) noexcept {
		auto begin1 = first.cbegin();
		auto begin2 = second.cbegin();
		auto end1 = first.cend();
		auto end2 = second.cend();

		for (; begin1 != end1 && begin2 != end2; ++begin1, ++begin2) {
			if (*begin1 <= *begin2)
				return true;
		}

		return first.size() <= second.size();
	}

	friend bool operator>(Derived const &first, Derived const &second) noexcept {
		return !(first <= second);
	}

	friend bool operator>=(Derived const &first, Derived const &second) noexcept {
		return !(first < second);
	}
};

}
#endif // !M_UTILITY_HPP

