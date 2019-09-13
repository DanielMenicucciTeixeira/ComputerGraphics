using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum eMovementType
{
    Forward,
    Line,
    Circle,
    Follow
}

[RequireComponent (typeof(Rigidbody))]
public class EnemyMovement : MonoBehaviour
{
    public eMovementType MovementType;
    public float Speed;
    public float Radius;
    private GameObject Target;
    private Vector3 StartPosition;
    private bool GoingForward = true;
    private Vector3 Direction;//Used to the the return angle in MoveLine Function

	// Use this for initialization
	void Start ()
    {
        StartPosition = gameObject.transform.position;
        Direction = gameObject.transform.forward.normalized;
	}
	
	// Update is called once per frame
	void Update ()
    {
        Move(MovementType);
	}

    void Move(eMovementType _MovementType)
    {
        switch(_MovementType)
        {
            case eMovementType.Forward: MoveForward(); break;
            case eMovementType.Line: MoveLine(); break;
            case eMovementType.Circle: MoveCircle(); break;
            case eMovementType.Follow: MoveFollow(); break;
            default: break;
        }
    }

    void MoveForward()
    {
        GetComponent<Rigidbody>().velocity = gameObject.transform.forward.normalized * Speed;
    }

    void MoveLine()
    {
        if (GoingForward)
        {
            
            if (GoingForward && (StartPosition - gameObject.transform.position).magnitude <= Radius)
            {
               
                GetComponent<Rigidbody>().velocity = Direction * Speed;
            }
            else
            {
                GoingForward = false;
                GetComponent<Rigidbody>().velocity = -Direction * Speed;
            }
        }
        else
        {
           
            if (!GoingForward && (StartPosition - gameObject.transform.position).x >= 0)
            {
                GetComponent<Rigidbody>().velocity = -Direction * Speed;
            }
            else
            {
                GoingForward = true;
                GetComponent<Rigidbody>().velocity = Direction * Speed;
            }
        }
        
    }

    void MoveCircle()
    {

    }

    void MoveFollow()
    {

    }
}
