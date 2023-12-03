#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class LavaAttackSpawn : public MonoBehaviour
{
private:
    GameObject* lavaAttackPrefab;
    float spawnTimer;
    float spawnInterval;

public:
    LavaAttackSpawn()
    {
        spawnTimer = 0.0f;
        spawnInterval = 2.0f;
    }

    void Start()
    {
        // Initialize the lava attack prefab
        lavaAttackPrefab = Resources::Load<GameObject>("Prefabs/LavaAttack");
    }

    void Update()
    {
        // Check if it's time to spawn a lava attack
        spawnTimer += Time.deltaTime;
        if (spawnTimer >= spawnInterval) {
            SpawnLavaAttack();
            spawnTimer -= spawnInterval;
        }
    }

    void SpawnLavaAttack()
    {
        // Instantiate a lava attack object at a random position
        Vector3 spawnPosition = new Vector3(Random.Range(-5.0f, 5.0f), 0.0f, 0.0f);
        Instantiate(lavaAttackPrefab, spawnPosition, Quaternion.identity);
    }
};
