#pragma once

#include <iostream>
#include <string>
#include <map>
#include <cassert> 
#include <cmath> 
#include <exception> 
#include <chrono> 

const double EPS = 1e-9;

class TestException : public std::exception {
private:
    std::string msg;

public:
    const char* file;
    int line;

    TestException(const std::string& message, const char* file, int line) : msg(message), file(file), line(line) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

using TestCase = void(*)();

std::map<std::string, TestCase> test_registry;

#define TEST(test_suite, test_name) \
    void test_name(); \
    struct test_name##_Reg { \
        test_name##_Reg() { \
            test_registry[#test_suite "." #test_name] = &test_name; \
        } \
    } test_name##_reg; \
    void test_name()

#define EQ(a, b) if (a != b) throw TestException("EQ failed.", __FILE__, __LINE__)
#define NEQ(a, b) if (a == b) throw TestException("NEQ failed.", __FILE__, __LINE__)
#define NEAR(a, b, eps) if (std::abs(a - b) > eps) throw TestException("NEAR failed.", __FILE__, __LINE__)

void RunAllTests() {
    for (const auto& [test_name, proc] : test_registry) {
        std::cout << "Running test: " << test_name << std::endl;
        try {
            auto start = std::chrono::high_resolution_clock::now();
            proc();
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "✅ Test passed!" << std::endl;
            std::cout << "     Time: " << elapsed << " ms" << std::endl;
        } catch(TestException& e) {
            std::cerr << "❌ Test failed: " << e.what() << std::endl;
            std::cerr << "     File: " << e.file << std::endl; 
            std::cerr << "     Line: " << e.line << std::endl; 
        }
    }
}
