#ifndef STOPWATCH
#define STOPWATCH
#include <chrono>

/* reset() := タイマーを0にリセット
 * get_milliseconnds() := ミリ秒を返す
 * get_seconnds() := 秒を返す
 */
class {
  private:
    std::chrono::system_clock::time_point start, end;

  public:
    void reset(){ start = std::chrono::system_clock::now(); }
    long long get_millisecconds(){
        end = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    }
    long long get_secconds(){
        end = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
    }
} static stopwatch;

#endif