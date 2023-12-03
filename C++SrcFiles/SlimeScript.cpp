#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class SlimeScript : public MonoBehaviour
{
private:
    bool isAttacking;
    GameObject* firePrefab;
    Animator* animator;
    int maxHealth;
    int currentHealth;
    Rigidbody2D* slimeBody;
    float jumpForce;
    float slimeSpeed;
    bool slimeInJump;
    bool slimeEnter;
    HealthBarScript* healthBar;

public:
    SlimeScript()
    {
        isAttacking = false;
        firePrefab = Resources::Load<GameObject>("Prefabs/Fire");
        animator->SetInteger("Speed", 0);
        maxHealth = currentHealth = 100;
        healthBar->SetMaxHealth(currentHealth);
    }

    void Update()
    {
        if (Input::GetKeyDown(KeyCode::Space) && !slimeInJump) {
            slimeInJump = true;
            animator->SetTrigger("Jump");
            slimeBody->velocity = Vector2::up * jumpForce;
        }

        // Character movement
        transform->Translate(Input::GetAxis("Horizontal") * slimeSpeed * Time.deltaTime, 0.0f, 0.0f);

        // Flip the character if going left
        Vector3 characterScale = transform->localScale;
        if (Input::GetAxis("Horizontal") < 0.0f) {
            animator->SetInteger("Speed", 2);
            characterScale.x = -30.0f;
        }

        // Flip the character if going right
        if (Input::GetAxis("Horizontal") > 0.0f) {
            animator->SetInteger("Speed", 2);
            characterScale.x = 30.0f;
        }

        // Reset the animation speed to default if not moving
        if (Input::GetAxis("Horizontal") == 0.0f) {
            animator->SetInteger("Speed", 0);
        }

        // Character attacks
        if (Input::GetKey(KeyCode::UpArrow)) {
            if (Input::GetKeyDown(KeyCode::LeftShift) && !isAttacking) {
                print("UpAttack");
                Quaternion newRotation = transform->rotation * Quaternion::Euler(0.0f, 0.0f, 90.0f);
                Instantiate(firePrefab, transform->position, newRotation);
                isAttacking = true;
            }
        } else if (Input::GetKeyDown(KeyCode::LeftShift)) {
            print("Attack");
            if (transform->localScale.x > 0.0f) {
                Instantiate(firePrefab, transform->position, transform->rotation);
            } else if (transform->localScale.x < 0.0f) {
                Quaternion newRotation = transform->rotation * Quaternion::Euler(0.0f, 0.0f, 180.0f);
                Instantiate(firePrefab, transform->position, newRotation);
            }
        }

        // Reset the attack flag after a fixed duration
        Invoke("ResetAttackFlag", 0.5f);

        transform->localScale = characterScale;
    }

    void FixedUpdate()
    {
        Invoke("ResetAttackFlag", 0.5f);
    }

    void ResetAttackFlag()
    {
        isAttacking = false;
    }

    void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject->CompareTag("Platform_collider")) {
            slimeInJump = false;
        }

        if (collision.gameObject->CompareTag("Wall") && !slimeEnter) {
            // Trigger the event of spawning the first ghost
            CharachterEvent?.Invoke();
            print("Event Triggered! << count down started!");

            // Change the state of the bool variable so it doesn't start repeatedly
            slimeEnter = true;
        }
    }

    public void TakeDamage(int damage)
    {
        currentHealth -= damage;
        healthBar->SetHealth(currentHealth);
    }
};
