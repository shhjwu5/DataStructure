/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

template<class T>
T max(const T &a, const T &b){
    return (a>b)?a:b;
}

template<
	class Key,
	class T,
	class Compare = std::less<Key>
> class map {
public:
	typedef pair<const Key, T> value_type;
private:
    Compare cp;
    bool lesser(const Key &a, const Key &b) const {return cp(a,b);}

    struct avlNode{
        value_type* myData;
        avlNode* left;
        avlNode* right;

        avlNode* big;
        avlNode* small;

        size_t h;

        avlNode():myData(NULL),left(NULL),right(NULL),big(NULL),small(NULL),h(0){}
        avlNode(const avlNode &other):left(NULL),right(NULL),big(NULL),small(NULL),h(other.h){
            if(other.myData!=NULL){myData = new value_type(*(other.myData));}
            else{myData = NULL;}
            if(other.left!=NULL){left = new avlNode(*(other.left));}
			else{left = NULL;}
			if(other.right!=NULL){right = new avlNode(*(other.right));}
			else{right = NULL;} 
        }
        avlNode(const value_type &x):left(NULL),right(NULL),big(NULL),small(NULL),h(0){
            myData = new value_type(x);
        }
        size_t getH(avlNode* &t){
            if(t!=NULL){return t->h;}
            else{return 0;}
        }
        void update(){
            h = max(getH(left),getH(right))+1;
        }
        ~avlNode(){
            if(left!=NULL){delete left;}
            if(right!=NULL){delete right;}
            if(myData!=NULL){delete myData;}
        }
    };
    size_t getH(avlNode* &t){
        if(t!=NULL){return t->h;}
        else{return 0;}
    }

    void LL(avlNode* &t){
        avlNode* t1 = t->left;
        t->left = t1->right;
        t1->right = t;
        t->update();
        t1->update();
        t = t1;
    }
    void RR(avlNode* &t){
        avlNode* t1 = t->right;
        t->right = t1->left;
        t1->left = t;
        t->update();
        t1->update();
        t = t1;
    }
    void LR(avlNode* &t){
        RR(t->left);
        LL(t);
    }
    void RL(avlNode* &t){
        LL(t->right);
        RR(t);
    }
public:
	class const_iterator;
	class iterator {
	    friend class map;
	private:
	    map* origin;
	    avlNode* pos;

	    iterator(map* theOri, avlNode* thePos):origin(theOri),pos(thePos){}
	public:
		iterator():origin(NULL),pos(NULL){}
		iterator(const iterator &other):origin(other.origin),pos(other.pos) {}
		iterator(const const_iterator &other):origin(other.origin),pos(other.pos){}
		iterator operator++(int) {
            if(pos->big==NULL){throw invalid_iterator();}
            iterator tmp(*this);
            pos = pos->big;
            return tmp;
		}
		iterator & operator++() {
            if(pos->big==NULL){throw invalid_iterator();}
            pos = pos->big;
            return *this;
		}
		iterator operator--(int) {
            if(pos->small==NULL){throw invalid_iterator();}
            iterator tmp(*this);
            pos = pos->small;
            return tmp;
		}
		iterator & operator--() {
            if(pos->small==NULL){throw invalid_iterator();}
            pos = pos->small;
            return *this;
		}
		value_type & operator*() const {
            if(pos->myData==NULL){throw invalid_iterator();}
            return *(pos->myData);
		}
		bool operator==(const iterator &rhs) const {
            return ((origin==rhs.origin) and (pos==rhs.pos));
		}
		bool operator==(const const_iterator &rhs) const {
            return ((origin==rhs.origin) and (pos==rhs.pos));
        }
		bool operator!=(const iterator &rhs) const {
            return ((origin!=rhs.origin) or (pos!=rhs.pos));
		}
		bool operator!=(const const_iterator &rhs) const {
            return ((origin!=rhs.origin) or (pos!=rhs.pos));
		}
		value_type* operator->() const noexcept {
            return pos->myData;
		}
	};
	class const_iterator {
	    friend class map;
    private:
        const map* origin;
        const avlNode* pos;

        const_iterator(const map* theOri, const avlNode* thePos):origin(theOri),pos(thePos){}
    public:
        const_iterator():origin(NULL),pos(NULL) {}
        const_iterator(const const_iterator &other):origin(other.origin),pos(other.pos) {}
        const_iterator(const iterator &other):origin(other.origin),pos(other.pos) {}

        const_iterator operator++(int) {
            if(pos->big==NULL){throw invalid_iterator();}
            const_iterator tmp(*this);
            pos = pos->big;
            return tmp;
		}
		const_iterator & operator++() {
            if(pos->big==NULL){throw invalid_iterator();}
            pos = pos->big;
            return *this;
		}
		const_iterator operator--(int) {
            if(pos->small==NULL){throw invalid_iterator();}
            const_iterator tmp(*this);
            pos = pos->small;
            return tmp;
		}
		const_iterator & operator--() {
            if(pos->small==NULL){throw invalid_iterator();}
            pos = pos->small;
            return *this;
		}
		value_type & operator*() const {
            if(pos->myData==NULL){throw invalid_iterator();}
            return *(pos->myData);
		}
		bool operator==(const iterator &rhs) const {
            return ((origin==rhs.origin) and (pos==rhs.pos));
		}
		bool operator==(const const_iterator &rhs) const {
            return ((origin==rhs.origin) and (pos==rhs.pos));
        }
		bool operator!=(const iterator &rhs) const {
            return ((origin!=rhs.origin) or (pos!=rhs.pos));
		}
		bool operator!=(const const_iterator &rhs) const {
            return ((origin!=rhs.origin) or (pos!=rhs.pos));
		}
		value_type* operator->() const noexcept {
            return pos->myData;
		}
	};
private:
    size_t totalSize;
    avlNode* root;
    avlNode* start;
    avlNode theEnd;
public:
	map():root(NULL),start(&theEnd),totalSize(0) {}
	map(const map &other):totalSize(other.totalSize) {}
	/**
	 * TODO assignment operator
	 */
	map & operator=(const map &other){}
	/**
	 * TODO Destructors
	 */
	~map() {}

	T & at(const Key &key) {
        avlNode* tmp = root;
        while(tmp!=NULL){
            if(lesser(tmp->myData->first,key)){tmp = tmp->right;}
            else if(lesser(key,tmp->myData->first)){tmp = tmp->left;}
            else{return tmp->myData->second;}
        }
        throw index_out_of_bound();
	}
	const T & at(const Key &key) const {
        const avlNode* tmp = root;
        while(tmp!=NULL){
            if(lesser(tmp->myData->first,key)){tmp = tmp->right;}
            else if(lesser(key,tmp->myData->first)){tmp = tmp->left;}
            else{return tmp->myData->second;}
        }
        throw index_out_of_bound();
	}

	T & operator[](const Key &key) {
        avlNode* tmp = root;
        while(tmp!=NULL){
            if(lesser(tmp->myData->first,key)){tmp = tmp->right;}
            else if(lesser(key,tmp->myData->first)){tmp = tmp->left;}
            else{return tmp->myData->second;}
        }
        iterator newIte = insert(pair<Key,T>(key,T())).first;
        tmp = newIte.pos;
        return tmp->myData->second;
	}

	const T & operator[](const Key &key) const {
        const avlNode* tmp = root;
        while(tmp!=NULL){
            if(lesser(tmp->myData->first,key)){tmp = tmp->right;}
            else if(lesser(key,tmp->myData->first)){tmp = tmp->left;}
            else{return tmp->myData->second;}
        }
        throw index_out_of_bound();
	}

	iterator begin() {return iterator(this,start);}
	const_iterator cbegin() const {return const_iterator(this,start);}
	iterator end() {return iterator(this,&theEnd);}
	const_iterator cend() const {return const_iterator(this,&theEnd);}

	bool empty() const {return totalSize==0;}
	size_t size() const {return totalSize;}
	void clear() {}

	pair<iterator, bool> insert(const value_type &value) {
        if(totalSize==0){
            totalSize++;
            root = new avlNode(value);
            start = root;
            root->big = &theEnd;
            theEnd.small = root;
            return pair<iterator,bool>(iterator(this,root),true);
        }
        iterator position = find(value.first);
        if(position.pos!=&theEnd){return pair<iterator,bool>(position,false);}
        totalSize++;
        avlNode* newNode = new avlNode(value);
        insert(newNode,root);
        if(newNode->small==NULL){start = newNode;}
        if(newNode->big==NULL){newNode->big = &theEnd;theEnd.small = newNode;}
        return pair<iterator,bool>(iterator(this,newNode),true);
	}
	/**
	 * erase the element at pos.
	 *
	 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
	 */
	void erase(iterator pos) {}
	/**
	 * Returns the number of elements with key
	 *   that compares equivalent to the specified argument,
	 *   which is either 1 or 0
	 *     since this container does not allow duplicates.
	 * The default method of check the equivalence is !(a < b || b > a)
	 */
	size_t count(const Key &key) const {
        if(find(key).pos!=&theEnd){return 1;}
        else{return 0;}
	}
	/**
	 * Finds an element with key equivalent to key.
	 * key value of the element to search for.
	 * Iterator to an element with key equivalent to key.
	 *   If no such element is found, past-the-end (see end()) iterator is returned.
	 */
	iterator find(const Key &key) {
        avlNode* tmp = root;
        while(tmp!=NULL){
            if(lesser(tmp->myData->first,key)){tmp = tmp->right;}
            else if(lesser(key,tmp->myData->first)){tmp = tmp->left;}
            else{return iterator(this,tmp);}
        }
        return iterator(this,&theEnd);
	}
	const_iterator find(const Key &key) const {
        const avlNode* tmp = root;
        while(tmp!=NULL){
            if(lesser(tmp->myData->first,key)){tmp = tmp->right;}
            else if(lesser(key,tmp->myData->first)){tmp = tmp->left;}
            else{return const_iterator(this,tmp);}
        }
        return const_iterator(this,&theEnd);
	}
private:
    void insert(avlNode* &x, avlNode* t){
        if(t==NULL){t = x;}
        else if(lesser(x->myData->first,t->myData->first)){
            x->big = t;
            insert(x,t->left);
            if(getH(t->left)-getH(t->right)==2){
                if(lesser(x->myData->first,t->left->myData->first)){LL(t);}
                else{LR(t);}
            }
        }else if(lesser(t->myData->first,x->myData->first)){
            x->small = t;
            insert(x,t->right);
            if(getH(t->right)-getH(t->left)==2){
                if(lesser(t->right->myData->first,x->myData->first)){RR(t);}
                else{RL(t);}
            }
        }
        t->h = max(getH(t->left),getH(t->right))+1;
    }
    int build(avlNode* newRoot, avlNode* oldRoot, avlNode** tmp, int idx){
        if(oldRoot==NULL){return idx;}
        newRoot = new avlNode(*oldRoot);
        if(oldRoot->left!=NULL){idx = build(newRoot->left,oldRoot->left,tmp,idx);}
        tmp[idx++] = newRoot;
        if(oldRoot->right!=NULL){idx = build(newRoot->right,oldRoot->right,tmp,idx);}
    }
};

}

#endif
