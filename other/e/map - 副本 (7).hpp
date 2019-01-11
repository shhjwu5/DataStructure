#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

#include <iostream>

#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

template<class T>
T max(const T &a, const T &b){return a>b?a:b;}

template<
	class Key,
	class T,
	class Compare = std::less<Key>
> class map {
public:
	typedef pair<const Key, T> value_type;
private:
    Compare comP;
    bool lesser(const Key &a, const Key &b) const {return comP(a,b);}
    bool isEqual(const Key &a, const Key &b) const {return (!comP(a,b) and !comP(b,a));}

    struct avlNode{
		value_type* myData;
		avlNode* left;
		avlNode* right;

		avlNode* big;
		avlNode* small;
		int height;

        avlNode():myData(NULL),left(NULL),right(NULL),small(NULL),big(NULL),height(0){};
		avlNode(const value_type &element):left(NULL),right(NULL),big(NULL),small(NULL),height(0){myData = new value_type(element);}
        avlNode(const avlNode &other):big(NULL),small(NULL),height(other.height){
            if(other.myData!=NULL){myData = new value_type(*(other.myData));}
            else{myData = NULL;}
            if(other.left!=NULL){left = new avlNode(*(other.left));}
            else{left = NULL;}
            if(other.right!=NULL){right = new avlNode(*(other.right));}
            else{right = NULL;}
        }
        update(){height = max(getH(left),getH(right))+1;}
        getH(avlNode* &t){if(t==NULL){return 0;}else{return t->height;}}
	};
    size_t getH(avlNode* &t){
        if(t!=NULL){return t->height;}
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
    void clear(avlNode* &t){
        if(t==NULL){return;}
        clear(t->left);
        clear(t->right);
        delete t;
    }
    bool insert(avlNode* &x, avlNode* &t){
        bool flag = 0;
        if(t==NULL){t = x;flag = 1;}
        else if(lesser(x->myData->first,t->myData->first)){
            x->big = t;
            flag = insert(x,t->left);
            if(getH(t->left)-getH(t->right)==2){
                if(lesser(x->myData->first,t->left->myData->first)){LL(t);}
                else{LR(t);}
            }
        }else if(lesser(t->myData->first,x->myData->first)){
            x->small = t;
            flag = insert(x,t->right);
            if(getH(t->right)-getH(t->left)==2){
                if(lesser(t->right->myData->first,x->myData->first)){RR(t);}
                else{RL(t);}
            }
        }else{
            flag = 0;
            delete x;
            x = t;
        }
        t->update();
        return flag;
    }
    bool remove(const Key &x, avlNode* &t)
    {
        if(t==NULL){return true;}
        else if(isEqual(x,t->myData->first)){
            totalSize--;
            if(t->big==&theEnd){theEnd.small = t->small;}
            else{t->big->small = t->small;}
            if(t->small==NULL){start = t->big;}
            else{t->small->big = t->big;}

            if(t->left==NULL or t->right==NULL){
                avlNode* oldNode = t;
                t = (t->left!=NULL)?t->left:t->right;
                delete oldNode;
                return false;
            }else{
                avlNode* tmp = t->right;
                while(tmp->left!=NULL){tmp = tmp->left;}
                t->myData = tmp->myData;
                if(remove(tmp->myData->first,t->right)){return true;}
                return adjust(t,1);
            }
        }else if(lesser(x,t->myData->first)){
            if(remove(x,t->left)){return true;}
            return adjust(t,0);
        }else{
            if(remove(x,t->right)){return true;}
            return adjust(t,1);
        }
    }
    bool adjust(avlNode* &t, int subTree)
    {
        if(subTree){
            if(getH(t->left)-getH(t->right)==1){return true;}
            if(getH(t->right)==getH(t->left)){--t->height;return false;}
            if(getH(t->left->right)>getH(t->left->left)){LR(t);return false;}
            LL(t);
            if(getH(t->right)==getH(t->left)){return false;}
            else{return true;}
        }else{
            if(getH(t->right)-getH(t->left)==1){return true;}
            if(getH(t->right)==getH(t->left)){--t->height;return false;}
            if(getH(t->right->left)>getH(t->right->right)){RL(t);return false;}
            RR(t);
            if(getH(t->right)==getH(t->left)){return false;}
            else{return true;}
        }
    }

public:
	class const_iterator;
	class iterator {
	    friend class map;
	private:
	    map* origin;
	    avlNode* point;

	    iterator(map* theOri, avlNode* thePos):origin(theOri),point(thePos){}
	public:
		iterator():origin(NULL),point(NULL){}
		iterator(const iterator &other):origin(other.origin),point(other.point) {}
		iterator(const const_iterator &other):origin(other.origin),point(other.point){}
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
            if(point->myData==NULL){throw invalid_iterator();}
            return *(point->myData);
		}

		bool operator==(const iterator &rhs) const {return ((origin==rhs.origin) and (point==rhs.point));}
		bool operator==(const const_iterator &rhs) const {return ((origin==rhs.origin) and (point==rhs.point));}
		bool operator!=(const iterator &rhs) const {return ((origin!=rhs.origin) or (point!=rhs.point));}
		bool operator!=(const const_iterator &rhs) const {return ((origin!=rhs.origin) or (point!=rhs.point));}

		value_type* operator->() const noexcept {return point->myData;}
	};
	class const_iterator {
	    friend class map;
    private:
        const map* origin;
        const avlNode* point;

        const_iterator(const map* theOri, const avlNode* thePos):origin(theOri),point(thePos){}
    public:
        const_iterator():origin(NULL),point(NULL) {}
        const_iterator(const const_iterator &other):origin(other.origin),point(other.point) {}
        const_iterator(const iterator &other):origin(other.origin),point(other.point) {}

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
            if(point->myData==NULL){throw invalid_iterator();}
            return *(point->myData);
		}

		bool operator==(const iterator &rhs) const {return ((origin==rhs.origin) and (point==rhs.point));}
		bool operator==(const const_iterator &rhs) const {return ((origin==rhs.origin) and (point==rhs.point));}
		bool operator!=(const iterator &rhs) const {return ((origin!=rhs.origin) or (point!=rhs.point));}
		bool operator!=(const const_iterator &rhs) const {return ((origin!=rhs.origin) or (point!=rhs.point));}

		value_type* operator->() const noexcept {return point->myData;}
	};
