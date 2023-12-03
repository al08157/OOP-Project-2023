#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class FireMageSpawnerScript : public MonoBehaviour
{
private:
    GameObject* fireMagePrefab;
    float timer;
    bool startTimer;

public:
    FireMageSpawnerScript()
    {
        timer = 10.0f;
        startTimer = false;

        // Add the callback function to the event
        SlimeScript::CharacterEvent += StartEnemyTimer;
    }

    void Update()
    {
        // Check if the timer is expired and send an enemy
        if (startTimer && timer <= 0.0f) {
            SendEnemy();
            startTimer = false;
        } else if (startTimer && timer > 0.0f) {
            timer -= 1.0f * Time.deltaTime;
            cout << timer << endl;
        }
    }

    void StartEnemyTimer()
    {
        startTimer = true;
    }

    void SendEnemy()
    {
        // Instantiate the FireMage object at the spawner's position
        Instantiate(fireMagePrefab, transform->position, transform->rotation);
    }
};
