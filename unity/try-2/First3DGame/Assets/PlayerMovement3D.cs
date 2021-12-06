using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement3D : MonoBehaviour
{
    public float speed = 20;
    private Vector3 motion;
    private Vector3 rotateValue;
    private Rigidbody rb;
    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();   
    }

    // Update is called once per frame
    void Update()
    {
        motion = new Vector3(Input.GetAxisRaw("Horizontal"), 0, Input.GetAxisRaw("Vertical"));
        rb.velocity = motion * speed;
        if (Input.GetMouseButton(1))
        {
            rotateValue = new Vector3(0, Input.GetAxis("Mouse X"), 0);
            transform.eulerAngles = transform.eulerAngles - rotateValue;
        }
    }
}
