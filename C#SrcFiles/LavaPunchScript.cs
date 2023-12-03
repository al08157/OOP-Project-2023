using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LavaPunchScript : MonoBehaviour
{
    private GameObject player;
    //private float Distance;
   
    private float Xpos;
    private float Ypos;
    private float Timer;
    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
        Timer = 2f;
        Xpos = transform.position.x;
        Ypos = transform.position.y;
        if (transform.position.y <= -9f)
        {
            Ypos = -8f;
            transform.position = new Vector3(transform.position.x, Ypos, transform.position.z);
        }
        if (transform.position.y <= -7f)
        {
            if (player.transform.position.x > transform.position.x)
            {
                Xpos = player.transform.position.x;
            }
            else
            {
                Xpos = player.transform.position.x;
            }
            transform.position = new Vector3(Xpos, transform.position.y, transform.position.z);
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.CompareTag("Player"))
        {
            print("Hit Target");
            // giving 20 damage if bullet hits target;
            collision.gameObject.GetComponent<SlimeScript>().TakeDamage(20);
            print("Deleting bullet!");
        }
    }
}
