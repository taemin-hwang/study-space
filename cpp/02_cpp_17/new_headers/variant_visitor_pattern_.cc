#include <iostream>
#include <variant>
#include <utility>

using namespace std;

class Man{};
class IronMan : public Man {
 public:
    IronMan() : Man() { std::cout << __func__ << std::endl; }
    void ShowMeTheMoney() { std::cout << __func__ << std::endl; }
 private:
    int money = 100;
};
class SpiderMan : public Man {
 public:
    SpiderMan() : Man() { std::cout << __func__ << std::endl; }
    void GiveMeTheMoney() { std::cout << __func__ << std::endl; }
};

// template <class Visitor, class ... Variants>
// constexpr visit(Visitor&& vis, Variants&&... vars)
// vis: a callable that accepts every possible alternative from every varaint
// vars: list of variatns to pass to the visitor

template <class... Ts>
struct overload : Ts... {
    using Ts::operator()...;
};

template <class... Ts>
overload(Ts...)->overload<Ts...>;

int main() {
    std::variant<IronMan, SpiderMan> man{IronMan()}; // type-safe union
    std::visit(overload{
        [](IronMan& obj) { obj.ShowMeTheMoney(); },
        [](SpiderMan& obj) { obj.GiveMeTheMoney(); }
    }, man);
}

#if operator_overload
struct ManOverload {
    void operator()(IronMan& obj) { obj.ShowMeTheMoney(); }
    void operator()(SpiderMan& obj) { obj.GiveMeTheMoney(); }
};

int main() {
    std::variant<IronMan, SpiderMan> man{IronMan()};
    // visitor(a callable like function), variant
    std::visit(ManOverload(), man);
}
#endif

#if lambda_expression
int main() {
    std::variant<IronMan, SpiderMan> man{IronMan()};
    std::visit([](auto&& args) {
        // decay_t
        using T = std::decay_t<decltype(args)>;
        if constexpr (std::is_same_v<T, IronMan>)
            args.ShowMeTheMoney();
        else if constexpr (std::is_same_v<T, SpiderMan>)
            args.GiveMeTheMoney();
    }, man);
}
#endif
