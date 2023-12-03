using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cathulu : MonoBehaviour
{
    public HealthBarScript healthbar;
    private GameObject player;
    private float chaseSpeed;
    private float Distance;
    private float MaxDistance;
    private float Xpos;
    private float Ypos;
    public int maxHealth;
    public int currHealth;
    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
        MaxDistance = 30f;
        chaseSpeed = 8f;
        maxHealth = currHealth = 100;
        healthbar.SetMaxHealth(maxHealth);
        healthbar.SetHealth(currHealth);
    }

    // Update is called once per frame
    void Update()
    {
        Xpos = transform.position.x;
        Ypos = transform.position.y;
        Distance = Vector2.Distance(transform.position, player.transform.position);
        Vector2 direction = player.transform.position - transform.position;
        direction.Normalize();
        float angle = Mathf.Atan2(direction.y, direction.x) * Mathf.Rad2Deg;

        transform.position = Vector2.MoveTowards(this.transform.position, player.transform.position, chaseSpeed * Time.deltaTime);
        transform.rotation = Quaternion.Euler(Vector3.forward * (angle + 180));


        if (transform.position.y <= 20f) 
        {
            if (player.transform.position.x > transform.position.x) 
            {
                Xpos += chaseSpeed * Time.deltaTime;
            }
            else
            {
                Xpos -= chaseSpeed * Time.deltaTime;
            }
            transform.position = new Vector3(Xpos, transform.position.y, transform.position.z);
        }
        if (transform.position.y <= 19f)
        {
            Ypos += chaseSpeed * Time.deltaTime;
            transform.position = new Vector3(transform.position.x, Ypos, transform.position.z);
        }

    }
    public void TakeDamage(int Damage)
    {
        currHealth -= Damage;
        healthbar.SetHealth(currHealth);
    }
}

