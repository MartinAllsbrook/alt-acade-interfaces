using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Whisk : MonoBehaviour
{
    [SerializeField] private int numCooldownTicks;
    [SerializeField] private float cooldownTime;
    [SerializeField] private float forceMultiplier;
    private Rigidbody2D _rigidbody2D;
    
    private float _numRecentTicks;

    private void Awake()
    {
        _rigidbody2D = GetComponent<Rigidbody2D>();
    }

    /*private void Update()
    {
        RotateClockwise(_numRecentTicks * rotationMultiplier);
    }*/

    private void FixedUpdate()
    {
        // Debug.Log(_numRecentTicks);
        _rigidbody2D.AddForce(Time.deltaTime * _numRecentTicks * forceMultiplier * Vector2.up);
    }

    public void WhiskTick()
    {
        _numRecentTicks++;
        StartCoroutine(WaitAndRemoveTick());
    }

    private IEnumerator WaitAndRemoveTick()
    {
        float cooldownTickStrength = (float) 1 / numCooldownTicks;
        float cooldownTickLength = cooldownTime / numCooldownTicks;
        
        for (int i = 0; i < numCooldownTicks; i++)
        {
            _numRecentTicks -= cooldownTickStrength;
            yield return new WaitForSeconds(cooldownTickLength);
        }

        yield return null;
    }
    
    // This method takes a float parameter called angle and rotates the GameObject clockwise by that amount
    /*public void RotateClockwise(float angle)
    {
        // Get the current rotation of the GameObject in Euler angles
        Vector3 currentRotation = transform.eulerAngles;
        
        // Add the angle parameter to the z component of the current rotation
        currentRotation.z += angle;
        
        // Set the new rotation of the GameObject using Quaternion.Euler
        transform.rotation = Quaternion.Euler(currentRotation);
    }*/
}
