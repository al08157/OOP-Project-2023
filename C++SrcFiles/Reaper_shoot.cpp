#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class ReaperShoot : public MonoBehaviour
{
private:
    GameObject* attackPrefab;
    Transform* attackPosition;
    float attackTimer;

public:
    ReaperShoot()
    {
        attackPrefab = Resources::Load<GameObject>("Prefabs/ReaperAttack");
        attackPosition = transform->Find("AttackPosition");
        attackTimer = 0.0f;
    }

    void Update()
    {
        // Count up the attack timer
        attackTimer += Time.deltaTime;

        // Check if it's time to attack
        if (attackTimer >= 3.0f) {
            attackTimer = 0.0f;
            Shoot();
        }
    }

    void Shoot()
    {
        // Instantiate an attack object at the attack position
        Instantiate(attackPrefab, attackPosition->position, Quaternion::identity);
    }
};
