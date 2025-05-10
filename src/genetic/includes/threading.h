//
// Created by Mateusz Mikiciuk on 09/05/2025.
//

#ifndef THREADING_H
#define THREADING_H

#include <thread>
#include <spdlog/spdlog.h>

template<typename Func>
void parallelFor(const size_t count, Func func) {
    const unsigned thread_count = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(thread_count);

    for (size_t t = 0; t < thread_count; ++t) {
        threads[t] = std::thread([=, &func]() {
           for (size_t i = t; i < count; i += thread_count) {
               try {
                func(i);
               }
               catch (const std::exception &e) {
                   spdlog::error("Exception in thread {} at iteration: {} {}", t, i , e.what());
               }
           }
        });
    }

    for (auto &t : threads) {
        t.join();
    }
}

#endif //THREADING_H
