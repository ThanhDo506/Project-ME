#include <iostream>
#include <vector>

#include "common.h"
#include "glm/glm.hpp"
#include "Application.h"
#include "Components/GameObject.h"
#include "Components/Component.h"
#include "Components/Transform.h"


class A : public Component {
public:
    A(int a, GameObject* gameObject, std::string name, bool isActive = true) : Component(gameObject, name, isActive), _a(a) {

    };
    int _a;

    std::string to_string() const {
        return std::to_string(_a);
    }
};

int main() {
    Logger::init();
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
   /* GameObject* z = new GameObject(Transform(glm::vec3(1.0, -5.0, -10.0), glm::vec3(2.0, -2.0, 2.0), glm::quat(glm::vec3(0, 90, 90))), "Z");
    GameObject* g = new GameObject(Transform(glm::vec3(1.0, 5.0, 10.0), glm::vec3(2.0, 2.0, 2.0), glm::quat(glm::vec3(0, 90, 0)), false), "G");
    A* a = new A(5, g, "A");
    g->AddComponent(a);
    g->set_parent(z);
    GameObject copy = GameObject::swallow_copy(*g);
    std::cout << "                  |       t       |       cpy       |\n";
    std::cout << "Address this      | " << g << "       | " << &copy << "      |\n";
    std::cout << "Address parent    | " << g->get_parent() << "       | " << copy.get_parent() << "      |\n";
    g->transform->position = glm::vec3(10, 5, 10);
    std::cout << "Address transform | " << g->transform << "       | " << copy.transform << "      |\n";
    std::cout << "Num components    | " << g->_components.size() << "   | " << copy._components.size() << "     |\n";
    copy.GetComponent<A>()->_a += 1;
    std::cout << "Component A       | " << g->GetComponent<A>() << "   | " << copy.GetComponent<A>() << "     |\n";*/
    Logger::clean();
    return 0;
}
