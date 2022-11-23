#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedefs for the data structures
typedef struct Stack Stack;
typedef struct Node Node;

// This defines the data structures for the node.
struct Node {
    Node * next;
    int EXHIBIT_ID;
    int NumOfMonkeys;
};

// This defines the data structures for the stack with node.
struct Stack {
    Node * head;
};

// This function that adds a new value in the stack using the exhibit ID and the number of monkeys at the exhibit as parameters.
void push(Stack * stack, int EXHIBIT_ID, int NumOfMonkeys, int NumOfExhibits) {

    // This will create a new node that we will add to the stack later.
    Node * newNode = (Node *) malloc(sizeof(Node));

    // If the stack is empty, then the new node will be the head of the stack.
    if (stack->head == NULL) {
        stack->head = newNode;
        newNode->next = NULL;
        newNode->EXHIBIT_ID = EXHIBIT_ID;
        newNode->NumOfMonkeys = NumOfMonkeys;    
    } else {
        // If the stack is not empty, then the new node will be the head of the stack and the old head will be the next node.
        newNode->next = stack->head;
        stack->head = newNode;
        newNode->EXHIBIT_ID = EXHIBIT_ID;
        newNode->NumOfMonkeys = NumOfMonkeys;
    }
}

// This function will remove the head of the stack.
void pop(Stack * stack) {
    // corner case to check if the stack is empty
    if (stack->head == NULL) {
        return;
    }

    // This will change the head of the stack to the next node, which will remove the old head.
    stack->head = stack->head->next;
}

// This function returns the number of the exhibit ID on the top of the stack
int topExhibitID(Stack * stack) {
    // corner case to check if the stack is empty
    if (stack->head == NULL) {
        return -1;
    }

    // This will return the number of the exhibit ID on the top of the stack
    return stack->head->EXHIBIT_ID;
}

// This function returns the number of monkeys on the top of the stack
int topNumOfMonkeys(Stack * stack) {
    // corner case to check if the stack is empty
    if (stack->head == NULL) {
        return -1;
    }

    // This will return the number of the monkeys on the top of the stack
    return stack->head->NumOfMonkeys;
}

// This function will sort the double pointer array of exhibits in ascending order based on the exhibit ID using heap sort algorithm.
void heapify(long long int ** exhibits, int NumOfExhibits, int i) {
    // This sets the largest value to the root.
    int largest = i;

    // This sets the left child to the root.
    int left = 2 * i + 1;

    // This sets the right child to the root.
    int right = 2 * i + 2;

    // If the left child is larger than the root, then set the largest value to the left child.
    if (left < NumOfExhibits && exhibits[left][0] > exhibits[largest][0]) {
        largest = left;
    }

    // If the right child is larger than the root, then set the largest value to the right child.
    if (right < NumOfExhibits && exhibits[right][0] > exhibits[largest][0]) {
        largest = right;
    }

    // If the largest value is not the root, then swap the largest value with the root.
    if (largest != i) {
        // This will swap the largest value with the root.
        long long int * temp = exhibits[i];
        exhibits[i] = exhibits[largest];
        exhibits[largest] = temp;

        // Recursively heapify the affected sub-tree.
        heapify(exhibits, NumOfExhibits, largest);
    }
}

void heapSort(long long int ** exhibits, int NumOfExhibits) {
    // This is a for loop to heapify the array.
    for (int i = NumOfExhibits / 2 - 1; i >= 0; i--) {
        // call the heapify function to heapify the array
        heapify(exhibits, NumOfExhibits, i);
    }

    // This is a for loop to extract the elements from the array.
    for (int i = NumOfExhibits - 1; i >= 0; i--) {
        // This will swap the root with the last element.
        long long int * temp = exhibits[0];
        exhibits[0] = exhibits[i];
        exhibits[i] = temp;

        // This line calls the heapify function to heapify the array.
        heapify(exhibits, i, 0);
    }
}

