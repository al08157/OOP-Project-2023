using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cathulubullet : MonoBehaviour
{
    // the prefab of the Cathuluattack png;
    public GameObject attack;
    //position of the attack;
    public Transform attackposition;

    // Intervals between attacks;
    private float attacktimer;
    void Update()
    {
        // counting till 3 seconds and then shooting the reaper bullet.
        attacktimer += Time.deltaTime;
        if (attacktimer > 2)
        {
            attacktimer = 0;
            shoot();
        }
    }


    private void shoot()
    {
        Instantiate(attack, attackposition.position, Quaternion.identity);
    }
}
