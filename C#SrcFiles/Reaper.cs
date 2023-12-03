using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Reaper : MonoBehaviour
{


    private float ReaperSpeed;
    private GameObject player;
    private float chaseSpeed;
    private float PlayerDistance;
    private bool Entry;
    private float traveltime;
    private float EndEntry;
    public int maxHealth;
    public int currHealth;
    private bool deathtimer;
    private float countdown;
    public HealthBarScript healthbar;

    // Start is called before the first frame update
    void Start()
    {
        traveltime = 6f;
        EndEntry = 1;
        ReaperSpeed = chaseSpeed = 5f;
        player = GameObject.FindGameObjectWithTag("Player");// slime has the tag "Player"
        Entry = true;

        
        countdown = 2;
        maxHealth = 250;
        currHealth = maxHealth;

        healthbar.SetMaxHealth(maxHealth);
        healthbar.SetHealth(currHealth - 50);
    }

    // Update is called once per frame
    void Update()
    {

        // Flip the character if going left;
        Vector3 characterScale = transform.localScale;
        if (player.transform.position.x > transform.position.x)
        {
            characterScale.x = 2f;
        }
        else if (player.transform.position.x < transform.position.x)
        {
            characterScale.x = -2f;
        }
        transform.localScale = characterScale;


        if (traveltime > 0 && Entry)
        {
            transform.position += (Vector3.left * ReaperSpeed) * Time.deltaTime;
            traveltime -= 1 * Time.deltaTime;
            if (traveltime <= EndEntry) { 
                Entry = false;
                print("Finished Entering the map!");
            }
        }

        else if (Entry == false)
        {
            
            // get the PlayerDistance between the reaper and the player;
            PlayerDistance = Vector2.Distance(transform.position, player.transform.position);

            // The reaper is going to chase the player in a specific range;
            if (PlayerDistance < 40f) {
                // getting the reaper will take to follow the player; 
                Vector2 direction = player.transform.position - transform.position;

                transform.position = Vector2.MoveTowards(this.transform.position, player.transform.position, chaseSpeed * Time.deltaTime);
            }
            
        }

        // death trigger
        if (currHealth < 1)
        {
            ReaperDeath();
        }

        if (deathtimer)
        {
            if (countdown > 1)
            {
                countdown -= 1 * Time.deltaTime;
            }
            else
            {
                Destroy(gameObject);
            }
        }

    }

    private void ReaperDeath()
    {
        deathtimer = true;
    }

    public void TakeDamage(int Damage)
    {
        currHealth -= Damage;
        healthbar.SetHealth(currHealth);
    }

}
