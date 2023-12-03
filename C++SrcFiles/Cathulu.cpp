#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class Cathulu {
private:
    GameObject* player;
    float chaseSpeed;
    float distance;
    float maxDistance;
    float xPos;
    float yPos;
    int maxHealth;
    int currHealth;
    HealthBarScript healthbar;

public:
    Cathulu() {
        player = GameObject::FindWithTag("Player");
        maxDistance = 30.0f;
        chaseSpeed = 8.0f;
        maxHealth = currHealth = 100;
        healthbar.SetMaxHealth(maxHealth);
        healthbar.SetHealth(currHealth);
    }

    void Update() {
        xPos = transform->position.x;
        yPos = transform->position.y;
        distance = Vector2::Distance(transform->position, player->transform->position);

        // Calculate movement direction
        Vector2 direction = player->transform->position - transform->position;
        direction.Normalize();
        float angle = atan2(direction.y, direction.x) * Mathf::Rad2Deg;

        // Move towards player
        transform->position = Vector2::MoveTowards(transform->position, player->transform->position, chaseSpeed * Time.deltaTime);
        transform->rotation = Quaternion::Euler(Vector3::forward * (angle + 180.0f));

        // Limit vertical movement
        if (transform->position.y <= 20.0f) {
            if (player->transform->position.x > transform->position.x) {
                xPos += chaseSpeed * Time.deltaTime;
            } else {
                xPos -= chaseSpeed * Time.deltaTime;
            }

            transform->position = new Vector3(xPos, transform->position.y, transform->position.z);
        }

        if (transform->position.y <= 19.0f) {
            yPos += chaseSpeed * Time.deltaTime;
            transform->position = new Vector3(transform->position.x, yPos, transform->position.z);
        }
    }

    void TakeDamage(int damage) {
        currHealth -= damage;
        healthbar.SetHealth(currHealth);
    }
};
