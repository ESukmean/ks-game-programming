
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MuteOnMButton : MonoBehaviour
{
    public AudioSource audio;

    private bool is_pause = false;
    // Start is called before the first frame update
    void Start()
    {
        audio = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetKeyDown("m"))
        {
            if (is_pause)
            {
                audio.Play(0);
            } else
            {
                audio.Pause();
            }
        }

        is_pause = !is_pause;
    }
}
