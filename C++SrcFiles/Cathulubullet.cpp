#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class Cathulubullet {
private:
    GameObject* attackPrefab;
    Transform* attackPosition;
    float attackTimer;

public:
    Cathulubullet(GameObject* attackPrefab, Transform* attackPosition) {
        this->attackPrefab = attackPrefab;
        this->attackPosition = attackPosition;
        attackTimer = 0.0f;
    }

    void Update() {
        attackTimer += Time.deltaTime;
        if (attackTimer > 2.0f) {
            attackTimer = 0.0f;
            Shoot();
        }
    }

    void Shoot() {
        Instantiate(attackPrefab, attackPosition->position, Quaternion::identity);
    }
};
