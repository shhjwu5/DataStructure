#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
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

    struct avlNode {
        value_type* myData;
        avlNode* left;
        avlNode* right;

        avlNode* big;
        avlNode* small;

        size_t h;

        avlNode():myData(NULL),left(NULL),right(NULL),big(NULL),small(NULL),h(0){}
        avlNode(const value_type &x):left(NULL),right(NULL),big(NULL),small(NULL),h(0){myData = new value_type(x);}
        avlNode(const avlNode &other):left(NULL),right(NULL),big(NULL),small(NULL),h(other.h){
            if(other.myData!=NULL){myData = new value_type(*(other.myData));}
            else{myData = NULL;}
        }
        size_t getH(avlNode* &t){
            if(t!=NULL){return t->h;}
            else{return 0;}
        }
        void update(){h = max(getH(left),getH(right))+1;}
        ~avlNode(){
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
    size_t totalSize;
    avlNode* root;
    avlNode* start;
    avlNode theEnd;

    void build(avlNode* &to, avlNode* from, avlNode** &tmp,int &idx){
        if(from==NULL){return;}
        to = new avlNode(*(from));
        build(to->left,from->left,tmp,idx);
        tmp[idx++] = to;
        build(to->right,from->right,tmp,idx);
	}

	void clear(avlNode* &t){
        if(t==NULL){return;}
        clear(t->left);
        clear(t->right);
        delete t;
	}
public:
	map():root(NULL),start(&theEnd),totalSize(0) {}
	map(const map &other): totalSize(other.totalSize) {
        avlNode** tmp = new avlNode*[totalSize];
        int idx = 0;
        build(root, other.root, tmp, idx);
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
	}

	map & operator=(const map &other) {
	    if(&other==this){return *this;}
        totalSize = other.totalSize;
        clear(root);

        avlNode** tmp = new avlNode*[totalSize];
        int idx = 0;
        build(root, other.root, tmp, idx);
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
        tmp = newIte.point;
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

	void clear() {
        clear(root);
        root = NULL;
        totalSize = 0;
        theEnd.small = theEnd.big = NULL;
        start = &theEnd;
	}

	pair<iterator, bool> insert(const value_type &value) {
        avlNode* newNode = new avlNode(value);
        bool flag = insert(newNode,root);

        if(flag==1){
            totalSize++;
            if(newNode->big==NULL){theEnd.small = newNode;newNode->big = &theEnd;}
            else{newNode->big->small = newNode;}
            if(newNode->small==NULL){start = newNode;}
            else{newNode->small->big = newNode;}
        }

        return pair<iterator, bool>(iterator(this, newNode), flag);
	}

	void erase(iterator thePoint) {
        if(thePoint.origin!=this||thePoint.point==&theEnd){throw index_out_of_bound();}
        totalSize--;
        value_type tmp = *(thePoint.point->myData);
        Remove(tmp.first,root);
	}

	size_t count(const Key &key) const {
        if(find(key).point!=&theEnd){return 1;}
        else{return 0;}
	}
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
    bool Remove(const Key &x, avlNode* &t) {
        bool flag = 0;
        int subTree = 0;
        if(t==NULL){return true;}
        else if(lesser(x,t->myData->first)){
            flag = Remove(x,t->left);
            subTree = 0;
        }else if(lesser(t->myData->first,x)){
            flag = Remove(x,t->right);
            subTree = 1;
        }else{
            if(t->big!=&theEnd){t->big->small = t->small;}
            else{theEnd.small = t->small;}
            if(t->small!=NULL){t->small->big = t->big;}
            else{start = t->big;}

            if(t->left==NULL or t->right==NULL){
                avlNode* oldNode = t;
                t = (t->left!=NULL)?t->left:t->right;
                delete oldNode;
                return false;
            }else{
                avlNode* tmp = t->right;
                while(tmp->left!=NULL){tmp = tmp->left;}
                t->myData = tmp->myData;
                if(Remove(tmp->myData->first,t->right)){return true;}
                return adjust(t,1);
            }
        }
        if(lesser(x,t->myData->first)){
            if(Remove(x,t->left)){return true;}
            return adjust(t,0);
        }else{
            if(Remove(x,t->right)){return true;}
            return adjust(t,1);
        }
    }
    bool adjust(avlNode* &t, int subTree)
    {
        if(subTree){
            if(getH(t->left)-getH(t->right)==1){return true;}
            if(getH(t->right)==getH(t->left)){t->h--;return false;}
            if(getH(t->left->right)>getH(t->left->left)){LR(t);return false;}
            LL(t);
            if(getH(t->right)==getH(t->left)){return false;}
            else{return true;}
        }else{
            if(getH(t->right)-getH(t->left)==1){return true;}
            if(getH(t->right)==getH(t->left)){t->h--;return false;}
            if(getH(t->right->left)>getH(t->right->right)){RL(t);return false;}
            RR(t);
            if(getH(t->right)==getH(t->left)){return false;}
            else{return true;}
        }
    }
};

}

#endif
