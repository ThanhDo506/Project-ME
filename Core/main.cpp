//#pragma region Test Component system
////#include <iostream>
////#include <string>
////
////#include "common.h"
////#include "glm/glm.hpp"
////#include "Application.h"
////#include "../Core/Components/Component.h"
////#include "../Core/Components/GameObject.h"
////#include "../../Core/Render/Lighting/Light.h"
////
////class A : public Component {
////public:
////    int _a;
////
////    A(int a) : Component(nullptr, true) { this->_a = a; }
////
////    A* Clone() const override {
////        return new A(*this);
////    }
////    std::string to_string() const override {
////        return "A";
////    }
////};
////
////class B : public Component {
////public:
////    std::string _b;
////
////    B(std::string b)
////        : Component(nullptr, true),
////        _b(b) { }
////
////    B* Clone() const override {
////        return new B(*this);
////    }
////
////    std::string to_string() const override {
////        return "B";
////    }
////};
////
////void print_hierachy(GameObject* root, int level) {
////    for (int i = 0; i < level; i++) {
////        std::cout << "\t";
////    }
////    std::string parentName = "null";
////    if (root->parent) {
////        parentName = root->parent->name;
////    }
////    std::cout << "- Name: " << root->name << " || Address: " << root << " || Parent: " << parentName << std::endl;
////    for (int i = 0; i < level; i++) {
////        std::cout << "\t";
////    }
////    std::cout << "\tComponent:\n";
////    for (auto component : root->_components) {
////        for (int i = 0; i < level + 2; i++) {
////            std::cout << "\t";
////        }
////        std::cout << component.second->to_string() << " || Address: " << component.second;
////        std::cout << " || Attach to: " << component.second->gameObject->name << std::endl;
////        Transform* t = dynamic_cast<Transform*>(component.second);
////        if (t) {
////            for (int i = 0; i < level + 3; i++) {
////                std::cout << "\t";
////            }
////            std::cout << "Position: " << t->position.x << " " << t->position.y << " " << t->position.z << std::endl;
////            for (int i = 0; i < level + 3; i++) {
////                std::cout << "\t";
////            }
////            std::cout << "Scale: " << t->scale.x << " " << t->scale.y << " " << t->scale.z << std::endl;
////            for (int i = 0; i < level + 3; i++) {
////                std::cout << "\t";
////            }
////            glm::vec3 rotation = t->get_local_euler_angles();
////            std::cout << "Rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
////        }
////    }
////    if (!root->_children.empty()) {
////        for (int i = 0; i < level; i++) {
////            std::cout << "\t";
////        }
////        std::cout << "\tChildren:\n";
////    }
////    for (auto child : root->_children) {
////        print_hierachy(child, level + 2);
////    }
////}
////
////int main() {
////    GameObject* root = new GameObject(Transform(), "root");
////
////    GameObject* gObj = new GameObject(Transform(), "gObj", root);
////    gObj->AddComponent<A>(10);
////    gObj->AddComponent<B>("asdasd");
////
////    GameObject* c1Obj = new GameObject(Transform(glm::vec3(5.0f), glm::vec3(1.0f), glm::vec3(45.0f)), "c1Obj", gObj);
////
////    GameObject* c2Obj = new GameObject(Transform(glm::vec3(7.0f), glm::vec3(2.0f), glm::vec3(90.0f)), "c2Obj", gObj);
////    c2Obj->AddComponent<B>("asd");
////
////    GameObject* c3Obj = new GameObject(Transform(glm::vec3(8.0f), glm::vec3(5.0f), glm::vec3(45.0f)), "c3Obj", c1Obj);
////
////
////    GameObject* copyObj = new GameObject(*gObj);
////    //copyObj->parent = root;
////    copyObj->name = "copyObj";
////
////    print_hierachy(root, 0);
////    std::cout << "-----------------------------------------------------------\n";
////
////    //std::cout << "size of gObj " << sizeof(gObj) << " || size of copyObj " << sizeof(copyObj) << std::endl;
////    //std::cout << "gObj " << gObj->_components.size() << " || copyObj " << copyObj->_components.size() << std::endl;
////    //std::cout << gObj->GetComponent<A>()->_a << std::endl;
////    //std::cout << gObj->GetComponent<B>()->_b << std::endl;
////    //std::cout << copyObj->GetComponent<A>()->_a << std::endl;
////    //std::cout << copyObj->GetComponent<B>()->_b << std::endl;
////    gObj->RemoveComponent<B>();
////    std::cout << "gObj " << gObj->_components.size() << " || copyObj " << copyObj->_components.size() << std::endl;
////    std::cout << std::is_same<decltype(gObj->GetComponent<A>()), B*>::value << std::endl;
////    std::cout << std::endl;
////
////    copyObj->_children[0]->set_parent(c2Obj);
////
////    print_hierachy(root, 0);
////    std::cout << "-----------------------------------------------------------\n";
////
////    if (c2Obj == nullptr) {
////        std::cout << "dafug\n";
////    } else {
////        Transform* tr = c3Obj->GetComponent<Transform>();
////        if (!tr) {
////            std::cout << "dafug\n";
////        } else {
////            glm::vec3 t = tr->get_world_position();
////            std::cout << "Position: " << t.x << " " << t.y << " " << t.z << std::endl;
////            t = tr->get_world_scale();
////            std::cout << "Scale: " << t.x << " " << t.y << " " << t.z << std::endl;
////            glm::vec3 rotation = tr->get_world_euler_angles();
////            std::cout << "Rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
////        }
////    }
////
////    Light* l = new Light();
////    l->attach_to_gameObject(c2Obj);
////    std::cout << l->get_gameObject()->name << std::endl;
////    glm::vec3 r1 = glm::degrees(
////        glm::eulerAngles(
////            glm::quat(glm::vec3(
////                glm::radians(30.0f), 
////                glm::radians(90.0f), 
////                glm::radians(45.0f)))));
////    std::cout << r1.x << " " << r1.y << " " << r1.z << std::endl;
////    c2Obj->AddComponent<Light>();
////    Logger::clean();
////}
//#pragma endregion
//
#include <iostream>
#include <string>

#include "common.h"
#include "glm/glm.hpp"
#include "Application.h"

int main() {
    Logger::init();
    WindowSetting setting = {
        1920,
        1080,
        0,
        "Material Editor",
        false,
        false,
        false
    };
    Application* app = new Application(setting);
    app->Run();
    Logger::clean();
    return 0;
}