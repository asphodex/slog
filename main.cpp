#include <map>
#include "include/slog.h"
#include <vector>

int main() {
    std::map<std::string, int> map;
    map["foo"] = 1;
    std::vector vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Slog::info("log example", Slog::opt("key", "val"), Slog::opt("vector", vec),
               Slog::opt("map", map));
}
