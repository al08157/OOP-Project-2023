#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class Reaper : public MonoBehaviour
{
private:
    float reaperSpeed;
    GameObject* player;
    float chaseSpeed;
    float playerDistance;
    bool entry;
    float travelTime;
    float endEntry;
    int maxHealth;
    int currHealth;
    bool deathTimer;
    float countdown;
    HealthBarScript* healthBar;

public:
    Reaper()
    {
        travelTime = 6.0f;
        endEntry = 1.0f;
        reaperSpeed = chaseSpeed = 5.0f;
        player = GameObject::FindGameObjectWithTag("Player"); // Slime has the tag "Player"
        entry = true;

        countdown = 2.0f;
        maxHealth = 250;
        currHealth = maxHealth;

        healthBar = GetComponentInChildren<HealthBarScript>();
        healthBar->SetMaxHealth(maxHealth);
        healthBar->SetHealth(currHealth - 50);
    }

    void Update()
    {
        // Flip the character if going left
        Vector3 characterScale = transform->localScale;
        if (player->transform->position.x > transform->position.x) {
            characterScale.x = 2.0f;
        } else if (player->transform->position.x < transform->position.x) {
            characterScale.x = -2.0f;
        }
        transform->localScale = characterScale;

        if (travelTime > 0.0f && entry) {
            transform->position += (Vector3::left * reaperSpeed) * Time.deltaTime;
            travelTime -= 1.0f * Time.deltaTime;

            if (travelTime <= endEntry) {
                entry = false;
                cout << "Finished Entering the map!" << endl;
            }
        } else if (entry == false) {
            // Get the player distance between the reaper and the player
            playerDistance = Vector2::Distance(transform->position, player->transform->position);

            // The reaper is going to chase the player in a specific range
            if (playerDistance < 40.0f) {
                // Getting the time the reaper will take to follow the player
                Vector2 direction = player->transform->position - transform->position;

                transform->position = Vector2::MoveTowards(transform->position, player->transform->position, chaseSpeed * Time.deltaTime);
            }
        }

        // Death trigger
        if (currHealth < 1) {
            ReaperDeath();
        }

        if (deathTimer) {
            if (countdown > 1.0f) {
                countdown -= 1.0f * Time.deltaTime;
            } else {
                Destroy(gameObject);
            }
        }
    }

    void ReaperDeath()
    {
        deathTimer = true;
    }

    void TakeDamage(int damage)
    {
        currHealth -= damage;
        healthBar->SetHealth(currHealth);
    }
};
