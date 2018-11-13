

// Declaring a Linked list :
struct Batch{
    int data;
    struct Batch *next;
 };
 
//Creating a Node:
typedef struct Batch *job; //Define node as pointer of data type struct LinkedList

void createJob(){
    job temp; // declare a node
    temp = (job)malloc(sizeof(struct Batch)); // allocate memory using malloc()
    temp->next = NULL;// make next point to NULL
}

//add a node to the linked list:
void addNode(job head, int value){
    job temp,p;// declare two nodes temp and p
    temp = createJob();//createNode will return a new node with data = value and next pointing to NULL.
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
job p;
p = head;
while(p != NULL){
    p = p->next;
}