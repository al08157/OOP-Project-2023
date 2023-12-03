using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using Unity.VisualScripting;
using UnityEngine;
using static UnityEngine.EventSystems.EventTrigger;

public class ScarletWidow : MonoBehaviour
{

    public Animator animator;
    private GameObject player;
    private float PlayerDistance;
    private float chaseSpeed;
    private bool Entry;
    private float traveltime;
    private float EndEntry;
    public GameObject Shard;
    public Transform shardspawn;
    // to check if the mage is firing at the given moment;
    // fire trigger object;
    public LayerMask TargetLayer;
    // Start is called before the first frame update
    private bool Isfiring;
    public int maxHealth;
    public int currHealth;
    
    public HealthBarScript healthbar;


    void Start()
    {
        
        maxHealth = currHealth = 100;
        Isfiring = false;
        chaseSpeed = 0f;
        animator.SetInteger("Speed", 4); // this will trigger the conditions on which the key animation of this character changes according to the conditions set on the float "Speed".

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
            characterScale.x = -17.5f;
        }
        else if (player.transform.position.x < transform.position.x && !Isfiring)
        {
            characterScale.x = 17.5f;
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
            if (PlayerDistance < 20f)
            {
                if (!Isfiring)
                {
                    Shoot();
                }

            }
            // Run Range for Fire Mage
            else if (PlayerDistance > 30f)
            {
                Run();
            }
            // Walk Range for Fire Mage
            else if (PlayerDistance < 30f && PlayerDistance > 20f && !Isfiring)
            {
                Walk();
                Shoot();
            }
        }

        if (currHealth <= 1)
        {
            ScarletDeath();
        }

        

    }



    private void ScarletDeath()
    {
        chaseSpeed = 0;
        Isfiring = false;
        animator.SetTrigger("Dead");
    }

    private void Run()
    {
        Isfiring = false;
        chaseSpeed = 13f;
        animator.SetInteger("Speed", 10);
        transform.position = Vector2.MoveTowards(this.transform.position, player.transform.position, chaseSpeed * Time.deltaTime);
    }

    private void Walk()
    {
        Isfiring = false;
        chaseSpeed = 7f;
        animator.SetInteger("Speed", 4);
        transform.position = Vector2.MoveTowards(this.transform.position, player.transform.position, chaseSpeed * Time.deltaTime);
    }

    private void Shoot()
    {
        Isfiring = true;
        ShardAttack();
    }

    private void ShardAttack()
    {
        // Melee attack damage logic;
        if (Isfiring)
        {
            animator.SetTrigger("Attack");
            Instantiate(Shard, shardspawn.transform.position, Quaternion.identity);
        }
    }

    public void TakeDamage(int Damage)
    {
        animator.SetTrigger("Hurt");
        currHealth -= Damage;
        healthbar.SetHealth(currHealth);
    }
}
