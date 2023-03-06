using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class SerialManager : MonoBehaviour
{
    [SerializeField] private Whisk whisk;
    
    SerialPort _stream = new SerialPort("COM6", 9600); //Set the port (com6) and the baud rate (9600, is standard on most devices)

    // Start is called before the first frame update
    void Start()
    {
        _stream.Open(); //Open the Serial Stream.
    }

    // Update is called once per frame
    void Update()
    {
        var serialIn = _stream.ReadLine();
        // Debug.Log(serialIn);
        int value = int.Parse(serialIn);
        
        if (value == 1)
        {
            whisk.WhiskTick();
            // Debug.Log("tick");
        }
    }
}
