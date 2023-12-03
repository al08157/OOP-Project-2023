using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShardShoot : MonoBehaviour
{
    // the prefab of the reaperattack png;
    public GameObject Shard;
    //position of the attack;
    public Transform shardspawn;
    
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
        Instantiate(Shard, shardspawn.transform.position, Quaternion.identity);
    }
}