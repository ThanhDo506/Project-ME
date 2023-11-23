#pragma region Test Component system
#include <iostream>
#include <string>

#include "common.h"
#include "glm/glm.hpp"
#include "Application.h"
#include "../Core/Components/Component.h"
#include "../Core/Components/GameObject.h"

class A : public Component {
public:
    int _a;

    A(int a) : Component(nullptr, true) { this->_a = a; }

    A* Clone() const override {
        return new A(*this);
    }
    std::string to_string() const override {
        return "A";
    }
};

class B : public Component {
public:
    std::string _b;

    B(std::string b)
        : Component(nullptr, true),
        _b(b) { }

    B* Clone() const override {
        return new B(*this);
    }

    std::string to_string() const override {
        return "B";
    }
};

void print_hierachy(GameObject* root, int level) {
    for (int i = 0; i < level; i++) {
        std::cout << "\t";
    }
    std::string parentName = "null";
    if (root->parent) {
        parentName = root->parent->name;
    }
    std::cout << "- Name: " << root->name << " || Address: " << root << " || Parent: " << parentName << std::endl;
    for (int i = 0; i < level; i++) {
        std::cout << "\t";
    }
    std::cout << "\tComponent:\n";
    for (auto component : root->_components) {
        for (int i = 0; i < level + 2; i++) {
            std::cout << "\t";
        }
        std::cout << component.second->to_string() << " || Address: " << component.second;
        std::cout << " || Attach to: " << component.second->gameObject->name << std::endl;
    }
    if (!root->_children.empty()) {
        for (int i = 0; i < level; i++) {
            std::cout << "\t";
        }
        std::cout << "\tChildren:\n";
    }
    for (auto child : root->_children) {
        print_hierachy(child, level + 2);
    }
}

int main() {
    /*Logger::init();
    WindowSetting setting = {
        1600,
        900,
        0,
        "Material Editor",
        false,
        false,
        false
    };
    Application* app = new Application(setting);
    app->Run();
    Logger::clean();
    system("pause");
    return 0;*/
    GameObject* root = new GameObject(Transform(), "root");
    print_hierachy(root, 0);
    std::cout << "-----------------------------------------------------------\n";

    GameObject* gObj = new GameObject(Transform(), "gObj", root);
    gObj->AddComponent<A>(10);
    gObj->AddComponent<B>("asdasd");
    print_hierachy(root, 0);
    std::cout << "-----------------------------------------------------------\n";


    GameObject* c1Obj = new GameObject(Transform(glm::vec3(0.0), glm::vec3(1.0), glm::vec3(0.0)), "c1Obj", gObj);
    print_hierachy(root, 0);
    std::cout << "-----------------------------------------------------------\n";

    GameObject* c2Obj = new GameObject(Transform(glm::vec3(0.0), glm::vec3(1.0), glm::vec3(0.0)), "c2Obj", gObj);
    c2Obj->AddComponent<B>("asd");
    print_hierachy(root, 0);
    std::cout << "-----------------------------------------------------------\n";

    GameObject* c3Obj = new GameObject(Transform(glm::vec3(0.0), glm::vec3(1.0), glm::vec3(0.0)), "c3Obj", c1Obj);
    print_hierachy(root, 0);
    std::cout << "-----------------------------------------------------------\n";


    GameObject* copyObj = new GameObject(*gObj);
    //copyObj->parent = root;
    copyObj->name = "copyObj";
    print_hierachy(root, 0);
    std::cout << "-----------------------------------------------------------\n";

    //std::cout << "size of gObj " << sizeof(gObj) << " || size of copyObj " << sizeof(copyObj) << std::endl;
    //std::cout << "gObj " << gObj->_components.size() << " || copyObj " << copyObj->_components.size() << std::endl;
    //std::cout << gObj->GetComponent<A>()->_a << std::endl;
    //std::cout << gObj->GetComponent<B>()->_b << std::endl;
    //std::cout << copyObj->GetComponent<A>()->_a << std::endl;
    //std::cout << copyObj->GetComponent<B>()->_b << std::endl;
    gObj->RemoveComponent<B>();
    std::cout << "gObj " << gObj->_components.size() << " || copyObj " << copyObj->_components.size() << std::endl;
    std::cout << std::is_same<decltype(gObj->GetComponent<A>()), B*>::value << std::endl;
    std::cout << std::endl;
    print_hierachy(root, 0);
    std::cout << "-----------------------------------------------------------\n";

    GameObject* duma = copyObj->_children[0];
    std::cout << duma << std::endl;
    duma->set_parent(c2Obj);

    print_hierachy(root, 0);
    std::cout << "-----------------------------------------------------------\n";
    Logger::clean();
}
#pragma endregion

//#include <iostream>
//#include <string>
//
//#include "common.h"
//#include "glm/glm.hpp"
//#include "Application.h"
//
//int main() {
//    Logger::init();
//    WindowSetting setting = {
//        1600,
//        900,
//        0,
//        "Material Editor",
//        false,
//        false,
//        false
//    };
//    Application* app = new Application(setting);
//    app->Run();
//    Logger::clean();
//    system("pause");
//    return 0;
//}
