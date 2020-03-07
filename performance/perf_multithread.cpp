#include <hjson.h>

#include <chrono>
#include <thread>
#include <vector>
#include <iostream>


static void _run_test() {
  std::string inString = R"(
{
  quotes:
  {
    num1: "1,2"
    num2: "-1.1 ,"
    num3: "1e10 ,2"
    num4: "-1e-10,"
    kw1: "true,"
    kw2: "false ,"
    kw3: "null,123"
    close1: "1}"
    close1b: "1 }"
    close2: "1]"
    close2b: "1 ]"
    close3: "1,"
    close3b: "1 ,"
    comment1: "1#str"
    comment2: "1//str"
    comment3: "1/*str*/"
    punc1: "{"
    punc1b: "{foo"
    punc2: "}"
    punc2b: "}foo"
    punc3: "["
    punc3b: "[foo"
    punc4: "]"
    punc4b: "]foo"
    punc5: ","
    punc5b: ",foo"
    punc6: ":"
    punc6b: ":foo"
  }
  noquotes:
  {
    num0: ".1,2"
    num1: "1.1.1,2"
    num2: "-.1,"
    num3: "1e10e,2"
    num4: "-1e--10,"
    kw1: "true1,"
    kw2: "false0,"
    kw3: "null0,"
    close1: "a}"
    close2: "a]"
    comment1: "a#str"
    comment2: "a//str"
    comment3: "a/*str*/"
  }
}
)";

  for (int a = 0; a < 10000; ++a) {
    Hjson::Unmarshal(inString);
  }
}


void perf_multithread() {
  std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

  std::vector<std::thread> threads;

  for (int a = 0; a < 16; ++a) {
    threads.push_back(std::thread(_run_test));
  }

  for (auto &th : threads) {
    if (th.joinable()) {
      th.join();
    }
  }

  std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();

  std::cout << "Runtime: " << std::chrono::duration<double>(stop -
    start).count() << " seconds" << std::endl;
}
