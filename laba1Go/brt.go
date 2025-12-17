package main

import "fmt"

// Цвета
const (
	RED   = true
	BLACK = false
)

// Узел дерева
type RBNode struct {
	value  int
	color  bool
	left   *RBNode
	right  *RBNode
	parent *RBNode
}

// Дерево
type RBTree struct {
	root *RBNode
}

// Вспомогательная функция — левый поворот
func (t *RBTree) rotateLeft(x *RBNode) {
	y := x.right
	x.right = y.left
	if y.left != nil {
		y.left.parent = x
	}
	y.parent = x.parent
	if x.parent == nil {
		t.root = y
	} else if x == x.parent.left {
		x.parent.left = y
	} else {
		x.parent.right = y
	}
	y.left = x
	x.parent = y
}

// Правый поворот
func (t *RBTree) rotateRight(x *RBNode) {
	y := x.left
	x.left = y.right
	if y.right != nil {
		y.right.parent = x
	}
	y.parent = x.parent
	if x.parent == nil {
		t.root = y
	} else if x == x.parent.right {
		x.parent.right = y
	} else {
		x.parent.left = y
	}
	y.right = x
	x.parent = y
}

// Исправление свойств после вставки
func (t *RBTree) fixInsert(z *RBNode) {
	for z.parent != nil && z.parent.color == RED {
		if z.parent == z.parent.parent.left {
			y := z.parent.parent.right
			if y != nil && y.color == RED {
				// Случай 1: дядя красный
				z.parent.color = BLACK
				y.color = BLACK
				z.parent.parent.color = RED
				z = z.parent.parent
			} else {
				if z == z.parent.right {
					// Случай 2: поворот влево
					z = z.parent
					t.rotateLeft(z)
				}
				// Случай 3: поворот вправо
				z.parent.color = BLACK
				z.parent.parent.color = RED
				t.rotateRight(z.parent.parent)
			}
		} else {
			y := z.parent.parent.left
			if y != nil && y.color == RED {
				z.parent.color = BLACK
				y.color = BLACK
				z.parent.parent.color = RED
				z = z.parent.parent
			} else {
				if z == z.parent.left {
					z = z.parent
					t.rotateRight(z)
				}
				z.parent.color = BLACK
				z.parent.parent.color = RED
				t.rotateLeft(z.parent.parent)
			}
		}
	}
	t.root.color = BLACK
}

// Вставка нового узла
func (t *RBTree) Insert(value int) {
	newNode := &RBNode{value: value, color: RED}
	var y *RBNode
	x := t.root

	// Обычная вставка как в BST
	for x != nil {
		y = x
		if newNode.value < x.value {
			x = x.left
		} else {
			x = x.right
		}
	}
	newNode.parent = y
	if y == nil {
		t.root = newNode
	} else if newNode.value < y.value {
		y.left = newNode
	} else {
		y.right = newNode
	}

	// Исправляем баланс
	t.fixInsert(newNode)
}

// Печать дерева (in-order)
func (t *RBTree) InOrder() {
	fmt.Println("InOrder Traversal (value [color]):")
	printInOrder(t.root)
	fmt.Println()
}

func printInOrder(n *RBNode) {
	if n != nil {
		printInOrder(n.left)
		color := "B"
		if n.color == RED {
			color = "R"
		}
		fmt.Printf("%d[%s] ", n.value, color)
		printInOrder(n.right)
	}
}
