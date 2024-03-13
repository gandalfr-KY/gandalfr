#pragma once

#include <cassert>
#include <chrono>
#include <cmath>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <utility>

#include "gandalfr/types.hpp"

namespace gandalfr {

const double EPS = 1e-9;

class TestException : public std::exception {
  private:
    std::string msg;

  public:
    const char *file;
    int line;

    TestException(const std::string &message, const char *file, int line)
        : msg(message), file(file), line(line) {}

    const char *what() const noexcept override { return msg.c_str(); }
};

using TestCase = void (*)();

std::map<std::pair<std::string, std::string>, TestCase> test_registry;

#define TEST(test_suite, test_name)                                            \
    void test_suite##_##test_name();                                           \
    struct test_suite##_##test_name##_Reg {                                    \
        test_suite##_##test_name##_Reg() {                                     \
            test_registry[{#test_suite, #test_name}] =                         \
                &test_suite##_##test_name;                                     \
        }                                                                      \
    } test_suite##_##test_name##_reg;                                          \
    void test_suite##_##test_name()

#define EQ(a, b)                                                               \
    if (a != b)                                                                \
    throw TestException("EQ failed.", __FILE__, __LINE__)
#define NEQ(a, b)                                                              \
    if (a == b)                                                                \
    throw TestException("NEQ failed.", __FILE__, __LINE__)
#define NEAR(a, b, eps)                                                        \
    if (std::abs(a - b) > eps)                                                 \
    throw TestException("NEAR failed.", __FILE__, __LINE__)

template <bool enableCout = true> void RunAllTests() {
    if constexpr (enableCout) {
        std::string prev_suite = test_registry.begin()->first.first;
        i32 num_tests = 0, num_correct = 0;

        std::cout << "Running suite: " << prev_suite << std::endl;
        for (const auto &[test_name, proc] : test_registry) {
            auto &[suite, name] = test_name;
            if (prev_suite != suite) {
                prev_suite = suite;
                std::cout << "Result: " << num_correct << "/" << num_tests
                          << std::endl;
                std::cout << std::endl;
                std::cout << "Running suite: " << suite << std::endl;
                num_tests = num_correct = 0;
            }
            std::string testNameWithPadding = suite + '.' + name;
            testNameWithPadding.resize(35, ' ');
            std::cout << "  " << testNameWithPadding << "  ";
            try {
                auto start = std::chrono::high_resolution_clock::now();
                proc();
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsed =
                    std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                          start)
                        .count();
                std::cout << "✅ " << elapsed << " ms" << std::endl;
                ++num_correct;
            } catch (TestException &e) {
                std::cerr << "❌" << std::endl;
                std::cerr << "    File: " << e.file << std::endl;
                std::cerr << "    Line: " << e.line << std::endl;
            }
            ++num_tests;
        }
        std::cout << "Result: " << num_correct << "/" << num_tests << std::endl;
    } else {
        // for dummy test
        for (const auto &[test_name, proc] : test_registry) {
            try {
                proc();
            } catch (TestException &e) {
                std::cout << "❌" << std::endl;
                std::cerr << "    File: " << e.file << std::endl;
                std::cerr << "    Line: " << e.line << std::endl;
            }
        }
        std::cout << "Hello World" << std::endl;
    }
}
} // namespace gandalfr
