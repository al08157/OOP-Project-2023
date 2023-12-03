#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class SkeletonScript : public MonoBehaviour
{
private:
    Animator* animator;
    GameObject* player;
    float playerDistance;
    float chaseSpeed;
    bool entry;
    float travelTime;
    float endEntry;
    GameObject* arrowPrefab;
    Transform* arrowSpawn;
    float attackRange;
    LayerMask targetLayer;
    bool isFiring;
    int maxHealth;
    int currHealth;
    bool deathTimer;
    float countdown;
    int attackDamage;
    bool canShoot;
    HealthBarScript* healthBar;

public:
    SkeletonScript()
    {
        countdown = 2.0f;
        maxHealth = 100;
        currHealth = maxHealth;
        attackRange = 20.0f;
        attackDamage = 40;
        isFiring = false;
        chaseSpeed = 0.0f;
        animator->SetInteger("Speed", 4);

        player = GameObject::FindGameObjectWithTag("Player");
        healthBar->SetMaxHealth(maxHealth);
        healthBar->SetHealth(currHealth - 50);
    }

    void Update()
    {
        playerDistance = Vector2::Distance(transform->position, player->transform->position);

        // Flip the character if going left
        Vector3 characterScale = transform->localScale;
        if (player->transform->position.x > transform->position.x && !isFiring) {
            characterScale.x = -21.0f;
        } else if (player->transform->position.x < transform->position.x && !isFiring) {
            characterScale.x = 21.0f;
        }
        transform->localScale = characterScale;

        // Traveling into the scene
        if (travelTime > 0.0f && entry) {
            chaseSpeed = 4.0f;
            animator->SetInteger("Speed", 4);
            transform->position += (Vector3::left * chaseSpeed) * Time.deltaTime;
            travelTime -= 1.0f * Time.deltaTime;

            if (travelTime <= endEntry) {
                entry = false;
                cout << "Finished Entering the map!" << endl;
            }
        } else if (entry == false) {
            // Movement logic
            if (playerDistance < 40.0f) {
                if (isFiring == false) {
                    isFiring = true;
                    ArrowAttack();
                }
            } else if (playerDistance > 40.0f) {
                isFiring = false;
                Walk();
            }
        }

        if (currHealth < 1) {
            SkeletonDeath();
        }

        if (deathTimer) {
            if (countdown > 1) {
                countdown -= 1.0f * Time.deltaTime;
            } else {
                Destroy(gameObject);
            }
        }
    }

    void SkeletonDeath()
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

    void ArrowAttack()
    {
        animator->SetInteger("Speed", 1);
        animator->SetTrigger("Attack");
        Instantiate(arrowPrefab, arrowSpawn->position, Quaternion::identity);
    }

    void TakeDamage(int damage)
    {
        currHealth -= damage;
        healthBar->SetHealth(currHealth);
    }
};
