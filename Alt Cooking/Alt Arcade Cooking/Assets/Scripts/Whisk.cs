using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Whisk : MonoBehaviour
{
    [SerializeField] private int numCooldownTicks;
    [SerializeField] private float cooldownTime;
    [SerializeField] private float forceMultiplier;
    [SerializeField] private UI ui;
    private Rigidbody2D _rigidbody2D;

    private float _numRecentTicks;

    private void Awake()
    {
        _rigidbody2D = GetComponent<Rigidbody2D>();
    }

    private void FixedUpdate()
    {
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

    private void OnCollisionEnter2D(Collision2D col)
    {
        if (col.gameObject.CompareTag("Salami"))
            ui.AddSalami();

        if (col.gameObject.CompareTag("Cucumber"))
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
}
