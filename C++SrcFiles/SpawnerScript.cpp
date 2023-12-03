using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnerScript : MonoBehaviour
{
    public GameObject enemyPrefab;
    public Transform spawnPoint;
    public float spawnInterval;

    private float spawnTimer;

    void Start()
    {
        spawnTimer = 0.0f;
    }

    void Update()
    {
        spawnTimer += Time.deltaTime;

        if (spawnTimer >= spawnInterval)
        {
            Instantiate(enemyPrefab, spawnPoint.position, Quaternion.identity);
            spawnTimer = 0.0f;
        }
    }
}