// This function looks for the Visitor ID in the double pointer array of exhibits using the ternary search and returns the index of the visitor when the exhibit ID is found.
int ternarySearch(long long int ** visitors, int left, int right, long long int VisitorID) {
    // If the left index is greater than the right index, then return -1.
    if (right >= left) {

        // This sets the mid1 and mid2 values.
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        // If the Visitor ID is found at mid1, then return mid1.
        if (visitors[mid1][0] == VisitorID) {
            return mid1;
        }

        // If the Visitor ID is found at mid2, then return mid2.
        if (visitors[mid2][0] == VisitorID) {
            return mid2;
        }

        // If the Visitor ID is less than mid1, then recursively call the function with the left index and mid1 - 1.
        if (VisitorID < visitors[mid1][0]) {
            return ternarySearch(visitors, left, mid1 - 1, VisitorID);
        } else if (VisitorID > visitors[mid2][0]) { // If the Visitor ID is greater than mid2, then recursively call the function with the mid2 + 1 and right index.
            return ternarySearch(visitors, mid2 + 1, right, VisitorID);
        } else { // If the Visitor ID is between mid1 and mid2, then recursively call the function with the mid1 + 1 and mid2 - 1.
            return ternarySearch(visitors, mid1 + 1, mid2 - 1, VisitorID);
        }
    }

    // This returns -1 if the Visitor ID is not found.
    return -1;
}

