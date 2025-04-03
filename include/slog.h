//
// Created by sphdx.
//

#ifndef SLOG_H
#define SLOG_H

#include <iostream>
#include <ostream>
#include <string>
#include <chrono>
#include <iomanip>

template<typename T>
concept Container = requires(T t)
{
    t.begin();
    t.end();
} && !std::is_same_v<T, std::string>;

class Slog {
    Slog() = default;

    template<typename Key, typename Val>
    class LoggerOption {
    public:
        const Key key_;
        const Val value_;

        LoggerOption(Key &&key, Val &&val)
            : key_(std::forward<Key>(key)), value_(std::forward<Val>(val)) {
        }
    };

    template<typename... Keys, typename... Vals>
    static void log(const std::string &type, const std::string &message, const LoggerOption<Keys, Vals> &... args);

    template<typename T>
    static void sl_print(const T &val);

    template<typename A, typename B>
    static void sl_print(const std::pair<A, B>& p);

    template<Container C>
    static void sl_print(const C &container);

public:
    Slog(const Slog &) = delete;

    Slog &operator=(const Slog &) = delete;

    template<typename... Keys, typename... Vals>
    static void info(const std::string &message, const LoggerOption<Keys, Vals> &... args);

    template<typename... Keys, typename... Vals>
    static void warn(const std::string &message, const LoggerOption<Keys, Vals> &... args);

    template<typename... Keys, typename... Vals>
    static void error(const std::string &message, const LoggerOption<Keys, Vals> &... args);

    template<typename Key, typename Val>
    static LoggerOption<Key, Val> opt(Key &&key, Val &&val);
};

template<typename... Keys, typename... Vals>
void Slog::info(const std::string &message, const LoggerOption<Keys, Vals> &... args) {
    log("INFO", message, args...);
}

template<typename... Keys, typename... Vals>
void Slog::warn(const std::string &message, const LoggerOption<Keys, Vals> &... args) {
    log("WARN", message, args...);;
}

template<typename... Keys, typename... Vals>
void Slog::error(const std::string &message, const LoggerOption<Keys, Vals> &... args) {
    log("ERROR", message, args...);
}

template<typename Key, typename Val>
Slog::LoggerOption<Key, Val> Slog::opt(Key &&key, Val &&val) {
    return LoggerOption<Key, Val>(std::forward<Key>(key), std::forward<Val>(val));
}

template<typename... Keys, typename... Vals>
void Slog::log(const std::string &type, const std::string &message, const LoggerOption<Keys, Vals> &... args) {
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // "%Y-%m-%d %H:%M:%S"
    std::cout << std::put_time(std::localtime(&now), "%H:%M:%S") << ' ';

    std::cout << "[" << type << "] " << message;

    ((std::cout << ", " << args.key_ << '=', sl_print(args.value_)), ...);

    std::cout << std::endl;
}

template<typename T>
void Slog::sl_print(const T &val) {
    std::cout << val;
}

template<typename A, typename B>
void Slog::sl_print(const std::pair<A, B> &p) {
    std::cout << '(';
    sl_print(p.first);
    std::cout << ", ";
    sl_print(p.second);
    std::cout << ')';
}

template<Container C>
void Slog::sl_print(const C &container) {
    std::cout << '[';
    auto it = container.begin();
    if (it != container.end()) {
        sl_print(*it);
        ++it;
    }
    for (; it != container.end(); ++it) {
        std::cout << ", ";
        sl_print(*it);
    }
    std::cout << ']';
}

#endif //SLOG_H
