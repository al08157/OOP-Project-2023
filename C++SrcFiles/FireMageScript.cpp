#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class FireMageScript : public MonoBehaviour
{
private:
    Animator* animator;
    GameObject* player;
    float playerDistance;
    float chaseSpeed;
    bool entry;
    float travelTime;
    float endEntry;
    bool isFiring;
    public GameObject* attack;
    public Transform firespawn;
    float attackRange;
    public LayerMask targetLayer;
    int maxHealth;
    int currHealth;
    int attackDamage;
    HealthBarScript* healthbar;

public:
    FireMageScript()
    {
        maxHealth = currHealth = 100;
        attackRange = 5.0f;
        attackDamage = 40;
        isFiring = false;
        chaseSpeed = 0.0f;
        animator->SetFloat("Speed", 0.0f); // This will trigger the conditions on which the key animation of this character changes according to the conditions set on the float "Speed".

        player = GameObject::FindGameObjectWithTag("Player");
        healthbar->SetMaxHealth(maxHealth);
        healthbar->SetHealth(currHealth);
    }

    void Update()
    {
        playerDistance = Vector2::Distance(transform->position, player->transform->position);

        // Flip the character if going left;
        Vector3 characterScale = transform->localScale;
        if (player->transform->position.x > transform->position.x && !isFiring) {
            characterScale.x = -18.0f;
        } else if (player->transform->position.x < transform->position.x && !isFiring) {
            characterScale.x = 18.0f;
        }
        transform->localScale = characterScale;

        if (travelTime > 0.0f && entry) {
            chaseSpeed = 4.0f;
            animator->SetFloat("Speed", 4.0f);
            transform->position += (Vector3::left * chaseSpeed) * Time.deltaTime;
            travelTime -= 1.0f * Time.deltaTime;
            if (travelTime <= endEntry) {
                entry = false;
                print("Finished Entering the map!");
            }
        }
        // Movement logic;
        else if (entry == false) {
            // Shoot range for Fire Mage;
            if (playerDistance < 16.0f) {
                if (!isFiring) {
                    Shoot();
                }
            }
            // Run Range for Fire Mage
            else if (playerDistance < 30.0f && playerDistance > 16.0f && !isFiring) {
                Run();
            }
            // Walk Range for Fire Mage
            else if (playerDistance > 30.0f) {
                Walk();
            }
        }

        if (currHealth <= 1) {
            FireMageDeath();
        }
    }

private:
    void FireMageDeath()
    {
        chaseSpeed = 0.0f;
        isFiring = false;
        animator->SetTrigger("Dead");
    }

    void Run()
    {
        chaseSpeed = 14.0f;
        animator->SetFloat("Speed", 10.0f);
        transform->position = Vector2::MoveTowards(transform->position, player->transform->position, chaseSpeed * Time.deltaTime);
    }

    void Walk()
    {
        isFiring = false;
        chaseSpeed = 5.0f;
        animator->SetFloat("Speed", 4.0f);
        transform->position = Vector2::MoveTowards(transform->position, player->transform->position, chaseSpeed * Time.deltaTime);
    }

    void Shoot()
    {
        isFiring = true;
        chaseSpeed = 0.0f;
        animator->SetFloat("Speed", 0.0f);
        FireAttack();
    }

    void FireAttack()
    {
        // Melee attack damage logic;
        if (isFiring) {
            animator->SetTrigger("FireBall");

            // Get all the colliders within the attack range and layer mask
            Collider2D** hitTargets = Physics2D::OverlapCircleAll(firespawn->position, attackRange, targetLayer);

            // Iterate through the hit targets and apply damage
            for (Collider2D* target : *hitTargets) {
                target->GetComponent<SlimeScript>()->TakeDamage(attackDamage);
                print("hit slime!");
            }

            // Free the allocated memory
            delete[] hitTargets;
        }
    }

    void OnDrawGizmosSelected() {
        if (firespawn == nullptr) {
            return;
        }

        Gizmos::DrawWireSphere(firespawn->position, attackRange);
    }

    void TakeDamage(int damage) {
        currHealth -= damage;
        healthbar->SetHealth(currHealth);
    }

}
