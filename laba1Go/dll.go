package main

import "fmt"

type DLLNode struct {
	value int
	prev  *DLLNode
	next  *DLLNode
}

type DoublyLinkedList struct {
	head *DLLNode
	tail *DLLNode
}

func (l *DoublyLinkedList) Append(value int) {
	newNode := &DLLNode{value: value}
	if l.head == nil {
		l.head, l.tail = newNode, newNode
		return
	}
	l.tail.next = newNode
	newNode.prev = l.tail
	l.tail = newNode
}

func (l *DoublyLinkedList) PrintForward() {
	cur := l.head
	for cur != nil {
		fmt.Printf("%d <-> ", cur.value)
		cur = cur.next
	}
	fmt.Println("nil")
}

func (l *DoublyLinkedList) PrintBackward() {
	cur := l.tail
	for cur != nil {
		fmt.Printf("%d <-> ", cur.value)
		cur = cur.prev
	}
	fmt.Println("nil")
}
