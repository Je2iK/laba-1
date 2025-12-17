package main

import "fmt"

type Queue struct {
	data []int
}

func NewQueue() *Queue {
	return &Queue{data: make([]int, 0)}
}

func (q *Queue) Enqueue(value int) {
	q.data = append(q.data, value)
}

func (q *Queue) Dequeue() (int, bool) {
	if len(q.data) == 0 {
		return 0, false
	}
	val := q.data[0]
	q.data = q.data[1:]
	return val, true
}

func (q *Queue) Print() {
	fmt.Println(q.data)
}
