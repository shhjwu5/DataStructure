#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"
#include <iostream>

#include <cstddef>

namespace sjtu {

template<class T>
class deque {
private:
 	static const int block = 1000;
	struct node{
		size_t elements;
		T* myData[block];
		node* pre;
		node* next;

		node():elements(0),pre(NULL),next(NULL){
			for(int i = 0;i<block;i++){
				myData[i] = NULL;
			}
		}
		node(const T &x):elements(1),pre(NULL),next(NULL){
			myData[0] = new T(x);
			for(int i = 1;i<block;i++){
				myData[i] = NULL;
			}
		}
		node(const node &copyNode):elements(copyNode.elements),pre(NULL),next(NULL){
			for(int i = 0;i<elements;i++){
				myData[i] = new T(*(copyNode.myData[i]));
			}
			for(int i = elements;i<block;i++){
				myData[i] = NULL;
			}
		}
		~node(){
			for(int i = 0;i<block;i++){
				delete myData[i];
			}
		}
	};
public:
	class const_iterator;
	class iterator {
		friend deque;
		private:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		deque* que;
		node* big;
		size_t small;
		iterator(deque* theQue, node* theNode, size_t theInt):que(theQue), big(theNode), small(theInt){}
		public:
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, the behaviour is **undefined**.
		 * as well as operator-
		 */
		iterator():que(NULL),big(NULL),small(0){}
		iterator(const iterator &other):que(other.que),big(other.big),small(other.small){}
		iterator operator+(const int &n) const {
			//TODO
			if(n<0){
				return *this-(-n);
			}
			node* theBig = big;
			size_t theSmall = small;
			size_t add = n;
			while(theSmall+add>=theBig->elements and theBig!=&(que->theEnd)){
				add-=theBig->elements-theSmall;
				theBig = theBig->next;
				theSmall = 0;
			}
			return iterator(que,theBig,theSmall+add);
		}
		iterator operator-(const int &n) const {
			//TODO
			if(n<0){
				return *this+(-n);
			}
			node* theBig = big;
			size_t theSmall = small;
			size_t sub = n;
			while(theSmall<sub){
				sub-=theSmall+1;
				theBig = theBig->pre;
				theSmall = theBig->elements-1;
			}
			return iterator(que,theBig,theSmall-sub);
		}
		// return th distance between two iterator,
		// if these two iterators points to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const {
			//TODO
			if(que!=rhs.que){
				throw invalid_iterator();
			}
			node* p = big;
			node* op = rhs.big;
			if(p==op){
				return small-rhs.small;
			}

			int pos1 = small;
			p = p->pre;
			while(p!=NULL and p!=op){
				pos1+=p->elements;
				p = p->pre;
			}
			if(p==op){
				return pos1+=p->elements-rhs.small;
			}

