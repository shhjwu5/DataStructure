#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>

namespace sjtu {

template<class T>
class deque {
private:
    static const int nodeSize = 1000;
    struct node{
        size_t elements;
        T* myData[nodeSize];
        node* pre;
        node* next;

        node():elements(0),pre(NULL),next(NULL){
            for(int i = 0;i<nodeSize;i++){myData[i] = NULL;}
        }
        node(const T &x):elements(1),pre(NULL),next(NULL){
            myData[0] = new T(x);
            for(int i = 1;i<nodeSize;i++){myData[i] = NULL;}
        }
        node(const node &other):elements(other.elements),pre(NULL),next(NULL){
            for(int i = 0;i<elements;i++){myData[i] = new T(*(other.myData[i]));}
            for(int i = elements;i<nodeSize;i++){myData[i] = NULL;}
        }
        ~node() {
            for(int i = 0;i<elements;i++){delete myData[i];}
        }
    };
public:
	class const_iterator;
	class iterator {
	    /**
		 * TODO add data members
		 *   just add whatever you want.
		 */
        friend deque;
	private:
        deque* que;
        node* big;
        size_t small;
        iterator(deque* theQue, node* theBig, size_t theSmall):que(theQue),big(theBig),small(theSmall){}
	public:
        iterator():que(NULL),big(NULL),small(0){}
        iterator(const iterator &other):que(other.que),big(other.big),small(other.small){}
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, the behaviour is **undefined**.
		 * as well as operator-
		 */
		iterator operator+(const int &n) const {
		    //TODO
		    if(n<0){return *this-(-n);};

            node* theBig = big;
            size_t theSmall = small;
            int ope = n;
            while(theSmall+ope>=theBig->elements and theBig!=&(que->theEnd)){
                ope-=theBig->elements-theSmall;
                theBig = theBig->next;
                theSmall = 0;
            }

            return iterator(que, theBig, theSmall+ope);
		}
		iterator operator-(const int &n) const {
		    //TODO
            if(n<0){return *this+(-n);};

            node* theBig = big;
            size_t theSmall = small;
            int ope = n;
            while(theSmall<ope and theBig!=NULL){
                ope-=theSmall+1;
                theBig = theBig->pre;
                theSmall = theBig->elements-1;
            }

            return iterator(que, theBig, theSmall-ope);
		}
		// return th distance between two iterator,
		// if these two iterators points to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const {
		    //TODO
            if(que!=rhs.que){throw invalid_iterator();};
            int pos1 = small;
            int pos2 = rhs.small;

            node* theBig;
            for(theBig = big->pre;theBig!=NULL;theBig = theBig->pre){pos1+=theBig->elements;}
            for(theBig = (rhs.big)->pre;theBig!=NULL;theBig = theBig->pre){pos2+=theBig->elements;}

