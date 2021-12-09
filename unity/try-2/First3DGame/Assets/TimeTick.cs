using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TimeTick : MonoBehaviour
{
    public Text clock;
    private double StartTime;
    // Start is called before the first frame update
    void Start()
    {
        StartTime = Time.realtimeSinceStartup;
        clock = GameObject.Find("TimeElpased").GetComponent<Text>();
    }

    // Update is called once per frame
    void Update()
    {
        int time = (int)(Time.realtimeSinceStartup - StartTime);

        clock.text = (time / 60) + "분 " + (time % 60) + "초";
    }
}
