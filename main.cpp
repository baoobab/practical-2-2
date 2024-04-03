﻿#include <iostream>
using namespace std;


struct List
{
	int data;
	List *head;
	List *tail;
};


int getRandomValueFromRange(int leftLimit, int rightLimit) {
  return leftLimit + rand() % (rightLimit - leftLimit + 1);
}


int countLength(List * &arr) {
  int counter = 0;
  List* curr = arr;
  while (curr) {
    curr = curr->tail;
    counter++;
  }
  return counter;
}


bool checkIndex(List* &arr, int idx) {
  return (idx >= 0 && idx < countLength(arr));
}

void printNode(List* curr) {
  cout << "\nItem\n"
  << " Data: " << curr->data << "\n"
  << " Tail: " << curr->tail << "\n"
  << " Addr: " << curr << "\n"
  << " Head: " << curr->head << "\n";
}

List* findItemByIndex(List* &arr, unsigned idx) {
  List* curr = arr;
  int counter = 0;

  if (!checkIndex(arr, idx)) return NULL;
  while (curr) {
    if (counter == idx) return curr;
    curr = curr->tail;
    counter++;
  }
  return NULL;
}

void findItemsByData(List* &arr, int data) {
  List* curr = arr;

  while (curr) {
    if (curr->data == data) printNode(curr);
    curr = curr->tail;
  }
}

int getIndexOfItem(List* arr, int item, int startIdx = 0) {
  List* curr = arr;
  int counter = 0;
  if (startIdx) if (!checkIndex(arr, startIdx)) return -1;
  
  while (curr) {
    if (counter >= startIdx) {
      if (curr->data == item) return counter;
    }
    curr = curr->tail;
    counter++;
  }
  return -1;
}


int getNumberOfEntries(List* &arr, int item) {
  List* curr = arr;
  int counter = 0;

  while (curr) {
    if (curr->data == item) counter++;
    curr = curr->tail;
  }
  return counter;
}

List *createList(int length)
{
  List *curr = 0,
  *next = 0;
  for (int i = 1; i <= length; ++i)
  {
    curr = new List;
    curr -> tail = next;
    if (next) {
      next -> head = curr;
    }
      next = curr;
  }
  curr -> head = 0;
  return curr;
}

List* addItem(List* &beg, int data) {
  List* lastItem = findItemByIndex(beg, countLength(beg) - 1);
  List* item = new List;

  item->data = data;
  item->head = lastItem;
  item->tail = 0;

  if (lastItem) lastItem->tail = item;
  else beg = item;

  return item;
}

List* insItem( List* &beg, int index )
{
  List * item = new List;
  if (!index || !beg) {
    beg -> head = item;
    item -> head = NULL;
    item -> tail = beg;
    beg = item;
    return item;
  }
  List* prevItem = beg;
  --index;
  while (prevItem -> tail && (index--)) {
    prevItem = prevItem -> tail; 
  }
  item -> head = prevItem;
  item -> tail -> head = item;
  item -> tail = prevItem -> tail;
  prevItem -> tail = item;
  return item;
}


void delItemByIndex(List* &beg, int index)
{
  if(!checkIndex(beg, index)) {
    cout << "\nIncorrect index value\n";
    return;
  }

  List* item = NULL;
  if (index == 0) {
    item = beg -> tail;
    delete beg;
    beg = item;
    if (countLength(beg) == 0) {
      delete beg;
      beg = NULL;
      return;
    }
    beg -> head = NULL;
    return;
  }

  item = findItemByIndex(beg, index - 1);
  List* dItem = item -> tail;
  item -> tail = dItem -> tail;
  List* nItem = findItemByIndex(beg, index + 1);
  if (nItem) nItem -> head = item;

  delete dItem;
}

void delItemByValue(List* &beg, int value)
{
  while(getNumberOfEntries(beg, value) > 0) {
    int index = getIndexOfItem(beg, value);
    delItemByIndex(beg, index);
  }
}


void swapElementsByIndex(List* &arr, int index1, int index2) {

  if (!checkIndex(arr, index1) || !(checkIndex(arr, index2))) {
    cout << "\nIncorrect index value(-s)\n";
    return;
  }

  if (index2 < index1) {
    int buffer = index1;
    index1 = index2;
    index2 = buffer;
  }

  List* el1m = findItemByIndex(arr, index1 - 1);
  List* el1 = findItemByIndex(arr, index1);
  List* el1p = findItemByIndex(arr, index1 + 1);
  List* el2m = findItemByIndex(arr, index2 - 1);
  List* el2 = findItemByIndex(arr, index2);
  List* el2p = findItemByIndex(arr, index2 + 1);
  
  List* head2 = el2->head;
  List* tail2 = el2->tail;
  List* head1 = el1->head;
  List* tail1 = el1->tail;

  switch (abs(index1 - index2)) {
    case 0: 
      return;
    case 1:
      el2->tail = el1;
      el1->head = el2;
      break;
    default:
      el2->head = head1;
      el2->tail = tail1;
      el1->head = head2;

      el1p->head = el2;
      el2m->tail = el1;
      break;
  }
  el2->head = head1;
  el1->tail = tail2;

  if (index1 != 0) el1m->tail = el2;
  else arr = el2;
  if (index2 != countLength(arr) - 1) el2p->head = el1;
}

