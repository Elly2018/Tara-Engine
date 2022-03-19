#pragma once
#include <string>
#include <vector>

namespace Tara {
	template<typename T>
	struct tree {
	public:
		using container = std::vector<tree<T>>;
		using iterator = typename container::iterator;
		using const_iterator = typename container::const_iterator;

		tree() : tree(nullptr) {}
		tree(T _target) {
			target = _target;
			children = std::vector<tree<T>>();
		}

		iterator begin() noexcept  { return children.begin(); }
		iterator end() noexcept  { return children.end(); }
		const_iterator cbegin() const noexcept { return children.begin(); }
		const_iterator cend() const noexcept { return children.end(); }

		size_t count() const noexcept { return children.size(); }

		void push_back(tree<T> t) {
			children.push_back(t);
		}
		void push_back(T t) {
			children.push_back(tree<T>(t));
		}

		void clean() {
			children = std::vector<tree<T>>();
		}

		friend bool operator==(const tree<T>& t1, const tree<T>& t2) {
			return t1.target == t2.target;
		}
		friend bool operator!=(const tree<T>& t1, const tree<T>& t2)  {
			return t1.target != t2.target;
		}

		T target;
		std::vector<tree<T>> children;
	};

	template<typename T>
	class TARA_API nametree : tree<T> {
	public:
		nametree(std::string _name, T _target) {
			name = _name;
			target = _target;
			children = std::vector<tree<T>>();
		}

	public:
		std::string name;
	};
}