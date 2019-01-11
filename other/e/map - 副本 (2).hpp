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
private:
    Compare comKey;
    bool lesser(const Key &a, const Key &b) const {return comKey(a,b);}
    bool equality(const Key &a, const Key &b) const {return !comKey(a,b) and !comKey(b,a);}
    struct avlNode{
        value_type* myData;
        avlNode* left;
        avlNode* right;

        avlNode* big;
        avlNode* small;
        int height;

        avlNode():myData(NULL),left(NULL),right(NULL),big(NULL),small(NULL),height(0){}
        avlNode(value_type* element, avlNode* lt, avlNode* rt, int h = 1):myData(element),left(lt),right(rt),height(h),big(NULL),small(NULL){}
        avlNode(avlNode* t):myData(t->myData),left(t->left),right(t->right),height(t->height),big(t->big),small(t->small){}
    };
public:
    /**
	 * see BidirectionalIterator at CppReference for help.
	 *
	 * if there is anything wrong throw invalid_iterator.
	 *     like it = map.begin(); --it;
	 *       or it = map.end(); ++end();
	 */
	class const_iterator;
	class iterator {
	    friend class map;
	private:
	    map* origin;
		avlNode* t;
     /**
		 * TODO add data members
		 *   just add whatever you want.
		 */
        iterator(map* ori, avlNode* p):origin(ori), t(p){}
    public:
		iterator():origin(NULL),t(NULL){}
		iterator(const iterator &other):origin(other.origin),t(other.t){}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
			if(t->big==NULL){throw invalid_iterator();};

            iterator tmp(*this);
            t = t->big;

            return tmp;
		}
		/**
		 * TODO ++iter
		 */
		iterator & operator++() {
			if(t->big==NULL){throw invalid_iterator();};

            t = t->big;

            return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
			if(t->small==NULL){throw invalid_iterator();};

            iterator tmp(*this);
            t = t->small;

            return tmp;
		}
		/**
		 * TODO --iter
		 */
		iterator & operator--() {
			if(t->small==NULL){throw invalid_iterator();};

            t = t->small;

            return *this;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		value_type & operator*() const {
			if(t==NULL){throw invalid_iterator();};

            return *(t->myData);
		}

		bool operator==(const iterator &rhs) const {
			return ((origin== rhs.origin) and (t==rhs.t));
		}
		bool operator==(const const_iterator &rhs) const {
			return ((origin== rhs.origin) and (t==rhs.t));
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
			return ((origin!= rhs.origin) or (t!=rhs.t));
		}
		bool operator!=(const const_iterator &rhs) const {
			return ((origin!= rhs.origin) or (t!=rhs.t));
		}

		/**
		 * for the support of it->first.
		 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		 */
		value_type* operator->() const noexcept {
			return t->myData;
		}
	};
	class const_iterator {
	// it should has similar member method as iterator.
	//  and it should be able to construct from an iterator.
        friend class map;
    private:
	    const map* origin;
		const avlNode* t;
		// data members.
		const_iterator(const map* theMap, const avlNode* p):origin(theMap),t(p){}
	public:
		const_iterator():t(NULL) {}
		const_iterator(const const_iterator &other):origin(other.origin),t(other.t) {}
		const_iterator(const iterator &other) :origin(other.origin),t(other.t){}
		// And other methods in iterator.
		// And other methods in iterator.
		// And other methods in iterator.
		const_iterator operator++(int) {
			if(t->big==NULL){throw invalid_iterator();};

            const_iterator tmp(*this);
            t = t->big;

            return tmp;
		}
		const_iterator & operator++() {
			if(t->big==NULL){throw invalid_iterator();};

            t = t->big;

            return *this;
		}
		const_iterator operator--(int) {
			if(t->small==NULL){throw invalid_iterator();};

            const_iterator tmp(*this);
            t = t->small;

            return tmp;
		}
		const_iterator & operator--() {
			if(t->small==NULL){throw invalid_iterator();};

            t = t->small;

            return *this;
		}
		const value_type & operator*() const {
			if(t==NULL){throw invalid_iterator();};

            return *(t->myData);
		}

		bool operator==(const iterator &rhs) const {
			return ((origin==rhs.origin) and (t==rhs.t));
		}
		bool operator==(const const_iterator &rhs) const {
			return ((origin==rhs.origin) and (t==rhs.t));
		}
		bool operator!=(const iterator &rhs) const {
			return ((origin!=rhs.origin) or (t!=rhs.t));
		}
		bool operator!=(const const_iterator &rhs) const {
			return ((origin!=rhs.origin) or (t!=rhs.t));
		}
		value_type* operator->() const noexcept {
			return t->myData;
		}
	};
	/**
	 * TODO two constructors
	 */
