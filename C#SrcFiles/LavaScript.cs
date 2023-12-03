using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LavaScript : MonoBehaviour
{
    public Animator animator;
    private GameObject player;
    public GameObject LavaPunch;
    private float PlayerDistance;
    private float chaseSpeed;
    private bool Entry;
    private float traveltime;
    private float EndEntry;
    // to check if the mage is firing at the given moment;
    // fire trigger object;
    public LayerMask TargetLayer;
    // Start is called before the first frame update
    private bool Isfiring;
    public int maxHealth;
    public int currHealth;
    private bool deathtimer;
    private float countdown;
    private float Timer;
    public HealthBarScript healthbar;


    void Start()
    {
        Timer = 5;
        Entry = true;
        traveltime = 5;
        countdown = 2;
        maxHealth = 100;
        currHealth = maxHealth;
        chaseSpeed = 0f;
        animator.SetInteger("Speed", 6); // this will trigger the conditions on which the key animation of this character changes according to the conditions set on the float "Speed".

        player = GameObject.FindGameObjectWithTag("Player");
        healthbar.SetMaxHealth(maxHealth);
        healthbar.SetHealth(currHealth);

    }

    // Update is called once per frame
    void Update()
    {
        PlayerDistance = Vector2.Distance(transform.position, player.transform.position);

        // Flip the character if going left;
        Vector3 characterScale = transform.localScale;
        if (player.transform.position.x > transform.position.x && !Isfiring)
        {
            characterScale.x = -31f;
        }
        else if (player.transform.position.x < transform.position.x && !Isfiring)
        {
            characterScale.x = 31f;
        }
        transform.localScale = characterScale;

        // traveling into the scene
        if (traveltime > 0 && Entry)
        {
            Walk();
            traveltime -= 1 * Time.deltaTime;
            if (traveltime <= EndEntry)
            {
                animator.SetInteger("Speed", 0);
                Entry = false;
                print("Finished Entering the map!");
            }
        }

        // Creating  a timer for Lava Punch to come;
        if (Timer <= 0)
        {
            Instantiate(LavaPunch, LavaPunch.transform.position, LavaPunch.transform.rotation);
            Timer = 5;
        }
        else if (Timer > 0)
        {
            Timer -= 1 * Time.deltaTime;
        }

        // death trigger
        if (currHealth < 1)
        {
            LavaDeath();
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

    private void LavaDeath()
    {
        animator.SetTrigger("Dead");
        chaseSpeed = 0;
        Isfiring = false;
        deathtimer = true;
    }

    private void Walk()
    {
        chaseSpeed = 7f;
        animator.SetInteger("Speed", 6);
        transform.position = Vector2.MoveTowards(this.transform.position, player.transform.position, chaseSpeed * Time.deltaTime);
    }
    public void TakeDamage(int Damage)
    {
        currHealth -= Damage;
        healthbar.SetHealth(currHealth);
    }

}