void printList(List* &arr) {
  List* curr = arr;
  while (curr) {
    printNode(curr);
    curr = curr->tail;
  }
}


int main() {
  setlocale(LC_ALL, "Russian");
  srand(time(0));

  cout << "Navigation:" << "\n"
  << "1) Create a new list" << "\n"
  << "2) Speeed" << "\n"
  << "3) Operations with list" << "\n"
  << "4) Tiiime" << "\n"
  << "5) Print list" << "\n";
  
  List *list = NULL;

  while(true) {
    cin.clear(); // Clearing the input stream from possible errors
    cin.sync();
    short int workPoint;

    cout << "Select point of work (number 1 to 5): ";
    cin >> workPoint;

    switch (workPoint)
    {   
      case 1: {
        cout << "Choose the way (eng)\n"
        << "(A) - Enter the dimension and fill it with random\n"
        << "(B) - Enter the number yourself skok hosh\n";
        char creatingType;
        cin >> creatingType;
        if (!cin.good()) {
          cout << "\nYou entered an incorrect value\n";
          break;
        }
        if (creatingType == 'B' || creatingType == 'b') {
          cout << "Enter items, to stop it - enter any char\n";
          list = NULL;
          int item;

          while (cin >> item) addItem(list, item);
        
          cout << "\nList length: " << countLength(list) << "\n";
        } else {
          cout << "\nEnter elements count: ";
          unsigned listSize = 0;
          cin >> listSize;
          if (!cin.good()) {
            cout << "\nYou entered an incorrect value\n";
            break;
          }
          list = createList(listSize);
          List* curr = list;
          while (curr) {
            curr->data = getRandomValueFromRange(0, 99);
            curr = curr->tail;
          }
        }
        printList(list);
        break;
      }
      case 2: {
        printList(list);
        break;
      }
      case 3: {
        cout << "Choose the action (eng)\n"
        << "(G) - Get element\n"
        << "(I) - Insert element\n"
        << "(S) - Swap elements\n"
        << "(D) - Delete element\n";

        List* foundedItem = NULL;
        char actionType;
        char choiseType;
        cin >> actionType;

        switch (actionType)
        {
        case 'G':
          cout << "By index or by value (I/V)?: ";
          cin >> choiseType;
          if (!cin.good()) {
            cout << "\nYou entered an incorrect value\n";
            break;
          }
          if (choiseType == 'I' || choiseType == 'i') {
            cout << "Enter an index of element (length is " << countLength(list) << "): ";
            int index;
            cin >> index;
            if (!cin.good()) {
              cout << "\nYou entered an incorrect value\n";
              break;
            }
            foundedItem = findItemByIndex(list, index);
            if (!foundedItem) {
              cout << "\nYou entered an incorrect value\n";
              break;
            }
            printNode(foundedItem);
          } else {
            cout << "Enter a value of element: ";
            int data;
            cin >> data;
            if (!cin.good()) {
              cout << "\nYou entered an incorrect value\n";
              break;
            }
            findItemsByData(list, data);
          }
          break;
        case 'I':
          break;
        case 'S':
          break;
        case 'D':
          cout << "By index or by value (I/V)?: ";
          cin >> choiseType;
          if (!cin.good()) {
            cout << "\nYou entered an incorrect value\n";
            break;
          }
          if (choiseType == 'I' || choiseType == 'i') {
            cout << "Enter an index of element (length is " << countLength(list) << "): ";
            int index;
            cin >> index;
            if (!cin.good()) {
              cout << "\nYou entered an incorrect value\n";
              break;
            }
            delItemByIndex(list, index);
          } else {
            cout << "Enter a value of element: ";
            int data;
            cin >> data;
            if (!cin.good()) {
              cout << "\nYou entered an incorrect value\n";
              break;
            }
            delItemByValue(list, data);
          }
          cout << "Updated list (length is " << countLength(list) << "):\n";
          printList(list);
          break;
        default:
          cout << "\nYou entered an incorrect value\n";
          break;
        }
        break;
      }
      case 4: {
        break;
      }
      case 5: {
        printList(list);
        break;
      }
      default: {
        cout << "\n" << "You did not enter a number in the range from 1 to 5";
        break;
      }
    }

    cin.clear(); // Clearing the input stream from possible errors
    cin.sync();

    char stopFlag;
    cout << "\n" << "Continue the program? (Y/N) ";
    cin >> stopFlag;
        
    if (stopFlag != 'Y' && stopFlag != 'y') break;

    }
    
    return 0;
}