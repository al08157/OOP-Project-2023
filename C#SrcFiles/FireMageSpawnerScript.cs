using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FireMageSpawnerScript : MonoBehaviour
{
    public GameObject FireMage;
    private float Timer;
    private bool startTimer = false;

    // Start is called before the first frame update
    void Start()
    {
        // at start the timer is 0.
        Timer = 10;
        // adding the function to the Event!
        SlimeScript.CharachterEvent += StartEnemyTimer;
    }

    // Update is called once per frame
    void Update()
    {
        // Creating  a timer for first enemy to come;
        if (startTimer && Timer <= 0)
        {
            SendEnemy();
            startTimer = false;
        }
        else if (startTimer && Timer > 0)
        {
            Timer -= 1 * Time.deltaTime;
            print(Timer);
        }

    }

    private void StartEnemyTimer()
    {
        startTimer = true;
    }

    private void SendEnemy()
    {
        //Instantiate(FireMage, transform.position, transform.rotation);
    }

}
