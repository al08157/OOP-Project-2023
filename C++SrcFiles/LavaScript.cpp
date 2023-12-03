#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class LavaScript : public MonoBehaviour
{
private:
    Animator* animator;
    GameObject* player;
    GameObject* lavaPunchPrefab;
    float playerDistance;
    float chaseSpeed;
    bool entry;
    float travelTime;
    float endEntry;
    bool isFiring;
    int maxHealth;
    int currHealth;
    bool deathTimer;
    float countdown;
    float timer;
    HealthBarScript* healthBar;

public:
    LavaScript()
    {
        animator = GetComponent<Animator>();
        player = GameObject::FindGameObjectWithTag("Player");
        lavaPunchPrefab = Resources::Load<GameObject>("Prefabs/LavaPunch");

        timer = 5.0f;
        entry = true;
        travelTime = 5.0f;
        countdown = 2.0f;
        maxHealth = 100;
        currHealth = maxHealth;
        chaseSpeed = 0.0f;

        animator->SetInteger("Speed", 6); // This will trigger the conditions on which the key animation of this character changes according to the conditions set on the float "Speed".

        healthBar = GetComponentInChildren<HealthBarScript>();
        healthBar->SetMaxHealth(maxHealth);
        healthBar->SetHealth(currHealth);
    }

    void Update()
    {
        playerDistance = Vector2::Distance(transform->position, player->transform->position);

        // Flip the character if going left
        Vector3 characterScale = transform->localScale;
        if (player->transform->position.x > transform->position.x && !isFiring) {
            characterScale.x = -31.0f;
        } else if (player->transform->position.x < transform->position.x && !isFiring) {
            characterScale.x = 31.0f;
        }
        transform->localScale = characterScale;

        // Traveling into the scene
        if (travelTime > 0.0f && entry) {
            Walk();
            travelTime -= 1.0f * Time.deltaTime;

            if (travelTime <= endEntry) {
                animator->SetInteger("Speed", 0);
                entry = false;
                cout << "Finished Entering the map!" << endl;
            }
        }

        // Creating a timer for Lava Punch attack
        if (timer <= 0.0f) {
            Instantiate(lavaPunchPrefab, lavaPunchPrefab->transform->position, lavaPunchPrefab->transform->rotation);
            timer = 5.0f;
        } else if (timer > 0.0f) {
            timer -= 1.0f * Time.deltaTime;
        }

        // Death trigger
        if (currHealth < 1) {
            LavaDeath();
        }

        if (deathTimer) {
            if (countdown > 1.0f) {
                countdown -= 1.0f * Time.deltaTime;
            } else {
                Destroy(gameObject);
            }
        }
    }

    void LavaDeath()
    {
        animator->SetTrigger("Dead");
        chaseSpeed = 0.0f;
        isFiring = false;
        deathTimer = true;
    }

    void Walk()
    {
        chaseSpeed = 7.0f;
        animator->SetInteger("Speed", 6);
        transform->position = Vector2::MoveTowards(transform->position, player->transform->position, chaseSpeed * Time.deltaTime);
    }

    void TakeDamage(int damage)
    {
        currHealth -= damage;
        healthBar->SetHealth(currHealth);
    }
};
