# Slog

Slog (simple logger) is a primitive logger that I use in my student lab work. It is not thread-safe and is not fully ready yet. 

### Usage

Just call `Slog::<info, warn, error>(<message>)`. 
Logger messages can be supplemented with `Slog::opt(<key>, <val>)` 
and `<val>` It can be a container that implements the `begin()` and 
`end()` methods using iterators and `std::map`. 

### Example
[main.go](main.cpp)

    std::map<std::string, int> map;
    map["foo"] = 1;
    std::vector vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Slog::info("log example", Slog::opt("key", "val"), Slog::opt("vector", vec),
               Slog::opt("map", map));

    // 07:21:34 [INFO] log example, key=val, vector=[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], map=[(foo, 1)]

