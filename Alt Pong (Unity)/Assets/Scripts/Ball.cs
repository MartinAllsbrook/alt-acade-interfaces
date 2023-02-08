using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class Ball : MonoBehaviour
{
    public static Ball Instance;
    
    [SerializeField] private float speed;
    [SerializeField] private float angleMultiplier;
    [SerializeField] private float bounds;
    private Vector3 _direction;
    private Vector3 _velocity;
    private void Awake()
    {
        if (Instance == null)
            Instance = this;
    }

    void Start()
    {
        _velocity = Vector3.right * speed;
    }

    private void Update()
    {
        transform.position += _velocity * Time.deltaTime;
        if (Mathf.Abs(transform.position.x) > bounds)
            Reset();
    }

    private void Reset()
    {
        transform.position = Vector3.zero;
        _velocity = Vector3.right * speed;
    }

    private void OnTriggerEnter(Collider collision)
    {
        Debug.Log("collide");
        if (collision.gameObject.CompareTag("Paddle"))
        {
             _velocity = new Vector3(
                -_velocity.x, 
                _velocity.y + (collision.transform.position.y - transform.position.y) * angleMultiplier, 
                0);
        }
        if (collision.gameObject.CompareTag("Wall"))
        {
            _velocity = new Vector3(
                _velocity.x, 
                -_velocity.y, 
                0);
        }
        // _direction = -_direction;
        // _ballRigidbody.velocity = _direction * speed;
    }
}
