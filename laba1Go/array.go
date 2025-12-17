package main

import "fmt"

type Array struct {
	data []int
}

func NewArray() *Array {
	return &Array{data: make([]int, 0)}
}

func (a *Array) Append(value int) {
	a.data = append(a.data, value)
}

func (a *Array) Get(index int) (int, bool) {
	if index < 0 || index >= len(a.data) {
		return 0, false
	}
	return a.data[index], true
}

func (a *Array) Remove(index int) bool {
	if index < 0 || index >= len(a.data) {
		return false
	}
	a.data = append(a.data[:index], a.data[index+1:]...)
	return true
}

func (a *Array) Print() {
	fmt.Println(a.data)
}
