using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShootScript : MonoBehaviour
{
    // the prefab of the reaperattack png;
    public GameObject Arrow;
    //position of the attack;
    public Transform Arrowspawn;

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
        Instantiate(Arrow, Arrowspawn.transform.position, Quaternion.identity);
    }
}
