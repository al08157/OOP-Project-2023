#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class FireScript : public MonoBehaviour
{
private:
    Rigidbody2D* rb;
    int attackDamage;

public:
    FireScript()
    {
        attackDamage = 15;
    }

    void Start()
    {
        float bulletSpeed = 20.0f;
        rb = GetComponent<Rigidbody2D>();

        // Calculate the direction vector based on the object's rotation
        float angle = transform->eulerAngles.z;
        float directionX = cosf(angle * Mathf::Deg2Rad);
        float directionY = sinf(angle * Mathf::Deg2Rad);
        Vector2 constantDirection = Vector2(directionX, directionY);

        rb->velocity = constantDirection.normalized * bulletSpeed;
    }

    void OnTriggerEnter2D(Collider2D* collision)
    {
        if (collision->gameObject->CompareTag("BulletKiller"))
        {
            cout << "Bullet Hit Wall! Deleting bullet!" << endl;
            DeleteBullet();
        } else if (collision->gameObject->CompareTag("Reaper"))
        {
            collision->gameObject->GetComponent<Reaper>()->TakeDamage(attackDamage);
            DeleteBullet();
        } else if (collision->gameObject->CompareTag("FireMage"))
        {
            collision->gameObject->GetComponent<FireMageScript>()->TakeDamage(attackDamage - 3);
            DeleteBullet();
        } else if (collision->gameObject->CompareTag("ScarletWidow"))
        {
            collision->gameObject->GetComponent<ScarletWidow>()->TakeDamage(attackDamage - 5);
            DeleteBullet();
        } else if (collision->gameObject->CompareTag("Cathulu"))
        {
            collision->gameObject->GetComponent<Cathulu>()->TakeDamage(attackDamage - 3);
            DeleteBullet();
        } else if (collision->gameObject->CompareTag("Skeleton"))
        {
            collision->gameObject->GetComponent<SkeletonScript>()->TakeDamage(attackDamage - 6);
            DeleteBullet();
        } else if (collision->gameObject->CompareTag("LavaGolem"))
        {
            collision->gameObject->GetComponent<LavaScript>()->TakeDamage(attackDamage - 8);
            DeleteBullet();
        }
    }

    void DeleteBullet()
    {
        Destroy(gameObject);
    }
};
