
### 单例模式

应用场景：如果希望系统中某个类的对象只能存在一个，单例是最好的解决方案。

```c++
// 懒汉式单例模式
class Singleton {
private:
    Singleton(){}
    static Singleton* pInstance;
public:
    static Singleton* getInstance() {
        if (pInstance == nullptr)
            pInstance = new Singleton();
        return pInstance;
    }
};

//线程安全的单例模式
class Singleton {
private:
    Singleton(){}
    Singleton(const Singleton&);
    Singleton& operator= (const Singleton&);
public:
    static Singleton& getInstance() {
        static Singleton pInstance;
        return pInstance;
    }
};
```

[c++静态局部变量什么时候初始化？](https://segmentfault.com/q/1010000004157283)

    c++11标准要求局部静态变量初始化的线程安全性，g++编译器的实现相当于使用了一个全局锁来控制一个局部静态变量的标识（标识用来判定是否已经初始化。

### 工厂模式

应用场景：在编码时不能遇见创建哪些类的实例；

### 适配器

应用场景：stl容器

```c++
//俄罗斯提供的插座
class IRussiaSocket {
public:
    //使用双脚圆形充电
    virtual void charge() = 0;
}

//自带的充电器，双脚扁型
class OwnCharger {
public:
    void chargeWithFeetFlat() {
        std::cout << "owncharge" << std::endl;
    }
}

class PowerAdapter : public IRussiaSocket {
public:
    PowerAdapter() : m_pCharger(new OwnCharger()){};
    ~PowerAdapter() {SAFE_DELETE(m_pCharger);};
    void charge() {
        m_pCharger->chargeWithFeetFlat();
    }
private:
    OwnCharger* m_pCharger;
}

void AdapterMain()
{
    IRussiaSocket * pAdapter = new PowerAdapter();
    pAdapter->Charge();
    SAFE_DELETE(pAdapter);
}
```

### 观察者模式

应用场景：发布/订阅模式

+ 对一个对象状态的更新，需要其他对象同步更新；
+ 对象仅需要将自己的更新通知给其他对象而不需知道其他对象的细节；

```c++
class ISubject {
public:
    virtual void attach(IObserver*) = 0; // 注册观察者
    virtual void detach(IObserver*) = 0; // 注销观察者
    virtual void notify() = 0; // 通知观察者
}

//抽象观察者
class IObserver {
public:
    virtual void update(float price) = 0; // 更新价格
}

class ConcreteObserver : public IObserver {
public:
    ConcreteObserver(std::string name) {m_strName = name;}
    void update(float price) {}
private:
    std::string m_strName;

class  ConcreteSubject : public ISubject
{
public:
    ConcreteSubject(){ m_fPrice = 10.0; }
    void SetPrice(float price)
    {
        m_fPrice = price;
    }
    void Attach(IObserver * observer)
    {
        m_observers.push_back(observer);
    }
    void Detach(IObserver * observer)
    {
        m_observers.remove(observer);
    }
    // 通知所有观察者
    void Notify()
    {
        std::list<IObserver *>::iterator it = m_observers.begin();
        while (it != m_observers.end())
        {
            (*it)->Update(m_fPrice);
            ++it;
        }
    }
private:
    std::list<IObserver *> m_observers; // 观察者列表
    float m_fPrice;                     // 价格
};
```

参考：<https://www.yuque.com/huihut/interview/readme#ynbedm>