#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class LavaPunchScript : public MonoBehaviour
{
private:
    GameObject* player;
    float timer;
    float xpos;
    float ypos;

public:
    LavaPunchScript()
    {
        player = GameObject::FindGameObjectWithTag("Player");
        timer = 2.0f;
        xpos = transform->position.x;
        ypos = transform->position.y;

        if (transform->position.y <= -9.0f) {
            ypos = -8.0f;
            transform->position = Vector3(transform->position.x, ypos, transform->position.z);
        }

        if (transform->position.y <= -7.0f) {
            if (player->transform->position.x > transform->position.x) {
                xpos = player->transform->position.x;
            } else {
                xpos = player->transform->position.x;
            }
            transform->position = Vector3(xpos, transform->position.y, transform->position.z);
        }
    }

    void OnTriggerEnter2D(Collider2D* collision)
    {
        if (collision->gameObject->CompareTag("Player")) {
            cout << "Hit Target" << endl;
            collision->gameObject->GetComponent<SlimeScript>()->TakeDamage(20);
            cout << "Deleting bullet!" << endl;
        }
    }
};
