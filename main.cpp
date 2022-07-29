#include <dlfcn.h>
#include <stddef.h>

#include <chrono>
#include <exception>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "lib_common.h"

using namespace std::literals::chrono_literals;

namespace fs = std::filesystem;

typedef struct {
    void (*get_name)(char buf[MAX_NAME_LEN]);
    void (*action)();
} lib_fn_t;

auto& lib_handles() {
    static std::vector<std::pair<void*, lib_fn_t>> vec;
    return vec;
}

std::mutex& sync_mutex() {
    static std::mutex mu;
    return mu;
}

void close_all_handles(const std::vector<std::pair<void*, lib_fn_t>>& vec) {
    for (const auto& p : vec) {
        dlclose(p.first);
    }
}

void get_all_lib_path(std::vector<std::string>& libs, const std::string dir) {
    fs::path path{dir};
    if (!fs::is_directory(path)) {
        throw "path is not directory!";
    }
    for (fs::directory_iterator ed, it(path); it != ed; ++it) {
        std::string tmp = it->path().filename().string();
        if (tmp.rfind("lib", 0) == 0) {
            libs.push_back(dir + tmp);
        }
    }
}

void load_all_libs() {
    std::lock_guard<decltype(sync_mutex())> g(sync_mutex());
    auto&& vec = lib_handles();
    close_all_handles(vec);
    vec.clear();
    std::vector<std::string> paths;
    get_all_lib_path(paths, "./lib_srcs/");
    for (const std::string& s : paths) {
        void* p = dlopen(s.c_str(), RTLD_NOW);
        void* name_fn = dlsym(p, "get_name");
        void* action_fn = dlsym(p, "action");
        lib_fn_t tmp;
        tmp.get_name = reinterpret_cast<decltype(tmp.get_name)>(name_fn);
        tmp.action = reinterpret_cast<decltype(tmp.action)>(action_fn);
        vec.emplace_back(p, tmp);
    }
}

void execute_all_libs() {
    std::lock_guard<decltype(sync_mutex())> g(sync_mutex());
    const auto& vec = lib_handles();
    std::cout << "vec size:" << vec.size() << std::endl;
    for (const auto& p : vec) {
        char name[MAX_NAME_LEN];
        p.second.get_name(name);
        std::cout << "lib name:" << std::string(name) << ","
                  << "lib action:";
        p.second.action();
        std::cout << "\n";
        std::cout.flush();
    }
}

int main() {
    std::thread search_t([]() {
        for (size_t i = 0; i < 1000; ++i) {
            load_all_libs();
            std::cout.flush();
            std::this_thread::sleep_for(10s);
        }
    });
    std::thread exec_t([]() {
        for (size_t i = 0; i < 1000; ++i) {
            execute_all_libs();
            std::cout.flush();
            std::this_thread::sleep_for(3s);
        }
    });
    search_t.join();
    exec_t.join();
    return 0;
}