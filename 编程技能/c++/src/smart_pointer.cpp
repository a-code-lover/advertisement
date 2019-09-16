template <class T>
class auto_ptr {
private:
    T *pointee;

public:
    explicit auto_ptr(T *p = 0) : pointee(p) {}
    template<class U>
    auto_ptr(auto_ptr<U>& rhs) : pointee(rhs.release()){}
    ~ auto_ptr() {if(pointee) delete(pointee);}

    template<class U>
    auto_ptr<T>& operator=(auto_ptr<U>& rhs) {
        if (this != &rhs) reset(rhs.release());
        return *this;
    }
    T& operator*() {return *pointee;}
    T* operator->() {return pointee;}
    T* get() {return pointee;}
    //...
};

// unique_ptr
// https://www.cnblogs.com/ywy2090/p/5808266.html
// https://blog.csdn.net/liushengxi_root/article/details/80672901

// shared_ptr
// https://www.acodersjourney.com/implementing-smart-pointer-using-reference-counting/
// https://stackoverflow.com/questions/9200664/how-is-the-stdtr1shared-ptr-implemented

// weak_ptr


