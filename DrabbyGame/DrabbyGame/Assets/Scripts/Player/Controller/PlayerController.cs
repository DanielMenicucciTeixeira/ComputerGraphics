using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public enum eInventorySelection
{
    INVENTORY_NONE,
    INVENTORY_SWORD,
    INVENTORY_MEAT,
    INVENTORY_BUTTERFLY,
    INVENTORY_TOTAL
}

public class PlayerController : MonoBehaviour
{
    //Determines what Inventory item is selected
    private eInventorySelection SelectedItem = eInventorySelection.INVENTORY_NONE;

    //List of Items associated with Inventory Selections
    public ItemStruct ItemList;

    //LayerMask for the SpawnItem Raycasts
    public LayerMask hitLayers;

    private int fingerID = -1;

    private void Awake()
    {
#if !UNITY_EDITOR
         finger ID = 0;
#endif
    }

    // Use this for initialization
    void Start()
    {
        ItemList.Sword.GetComponent<Item_Sword>().Stock = 3;
        ItemList.Meat.GetComponent<Item>().Stock = 3;
        ItemList.Butterfly.GetComponent<Item_Butterfly>().Stock = 3;
    }

    // Update is called once per frame
    void Update()
    {
        //If mouse right clicked
        if(Input.GetMouseButtonDown(1))
        {
            //Deselect any selected items
            SelectedItem = eInventorySelection.INVENTORY_NONE;
            ButterflyClickFlag = false;//Make sure this flag is set to false, in case Butterfly was deselected mid click
        }
        //if left clicked, use selecated item, if any
        else if(Input.GetMouseButtonDown(0) || (ButterflyClickFlag && SelectedItem == eInventorySelection.INVENTORY_BUTTERFLY))
        {
            switch (SelectedItem)
            {
                case eInventorySelection.INVENTORY_NONE:
                    break;
                case eInventorySelection.INVENTORY_SWORD:
                    SpawnSword();
                    break;
                case eInventorySelection.INVENTORY_MEAT:
                    SpawnMeat();
                    break;
                case eInventorySelection.INVENTORY_BUTTERFLY:
                    SpawnButterfly();
                    break;
                default:
                    break;
            }
        }
    }

    private void SpawnItem(GameObject item)
    {

        if (!EventSystem.current.IsPointerOverGameObject(fingerID))
        {
            //Debug.Log(GetSelectedItem());
            if (item)
            {
                Vector3 mouse = Input.mousePosition;//Get the mouse position
                Ray castPoint = Camera.main.ScreenPointToRay(mouse);//Cast a ray to get where the mouse is pointing at
                RaycastHit hit;//Will store the position where the ray hit
                if (Physics.Raycast(castPoint, out hit, Mathf.Infinity, hitLayers))//If the Raycast does not hit a wall nor the UI
                {
                    //Instantiate(SelectedItem, hit.point, Quaternion.identity);
                    Instantiate(item, new Vector3(hit.point.x, GetComponent<MyGameManager>().GetPlayer().transform.position.y, hit.point.z), Quaternion.identity);

                }
            }
        }
    }

    //Function for when inventory Sword is selected
    protected void SpawnSword()
    {
        //If there swords in the inventory
        if(ItemList.Sword.GetComponent<Item_Sword>().Stock > 0)
        {
            //Spawn a sword at clicked location
            SpawnItem(ItemList.Sword);
            //Remove a sword from inventory stock
            ItemList.Sword.GetComponent<Item_Sword>().Stock --;
        }
    }

    //Function for when inventory Meat is selected
    protected void SpawnMeat()
    {
        //If there is meat in the inventory
        if (ItemList.Meat.GetComponent<Item>().Stock > 0)
        {
            //Spawn meat at clicked location
            SpawnItem(ItemList.Meat);
            //Remove one meat from inventory stock
            ItemList.Meat.GetComponent<Item>().Stock--;
        }
    }

    //Flag for the Spawnposition of SpawnButterfly 
    bool ButterflyClickFlag = false;
    //Varible to store the first click hit.point
    Vector3 ButterflySpawnLocation;
    //Function for when inventory Butterfly is selected
    protected void SpawnButterfly()
    {
        //If clicking on UI, ignore this function
        if (EventSystem.current.IsPointerOverGameObject(fingerID)) return;

            //If there is any butterfly in the inventory
            if (ItemList.Butterfly.GetComponent<Item_Butterfly>().Stock > 0)
        {
            //If the spawn location is not set, set it to mouse click location
            if (!ButterflyClickFlag)
            {
                Vector3 mouse = Input.mousePosition;//Get the mouse position
                Ray castPoint = Camera.main.ScreenPointToRay(mouse);//Cast a ray to get where the mouse is pointing at
                RaycastHit hit;//Will store the position where the ray hit
                if (Physics.Raycast(castPoint, out hit, Mathf.Infinity, hitLayers))//If the Raycast does not hit a wall nor the UI
                {
                    ButterflySpawnLocation = new Vector3(hit.point.x, 3, hit.point.z);//Set the butterfly spawn position
                    ButterflyClickFlag = true;//Set the first click flag to true;
                }
            }
            //If the spawn location is already set
            else if (Input.GetMouseButtonUp(0))
            {
                Vector3 mouse = Input.mousePosition;//Get the mouse position
                Ray castPoint = Camera.main.ScreenPointToRay(mouse);//Cast a ray to get where the mouse is pointing at
                RaycastHit hit;//Will store the position where the ray hit
                if (Physics.Raycast(castPoint, out hit, Mathf.Infinity, hitLayers))//If the Raycast does not hit a wall nor the UI
                {
                    Vector3 ButterflyTargetDirection = new Vector3(hit.point.x, 1.5f, hit.point.z);//Set the butterfly target direction

                    //Spawn the butterfly
                    Item_Butterfly butterfly = Instantiate(ItemList.Butterfly, ButterflySpawnLocation, Quaternion.identity).GetComponent<Item_Butterfly>();
                    //Set the butterflys flight direction
                    if (butterfly) butterfly.SetDirection(ButterflyTargetDirection);

                    //Decrease the amount of butterflies in stock by one
                    ItemList.Butterfly.GetComponent<Item_Butterfly>().Stock--;
                    //Reset the first click flag
                    ButterflyClickFlag = false;
                }
            }
        }
    }

    public void SetSelectedItem (eInventorySelection item)
    {
       SelectedItem = item;
    }

    //Workaround to unitys lack of enum buttons
    public void SetSelectedItem(string itemName)
    {
        if (itemName == "Sword") SetSelectedItem(eInventorySelection.INVENTORY_SWORD);
        else if (itemName == "Meat") SetSelectedItem(eInventorySelection.INVENTORY_MEAT);
        else if (itemName == "Butterfly") SetSelectedItem(eInventorySelection.INVENTORY_BUTTERFLY);
        else SetSelectedItem(eInventorySelection.INVENTORY_NONE);
    }
}
