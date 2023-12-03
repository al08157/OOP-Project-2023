#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class ReaperSpawnerScript : public MonoBehaviour
{
private:
    GameObject* reaperPrefab;
    float timer;
    bool startTimer;

public:
    ReaperSpawnerScript()
    {
        reaperPrefab = Resources::Load<GameObject>("Prefabs/Reaper");
        timer = 10.0f;
        startTimer = false;

        // Add the function to the event
        SlimeScript::CharacterEvent += StartEnemyTimer;
    }

    void Update()
    {
        // Creating a timer for the first enemy to come
        if (startTimer && timer <= 0.0f) {
            SendEnemy();
            startTimer = false;
        } else if (startTimer && timer > 0.0f) {
            timer -= 1.0f * Time.deltaTime;
        }
    }

    void StartEnemyTimer()
    {
        startTimer = true;
    }

    void SendEnemy()
    {
        // Instantiate the reaper object
        Instantiate(reaperPrefab, transform->position, transform->rotation);
    }
};
