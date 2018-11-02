#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>

const int maxn = 10000+5;
const int maxm = 1000+5;

namespace sjtu { 

template<class T>
class deque {
private:
	T* myData[maxn][maxm];
	iterator p; 
public:
	class const_iterator;
	class iterator {
	private:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		 int start[2];
		 int end[2];
		 
		 int pointer[2];
	public:
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, the behaviour is **undefined**.
		 * as well as operator-
		 */
		iterator()
		iterator operator+(const int &n) const {
			//TODO
			int tmp[2] = pointer;
			for(int i = 0;i<n;i++) {
				tmp[1]++;
				if(tmp[1]>=1000){
					tmp[0]++;
					tmp[1] = 0;
				}
				if(tmp[0]>end[0] or (tmp[0]==end[0] and tmp[1]>end[1])){
					return pointer;
				}
				if(tmp[0]>=10000){
					tmp[0] = 0;
				}
			}
			return tmp;
		}
		iterator operator-(const int &n) const {
			//TODO
			int tmp[2] = pointer;
			for(int i = 0;i<n;i++) {
				tmp[1]--;
				if(tmp[1]<0){
					tmp[0]--;
					tmp[1] = 999;
				}
				if(tmp[0]<start[0] or (tmp[0]==start[0] and tmp[1]<start[1])){
					return pointer;
				}
				if(tmp[0]<0){
					tmp[0] = 9999;
				}
			}
			return tmp;
		}
		// return th distance between two iterator,
		// if these two iterators points to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const {
			//TODO
		}
		iterator operator+=(const int &n) {
			//TODO
			int tmp[2] = pointer;
			for(int i = 0;i<n;i++) {
				tmp[1]++;
				if(tmp[1]>=1000){
					tmp[0]++;
					tmp[1] = 0;
				}
				if(tmp[0]>end[0] or (tmp[0]==end[0] and tmp[1]>end[1])){
					return pointer;
				}
				if(tmp[0]>=10000){
					tmp[0] = 0;
				}
			}
			return tmp;
		}
		iterator operator-=(const int &n) {
			//TODO
			int tmp[2] = pointer;
			for(int i = 0;i<n;i++) {
				tmp[1]--;
				if(tmp[1]<0){
					tmp[0]--;
					tmp[1] = 999;
				}
				if(tmp[0]<start[0] or (tmp[0]==start[0] and tmp[1]<start[1])){
					return pointer;
				}
				if(tmp[0]<0){
					tmp[0] = 9999;
				}
			}
			return tmp;
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
			int tmp[2] = pointer;
			for(int i = 0;i<1;i++) {
				tmp[1]++;
				if(tmp[1]>=1000){
					tmp[0]++;
					tmp[1] = 0;
				}
				if(tmp[0]>end[0] or (tmp[0]==end[0] and tmp[1]>end[1])){
					return pointer;
				}
				if(tmp[0]>=10000){
					tmp[0] = 0;
				}
			}
			int swap[2] = pointer;
			pointer = tmp;
			return swap;
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++() {}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {}
		/**
		 * TODO --iter
		 */
		iterator& operator--() {}
		/**
		 * TODO *it
		 */
		T& operator*() const {}
		/**
		 * TODO it->field
		 */
		T* operator->() const noexcept {}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) const {}
		bool operator==(const const_iterator &rhs) const {}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {}
		bool operator!=(const const_iterator &rhs) const {}
	};
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.
		private:
			// data members.
		public:
			const_iterator() {
				// TODO
			}
			const_iterator(const const_iterator &other) {
				// TODO
			}
			const_iterator(const iterator &other) {
				// TODO
			}
			// And other methods in iterator.
			// And other methods in iterator.
			// And other methods in iterator.
	};
	/**
	 * TODO Constructors
	 */
	deque() {}
	deque(const deque &other) {}
	/**
	 * TODO Deconstructor
	 */
	~deque() {}
	/**
	 * TODO assignment operator
	 */
	deque &operator=(const deque &other) {}
	/**
	 * access specified element with bounds checking
	 * throw index_out_of_bound if out of bound.
	 */
	T & at(const size_t &pos) {}
	const T & at(const size_t &pos) const {}
	T & operator[](const size_t &pos) {}
	const T & operator[](const size_t &pos) const {}
	/**
	 * access the first element
	 * throw container_is_empty when the container is empty.
	 */
	const T & front() const {}
	/**
	 * access the last element
	 * throw container_is_empty when the container is empty.
	 */
	const T & back() const {}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin() {}
	const_iterator cbegin() const {}
	/**
	 * returns an iterator to the end.
	 */
	iterator end() {}
	const_iterator cend() const {}
	/**
	 * checks whether the container is empty.
	 */
	bool empty() const {}
	/**
	 * returns the number of elements
	 */
	size_t size() const {}
	/**
	 * clears the contents
	 */
	void clear() {}
	/**
	 * inserts elements at the specified locat on in the container.
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value
	 *     throw if the iterator is invalid or it point to a wrong place.
	 */
	iterator insert(iterator pos, const T &value) {}
	/**
	 * removes specified element at pos.
	 * removes the element at pos.
	 * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
	 * throw if the container is empty, the iterator is invalid or it points to a wrong place.
	 */
	iterator erase(iterator pos) {}
	/**
	 * adds an element to the end
	 */
	void push_back(const T &value) {}
	/**
	 * removes the last element
	 *     throw when the container is empty.
	 */
	void pop_back() {}
	/**
	 * inserts an element to the beginning.
	 */
	void push_front(const T &value) {}
	/**
	 * removes the first element.
	 *     throw when the container is empty.
	 */
	void pop_front() {}
};

}

#endif
