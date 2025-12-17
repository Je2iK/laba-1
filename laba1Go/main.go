package main

func main() {
	// Array
	arr := NewArray()
	arr.Append(10)
	arr.Append(20)
	arr.Remove(0)
	arr.Print()

	// Singly Linked List
	sll := SinglyLinkedList{}
	sll.Append(1)
	sll.Append(2)
	sll.Append(3)
	sll.Print()

	// Doubly Linked List
	dll := DoublyLinkedList{}
	dll.Append(4)
	dll.Append(5)
	dll.PrintForward()
	dll.PrintBackward()

	// Stack
	stack := NewStack()
	stack.Push(10)
	stack.Push(20)
	stack.Pop()
	stack.Print()

	// Queue
	queue := NewQueue()
	queue.Enqueue(1)
	queue.Enqueue(2)
	queue.Dequeue()
	queue.Print()

	// RBT
	tree := RBTree{}
	tree.Insert(10)
	tree.Insert(20)
	tree.Insert(30)
	tree.Insert(15)
	tree.Insert(25)
	tree.Insert(5)
	tree.Insert(1)

	tree.InOrder()
}
