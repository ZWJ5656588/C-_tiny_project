#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <condition_variable>
#include <thread>
#include <memory>
#include <mutex>


// 单例模式建立线程池
class ThreadPoolSingleton
{
public:
    ThreadPoolSingleton(const ThreadPoolSingleton& other) = delete;
    ThreadPoolSingleton operator=(const ThreadPoolSingleton& other) = delete;

    static auto ThreadGetSingleInstance(int n) -> std::unique_ptr<ThreadPoolSingleton>
    {
        std::call_once(init_flag, [=]{
            // 这里捕获变量的[]不能写this static变量没有this指针
            _instance.reset(new ThreadPoolSingleton(n)); // 改进的懒汉式
            std::cout << "instance has been initialized,nums of thread: " <<  n << std::endl;

        });

        return std::move(_instance); // 返回_instance的右值，保证在函数中只有一个线程值 // unique_ptr不能拷贝
    }

    // 用户向任务队列中push任务 用future对象 
    template<class F, class... Args>
    void enqueue( F&& f, Args&&... args) {


    }

private:
    static std::unique_ptr<ThreadPoolSingleton> _instance;
    static std::once_flag init_flag;

    int nums;
    bool stops;
    std::vector<std::thread> threads; // 线程数组

    ThreadPoolSingleton() = default;
    ThreadPoolSingleton(int n) : nums(n),stops(false){
        for (int i = 0; i < n; i++)
        {
            // 创建异步任务 

            
        }
    }

};

std::unique_ptr<ThreadPoolSingleton> ThreadPoolSingleton::_instance = nullptr; // 注意 类中的静态变量要在类外定义
std::once_flag ThreadPoolSingleton::init_flag;


int main()
{
    auto thPool = ThreadPoolSingleton::ThreadGetSingleInstance(5);
    // auto thPoo2 = ThreadPoolSingleton::ThreadGetSingleInstance(6); // 改进的懒汉式 这个实例无用 不会创建


    for(int i = 0; i < 10 ; i++)
    {
        ;
    }
}