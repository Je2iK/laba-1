package main

import "fmt"

type SLLNode struct {
	value int
	next  *SLLNode
}

type SinglyLinkedList struct {
	head *SLLNode
}

func (l *SinglyLinkedList) Append(value int) {
	newNode := &SLLNode{value: value}
	if l.head == nil {
		l.head = newNode
		return
	}
	cur := l.head
	for cur.next != nil {
		cur = cur.next
	}
	cur.next = newNode
}

func (l *SinglyLinkedList) Print() {
	cur := l.head
	for cur != nil {
		fmt.Printf("%d -> ", cur.value)
		cur = cur.next
	}
	fmt.Println("nil")
}
