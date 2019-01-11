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

unsigned int seed = 0x49720718;
int rand(){
    return seed = (int)seed*482711LL%2147483647;
}

template<
	class Key,
	class T,
	class Compare = std::less<Key>
> class map {
public:
	/**
	 * the internal type of data.
	 * it should have a default constructor, a copy constructor.
	 * You can use sjtu::map as value_type by typedef.
	 */
	typedef pair<const Key, T> value_type;
	/**
	 * see BidirectionalIterator at CppReference for help.
	 *
	 * if there is anything wrong throw invalid_iterator.
	 *     like it = map.begin(); --it;
	 *       or it = map.end(); ++end();
	 */
private:
    Compare comP;
    bool lesser(const Key &a, const Key &b){return comP(a,b);}
    bool equality(const Key &a, const Key &b){return (!comP(a,b) and !comP(b,a));}

    struct treapNode{
        value_type* value;
        int siz,key;
        treapNode* left;
        treapNode* right;
        treapNode* big;
        treapNode* small;

        treapNode():value(NULL),siz(0),key(0),left(NULL),right(NULL),big(NULL),small(NULL){}
        treapNode(const value_type &val):key(rand()),siz(1),left(NULL),right(NULL),big(NULL),small(NULL){value = new value_type(val);}
        int getSize(const treapNode* t){
            if(t==NULL){return 0;}
            else{return t->siz;}
        }
        void update(){siz = getSize(left)+getSize(right)+1;}
    };
    void LL(treapNode* &t){
        treapNode* t1 = t->left;
        t->left = t1->right;
        t1->right = t;
        t1->update();
        t->update();
        t = t1;
    }
    void RR(treapNode* &t){
        treapNode* t1 = t->right;
        t->right = t1->left;
        t1->left = t;
        t->update();
        t1->update();
        t = t1;
    }
public:
	class const_iterator;
	class iterator {
	    friend class map;
	private:
	    map* ori;
	    treapNode* point;
        iterator(map* theMap, treapNode* theNode):ori(theMap),point(theNode){}
	public:
		iterator():ori(NULL),point(NULL) {}
		iterator(const iterator &other):ori(other.ori),point(other.point) {}
		iterator operator++(int) {
            if(point->big==NULL){throw invalid_iterator();}
            iterator tmp(*this);
            point = point->big;
            return tmp;
		}
		iterator & operator++() {
            if(point->big==NULL){throw invalid_iterator();}
            point = point->big;
            return *this;
		}
		iterator operator--(int) {
            if(point->small==NULL){throw invalid_iterator();}
            iterator tmp(*this);
            point = point->small;
            return tmp;
		}
		iterator & operator--() {
            if(point->small==NULL){throw invalid_iterator();}
            point = point->small;
            return *this;
		}
		value_type & operator*() const {
            if(point->val==NULL){throw invalid_iterator();}
            return *(point->value);
		}
		bool operator==(const iterator &rhs) const {return (ori==rhs.ori and point==rhs.point);}
		bool operator==(const const_iterator &rhs) const {return (ori==rhs.ori and point==rhs.point);}
		bool operator!=(const iterator &rhs) const {return (ori!=rhs.ori or point!=rhs.point);}
		bool operator!=(const const_iterator &rhs) const {return (ori!=rhs.ori or point!=rhs.point);}
		value_type* operator->() const noexcept {return point->value;}
	};
	class const_iterator {
	    friend class map;
    private:
        const map* ori;
        const treapNode* point;

        const_iterator(const map* theMap, const treapNode* theNode):ori(theMap),point(theNode){}
    public:
        const_iterator():ori(NULL),point(NULL) {}
        const_iterator(const const_iterator &other):ori(other.ori),point(other.point) {}
        const_iterator(const iterator &other):ori(other.ori),point(other.point) {}

        const_iterator operator++(int) {
            if(point->big==NULL){throw invalid_iterator();}
            const_iterator tmp(*this);
            point = point->big;
            return tmp;
		}
		const_iterator & operator++() {
            if(point->big==NULL){throw invalid_iterator();}
            point = point->big;
            return *this;
		}
		const_iterator operator--(int) {
            if(point->small==NULL){throw invalid_iterator();}
            const_iterator tmp(*this);
            point = point->small;
            return tmp;
		}
		const_iterator & operator--() {
            if(point->small==NULL){throw invalid_iterator();}
            point = point->small;
            return *this;
		}
		value_type & operator*() const {
            if(point->val==NULL){throw invalid_iterator();}
            return *(point->value);
		}
		bool operator==(const iterator &rhs) const {return (ori==rhs.ori and point==rhs.point);}
		bool operator==(const const_iterator &rhs) const {return (ori==rhs.ori and point==rhs.point);}
		bool operator!=(const iterator &rhs) const {return (ori!=rhs.ori or point!=rhs.point);}
		bool operator!=(const const_iterator &rhs) const {return (ori!=rhs.ori or point!=rhs.point);}
		value_type* operator->() const noexcept {return point->value;}
	};
private:
    treapNode* root;
    treapNode* start;
    treapNode theEnd;
    size_t totalSize;
public:
	map():root(NULL),start(&theEnd),totalSize(0) {}
	map(const map &other) {}
	/**
	 * TODO assignment operator
	 */
	map & operator=(const map &other) {}
	/**
	 * TODO Destructors
	 */
	~map() {}

	T & at(const Key &key) {
        treapNode* t = root;
        while(t!=NULL and !equality(key,t->value->first)){
            if(lesser(t->value->first,key)){t = t->right;}
            else{t = t->left;}
        }
        if(t==NULL){throw index_out_of_bound();}
        else{return t->value->second;}
	}
	const T & at(const Key &key) const {
        const treapNode* t = root;
        while(t!=NULL and !equality(key,t->value->first)){
            if(lesser(t->value->first,key)){t = t->right;}
            else{t = t->left;}
        }
        if(t==NULL){throw index_out_of_bound();}
        else{return t->value->second;}
	}
	/**
	 * TODO
	 * access specified element
	 * Returns a reference to the value that is mapped to a key equivalent to key,
	 *   performing an insertion if such key does not already exist.
	 */
	T & operator[](const Key &key) {
        treapNode* t = root;
        while(t!=NULL and !equality(key,t->value->first)){
            if(lesser(t->value->first,key)){t = t->right;}
            else{t = t->left;}
        }
        if(t!=NULL){return t->value->second;}
        iterator newIte = insert(pair<Key,T>(key,T())).first;
        t = newIte.point;
        return t->value->second;
	}
	/**
	 * behave like at() throw index_out_of_bound if such key does not exist.
	 */
	const T & operator[](const Key &key) const {
        const treapNode* t = root;
        while(t!=NULL and !equality(key,t->value->first)){
            if(lesser(t->value->first,key)){t = t->right;}
            else{t = t->left;}
        }
        if(t!=NULL){return t->value->second;}
        else{throw index_out_of_bound();}
	}

	iterator begin() {return iterator(this,start);}
	const_iterator cbegin() const {return const_iterator(this,start);}
	iterator end() {return iterator(this,&theEnd);}
	const_iterator cend() const {return const_iterator(this,&theEnd);}

	bool empty() const {return totalSize==0;}
	size_t size() const {return totalSize;}
	/**
	 * clears the contents
	 */
	void clear() {}
	/**
	 * insert an element.
	 * return a pair, the first of the pair is
	 *   the iterator to the new element (or the element that prevented the insertion),
	 *   the second one is true if insert successfully, or false.
	 */
	pair<iterator, bool> insert(const value_type &value) {
	    if(totalSize==0){
            totalSize++;
            root = new treapNode(value);
            start = root;
            root->big = &theEnd;
            theEnd.small = root;
            return pair<iterator, bool>(iterator(this,root),1);
	    }
        treapNode* save = NULL;
        bool flag = insert(root,value,NULL,0,save);
        if(flag){totalSize++;}
        return pair<iterator,bool>(iterator(this,save),flag);
	}
	/**
	 * erase the element at pos.
	 *
	 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
	 */
	void erase(iterator pos) {

	}
	/**
	 * Returns the number of elements with key
	 *   that compares equivalent to the specified argument,
	 *   which is either 1 or 0
	 *     since this container does not allow duplicates.
	 * The default method of check the equivalence is !(a < b || b > a)
	 */
	size_t count(const Key &key) const {}

	iterator find(const Key &key) {
        treapNode* t = root;
        while(t!=NULL and !equality(key,t->value->first)){
            if(lesser(t->value->first,key)){t = t->right;}
            else{t = t->left;}
        }
        if(t==NULL){return iterator(this,&theEnd);}
        else{return iterator(this,t);}
    }
	const_iterator find(const Key &key) const {
        treapNode* t = root;
        while(t!=NULL and !equality(key,t->value->first)){
            if(lesser(t->value->first,key)){t = t->right;}
            else{t = t->left;}
        }
        if(t==NULL){return const_iterator(this,&theEnd);}
        else{return const_iterator(this,t);}
	}
private:
    bool insert(treapNode* &t, const value_type &value,treapNode* father,int type, treapNode* &save){
        bool flag = 0;
        if(t==NULL){
            save = t = new treapNode(value);
            flag = 1;
            if(type==1){
                t->small = father->small;
                t->big = father;
                if(theEnd.small = father){theEnd.small = t;}
            }else{
                t->big = father->big;
                t->small = father;
                if(start==father){start = t;}
            }
            if(t->small!=NULL){t->small->big = t;}
            if(t->big!=NULL){t->big->small = t;}
        }
        else if(equality(t->value->first,value.first)){save = t;flag = 0;}
        else if(lesser(t->value->first,value.first)){
            flag = insert(t->right,value,t,1,save);
            if(lesser(t->right->key,t->key)){RR(t);}
        }else{
            flag = insert(t->left,value,t,0,save);
            if(lesser(t->left->key,t->key)){LL(t);}
        }
        t->update();
        return flag;
    }
};

}

#endif