            return pos1-pos2;
		}
		iterator operator+=(const int &n) {
		    //TODO
		    if(n<0){return *this-=(-n);};

			node* theBig = big;
            size_t theSmall = small;
            int ope = n;
            while(theSmall+ope>=theBig->elements and theBig!=&(que->theEnd)){
                ope-=theBig->elements-theSmall;
                theBig = theBig->next;
                theSmall = 0;
            }

            big = theBig;
            small = theSmall+ope;
            return *this;
		}
		iterator operator-=(const int &n) {
		    //TODO
		    if(n<0){return *this+=(-n);};

			node* theBig = big;
            size_t theSmall = small;
            int ope = n;
            while (theSmall<ope) {
                ope -= theSmall + 1;
                theBig = theBig->pre;
                theSmall = theBig->elements-1;
            }

            big = theBig;
            small = theSmall-ope;
            return* this;
        }
        /**
		 * TODO iter++
		 */
		iterator operator++(int) {
		    if(*this==(que->end())){throw invalid_iterator();};

            iterator tmp(*this);
            if(small+1<big->elements){small++;}
            else{
                big = big->next;
                small = 0;
            }

            return tmp;
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++() {
		    if(operator==(que->end())){throw invalid_iterator();};

            if(small+1<big->elements){small++;}
            else{
                big = big->next;
                small = 0;
            }

            return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
		    if(operator==(que->begin())){throw invalid_iterator();};

            iterator tmp(*this);
            if(small>0){small--;}
            else{
                big = big->pre;
                small = big->elements-1;
            }

            return tmp;
		}
		/**
		 * TODO --iter
		 */
		iterator& operator--() {
		    if(operator==(que->begin())){throw invalid_iterator();};

            if(small>0){small--;}
            else{
                big = big->pre;
                small = big->elements-1;
            }

            return *this;
        }
        /**
		 * TODO *it
		 */
		T& operator*() const {
		    if(big->myData[small]==NULL){throw invalid_iterator();};

            return *(big->myData[small]);
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
            return (que==rhs.que) and (big==rhs.big) and (small==rhs.small);
		}
		bool operator==(const const_iterator &rhs) const {
            return (que==rhs.que) and (big==rhs.big) and (small==rhs.small);
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
            return (que!=rhs.que) or (big!=rhs.big) or (small!=rhs.small);
		}
		bool operator!=(const const_iterator &rhs) const {
		    return (que!=rhs.que) or (big!=rhs.big) or (small!=rhs.small);
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
        size_t small;
        const_iterator(const deque* theQue, const node* theBig, size_t theSmall):que(theQue),big(theBig),small(theSmall) {}
    public:
        const_iterator():que(NULL),big(NULL),small(0) {}
        const_iterator(const const_iterator &other):que(other.que),big(other.big),small(other.small) {}
        const_iterator(const iterator &other):que(other.que),big(other.big),small(other.small) {}
        // And other methods in iterator.
        // And other methods in iterator.
        // And other methods in iterator.
        const_iterator operator+(const int &n) const {
            if(n<0){return *this-(-n);};

            const node* theBig = big;
            size_t theSmall = small;
            int ope = n;
            while(theSmall+ope>=theBig->elements and theBig!=&(que->theEnd)){
                ope-=theBig->elements-theSmall;
                theBig = theBig->next;
                theSmall = 0;
            }

            return const_iterator(que, theBig, theSmall+ope);
		}
		const_iterator operator-(const int &n) const {
            if(n<0){return *this+(-n);};

            const node* theBig = big;
            size_t theSmall = small;
            int ope = n;
            while(theSmall<ope and theBig!=NULL){
                ope-=theSmall+1;
                theBig = theBig->pre;
                theSmall = theBig->elements-1;
            }

            return const_iterator(que, theBig, theSmall-ope);
		}
		int operator-(const const_iterator &rhs) const {
            if(que!=rhs.que){throw invalid_iterator();};

            int pos1 = small;
            int pos2 = rhs.small;
            const node* theBig;

            for(theBig = big->pre;theBig!=NULL;theBig = theBig->pre){pos1+=theBig->elements;}
            for(theBig = (rhs.big)->pre; theBig; theBig = theBig->pre){pos2+=theBig->elements;}

            return pos1-pos2;
		}
		const_iterator operator+=(const int &n) {
		    if(n<0){return *this-=(-n);};

			const node* theBig = big;
            size_t theSmall = small;
            int ope = n;
            while(theSmall+ope>=theBig->elements and theBig!=&(que->theEnd)){
                ope-=theBig->elements-theSmall;
                theBig = theBig->next;
                theSmall = 0;
            }

            big = theBig;
            small = theSmall+ope;
            return *this;
		}
		const_iterator operator-=(const int &n) {
		    if(n<0){return *this+=(-n);};

			const node* theBig = big;
            size_t theSmall = small;
            int ope = n;
            while(theSmall<ope and theBig!=NULL){
                ope-=theSmall+1;
                theBig = theBig->pre;
                theSmall = theBig->elements-1;
            }

            big = theBig;
            small = theSmall-ope;
            return *this;
        }
		const_iterator operator++(int) {
		    if(operator==(que->cend())){throw invalid_iterator();};

            const_iterator tmp(*this);
            if(small+1<big->elements){small++;}
            else{
                big = big->next;
                small = 0;
            }

            return tmp;
		}
		const_iterator& operator++() {
		    if(operator==(que->cend())){throw invalid_iterator();};

            if(small+1<big->elements){small++;}
            else{
                big = big->next;
                small = 0;
            }

            return *this;
		}
		const_iterator operator--(int) {
		    if(operator==(que->cbegin())){throw invalid_iterator();};

            const_iterator tmp(*this);
            if(small>0){small--;}
            else{
                big = big->pre;
                small = big->elements-1;
            }

            return tmp;
		}
		const_iterator& operator--() {
		    if(operator==(que->cbegin())){throw invalid_iterator();};

            if(small>0){small--;}
            else{
                big = big->pre;
                small = big->elements-1;
            }

            return *this;
        }
		const T& operator*() const {
		    if(big->myData[small]==NULL){throw invalid_iterator();};

            return *(big->myData[small]);
		}
		const T* operator->() const noexcept {
            return big->myData[small];
		}
		bool operator==(const iterator &rhs) const {
            return (que==rhs.que) and (big==rhs.big) and (small==rhs.small);
		}
		bool operator==(const const_iterator &rhs) const {
            return (que==rhs.que) and (big==rhs.big) and (small==rhs.small);
		}
		bool operator!=(const iterator &rhs) const {
            return (que!=rhs.que) or (big!=rhs.big) or (small!=rhs.small);
		}
		bool operator!=(const const_iterator &rhs) const {
		    return (que!=rhs.que) or (big!=rhs.big) or (small!=rhs.small);
		}
	};
private:
    size_t totalSize;
    node* head;
    node* tail;
    node theEnd;
public:
    /**
	 * TODO Constructors
	 */
	deque():totalSize(0),head(NULL),tail(NULL){}
	deque(const deque &other):totalSize(other.totalSize){
        if(other.totalSize==0){
            head = NULL;
            tail = NULL;
            return;
        }

        node* newNode;
        node* preNode = NULL;

        const node* baseNode = other.head;
        while(true){
            newNode = new node(*baseNode);
            newNode->pre = preNode;
            if(baseNode==other.head){head = newNode;};
            if(preNode!=NULL){preNode->next = newNode;};
            preNode = newNode;
            if(baseNode==other.tail){
                tail = newNode;
                break;
            }
            baseNode = baseNode->next;
        }

        tail->next = &theEnd;
        theEnd.pre = tail;
    }
    /**
	 * TODO Deconstructor
	 */
	~deque(){clear();}
	/**
	 * TODO assignment operator
	 */
	deque &operator=(const deque &other) {
        if(this==&other){return *this;};

        clear();

        totalSize = other.totalSize;
        if(other.totalSize==0){
            head = NULL;
            tail = NULL;
            return *this;
        }

        node* newNode;
        node* preNode = NULL;

        const node* baseNode = other.head;
        while(true){
            newNode = new node(*baseNode);
            newNode->pre = preNode;
            if(baseNode==other.head){head = newNode;};
            if(preNode!=NULL){preNode->next = newNode;};
            preNode = newNode;
            if(baseNode==other.tail){
                tail = newNode;
                break;
            }
            baseNode = baseNode->next;
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
        if(thePos<0 or thePos>=totalSize){throw index_out_of_bound();};

        node* theNode = head;
        while(thePos>=theNode->elements){
            thePos-=theNode->elements;
            theNode = theNode->next;
        }

        return *(theNode->myData[thePos]);
	}
	const T & at(const size_t &pos) const {
	    size_t thePos = pos;
        if(thePos<0 or thePos>=totalSize){throw index_out_of_bound();};

        const node* theNode = head;
        while(thePos>=theNode->elements){
            thePos-=theNode->elements;
            theNode = theNode->next;
        }

        return *(theNode->myData[thePos]);
	}
	T & operator[](const size_t &pos) {
	    size_t thePos = pos;
        if(thePos<0 or thePos>=totalSize){throw index_out_of_bound();};

        int small = thePos;
        node* theNode = head;
        while(small>=theNode->elements){
            small-=theNode->elements;
            theNode = theNode->next;
        }

        return *(theNode->myData[small]);
	}
	const T & operator[](const size_t &pos) const {
	    size_t thePos = pos;
        if(thePos<0 or thePos>=totalSize){throw index_out_of_bound();};

        const node* theNode = head;
        while(thePos>=theNode->elements){
            thePos-=theNode->elements;
            theNode = theNode->next;
        }

        return *(theNode->myData[thePos]);
	}
	/**
	 * access the first element
	 * throw container_is_empty when the container is empty.
	 */
	const T & front() const {
        if(totalSize==0){throw container_is_empty();};

        return *(head->myData[0]);
	}
	/**
	 * access the last element
	 * throw container_is_empty when the container is empty.
	 */
	const T & back() const {
        if(totalSize==0){throw container_is_empty();};

        return *(tail->myData[tail->elements-1]);
	}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin() {
        if(totalSize==0){return iterator(this, &theEnd, 0);};

        return iterator(this, head, 0);
	}
	const_iterator cbegin() const {
        if(totalSize==0){return const_iterator(this, &theEnd, 0);};

        return const_iterator(this, head, 0);
	}
	/**
	 * returns an iterator to the end.
	 */
	iterator end() {
        return iterator(this, &theEnd, 0);
	}
	const_iterator cend() const {
        return const_iterator(this, &theEnd, 0);
	}
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
        if(totalSize==0){return;};

        node* theNode = head;
        node* tmp;
        while(theNode!=&theEnd){
            tmp = theNode;
            theNode = theNode->next;
            delete tmp;
        }
        theEnd.pre = NULL;
        totalSize = 0;
	}
private:
    int getPos(const node* big, int small) const {
        int tmp = small;
        while(big!=head){
            big = big->pre;
            tmp+=big->elements;
        }
        return tmp;
    }
    iterator findPos(int n) {
        node* theNode = head;
        while(n>=theNode->elements and theNode!=&theEnd){
            n-=theNode->elements;
            theNode = theNode->next;
        }

        return iterator(this, theNode, n);
    }
    bool mergeable(node* lt, node* rt) {
        if(lt==NULL or rt==NULL or rt==&theEnd){return false;};

        return lt->elements+rt->elements<=nodeSize;
    }
    void mergeNode(node* lt, node* rt) {
        for(int i = 0;i<rt->elements;i++){lt->myData[lt->elements+i] = new T(*(rt->myData[i]));};
        lt->elements+=rt->elements;
        if(rt==tail){tail = lt;};
        lt->next = rt->next;
        if(lt->next){lt->next->pre = lt;};
        delete rt;
    }
    node* splitNode(node* theNode, int small) {
        node* newNode = new node;
        newNode->elements = theNode->elements-small;
        for(int i = 0;i<newNode->elements;i++){newNode->myData[i] = new T(*(theNode->myData[small+i]));};
        for(int i = small;i<theNode->elements;i++){
            delete theNode->myData[i];
            theNode->myData[i] = NULL;
        }
        theNode->elements-=newNode->elements;
        if(theNode==tail){tail = newNode;};
        newNode->next = theNode->next;
        if(newNode->next){newNode->next->pre = newNode;};
        newNode->pre = theNode;
        theNode->next = newNode;
        return theNode;
    }
    void normalRemove(node* theBig, int theSmall) {
        delete theBig->myData[theSmall];
        for(int i = theSmall;i<theBig->elements-1;i++){theBig->myData[i] = theBig->myData[i+1];};
        theBig->myData[theBig->elements-1] = NULL;
        theBig->elements--;
    }
    void normalInsert(node* theBig, int theSmall, const T &x) {
        theBig->elements++;
        for(int i = theBig->elements-1;i>theSmall;i--){theBig->myData[i] = theBig->myData[i-1];};
        theBig->myData[theSmall] = new T(x);
    }
public:
    /**
	 * inserts elements at the specified locat on in the container.
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value
	 *     throw if the iterator is invalid or it point to a wrong place.
	 */
	iterator insert(iterator pos, const T &value) {
        if(pos.que!=this or pos.big==NULL){throw invalid_iterator();};

        totalSize++;
        if(totalSize==1){
            node* newNode = new node(value);
            head = newNode;
            tail = newNode;
            newNode->pre = NULL;
            newNode->next = &theEnd;
            theEnd.pre = newNode;
            return begin();
        }

        if(pos.big!=&theEnd and (pos.big)->elements+1<=nodeSize){
            normalInsert(pos.big, pos.small, value);
            return pos;
        }

        int totalPos = getPos(pos.big, pos.small);
        node* newNode = new node(value);
        node* preNode;
        node* nextNode;
        if(pos.small==0){
            preNode = pos.big->pre;
            nextNode = pos.big;
        }else{
            preNode = splitNode(pos.big, pos.small);
            nextNode = preNode->next;
        }

        if(preNode==NULL){
            head = newNode;
            newNode->pre = NULL;
        }else{
            newNode->pre = preNode;
            preNode->next = newNode;
        }

        if(nextNode==&theEnd){tail = newNode;};
        newNode->next = nextNode;
        nextNode->pre = newNode;

        if(mergeable(preNode, newNode)){mergeNode(preNode, newNode);};
        if(mergeable(nextNode->pre, nextNode)){mergeNode(nextNode->pre, nextNode);};

        return findPos(totalPos);
    }
    /**
	 * removes specified element at pos.
	 * removes the element at pos.
	 * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
	 * throw if the container is empty, the iterator is invalid or it points to a wrong place.
	 */
	iterator erase(iterator pos) {
        if(totalSize==0){throw container_is_empty();};

        if(pos.que!=this or pos.big==NULL or pos.big->elements==0){throw invalid_iterator();};

        totalSize--;
        if(totalSize==0){
            delete head;
            head = NULL;
            tail = NULL;
            theEnd.pre = NULL;
            return end();
        }

        int totalPos = getPos(pos.big, pos.small);
        node* preNode;
        node* nextNode;
        if(pos.big->elements==1){
            preNode = pos.big->pre;
            nextNode = pos.big->next;
            if(pos.big==head){head = nextNode;};
            if(pos.big==tail){tail = preNode;};
            if(preNode!=NULL){preNode->next = nextNode;};
            if(nextNode!=NULL){nextNode->pre = preNode;};
            delete pos.big;
            if(mergeable(preNode, nextNode)){mergeNode(preNode, nextNode);};
        }else{
            preNode = pos.big->pre;
            nextNode = pos.big->next;
            normalRemove(pos.big, pos.small);
            if(mergeable(preNode, pos.big)){mergeNode(preNode, pos.big);}
            else if(mergeable(pos.big, nextNode)){mergeNode(pos.big, nextNode);};
        }

        return findPos(totalPos);
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

	    if(tail->elements+1<=nodeSize){normalInsert(tail, tail->elements, value);}
	    else{
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
        if(totalSize==0){throw container_is_empty();};

        totalSize--;
        if(totalSize==0){
            delete head;
            head = NULL;
            tail = NULL;
            theEnd.pre = NULL;
            return;
        }

        if(tail->elements==1){
            if(tail->pre){tail->pre->next = tail->next;};
            if(tail->next){tail->next->pre = tail->pre;};
            delete tail;
            tail = theEnd.pre;
        }else{normalRemove(tail, tail->elements-1);};
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

        if(head->elements+1<=nodeSize){normalInsert(head, 0, value);}
        else{
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
        if(totalSize==0){throw container_is_empty();}

        totalSize--;
        if(totalSize==0){
            delete head;
            head = 0;
            tail = 0;
            theEnd.pre = NULL;
            return;
        }

        if(head->elements==1){
            node* tmp = head;
            head = head->next;
            head->pre = NULL;
            delete tmp;
        }else{normalRemove(head, 0);};
	}
};

}

#endif
