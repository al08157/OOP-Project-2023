using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using Unity.VisualScripting;
using UnityEngine;
using static UnityEngine.EventSystems.EventTrigger;

public class FireMageScript : MonoBehaviour
{
    
    public Animator animator;
    private GameObject player;
    private float PlayerDistance;
    private float chaseSpeed;
    private bool Entry;
    private float traveltime;
    private float EndEntry;
    // to check if the mage is firing at the given moment;
    // fire trigger object;
    public GameObject attack;
    public Transform firespawn;
    private float attackRange;
    public LayerMask TargetLayer;
    // Start is called before the first frame update
    private bool Isfiring;
    public int maxHealth;
    public int currHealth;
    private int attackdamage;
    public HealthBarScript healthbar;

    void Start()
    {
        
        maxHealth = currHealth = 100; ;
        attackRange = 5f;
        attackdamage = 40;
        Isfiring = false;
        chaseSpeed = 0f;
        animator.SetFloat("Speed", 0); // this will trigger the conditions on which the key animation of this character changes according to the conditions set on the float "Speed".

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
            characterScale.x = -18f;
        }
        else if (player.transform.position.x < transform.position.x && !Isfiring)
        {
            characterScale.x = 18f;
        }
        transform.localScale = characterScale;

        
        if (traveltime > 0 && Entry)
        {
            chaseSpeed = 4f;
            animator.SetFloat("Speed", 4f);
            transform.position += (Vector3.left * chaseSpeed) * Time.deltaTime;
            traveltime -= 1 * Time.deltaTime;
            if (traveltime <= EndEntry)
            {
                Entry = false;
                print("Finished Entering the map!");
            }
        }
        // movement logic;
        else if (Entry == false) {

            
            // Shoot range for Fire Mage;
            if (PlayerDistance < 16f)
            {
                if(!Isfiring)
                {
                    Shoot();
                }

            }
            // Run Range for Fire Mage
            else if (PlayerDistance < 30f && PlayerDistance > 16f && !Isfiring)
            {
                Run();
            }
            // Walk Range for Fire Mage
            else if (PlayerDistance > 30f)
            {
                Walk();
            }   
        }

        if (currHealth <= 1)
        {
            FireMageDeath();
        }


    }

    

    private void FireMageDeath()
    {
        chaseSpeed = 0;
        Isfiring = false;
        animator.SetTrigger("Dead");
    }

    private void Run()
    {
        chaseSpeed = 14f;
        animator.SetFloat("Speed", 10f);
        transform.position = Vector2.MoveTowards(this.transform.position, player.transform.position, chaseSpeed * Time.deltaTime);
    }

    private void Walk()
    {
        Isfiring = false;
        chaseSpeed = 5f;
        animator.SetFloat("Speed", 4f);
        transform.position = Vector2.MoveTowards(this.transform.position, player.transform.position, chaseSpeed * Time.deltaTime);
    }

    private void Shoot()
    {
        Isfiring = true;
        chaseSpeed = 0f;
        animator.SetFloat("Speed", 0);
        FireAttack();
    }

    private void FireAttack()
    {
        // Melee attack damage logic;
        if (Isfiring)
        {
            animator.SetTrigger("FireBall");
            Collider2D[] HitTarget = Physics2D.OverlapCircleAll(firespawn.position, attackRange, TargetLayer);
            foreach (Collider2D target in HitTarget)
            {
                // giving the slime 50 damage for the fire attack;
                target.GetComponent<SlimeScript>().TakeDamage(attackdamage);
                print("hit slime!");
            }
        }
    }

    void OnDrawGizmosSelected()
    {
        if (firespawn == null)
        {
            return;
        }
        Gizmos.DrawWireSphere(firespawn.position, attackRange);
    }
    public void TakeDamage(int Damage)
    {
        currHealth -= Damage;
        healthbar.SetHealth(currHealth);
    }
}
