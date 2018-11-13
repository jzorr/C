
// Declaring a Linked list :
struct LinkedList{
    int data;
    struct LinkedList *next;
 };
 
//Creating a Node:
typedef struct LinkedList *node; //Define node as pointer of data type struct LinkedList

void createNode(){
    node temp; // declare a node
    temp = (node)malloc(sizeof(struct LinkedList)); // allocate memory using malloc()
    temp->next = NULL;// make next point to NULL
}

//add a node to the linked list:
void addNode(node head, int value){
    node temp,p;// declare two nodes temp and p
    temp = createNode();//createNode will return a new node with data = value and next pointing to NULL.
    temp->data = value; // add element's value to data part of node
    if(head == NULL){
        head = temp;     //when linked list is empty
    }
    else{
        p  = head;//assign head to p 
        while(p->next != NULL){
            p = p->next;//traverse the list until p is the last node.The last node always points to NULL.
        }
        p->next = temp;//Point the previous last node to the new node created.
    }
}

//Traversing the list:
node p;
p = head;
while(p != NULL){
    p = p->next;
}