private:
    avlNode* root;
    avlNode* start;
    avlNode theEnd;

    size_t totalSize;
public:
	map():root(NULL),start(NULL),totalSize(0) {}
	map(const map &other) {}
	/**
	 * TODO assignment operator
	 */
	map & operator=(const map &other) {}
	/**
	 * TODO Destructors
	 */
	~map() {makeEmpty(root);}
	/**
	 * TODO
	 * access specified element with bounds checking
	 * Returns a reference to the mapped value of the element with key equivalent to key.
	 * If no such element exists, an exception of type `index_out_of_bound'
	 */
	T & at(const Key &key) {
        avlNode* p = root;
        while(p!=NULL and !equality(p->myData->first,key)){
            if(lesser(key, p->myData->first)){p = p->left;}
            else{p = p->right;}
        }
        if(p==NULL){throw index_out_of_bound();}
        else{return p->myData->second;}
	}
	const T & at(const Key &key) const {
        const avlNode* p = root;
        while(p!=NULL and !equality(p->myData->first,key)){
            if(lesser(key, p->myData->first)){p = p->left;}
            else{p = p->right;}
        }
        if(p==NULL){throw index_out_of_bound();}
        else{return p->myData->second;}
	}
	/**
	 * TODO
	 * access specified element
	 * Returns a reference to the value that is mapped to a key equivalent to key,
	 *   performing an insertion if such key does not already exist.
	 */
	T & operator[](const Key &key) {
        avlNode* p = root;
        while(p!=NULL and !equality(p->myData->first,key)){
            if(lesser(key, p->myData->first)){p = p->left;}
            else{p = p->right;}
        }
        if(p!=NULL){return p->myData->second;}
        iterator theIte = insert(pair<Key, T>(key, T())).first;
        p = theIte.t;
        return p->myData->second;
	}
	/**
	 * behave like at() throw index_out_of_bound if such key does not exist.
	 */
	const T & operator[](const Key &key) const {}
	/**
	 * return a iterator to the beginning
	 */
	iterator begin() {return iterator(this,start);}
	const_iterator cbegin() const {return const_iterator(this,start);}
	/**
	 * return a iterator to the end
	 * in fact, it returns past-the-end.
	 */
	iterator end() {return iterator(this,&theEnd);}
	const_iterator cend() const {return const_iterator(this,&theEnd);}
	/**
	 * checks whether the container is empty
	 * return true if empty, otherwise false.
	 */
	bool empty() const {return totalSize==0;}
	/**
	 * returns the number of elements.
	 */
	size_t size() const {return totalSize;}
	/**
	 * clears the contents
	 */
	void clear() {
        makeEmpty(root);
        start = NULL;
        theEnd.small = NULL;
	}
	/**
	 * insert an element.
	 * return a pair, the first of the pair is
	 *   the iterator to the new element (or the element that prevented the insertion),
	 *   the second one is true if insert successfully, or false.
	 */
	pair<iterator, bool> insert(value_type value) {
        avlNode* p = new avlNode(&value,NULL,NULL);
        bool flag = insert(p,root);
        return pair<iterator, bool>(iterator(this,p),flag);
	}
	/**
	 * erase the element at pos.
	 *
	 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
	 */
	void erase(iterator pos) {
        remove(pos.t->myData->first,root);
	}
	/**
	 * Returns the number of elements with key
	 *   that compares equivalent to the specified argument,
	 *   which is either 1 or 0
	 *     since this container does not allow duplicates.
	 * The default method of check the equivalence is !(a < b || b > a)
	 */
	size_t count(const Key &key) const {
        return count(key,root);
    }
	/**
	 * Finds an element with key equivalent to key.
	 * key value of the element to search for.
	 * Iterator to an element with key equivalent to key.
	 *   If no such element is found, past-the-end (see end()) iterator is returned.
	 */
	iterator find(const Key &key) {
        avlNode* p = root;
        while(p!=NULL and !equality(p->myData->first,key)){
            if(lesser(key,p->myData->first)){p = p->left;}
            else{p = p->right;}
        }
        if(p==NULL){return iterator();}
        else{return iterator(this,p);}
	}
	const_iterator find(const Key &key) const {}
