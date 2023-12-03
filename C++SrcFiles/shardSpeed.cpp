#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class ShardSpeed : public MonoBehaviour
{
private:
    float bulletSpeed;

    GameObject* player;
    Rigidbody2D* rb;
    LayerMask targetLayer;
    int attackDamage;

public:
    ShardSpeed()
    {
        bulletSpeed = 30.0f;
        attackDamage = 15;

        rb = GetComponent<Rigidbody2D>();
        player = GameObject::FindGameObjectWithTag("Player");

        Vector3 direction = player->transform->position - transform->position;
        rb->velocity = direction.normalized * bulletSpeed;
        float rotation = Mathf::Atan2(-direction.x, -direction.y) * Mathf::Rad2Deg;
        transform->rotation = Quaternion::Euler(0.0f, 0.0f, rotation + 105.0f);
    }

    void OnTriggerEnter2D(Collider2D* collision)
    {
        if (collision->gameObject->CompareTag("BulletKiller")) {
            cout << "Bullet Hit Wall! Deleting bullet!" << endl;
            DeleteBullet();
        } else if (collision->gameObject->CompareTag("Player")) {
            cout << "Hit Target" << endl;
            collision->gameObject->GetComponent<SlimeScript>()->TakeDamage(attackDamage);
            cout << "Deleting bullet!" << endl;
            DeleteBullet();
        }
    }

    void DeleteBullet()
    {
        Destroy(gameObject);
    }
};
