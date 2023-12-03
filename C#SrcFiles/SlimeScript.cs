using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using System;

public class SlimeScript : MonoBehaviour
{
    // Events related to Slime;
    public static event Action CharachterEvent;
    bool isAttacking = false; // Declare a flag to track attack status
    public GameObject Fire;
    public Animator Animator;
    public int maxHealth;
    public int currentHealth;
    public Rigidbody2D slime_Body;
    private float Jump_force = 38f;
    private float Slime_speed = 28f;
    private bool Slime_InJump = false;
    private bool Slime_enter = false;
    public HealthBarScript healthbar;

    void Start()
    {
        Animator.SetInteger("Speed", 0);
        maxHealth = currentHealth = 100;
        healthbar.SetMaxHealth(currentHealth);
        print(currentHealth);
        print(maxHealth);
    }

    // Update is called once per frame
    void Update()
    {

        if (Input.GetKeyDown(KeyCode.Space) == true && !Slime_InJump)
        {
            Slime_InJump = true;
            Animator.SetTrigger("Jump");
            slime_Body.velocity = Vector2.up * Jump_force;
        }
        // moving the character around => using deltatime so for all pcs the character has the same speed;
        transform.Translate(Input.GetAxis("Horizontal") * Slime_speed * Time.deltaTime, 0f, 0f);
        

        // Flip the character if going left;
        Vector3 characterScale = transform.localScale;
        if (Input.GetAxis("Horizontal") < 0) {
            Animator.SetInteger("Speed", 2);
            characterScale.x = -30f;
        }

        // Flip the character if going right;
        if (Input.GetAxis("Horizontal") > 0)
        {
            Animator.SetInteger("Speed", 2);
            characterScale.x = 30f;
        }

        if (Input.GetAxis("Horizontal") == 0)
        {
            Animator.SetInteger("Speed", 0);
        }
        if (Input.GetKey(KeyCode.UpArrow))
        {
            if (Input.GetKeyDown(KeyCode.LeftShift) && !isAttacking)
            {
                print("UpAttack");
                Quaternion newRotation = transform.rotation * Quaternion.Euler(0f, 0f, 90f); // Adding 90 degrees to the current rotation on the Y axis
                Instantiate(Fire, transform.position, newRotation);
                isAttacking = true;

            }
        }
        else if (Input.GetKeyDown(KeyCode.LeftShift))
        {
            print("Attack");
            if (transform.localScale.x > 0)
            {
                Instantiate(Fire, transform.position, transform.rotation);
            }
            else if (transform.localScale.x < 0)
            {
                Quaternion newRotation = transform.rotation * Quaternion.Euler(0f, 0f, 180f);
                Instantiate(Fire, transform.position, newRotation);
            }
        }

        if (!Input.GetKey(KeyCode.LeftShift) && !Input.GetKey(KeyCode.UpArrow))
        {
            isAttacking = false;
        }

        transform.localScale = characterScale;

    }


    void FixedUpdate()
    {
        // This will reset the attack flag after a fixed duration (adjust this duration as needed)
        Invoke("ResetAttackFlag", 0.5f);
    }

    void ResetAttackFlag()
    {
        isAttacking = false; // Reset the attack flag after a certain time
    }


    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Platform_collider")
        {
            Slime_InJump = false;
        }

        if (collision.gameObject.tag == "Wall" && !Slime_enter)
        {
            // trigger the event of spawning the first ghost;
            CharachterEvent?.Invoke();
            print("Event Triggered! << count down started!");
            // changing state of bool variable so it doesnt start repeatedly
            Slime_enter = true;
        }

    }

    


    public void TakeDamage(int Damage)
    {
        currentHealth -= Damage;
        healthbar.SetHealth(currentHealth);
    }

}