private:
    avlNode* root;
    avlNode* start;
    avlNode theEnd;
    size_t totalSize;

    void build(avlNode* &to, avlNode** &tmp,int &idx){
        if(to==NULL){return;}
        build(to->left,tmp,idx);
        tmp[idx++] = to;
        build(to->right,tmp,idx);
	}
public:
	map():root(NULL),start(&theEnd),totalSize(0){}
	map(const map &other): totalSize(other.totalSize) {
	    if(totalSize!=0){
            root = new avlNode(*(other.root));

            avlNode** tmp = new avlNode*[totalSize];
            int idx = 0;
            build(root, tmp, idx);

            for(int i = 1;i<totalSize;i++){
                tmp[i]->small = tmp[i-1];
                tmp[i-1]->big = tmp[i];
            }
            tmp[0]->small = NULL;
            start = tmp[0];
            theEnd.big = NULL;
            theEnd.small = tmp[totalSize-1];
            tmp[totalSize-1]->big = &theEnd;
            delete [] tmp;
	    }else{
            root = NULL;
            theEnd.small = theEnd.big = NULL;
            start = &theEnd;
	    }
	}
	map & operator=(const map &other) {
	    if(&other==this){return *this;}
        totalSize = other.totalSize;
        clear(root);

        root = new avlNode(*(other.root));

        avlNode** tmp = new avlNode*[totalSize];
        int idx = 0;
        build(root, tmp, idx);
        for(int i = 1;i<totalSize;i++){
            tmp[i]->small = tmp[i-1];
            tmp[i-1]->big = tmp[i];
        }
        tmp[0]->small = NULL;
        start = tmp[0];
        theEnd.big = NULL;
        theEnd.small = tmp[totalSize-1];
        tmp[totalSize-1]->big = &theEnd;
        delete [] tmp;
        return *this;
	}
	~map() {clear(root);}

	T & at(const Key &key) {
        avlNode* t = root;
        while(t!=NULL and !isEqual(t->myData->first,key)){
            if(lesser(key,t->myData->first)){t = t->left;}
            else{t = t->right;}
        }
        if(t==NULL){throw index_out_of_bound();}
        else{return t->myData->second;}
	}
	const T & at(const Key &key) const {
        const avlNode* t = root;
        while(t!=NULL and !isEqual(t->myData->first,key)){
            if(lesser(key,t->myData->first)){t = t->left;}
            else{t = t->right;}
        }
        if(t==NULL){throw index_out_of_bound();}
        else{return t->myData->second;}
	}

	T & operator[](const Key &key) {
        avlNode* t = root;
        while(t!=NULL and !isEqual(t->myData->first,key)){
            if(lesser(key,t->myData->first)){t = t->left;}
            else{t = t->right;}
        }
        if(t==NULL){
            iterator newIte = insert(value_type(key,T())).first;
            t = newIte.point;
            return t->myData->second;
        }else{return t->myData->second;}
	}
	const T & operator[](const Key &key) const {
        const avlNode* t = root;
        while(t!=NULL and !isEqual(t->myData->first,key)){
            if(lesser(key,t->myData->first)){t = t->left;}
            else{t = t->right;}
        }
        if(t==NULL){throw index_out_of_bound();}
        else{return t->myData->second;}
	}

	iterator begin() {return iterator(this,start);}
	const_iterator cbegin() const {return const_iterator(this,start);}
	iterator end() {return iterator(this,&theEnd);}
	const_iterator cend() const {return const_iterator(this,&theEnd);}

    bool empty() const {return totalSize==0;}
	size_t size() const {return totalSize;}

	void clear() {clear(root);}

	pair<iterator, bool> insert(const value_type &value) {
	    avlNode* t = new avlNode(value);
	    bool flag = insert(t,root);
	    if(flag==1){
            totalSize++;
            if(t->big==NULL){theEnd.small = t;t->big = &theEnd;}
            else{t->big->small = t;}
            if(t->small==NULL){start = t;}
            else{t->small->big = t;}
        }
        return pair<iterator, bool>(iterator(this, t), flag);
    }
	/**
	 * erase the element at pos.
	 *
	 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
	 */
	void erase(iterator pos) {
        if(pos.origin!=this||pos.point==&theEnd){throw index_out_of_bound();}
        if(totalSize==0){return;}

        avlNode* t = pos.point;
        remove(t->myData->first,root);
	}

	size_t count(const Key &key) const {
        if(find(key).point!=&theEnd){return 1;}
        else{return 0;}
	}
	iterator find(const Key &key) {
        avlNode* t = root;
        while(t!=NULL and !isEqual(t->myData->first,key)){
            if(lesser(key,t->myData->first)){t = t->left;}
            else{t = t->right;}
        }
        if(t==NULL){return iterator(this,&theEnd);}
        else{return iterator(this,t);}
	}

	const_iterator find(const Key &key) const {
        const avlNode* t = root;
        while(t!=NULL and !isEqual(t->myData->first,key)){
            if(lesser(key,t->myData->first)){t = t->left;}
            else{t = t->right;}
        }
        if(t==NULL){return const_iterator(this,&theEnd);}
        else{return const_iterator(this,t);}
	}
};

}

#endif
