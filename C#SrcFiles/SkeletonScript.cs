using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SkeletonScript : MonoBehaviour
{
    public Animator animator;
    private GameObject player;
    private float PlayerDistance;
    private float chaseSpeed;
    private bool Entry;
    private float traveltime;
    private float EndEntry;
    public GameObject Arrow;
    public Transform Arrowspawn;
    // to check if the mage is firing at the given moment;
    // fire trigger object;
    private float attackRange;
    public LayerMask TargetLayer;
    // Start is called before the first frame update
    private bool Isfiring;
    public int maxHealth;
    public int currHealth;
    private bool deathtimer;
    private float countdown;
    private int attackdamage;
    private bool CanShoot;
    public HealthBarScript healthbar;


    void Start()
    {
        countdown = 2;
        maxHealth = 100;
        currHealth = maxHealth;
        attackRange = 20f;
        attackdamage = 40;
        Isfiring = false;
        chaseSpeed = 0f;
        animator.SetInteger("Speed", 4); // this will trigger the conditions on which the key animation of this character changes according to the conditions set on the float "Speed".

        player = GameObject.FindGameObjectWithTag("Player");
        healthbar.SetMaxHealth(maxHealth);
        healthbar.SetHealth(currHealth-50);

    }

    // Update is called once per frame
    void Update()
    {
        PlayerDistance = Vector2.Distance(transform.position, player.transform.position);

        // Flip the character if going left;
        Vector3 characterScale = transform.localScale;
        if (player.transform.position.x > transform.position.x && !Isfiring)
        {
            characterScale.x = -21f;
        }
        else if (player.transform.position.x < transform.position.x && !Isfiring)
        {
            characterScale.x = 21f;
        }
        transform.localScale = characterScale;


        if (traveltime > 0 && Entry)
        {
            chaseSpeed = 4f;
            animator.SetInteger("Speed", 4);
            transform.position += (Vector3.left * chaseSpeed) * Time.deltaTime;
            traveltime -= 1 * Time.deltaTime;
            if (traveltime <= EndEntry)
            {
                Entry = false;
                print("Finished Entering the map!");
            }
        }
        // movement logic;
        else if (Entry == false)
        {


            // Shoot range for Fire Mage;
            if (PlayerDistance < 40f)
            {
                if (Isfiring == false)
                {
                    Isfiring = true;
                    ArrowAttack();
                }

            }
            // Walk Range for Fire Mage
            if (PlayerDistance > 40f)
            {
                Isfiring = false;
                Walk();
            }
        }

        if (currHealth < 1)
        {
            SkeletonDeath();
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

    private void SkeletonDeath()
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

    private void ArrowAttack()
    {
        animator.SetInteger("Speed", 1);
        animator.SetTrigger("Attack");
        Instantiate(Arrow, Arrowspawn.transform.position, Quaternion.identity);
    }
    public void TakeDamage(int Damage)
    {
        currHealth -= Damage;
        healthbar.SetHealth(currHealth);
    }
}