int main() {
    // NumOfExhibit is the number of exhibits in the zoo.
    // DestinationExhibit is the exhibit ID used to create the path.
    // MonkeyAtTheDestinationExhibit is the number of monkeys present at the destination exhibit.
    int NumOfExhibits = 0, DestinationExhibit = 0, MonkeysAtTheDestinationExhibit = 0;

    // TotalInStack is the total number of monkeys present in the stack.
    long long int TotalInStack = 0;

    // Using scanf to read the number of exhibits.
    scanf("%d", &NumOfExhibits);

    // When poping from the stack, the number of monkeys at the exhibit will be added to the a new double pointer array.
    long long int ** DestinationAndNumOfMonkeysSeen = (long long int **) malloc(sizeof(long long int *) * NumOfExhibits);

    // Creating a stack to store the exhibits using the Stack data structure.
    Stack * path = (Stack *) malloc(sizeof(Stack));
    path->head = NULL;

    // Using scanf to read the destination exhibit ID and the number of monkeys at the destination exhibit
    scanf("%d %d", &DestinationExhibit, &MonkeysAtTheDestinationExhibit);

    // Adding the destination exhibit and Monkeys presented there to the stack using the push function
    push(path, DestinationExhibit, MonkeysAtTheDestinationExhibit, NumOfExhibits);
    // Updating the total number of monkeys in the stack.
    TotalInStack += MonkeysAtTheDestinationExhibit;

    // Updating NumOfExhibits to be the number of exhibits - 1 because the destination exhibit is already added to the stack.
    NumOfExhibits--;

    // This for loop will read the exhibits and add them to the stack using the push function and remove them from the stack using the pop function.
    for (int i = NumOfExhibits, popCount = 0;i >= 1 || popCount <= NumOfExhibits;) {
        // If the number of exhibits is greater than 0, then read the exhibit ID and the number of monkeys at the exhibit.
        if(i > 0) {
            // DestinationExhibit is the exhibit ID used to create the path.
            scanf("%d", &DestinationExhibit);

            if(DestinationExhibit != -1) { // If the exhibit ID is not -1, then read the number of monkeys at the exhibit.

                // This will read the number of monkeys present at the current exhibit.
                scanf(" %d", &MonkeysAtTheDestinationExhibit);
                
                // This will add the exhibit and the number of monkeys to the stack using the push function.
                push(path, DestinationExhibit, MonkeysAtTheDestinationExhibit, NumOfExhibits);

                // This will add the number of monkeys at the destination exhibit to total in stack.
                TotalInStack += MonkeysAtTheDestinationExhibit;

                // This updates the i by decreasing it by 1 as the exhibit is added to the stack.
                i--;
            } else { // If the exhibit ID is -1, then pop the exhibit from the stack.

                // Before poping the stack, this will add the Last Destination Exhibit and total number of monkeys presented in the stack to the double pointer array.
                DestinationAndNumOfMonkeysSeen[popCount] = (long long int *) malloc(sizeof(long long int) * 2);
                DestinationAndNumOfMonkeysSeen[popCount][0] = topExhibitID(path);
                DestinationAndNumOfMonkeysSeen[popCount][1] = TotalInStack;

                // This will subtract the number of monkeys at the last destination exhibit from the total number of monkeys in the stack.
                TotalInStack -= topNumOfMonkeys(path);

                // This will pop the exhibit from the stack using the pop function.
                pop(path);

                // This will increase the popCount by 1 as the exhibit is poped from the stack.
                popCount++;
            }
        } else if(i == 0) { // If the number of exhibits is 0, then pop the exhibit from the stack.

            // The while loop will run if the stack is not empty.
            while (popCount <= NumOfExhibits) {

                // This will scan the exhibit ID.
                scanf("\n%d", &DestinationExhibit);

                // If the exhibit ID is -1, then pop the exhibit from the stack.
                if(DestinationExhibit == -1) {

                    // Before poping the stack, this will add the Last Destination Exhibit and total number of monkeys presented in the stack to the double pointer array.
                    DestinationAndNumOfMonkeysSeen[popCount] = (long long int *) malloc(sizeof(long long int) * 2);
                    DestinationAndNumOfMonkeysSeen[popCount][0] = topExhibitID(path);
                    DestinationAndNumOfMonkeysSeen[popCount][1] = TotalInStack;
                    
                    // This will subtract the number of monkeys at the last destination exhibit from the total number of monkeys in the stack.
                    TotalInStack -= topNumOfMonkeys(path);

                    // This will pop the exhibit from the stack using the pop function.
                    pop(path);

                    // This will increase the popCount by 1 as the exhibit is poped from the stack.
                    popCount++;

                    // If the stack has only one element, then pop the last element from the stack.
                    if(popCount == NumOfExhibits) {
                        // Before poping the stack, Add the Last Destination Exhibit and total number of monkeys presented in the stack to the double pointer array.
                        DestinationAndNumOfMonkeysSeen[popCount] = (long long int *) malloc(sizeof(long long int) * 2);
                        DestinationAndNumOfMonkeysSeen[popCount][0] = topExhibitID(path);
                        DestinationAndNumOfMonkeysSeen[popCount][1] = TotalInStack;
    
                        // This will subtract the number of monkeys at the last destination exhibit from the total number of monkeys in the stack.
                        TotalInStack -= topNumOfMonkeys(path);

                        // This will pop the exhibit from the stack using the pop function.
                        pop(path);

                        // This will increase the popCount by 1 as the exhibit is poped from the stack.
                        popCount++;
                    }
                }
            }
        }
    }
    
    // By calling this function, it will sort the double pointer array using the heap sort algorithm to sort it in ascending order based on the exhibit ID.
    heapSort(DestinationAndNumOfMonkeysSeen, NumOfExhibits+1);

    // NumOfVisitors is the number of visitors visiting the zoo.
    int NumOfVisitors = 0;

    // Using scanf to read the number of visitors
    scanf("%d", &NumOfVisitors);

    // VisitorWantsToGo is the exhibit ID that the visitor wants to go to.
    int VisitorWantsToGo = 0;

    // This for loop will run until the program reads all the number of visitors and outputs the data.
    for (int i = 0; i < NumOfVisitors;) {
        scanf("%d", &VisitorWantsToGo);    

        // This looks for the first index of the double pointer array which is equal to the VisitorWantsToGo of the visitor using ternary search.
        int index = ternarySearch(DestinationAndNumOfMonkeysSeen, 0, NumOfExhibits, VisitorWantsToGo);

        // If the index is not -1, print the DestinationAndNumOfMonkeysSeen of the double pointer array.
        if(index != -1) {
            printf("%lld\n", DestinationAndNumOfMonkeysSeen[index][1]);// This will print the number of monkeys seen by the visitor.
            i++;
        }
    }

    // This will free all the memory allocated to heap in the program so far.
    free(path);
    for(int i = 0; i < NumOfExhibits+1; i++) {
        free(DestinationAndNumOfMonkeysSeen[i]);
    }
    free(DestinationAndNumOfMonkeysSeen);

    return 0;
    
}