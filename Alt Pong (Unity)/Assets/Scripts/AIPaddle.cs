using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AIPaddle : Paddle
{
    // Update is called once per frame
    void Update()
    {
        _direction = Vector3.zero;
        if (Ball.Instance.transform.position.y >= transform.position.y)
            _direction += Vector3.up;
        else
            _direction += Vector3.down;

        transform.position += speed * Time.deltaTime * _direction;
    }
}
