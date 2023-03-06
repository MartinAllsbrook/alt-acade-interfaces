using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class UI : MonoBehaviour
{
    [SerializeField] private TextMeshProUGUI salamiCounter;
    private float _salamiCount;

    public void AddSalami()
    {
        _salamiCount++;
        salamiCounter.text = "Salamis: " + _salamiCount;
    }

}
