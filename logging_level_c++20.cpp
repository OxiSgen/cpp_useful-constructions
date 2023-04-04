#include <array>
#include <ranges>
#include <string_view>

#define QS_ENUM(T, ...)                                                 \
    enum class T { __VA_ARGS__ };                                       \
    template <>                                                         \
    inline constexpr auto Impl::Max<T> = Impl::enum_size(#__VA_ARGS__); \
    template <>                                                         \
    inline constexpr auto Impl::Tokens<T> =                             \
        Impl::tokenize_enum<Impl::Max<T>>(#__VA_ARGS__);

namespace Impl {

template <class Ty>
inline constexpr Ty Max = Ty{};

template <class Ty>
inline constexpr Ty Tokens = Ty{};

consteval size_t enum_size(std::string_view sv) {
    return std::ranges::count(sv, ',') + !sv.ends_with(',');
}

template <size_t N>
consteval std::array<std::string_view, N> tokenize_enum(std::string_view base) {
    size_t count{};
    std::array<std::string_view, N> tokens;
    for (const auto word : std::views::split(base, std::string_view{", "}))
        tokens[count++] = {word.begin(), *(word.end() - 1) == ','
                                             ? word.end() - 1
                                             : word.end()};
    return tokens;
}

}  // namespace Impl

template <class E>
constexpr auto enumToString(E e) {
    return Impl::Tokens<E>[static_cast<std::underlying_type_t<E>>(e)];
}

template <class E>
constexpr E stringToEnum(auto value) {
    for (int i = 0; i < Impl::Max<E>; ++i)
        if (Impl::Tokens<E>[i] == value) return static_cast<E>(i);
    return static_cast<E>(-1);
}

QS_ENUM(LogLevel,  // enum class LogLevel
        Alert,     // LogLevel::Alert
        Critical,  // LogLevel::Critical
        Error,     // LogLevel::Error
        Warning,   // LogLevel::Warning
        Notice,    // LogLevel::Notice
        Info,      // LogLevel::Info
        Debug      // LogLevel::Debug
);

QS_ENUM(Test,   // enum class Test
        Test0,  // Test::Test0
        Test1,  // Test::Test1
        Test2,  // Test::Test2
        Test3,  // Test::Test3
);

int main() {
    // serialize
    constexpr LogLevel a = LogLevel::Error;
    constexpr auto str{enumToString(a)};
    std::cout << str << std::endl;

    // deserialize

    constexpr auto index = stringToEnum<LogLevel>("Notice");
    switch (index) {
        case LogLevel::Alert:
            std::cout << "ALERT" << std::endl;
            break;
        case LogLevel::Critical:
            std::cout << "Critical" << std::endl;
            break;
        case LogLevel::Error:
            std::cout << "Error" << std::endl;
            break;
        case LogLevel::Warning:
            std::cout << "Warning" << std::endl;
            break;
        case LogLevel::Notice:
            std::cout << "Notice" << std::endl;
            break;
        case LogLevel::Info:
            std::cout << "Info" << std::endl;
            break;
        case LogLevel::Debug:
            std::cout << "Debug" << std::endl;
            break;
        default:
            std::cout << "Incorrect value" << std::endl;
            break;
    }

    return 0;
}
