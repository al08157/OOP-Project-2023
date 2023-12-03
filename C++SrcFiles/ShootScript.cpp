#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class ShootScript : public MonoBehaviour
{
private:
    GameObject* arrowPrefab;
    Transform* arrowSpawn;
    float attackTimer;

public:
    ShootScript()
    {
        arrowPrefab = Resources::Load<GameObject>("Prefabs/Arrow");
        arrowSpawn = transform->Find("ArrowSpawn");
        attackTimer = 0.0f;
    }

    void Update()
    {
        attackTimer += Time.deltaTime;

        if (attackTimer >= 2.0f) {
            attackTimer = 0.0f;
            Shoot();
        }
    }

    void Shoot()
    {
        Instantiate(arrowPrefab, arrowSpawn->position, Quaternion::identity);
    }
};
