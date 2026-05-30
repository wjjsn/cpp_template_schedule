// #include <iostream>
#include <tuple>
#include <cstdint>

// 为了代码可读性，先将确定的类型进行别名定义
using TimeProviderFunc = uint64_t(*)(); // 返回 uint64_t 的时间函数指针
using CallbackFunc = void(*)();         // 触发时调用的回调函数指针
struct TaskConfig {
    uint64_t interval;
    CallbackFunc callback;
}; // (隔多久触发一次, 回调函数)

// 模板类定义：第一个参数是时间函数，后续是至少一个 TimerTuple
template <TimeProviderFunc GetTime, TaskConfig FirstTimer, TaskConfig... RemainingTimers>
class StaticTimerManager {
private:
    // 将所有传入的元组静态组合成一个 std::tuple 数组
    // 这里的类型是完全确定的
    static constexpr std::size_t TimerCount = 1 + sizeof...(RemainingTimers);
    static constexpr TaskConfig Timers[TimerCount] = { FirstTimer, RemainingTimers... };

    // 静态内存：记录上一次触发的时间戳（初始化为 0）
    static inline uint64_t lastTriggerTimes[TimerCount] = { 0 };

public:
    // 静态轮询函数：在主循环中调用此函数
    static void poll() {
        uint64_t currentTime = GetTime();

        // 使用编译期展开或循环来处理确定的数组
        for (std::size_t i = 0; i < TimerCount; ++i) {
            uint64_t interval = Timers[i].interval;
            CallbackFunc callback = Timers[i].callback;

            // 首次运行时初始化时间戳，避免启动时瞬间全部触发
            if (lastTriggerTimes[i] == 0) {
                lastTriggerTimes[i] = currentTime;
                continue;
            }

            // 检查是否到达时间间隔
            if (currentTime - lastTriggerTimes[i] >= interval) {
                if (callback) {
                    callback(); // 执行回调
                }
                lastTriggerTimes[i] = currentTime; // 更新时间
            }
        }
    }
};