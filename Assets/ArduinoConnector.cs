using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Uduino;

public class ArduinoConnector : MonoBehaviour
{
    public float effectTimer = 5.0f;
    private bool timerOn = false;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            UduinoManager.Instance.sendCommand("turnOn");
            timerOn = true;
            effectTimer = 5.0f;
        }
        if (timerOn)
        {
            effectTimer -= Time.deltaTime;
        }
        if (effectTimer < 0.0f && timerOn)
        {
            UduinoManager.Instance.sendCommand("turnOff");
            timerOn = false;
        }
    }
}
