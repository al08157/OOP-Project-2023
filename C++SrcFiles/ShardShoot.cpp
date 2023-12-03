#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class ShardShoot : public MonoBehaviour
{
private:
    GameObject* shardPrefab;
    Transform* shardSpawn;
    float attackTimer;

public:
    ShardShoot()
    {
        shardPrefab = Resources::Load<GameObject>("Prefabs/Shard");
        shardSpawn = transform->Find("ShardSpawn");
        attackTimer = 0.0f;
    }

    void Update()
    {
        // Count up the attack timer
        attackTimer += Time.deltaTime;

        // Check if it's time to attack
        if (attackTimer >= 2.0f) {
            attackTimer = 0.0f;
            Shoot();
        }
    }

    void Shoot()
    {
        // Instantiate a shard object at the shard spawn position
        Instantiate(shardPrefab, shardSpawn->position, Quaternion::identity);
    }
};
