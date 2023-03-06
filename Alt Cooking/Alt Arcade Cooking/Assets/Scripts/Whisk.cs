using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using UnityEngine;
using UnityEngine.SceneManagement;
using Debug = UnityEngine.Debug;

public class Whisk : MonoBehaviour
{
    // [SerializeField] private int numCooldownTicks;
    // [SerializeField] private float cooldownTime;
    [SerializeField] private float forceMultiplier;
    [SerializeField] private Animator animator;
    [SerializeField] private UI ui;
    [SerializeField] private float maxWait;

    private Rigidbody2D _rigidbody2D;
    private Stopwatch _timer;
    private float _numRecentTicks;

    private void Awake()
    {
        _rigidbody2D = GetComponent<Rigidbody2D>();
        _timer = new Stopwatch();
    }

    private void Update()
    {
        animator.SetFloat("Speed", _numRecentTicks);
        if (_timer.ElapsedMilliseconds > maxWait)
        {
            _numRecentTicks = 0;
        }
    }

    private void FixedUpdate()
    {
        _rigidbody2D.AddForce(Time.deltaTime * _numRecentTicks * forceMultiplier * Vector2.up);
    }

    public void WhiskTick()
    {
        _numRecentTicks = maxWait - _timer.ElapsedMilliseconds;
        if (_numRecentTicks < 0)
            _numRecentTicks = 0;
        _timer.Reset();
        _timer.Start();
        Debug.Log(_numRecentTicks);
        // _numRecentTicks++;
        // StartCoroutine(WaitAndRemoveTick());
    }

    /*private IEnumerator WaitAndRemoveTick()
    {
        float cooldownTickStrength = (float) 1 / numCooldownTicks;
        float cooldownTickLength = cooldownTime / numCooldownTicks;
        
        for (int i = 0; i < numCooldownTicks; i++)
        {
            _numRecentTicks -= cooldownTickStrength;
            yield return new WaitForSeconds(cooldownTickLength);
        }

        yield return null;
    }*/

    private void OnCollisionEnter2D(Collision2D col)
    {
        if (col.gameObject.CompareTag("Salami"))
            ui.AddSalami();

        if (col.gameObject.CompareTag("Cucumber"))
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
}
