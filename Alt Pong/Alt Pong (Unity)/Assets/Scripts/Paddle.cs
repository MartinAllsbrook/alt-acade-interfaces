using System;
using System.Collections;
using System.Collections.Generic;
using UnityEditor.UIElements;
using UnityEngine;
using System.IO.Ports;

public class Paddle : MonoBehaviour
{
    [SerializeField] protected float speed;
    [SerializeField] private int maxExpectedInput;
    [SerializeField] private float minOutput;
    [SerializeField] private float maxOutput;
    
    protected Vector3 _direction;
    
    SerialPort _stream = new SerialPort("COM3", 9600); //Set the port (com4) and the baud rate (9600, is standard on most devices)
    
    private void Start()
    {
        _stream.Open(); //Open the Serial Stream.
    }

    void Update()
    {
        // _direction = Vector3.zero;
        //
        // if (Input.GetKey(KeyCode.UpArrow))
        //     _direction += Vector3.up;
        // if (Input.GetKey(KeyCode.DownArrow))
        //     _direction += Vector3.down;
        //
        // transform.position += speed * Time.deltaTime * _direction;

        var serialIn = _stream.ReadLine();
        int value = int.Parse(serialIn);
        Debug.Log("Value: " + value);

        float position = (float) value / maxExpectedInput; // Normalize
        
        var range = maxOutput - minOutput;
        position *= range;
        position += minOutput;
        Debug.Log("Position: " + position);
        
        transform.position = new Vector3(transform.position.x, position, 0);
        
    }
}
