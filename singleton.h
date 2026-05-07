#ifndef SINGLETON_H
#define SINGLETON_H
#include <global.h>
template <typename T>
class Singleton{/*你这个类叫 单例类 Singleton，不是“单立类”。它的作用是：

    保证某一个类在整个程序运行期间只创建一个对象，并且全局都通过同一个接口拿到它。*/
protected:
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton& operator = (const Singleton<T>& st) = delete;
    static std::shared_ptr<T> _instance;//智能指针会在没人使用的时候自动释放表示单例对象由智能指针管理，避免手动 delete
public:
    static std::shared_ptr<T> GetInstance(){
        static std::once_flag s_flag;/*std::once_flag flag;

                                 std::call_once(flag, 函数);*/
        std::call_once(s_flag, [&](){
            _instance = std::shared_ptr<T>(new T);
        });

        return _instance;
    }
    void PrintAddress(){
        std::cout << _instance.get() << std::endl;
    }
    ~Singleton(){
        std::cout << "this is singleton destruct" << std::endl;
    }
};

template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;


#endif // SINGLETON_H
