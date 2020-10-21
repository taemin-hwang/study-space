#include <iostream>
#include <vector>

using namespace std;

// class template
template <typename eNodeB, typename Ue>
class Network {
 public:
    Network(eNodeB e) : e_node_b_(e) { std::cout << __func__ << std::endl; }
    eNodeB GeteNodeB() { return e_node_b_; }
    void AddUserEquipment(Ue u) { user_equipments_.push_back(u); }
 private:
    eNodeB e_node_b_;
    std::vector<Ue> user_equipments_;
};

// template specilization
template <typename Ue>
class Network <std::string, Ue> {
 public:
    Network(std::string e) : e_node_b_(e) { std::cout << __func__ << ", " << e << std::endl; }
    std::string GeteNodeB() { return e_node_b_; }
    void AddUserEquipment(Ue u) { user_equipments_.push_back(u); }
 private:
    std::string e_node_b_;
    std::vector<Ue> user_equipments_;
};

class eNodeB {
 public:
    int x, y;
};

class UserEquipment {
 public:
    UserEquipment() : x(0), y(0) {}
    UserEquipment(int x, int y) : x(x), y(y) {}
    int x, y;
};

int main() {
    // template instantiation
    Network<std::string, UserEquipment> lte_network("LTE");
    lte_network.AddUserEquipment(UserEquipment(10, 10));
    lte_network.AddUserEquipment(UserEquipment(5, 10));

    eNodeB enodeb;
    Network<eNodeB, UserEquipment> wcdma_network(enodeb);
    wcdma_network.AddUserEquipment(UserEquipment(10, 10));
    wcdma_network.AddUserEquipment(UserEquipment(5, 10));
}
