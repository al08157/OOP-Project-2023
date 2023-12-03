#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class Eyespeed {
private:
    float bulletSpeed;
    GameObject* player;
    Rigidbody2D rb;
    int attackDamage;

public:
    Eyespeed() {
        bulletSpeed = 40.0f;
        attackDamage = 15;
    }

    void Start() {
        rb = GetComponent<Rigidbody2D>();
        player = GameObject::FindWithTag("Player");

        // Calculate bullet direction
        Vector3 direction = player->transform->position - transform->position;
        rb->velocity = direction.normalized * bulletSpeed;

        // Calculate bullet rotation
        float rot = atan2(-direction.x, -direction.y) * Mathf::Rad2Deg;
        transform->rotation = Quaternion::Euler(0.0f, 0.0f, rot + 105.0f);
    }

    void OnTriggerEnter2D(Collider2D collision) {
        if (collision.gameObject->CompareTag("BulletKiller")) {
            cout << "Bullet Hit Wall! Deleting bullet!" << endl;
            DeleteBullet();
        } else if (collision.gameObject->CompareTag("Player")) {
            cout << "Hit Target" << endl;
            collision.gameObject->GetComponent<SlimeScript>()->TakeDamage(attackDamage);
            cout << "Deleting bullet!" << endl;
            DeleteBullet();
        }
    }

    void DeleteBullet() {
        Destroy(gameObject);
    }
};