			int pos2 = rhs.small;
			p = rhs.big->pre;
			while(p!=NULL and p!=op){
				pos2+=p->elements;
				p = p->pre;
			}
			if(p==op){
				return pos2+=p->elements-small;
			}
		}
		iterator operator+=(const int &n) {
			//TODO
			if(n<0){
				return *this-=(-n);
			}
			node* theBig = big;
			size_t theSmall = small;
			size_t add = n;
			while(theSmall+add>=theBig->elements and theBig!=&(que->theEnd)){
				add-=theBig->elements-theSmall;
				theBig = theBig->next;
				theSmall = 0;
			}
			big = theBig;
			small = theSmall+add;
			return *this;
		}
		iterator operator-=(const int &n) {
			//TODO
			if(n<0){
				return *this+=(-n);
			}
			node* theBig = big;
			size_t theSmall = small;
			size_t sub = n;
			while(theSmall<sub){
				sub-=theSmall+1;
				theBig = theBig->pre;
				theSmall = theBig->elements-1;
			}
			big = theBig;
			small = theSmall-sub;
			return *this;
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
			if(*this==que->end()){
				throw invalid_iterator();
			}
			iterator tmp(*this);
			*this+=1;
			return tmp;
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++() {
			if(*this==que->end()){
				throw invalid_iterator();
			}
			*this+=1;
			iterator tmp(*this);
			return tmp;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
			if(*this==que->begin()){
				throw invalid_iterator();
			}
			iterator tmp(*this);
			*this-=1;
			return tmp;
		}
		/**
		 * TODO --iter
		 */
		iterator& operator--() {
			if(*this==que->begin()){
				throw invalid_iterator();
			}
			*this-=1;
			iterator tmp(*this);
			return tmp;
		}
		/**
		 * TODO *it
		 */
		T& operator*() const {
			if(big->myData[small]==NULL){
				throw invalid_iterator();
			}else{
				return *(big->myData[small]);
			}
		}
		/**
		 * TODO it->field
		 */
		T* operator->() const noexcept {
			return big->myData[small];
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) const {
			return que==rhs.que and big==rhs.big and small==rhs.small;
		}
		bool operator==(const const_iterator &rhs) const {
			return que==rhs.que and big==rhs.big and small==rhs.small;
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
			return que!=rhs.que or big!=rhs.big or small!=rhs.small;
		}
		bool operator!=(const const_iterator &rhs) const {
			return que!=rhs.que or big!=rhs.big or small!=rhs.small;
		}
	};
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.
		friend deque;
		private:
			// data members.
			const deque* que;
			const node* big;
			const size_t small;
			const_iterator(const deque* theQue, const node* theBig, const size_t theSmall):que(theQue),big(theBig),small(theSmall){}
		public:
			const_iterator():que(NULL),big(NULL),small(NULL) {}
			const_iterator(const const_iterator &other):que(other.que),big(other.big),small(other.small) {}
			const_iterator(const iterator &other):que(other.que),big(other.big),small(other.small) {}
			// And other methods in iterator.
			// And other methods in iterator.
			// And other methods in iterator.
	};
private:
	node* head;
	node* tail;
	size_t totalSize;
	node theEnd;
public:
	/**
	 * TODO Constructors
	 */
	deque():totalSize(0),head(NULL),tail(NULL) {}
	deque(const deque &other):totalSize(other.totalSize){
		if(other.totalSize==0){
            head = NULL;
            tail = NULL;
            return;
		}
		node* p;
		node* pPre = NULL;
		node* copyP = other.head;
		while(true){
			p = new node(*copyP);
			p->pre = pPre;
			if(copyP==other.head){
                head = p;
			}
			if(pPre!=NULL){
                pPre->next = p;
			}
			pPre = p;

			if(copyP==other.tail){
                tail = p;
                break;
			}
			copyP = copyP->next;
		}
		tail->next = &theEnd;
		theEnd.pre = tail;
	}
	/**
	 * TODO Deconstructor
	 */
	~deque() {
		clear();
	}
	/**
	 * TODO assignment operator
	 */
	deque &operator=(const deque &other) {
	    if(this==&other){
            return *this;
	    }
	    clear();
	    totalSize = other.totalSize;
		if(other.totalSize==0){
            head = NULL;
            tail = NULL;
			return *this;
		}

		node* p;
		node* pPre = NULL;
		node* copyP = other.head;
		while(true){
			p = new node(*copyP);
			p->pre = pPre;
			if(copyP==other.head){
                head = p;
			}
			if(pPre!=NULL){
                pPre->next = p;
			}
			pPre = p;

			if(copyP==other.tail){
                tail = p;
                break;
			}
			copyP = copyP->next;
		}
		tail->next = &theEnd;
		theEnd.pre = tail;
		return *this;
	}
	/**
	 * access specified element with bounds checking
	 * throw index_out_of_bound if out of bound.
	 */
	T & at(const size_t &pos) {
		size_t thePos = pos;
		if(thePos<0 or thePos>=totalSize){
			throw index_out_of_bound();
		}
		node* p = head;
		while(thePos>=p->elements){
			thePos-=p->elements;
			p = p->next;
		}
		return *(p->myData[thePos]);
	}
	const T & at(const size_t &pos) const {
		size_t thePos = pos;
		if(thePos<0 or thePos>=totalSize){
			throw index_out_of_bound();
		}
		node* p = head;
		while(p!=NULL and thePos>=p->elements){
			thePos-=p->elements;
			p = p->next;
		}
		return *(p->myData[thePos]);
	}
	T & operator[](const size_t &pos) {
        size_t thePos = pos;
		if(thePos<0 or thePos>=totalSize){
			throw index_out_of_bound();
		}
		int idx = thePos;
		node* p = head;
		while(idx>=p->elements){
			idx-=p->elements;
			p = p->next;
		}
		return *(p->myData[idx]);
	}
	const T & operator[](const size_t &pos) const {
		size_t thePos = pos;
		if(thePos<0 or thePos>=totalSize){
			throw index_out_of_bound();
		}
		node* p = head;
		while(thePos>=p->elements){
			thePos-=p->elements;
			p = p->next;
		}
		return *(p->myData[thePos]);
	}
	/**
	 * access the first element
	 * throw container_is_empty when the container is empty.
	 */
	const T & front() const {
		if(totalSize==0){
			throw container_is_empty();
		}
		return *(head->myData[0]);
	}
	/**
	 * access the last element
	 * throw container_is_empty when the container is empty.
	 */
	const T & back() const {
		if(totalSize==0){
			throw container_is_empty();
		}
		return *(tail->myData[tail->elements-1]);
	}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin() {
		if(totalSize==0){
			return iterator(this,&theEnd,0);
		}
		return iterator(this,head,0);
	}
	const_iterator cbegin() const {
		if(totalSize==0){
			return const_iterator(this,&theEnd,0);
		}
		return const_iterator(this,head,0);
	}
	/**
	 * returns an iterator to the end.
	 */
	iterator end() {
		if(totalSize==0){
			return iterator(this,&theEnd,0);
		}
		return iterator(this,tail,tail->elements-1);
	}
	const_iterator cend() const {
		if(totalSize==0){
			return const_iterator(this,&theEnd,0);
		}
		return const_iterator(this,tail,tail->elements-1);}
	/**
	 * checks whether the container is empty.
	 */
	bool empty() const {
		return totalSize==0;
	}
	/**
	 * returns the number of elements
	 */
	size_t size() const {
		return totalSize;
	}
	/**
	 * clears the contents
	 */
	void clear() {
		if(totalSize==0){
			return;
		}
		node* p = head;
		node* tmp;
		while(p!=&theEnd){
			tmp = p;
			p = p->next;
			delete tmp;
		}
		theEnd.pre = NULL;
		totalSize = 0;
	}

private:
	void normalInsert(node* theBig, size_t theSmall, const T &x){
	    theBig->elements++;
		for(int i = theBig->elements-1;i>theSmall;i--){
			theBig->myData[i] = theBig->myData[i-1];
		}
		theBig->myData[theSmall] = new T(x);
	}
	void normalDelete(node* theBig, size_t theSmall){
		delete theBig->myData[theSmall];
		for(int i = theSmall;i<theBig->elements-1;i++){
			theBig->myData[i] = theBig->myData[i+1];
		}
		theBig->myData[theBig->elements-1] = NULL;
		theBig->elements--;
	}
	node* splitBlock(node* atBig, size_t atSmall){
		node* theBig = new node;
		theBig->elements = atBig->elements-atSmall;
		for(int i = 0;i<theBig->elements;i++){
			theBig->myData[i] = new T(*(atBig->myData[i+atSmall]));
		}
		for(int i = atSmall;i<atBig->elements;i++){
            delete atBig->myData[i];
            atBig->myData[i] = NULL;
		}

		atBig->elements -= theBig->elements;

		if(atBig==tail){
            tail = theBig;
		}
		theBig->next = atBig->next;
		if(theBig->next!=NULL){
            theBig->next->pre = theBig;
		}

		theBig->pre = atBig;
		atBig->next = theBig;
		return atBig;
	}
	void mergeBlock(node* theBig){
		for(int i = theBig->elements;i<theBig->elements+theBig->next->elements;i++){
			theBig->myData[i] = new T(*(theBig->next->myData[i-theBig->elements]));
			theBig->next->myData[i-theBig->elements] = NULL;
		}
		node* tmp = theBig->next;
		theBig->elements = theBig->elements+tmp->elements;

		theBig->next = theBig->next->next;
		if(theBig->next!=NULL){
            theBig->next->pre = theBig;
		}else{
            tail = theBig;
		}
		delete tmp;
	}
public:
	/**
	 * inserts elements at the specified locat on in the container.
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value
	 *     throw if the iterator is invalid or it point to a wrong place.
	 */
	iterator insert(iterator pos, const T &value) {
		if(pos.que!=this or pos.big==NULL){
			throw invalid_iterator();
		}
		totalSize++;
		if(totalSize==1){
            node* newNode = new node(value);
            head = newNode;
            newNode->pre = NULL;
            newNode->next = &theEnd;
            theEnd.pre = newNode; 
            return begin();
		}
		
		int all = pos.small;
		node* theBig = pos.big;
        while(theBig!=head) {
            theBig = theBig->pre;
            all += theBig->elements;
        }
		
        normalInsert(pos.big,pos.small,value);
        
        if(pos.big->elements==nodeSize){
            splitBlock(pos.big,nodeSize/2);
        }
       
        theBig = head;
        while(all>=theBig->elements and theBig!=&theEnd){
        	all-=theBig->elements;
		}
		return iterator(this,theBig,all);
	}
	/**
	 * removes specified element at pos.
	 * removes the element at pos.
	 * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
	 * throw if the container is empty, the iterator is invalid or it points to a wrong place.
	 */
	iterator erase(iterator pos) {
	    if(totalSize==0){
            throw container_is_empty();
	    }
		if(pos.que!=this or pos.big==NULL or pos.big->elements==0){
			throw invalid_iterator();
		}
		totalSize--;

		normalDelete(pos.big,pos.small);
		if(pos.big->elements==0){
			node* tmp = pos.big;
			if(tmp->pre!=NULL){
				tmp->pre->next = tmp->next;
			}
			if(tmp->next!=NULL){
				tmp->next->pre = tmp->pre;
			}
			delete tmp;
		}
		if(pos.big->pre!=NULL){
			if(pos.big->elements+pos.big->pre->elements<nodeSize){
				mergeBlock(pos.big->pre);
			}
		}else if(pos.big->next!=NULL){
			if(pos.big->elements+pos.big->next->elements<nodeSize){
				mergeBlock(pos.big);
			}
		}
	}
	/**
	 * adds an element to the end
	 */
	void push_back(const T &value) {
	    totalSize++;
	    if(totalSize==1){
            node* newNode = new node(value);
            head = newNode;
            tail = newNode;
            newNode->next = &theEnd;
            theEnd.pre = newNode;
            return;
	    }
	    if(tail->elements+1<=block){
            normalInsert(tail,tail->elements,value);
	    }else{
            node* newNode = new node(value);
            newNode->pre = tail;
            newNode->next = &theEnd;
            theEnd.pre = newNode;
            tail->next = newNode;
            tail = newNode;
        }
	}
	/**
	 * removes the last element
	 *     throw when the container is empty.
	 */
	void pop_back() {
		if(totalSize==0){
			throw;
		}
		erase(iterator(this,tail,tail->elements-1));
	}
	/**
	 * inserts an element to the beginning.
	 */
	void push_front(const T &value) {
        totalSize++;
        if(totalSize==1){
            node* newNode = new node(value);
            head = newNode;
            tail = newNode;
            newNode->next = &theEnd;
            theEnd.pre = newNode;
            return;
        }
        if(head->elements+1<=block){
            normalInsert(head,0,value);
	    }else{
            node* newNode = new node(value);
            newNode->next = head;
            head->pre = newNode;
            head = newNode;
        }
	}
	/**
	 * removes the first element.
	 *     throw when the container is empty.
	 */
	void pop_front() {
		if(totalSize==0){
			throw;
		}
		erase(iterator(this,head,0));
	}
};

}

#endif
