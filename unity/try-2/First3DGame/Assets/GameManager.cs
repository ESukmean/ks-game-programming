using UnityEngine;
using System.Collections;

public class GameManager : MonoBehaviour
{

    public GameObject Canvas;
    public GameObject Camera;
    bool Paused = false;
    public AudioSource audio;

    void Start()
    {
        audio = GameObject.Find("BGM").GetComponent<AudioSource>();
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
                audio.Play();
                Paused = false;
            }
            else
            {
                Time.timeScale = 0.0f;
                Canvas.gameObject.SetActive(true);
                
                Cursor.visible = true;
                Screen.lockCursor = false;
                audio.Pause();
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

    public void exit()
    {
        Application.Quit();
    }
}