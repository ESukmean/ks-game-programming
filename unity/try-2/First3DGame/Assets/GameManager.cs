using UnityEngine;
using System.Collections;

public class GameManager : MonoBehaviour
{

    public GameObject Canvas;
    public GameObject Camera;
    bool Paused = false;

    void Start()
    {
        Canvas.gameObject.SetActive(false);
    }

    void Update()
    {
        if (Input.GetKeyDown("escape"))
        {
            if (Paused == true)
            {
                Time.timeScale = 1.0f;
                Canvas.gameObject.SetActive(false);
                Cursor.visible = false;
                Screen.lockCursor = true;
                Camera.GetComponent<AudioSource>().Play();
                Paused = false;
            }
            else
            {
                Time.timeScale = 0.0f;
                Canvas.gameObject.SetActive(true);
                
                Cursor.visible = true;
                Screen.lockCursor = false;
                Camera.GetComponent<AudioSource>().Pause();
                Paused = true;
            }
        }
    }
    public void Resume()
    {
        Time.timeScale = 1.0f;
        Canvas.gameObject.SetActive(false);
        Cursor.visible = false;
        Screen.lockCursor = true;
        Camera.GetComponent<AudioSource>().Play();
    }
}