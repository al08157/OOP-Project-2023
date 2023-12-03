using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static UnityEngine.RuleTile.TilingRuleOutput;

public class FireScript : MonoBehaviour
{
    
    // This is for the modification of bullet's scale and roatation;
    private Rigidbody2D rb;
    //private GameObject BulletKiller;
    private int attackdamage = 15;

    void Start()
    {
        float bulletSpeed = 20f;
        rb = GetComponent<Rigidbody2D>();
        
        
        float angle = transform.eulerAngles.z; // Get the Z rotation of the object

        // Calculate the X and Y components of a vector using trigonometric functions
        float directionX = Mathf.Cos(angle * Mathf.Deg2Rad);
        float directionY = Mathf.Sin(angle * Mathf.Deg2Rad);

        Vector2 constantDirection = new Vector2(directionX, directionY);

        rb.velocity = constantDirection.normalized * bulletSpeed;

    }

    private void OnTriggerEnter2D(Collider2D collision)
    {

        if (collision.gameObject.CompareTag("BulletKiller"))
        {
            print("Bullet Hit Wall! Deleting bullet!");
            DeleteBullet();
        }
        if (collision.gameObject.CompareTag("Reaper"))
        {
            print("Hit Target");
            // giving 20 damage if bullet hits target;
            collision.gameObject.GetComponent<Reaper>().TakeDamage(attackdamage);
            print("Deleting bullet!");
            DeleteBullet();
        }
        if (collision.gameObject.CompareTag("FireMage"))
        {
            print("Hit Target");
            // giving 20 damage if bullet hits target;
            collision.gameObject.GetComponent<FireMageScript>().TakeDamage(attackdamage-3);
            print("Deleting bullet!");
            DeleteBullet();
        }
        if (collision.gameObject.CompareTag("ScarletWidow"))
        {
            print("Hit Target");
            // giving 20 damage if bullet hits target;
            collision.gameObject.GetComponent<ScarletWidow>().TakeDamage(attackdamage - 5);
            print("Deleting bullet!!");
            DeleteBullet();
        }
        if (collision.gameObject.CompareTag("Cathulu"))
        {
            print("Hit Target");
            // giving 20 damage if bullet hits target;
            collision.gameObject.GetComponent<Cathulu>().TakeDamage(attackdamage - 3);
            print("Deleting bullet!");
            DeleteBullet();
        }
        if (collision.gameObject.CompareTag("Skeleton"))
        {
            print("Hit Target");
            // giving 20 damage if bullet hits target;
            collision.gameObject.GetComponent<SkeletonScript>().TakeDamage(attackdamage - 6);
            print("Deleting bullet!");
            DeleteBullet();
        }
        if (collision.gameObject.CompareTag("LavaGolem"))
        {
            print("Hit Target");
            // giving 20 damage if bullet hits target;
            collision.gameObject.GetComponent<LavaScript>().TakeDamage(attackdamage - 8);
            print("Deleting bullet!");
            DeleteBullet();
        }
    }


    private void DeleteBullet()
    {
        Destroy(gameObject);
    }
}
