using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class ObstacleSpawner : MonoBehaviour
{
    [SerializeField] private GameObject[] objects;
    [SerializeField] private float maxHeight;
    [SerializeField] private float minHeight;
    [SerializeField] private float maxWait;
    [SerializeField] private float minWait;

    private void Start()
    {
        StartCoroutine(SpawnObstaclesRoutine());
    }

    IEnumerator SpawnObstaclesRoutine()
    {
        while(true)
        {
            GameObject toSpawn = objects[Random.Range(0, objects.Length)];
            
            Vector2 spawnPosition = new Vector2(20, Random.Range(minHeight, maxHeight));
            Quaternion rotation = GetRandomQuaternionXY();
            Instantiate(toSpawn, spawnPosition, rotation);

            float waitTime = Random.Range(minWait, maxWait);
            yield return new WaitForSeconds(waitTime);
        }
    }
    
    public Quaternion GetRandomQuaternionXY()
    {
        float angle = Random.Range(0f, 360f);
        Quaternion rotation = Quaternion.AngleAxis(angle, Vector3.forward);
        return rotation;
    }

}
