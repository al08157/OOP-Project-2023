using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Reaper_shoot : MonoBehaviour
{
    // the prefab of the reaperattack png;
    public GameObject attack;
    //position of the attack;
    public Transform attackposition;

    // Intervals between attacks;
    private float attacktimer;
    void Update()
    {
        // counting till 3 seconds and then shooting the reaper bullet.
        attacktimer += Time.deltaTime;
        if (attacktimer > 3)
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
