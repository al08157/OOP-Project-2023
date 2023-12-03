using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class shardSpeed : MonoBehaviour
{
    private float bulletSpeed;

    // Refrence to slime GameObject;
    private GameObject player;
    // This is for the modification of bullet's scale and roatation;
    private Rigidbody2D rb;
    //private GameObject BulletKiller;
    public LayerMask TargetLayer;
    private int attackdamage;
    void Start()
    {
        bulletSpeed = 30f;
        attackdamage = 15;

        rb = GetComponent<Rigidbody2D>();
        // slime has the tag "Player"
        player = GameObject.FindGameObjectWithTag("Player");
        // storing the direction of the player to transform the bullet direction;
        Vector3 direction = player.transform.position - transform.position;
        // initializing the velocity of the Reaper_bullet 
        rb.velocity = new Vector2(direction.x, direction.y).normalized * bulletSpeed;
        float rot  = Mathf.Atan2(-direction.x, -direction.y) * Mathf.Rad2Deg;
        transform.rotation = Quaternion.Euler(0,0,rot + 105);

    }


    private void OnTriggerEnter2D(Collider2D collision)
    {

        if (collision.gameObject.CompareTag("BulletKiller"))
        {
            print("Bullet Hit Wall! Deleting bullet!");
            DeleteBullet();
        }
        if (collision.gameObject.CompareTag("Player"))
        {

            print("Hit Target");
            // giving 20 damage if bullet hits target;
            collision.gameObject.GetComponent<SlimeScript>().TakeDamage(attackdamage);
            print("Deleting bullet!");
            DeleteBullet();
        }

    }


    private void DeleteBullet()
    {
        Destroy(gameObject);
    }
}