private:
    size_t count(const Key &key, avlNode* p) const {
        if(p==NULL){return 0;}
        size_t sum = 0;
        sum+=count(key,p->left);
        sum+=count(key,p->right);
        if(equality(p->myData->first,key)){sum++;}
        return sum;
	}
    bool insert(avlNode* &p, avlNode* &q)
    {
        bool flag = 0;
        if(q==NULL){
            q = p;
            if(q->big!=NULL){q->big->small = q->small;}
            if(q->small!=NULL){q->small->big = q->big;}
            totalSize++;
            flag = 1;
        }else if(lesser(p->myData->first,q->myData->first)){
            p->big = q;
            flag = insert(p,q->left);
            if(height(q->left)-height(q->right)==2){
                if(lesser(p->myData->first,q->left->myData->first)){LL(q);}
                else{LR(q);}
            }
        }else if(lesser(q->myData->first,p->myData->first)){
            p->small = q;
            flag = insert(p,q->right);
            if(height(q->right)-height(q->left)==2){
                if(lesser(q->right->myData->first,p->myData->first)){RR(q);}
                else{RL(q);}
            }
        }
        q->height = max(height(q->left),height(q->right))+1;
        return flag;
    }
    bool remove(const Key &x, avlNode* &p)
    {
        if(p==NULL){return true;}
        if(equality(x,p->myData->first)){
            totalSize--;
            if(p->small!=NULL){p->small->big = p->big;}
            if(p->big!=NULL){p->big->small = p->small;}
            if(p->left==NULL or p->right==NULL){
                avlNode* oldNode = p;
                p = (p->left!=NULL)?p->left:p->right;
                delete oldNode;
                return false;
            }else{
                avlNode* tmp = p->right;
                while(tmp->left!=NULL){tmp = tmp->left;}
                p->myData = tmp->myData;
                if(remove(tmp->myData->first,p->right)){return true;}
                return adjust(root,1);
            }
        }
        if(lesser(x,p->myData->first)){
            if(remove(x,p->left)){return true;}
            return adjust(p,0);
        }else{
            if(remove(x,p->right)){return true;}
            return adjust(p,1);
        }
    }
    void LL(avlNode* &p) {
        avlNode* p1 = p->right;
        p->left = p1->right;
        p1->right = p;
        p->height = max(height(p->left),height(p->right))+1;
        p1->height = max(height(p1->left),height(p))+1;
        p = p1;
    }
    void RR(avlNode* &p)
    {
        avlNode* p1 = p->right;
        p->right = p1->left;
        p1->left = p;
        p->height = max(height(p->left),height(p->right))+1;
        p1->height = max(height(p1->left),height(p))+1;
        p = p1;
    }
    void LR(avlNode* &p)
    {
        RR(p->left);
        LL(p);
    }
    void RL(avlNode* &p)
    {
        LL(p->right);
        RR(p);
    }
    bool adjust(avlNode* &p, int subTree)
    {
        if(subTree){
            if(height(p->left)-height(p->right)==1){return true;}
            if(height(p->right)==height(p->left)){--p->height;return false;}
            if(height(p->left->right)>height(p->left->left)){LR(p);return false;}
            LL(p);
            if(height(p->right)==height(p->left)){return false;}
            else{return true;}
        }else{
            if(height(p->right)-height(p->left)==1){return true;}
            if(height(p->right)==height(p->left)){--p->height;return false;}
            if(height(p->right->left)>height(p->right->right)){RL(p);return false;}
            RR(p);
            if(height(p->right)==height(p->left)){return false;}
            else{return true;}
        }
    }
    int height(avlNode* p) const {
        return p==NULL?0:p->height;
    }

    int max(int a, int b){
        return (a>b)?a:b;
    }
    void makeEmpty(avlNode* p){
        if(p==NULL){return;}
        makeEmpty(p->left);
        makeEmpty(p->right);
        delete p;
    }
};

}

#endif
