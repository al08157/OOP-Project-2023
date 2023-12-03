#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class ScarletWidow : public MonoBehaviour
{
private:
    Animator* animator;
    GameObject* player;
    float playerDistance;
    float chaseSpeed;
    bool entry;
    float travelTime;
    float endEntry;
    GameObject* shardPrefab;
    Transform* shardSpawn;

    bool isFiring;
    int maxHealth;
    int currHealth;

    HealthBarScript* healthBar;

public:
    ScarletWidow()
    {
        animator = GetComponent<Animator>();
        player = GameObject::FindGameObjectWithTag("Player");

        travelTime = 5.0f;
        entry = true;
        chaseSpeed = 0.0f;
        animator->SetInteger("Speed", 4);

        healthBar = GetComponentInChildren<HealthBarScript>();
        maxHealth = 100;
        currHealth = maxHealth;
        isFiring = false;

        shardPrefab = Resources::Load<GameObject>("Prefabs/Shard");
        shardSpawn = transform->Find("ShardSpawn");
    }

    void Update()
    {
        playerDistance = Vector2::Distance(transform->position, player->transform->position);

        // Flip the character if going left
        Vector3 characterScale = transform->localScale;
        if (player->transform->position.x > transform->position.x && !isFiring) {
            characterScale.x = -17.5f;
        } else if (player->transform->position.x < transform->position.x && !isFiring) {
            characterScale.x = 17.5f;
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
            if (playerDistance < 20.0f) {
                if (!isFiring) {
                    Shoot();
                }
            } else if (playerDistance > 30.0f) {
                Run();
            } else if (playerDistance < 30.0f && playerDistance > 20.0f && !isFiring) {
                Walk();
                Shoot();
            }
        }

        if (currHealth <= 1) {
            ScarletDeath();
        }
    }

    void ScarletDeath()
    {
        chaseSpeed = 0.0f;
        isFiring = false;
        animator->SetTrigger("Dead");
    }

    void Run()
    {
        isFiring = false;
        chaseSpeed = 13.0f;
        animator->SetInteger("Speed", 10);
        transform->position = Vector2::MoveTowards(transform->position, player->transform->position, chaseSpeed * Time.deltaTime);
    }

    void Walk()
    {
        isFiring = false;
        chaseSpeed = 7.0f;
        animator->SetInteger("Speed", 4);
        transform->position = Vector2::MoveTowards(transform->position, player->transform->position, chaseSpeed * Time.deltaTime);
    }

    void Shoot()
    {
        isFiring = true;
        ShardAttack();
    }

    void ShardAttack()
    {
        if (isFiring) {
            animator->SetTrigger("Attack");
            Instantiate(shardPrefab, shardSpawn->position, Quaternion::identity);
        }
    }

    public void TakeDamage(int damage)
    {
        animator->SetTrigger("Hurt");
        currHealth -= damage;
        healthBar->SetHealth(currHealth);
    }
};
