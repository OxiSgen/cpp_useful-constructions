void myprint() { std::cout << std::endl; }

template<typename T, typename... Args> void myprint(const T& t, const Args& ... args)
{
    std::cout << t << " ";
    myprint(args...);
}
