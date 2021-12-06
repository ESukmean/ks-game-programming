using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneChange : MonoBehaviour
{
	public void ChangeToMainScene()
	{
		SceneManager.LoadScene("MainScene");
	}
	public void Exit()
	{
		Application.Quit();
	}
}