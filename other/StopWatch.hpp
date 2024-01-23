#pragma once
#include <chrono>

namespace gandalfr {

class StopWatch {
  private:
    std::chrono::system_clock::time_point start, end;

  public:
    // タイマーを0にリセット
    void reset() { start = std::chrono::system_clock::now(); }
    long long getMillisecconds() {
        end = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
            .count();
    }
    long long getSecconds() {
        end = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(end - start)
            .count();
    }
};
} // namespace gandalfr
