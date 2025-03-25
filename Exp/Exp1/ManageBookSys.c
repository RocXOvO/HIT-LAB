//
// Created by sapphire on 2025/3/25.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEFAULT_SIZE 10

typedef struct{
  char BookID[20];
  char BookName[100];
  char AuthorName[50];
  int stock;
  }Book;

typedef struct Node{
  Book newbook;
  struct Node *next;
}Node;

//return a pointer which points at Node *.
Node* CreatNode(Book book){
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL){
    printf("内存分配错误\n");
    exit(1);
  }
  newNode -> newbook = book;
  newNode -> next = NULL;
  return newNode;
}
//**head means a pointer which points at Node *.
//**head is the head of the chain. */
void InsertBook(Node **head, Book book){
  Node *newNode = CreatNode(book);
  newNode -> next = *head;
  *head = newNode;
}

//formerNode is to document the former node of current.
int DeleteBook(Node **head, char bookId[]){
  Node *Current = *head;
  Node *formerNode = NULL;
  while (Current != NULL){
    if (strcmp(Current -> newbook.BookID, bookId) == 0){
      if (formerNode == NULL){
        *head = Current -> next;
        printf("图书%s删除成功",bookId);
        return 1;
      }else{
        formerNode -> next = Current -> next;
        printf("图书%s删除成功",bookId);
        return 1;
      }
    }
    formerNode = Current;
    Current = Current -> next;
  }
  return 0;
}

/// @brief 修改图书数量，类似删除书籍，比起更加简单。
/// @param head 
/// @param bookId 
/// @param newstock 
/// @return newstock
int UpdateStock(Node *head, char bookId[],int newstock){
  while(head != NULL){
    if (strcmp(head -> newbook.BookID, bookId) == 0){
      head -> newbook.stock = newstock;
      return newstock;
    }
  }
  return newstock;
}

Node* FindBook(Node *head, char bookId[]){
  while(head != NULL){
    if (strcmp(head -> newbook.BookID, bookId) == 0){
      printf("查找的图书信息:\n");
      printf("书号：%s，书名：%s，作者：%s,库存：%d",head -> newbook.BookID, head -> newbook.AuthorName, head -> newbook.AuthorName, head -> newbook.stock);
    }
    head = head -> next;
  }
  return head;
}

void TraverseList(Node *head){
  while(head != NULL){
    printf("查找的图书信息:\n");
    printf("书号：%s，书名：%s，作者：%s,库存：%d",head -> newbook.BookID, head -> newbook.AuthorName, head -> newbook.AuthorName, head -> newbook.stock);
    head = head -> next;
  }
}

int main(){
  return 0;
}
