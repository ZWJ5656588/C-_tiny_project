// 实现一个简单的线程池
#include<iostream>
#include<thread>
#include<mutex>
#include<queue>
#include<functional>
#include<condition_variable>
#include<chrono>

#define NUM_TASK 1000
#define NUM_THREAD 500


// 任务队列 线程数组
// 复用线程资源 充分利用系统资源 减少系统开销 异步执行耗时任务
std::mutex iostream_;


class ThreadPool
{
public:

    ThreadPool (int numThreads) : stop(false),tasksCompleted(0)
    {
        for(int i = 0; i < numThreads; i++)
        {
            threads.emplace_back([this](){
                while(1) // 循环取任务
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    cond.wait(lock,[this]{
                        return !tasks.empty() || stop; // 线程池析构停止就不阻塞了 继续1执行后面代码退出 要不然会一直阻塞在这里
                    });

                    if (stop && tasks.empty()) // 当线程池关闭 并任务队列为空时关闭
                        return;

                    std::function<void()> task(std::move(tasks.front())); // 取队头的任务
                    tasks.pop(); // 出任务队列
                    lock.unlock(); // 解锁,关键一步 提前解锁，别的线程获得锁同步执行下一个任务，对于IO密集型任务至关重要
                    task(); // 执行任务 这个任务可能不是原子性的 有时需要继续处理
                    
                }
            });
        }
    }

    ~ThreadPool(){
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
        }

        cond.notify_all(); // 唤醒所有阻塞的线程,因为主线程快要结束

        for(auto &t: threads){
            t.join(); // 等待子线程
        }
    }

    // 用户向队列中push任务
    template<class F,class... Args>
    void enqueue(F &&f, Args&&... args)
    {
        std::function<void()>task = std::bind(std::forward<F>(f),std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex>lock(mtx);
            tasks.emplace(std::move(task)); // unique_lock括号作用域内释放 
        }
        cond.notify_one(); // 发布任务同时 唤醒线程
    }

    void taskCompleted()
    {
        std::unique_lock<std::mutex> lock(mtx);
        tasksCompleted++;
        cond.notify_all();

    }
    
    void waitForAllTasks()
    {
        std::unique_lock<std::mutex> lock(mtx);
        cond.wait(lock,[this]{
            return tasksCompleted == NUM_TASK;
        });
    }

private:
    bool stop; // 结束标志
    std::vector<std::thread> threads; // 线程数组
    std::queue<std::function<void()>> tasks; // 任务队列,用function包装

    // 线程池符合生产者消费者模型
    std::mutex mtx;
    std::condition_variable cond;
    int tasksCompleted; // 已完成的任务数量

};

int main()
{
    auto time_start = std::chrono::steady_clock::now();
    ThreadPool pool(NUM_THREAD);

    for(int i = 0; i < NUM_TASK; i++) // 提交任务到线程中
    {
        pool.enqueue([i,&pool]{
            // 执行任务的lambda函数 实际较为复杂的任务函数可以调用可调用对象 类中函数,function对象,全局函数等等
            {
                std::unique_lock<std::mutex> lock(iostream_);
                std::cout << "task :" << i <<" is running " << "thread id is: "<< std::this_thread::get_id() << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
            {
                std::unique_lock<std::mutex> lock(iostream_);
                std::cout << "task:" << i << " is done" << " thread id is: "<< std::this_thread::get_id() << std::endl;
            }
            pool.taskCompleted();
        });
    }

    // 添加任务完成标识 确保任务都完成之后才计时
    pool.waitForAllTasks();

    auto time_end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start)/1000.0;

    std::cout << "Total time cost: " << duration.count() << std::endl;
    
    
    return 0;
}