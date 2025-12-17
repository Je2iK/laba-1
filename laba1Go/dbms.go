package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"sort"
	"strconv"
	"strings"
)

type DBMS struct {
	Arrays  map[string][]string `json:"arrays"`
	Stacks  map[string][]string `json:"stacks"`
	Queues  map[string][]string `json:"queues"`
	SLists  map[string][]string `json:"slists"`
	DLists  map[string][]string `json:"dlists"`
	Trees   map[string][]int    `json:"trees"`
	filename string
}

func NewDBMS(filename string) *DBMS {
	dbms := &DBMS{
		Arrays:   make(map[string][]string),
		Stacks:   make(map[string][]string),
		Queues:   make(map[string][]string),
		SLists:   make(map[string][]string),
		DLists:   make(map[string][]string),
		Trees:    make(map[string][]int),
		filename: filename,
	}
	dbms.loadFromFile()
	return dbms
}

func (d *DBMS) saveToFile() {
	data, _ := json.MarshalIndent(d, "", "  ")
	ioutil.WriteFile(d.filename, data, 0644)
}

func (d *DBMS) loadFromFile() {
	data, err := ioutil.ReadFile(d.filename)
	if err != nil {
		return
	}
	json.Unmarshal(data, d)
}

func (d *DBMS) executeQuery(query string) {
	parts := strings.Fields(query)
	if len(parts) < 2 {
		return
	}
	
	cmd := parts[0]
	name := parts[1]
	
	switch cmd {
	// Array commands
	case "MPUSHEND":
		if len(parts) >= 3 {
			d.Arrays[name] = append(d.Arrays[name], parts[2])
			fmt.Println(parts[2])
		}
	case "MPUSHI":
		if len(parts) >= 4 {
			index, _ := strconv.Atoi(parts[3])
			if index >= 0 && index <= len(d.Arrays[name]) {
				arr := d.Arrays[name]
				arr = append(arr[:index], append([]string{parts[2]}, arr[index:]...)...)
				d.Arrays[name] = arr
				fmt.Println(parts[2])
			}
		}
	case "MREAD":
		for _, v := range d.Arrays[name] {
			fmt.Print(v + " ")
		}
		fmt.Println()
	case "MLEN":
		fmt.Println(len(d.Arrays[name]))
	case "MGET":
		if len(parts) >= 3 {
			index, _ := strconv.Atoi(parts[2])
			if index >= 0 && index < len(d.Arrays[name]) {
				fmt.Println(d.Arrays[name][index])
			}
		}
		
	// Stack commands
	case "STPUSH":
		if len(parts) >= 3 {
			d.Stacks[name] = append(d.Stacks[name], parts[2])
			fmt.Println(parts[2])
		}
	case "STPOP":
		if len(d.Stacks[name]) > 0 {
			stack := d.Stacks[name]
			val := stack[len(stack)-1]
			d.Stacks[name] = stack[:len(stack)-1]
			fmt.Println(val)
		}
	case "STREAD":
		for _, v := range d.Stacks[name] {
			fmt.Print(v + " ")
		}
		fmt.Println()
		
	// Queue commands
	case "QPUSH":
		if len(parts) >= 3 {
			d.Queues[name] = append(d.Queues[name], parts[2])
			fmt.Println(parts[2])
		}
	case "QPOP":
		if len(d.Queues[name]) > 0 {
			val := d.Queues[name][0]
			d.Queues[name] = d.Queues[name][1:]
			fmt.Println(val)
		}
	case "QREAD":
		for _, v := range d.Queues[name] {
			fmt.Print(v + " ")
		}
		fmt.Println()
		
	// SLL commands
	case "SLLADDH":
		if len(parts) >= 3 {
			d.SLists[name] = append([]string{parts[2]}, d.SLists[name]...)
			fmt.Println(parts[2])
		}
	case "SLLADDT":
		if len(parts) >= 3 {
			d.SLists[name] = append(d.SLists[name], parts[2])
			fmt.Println(parts[2])
		}
	case "SLLREAD":
		for _, v := range d.SLists[name] {
			fmt.Print(v + " ")
		}
		fmt.Println()
	case "SLLFINDV":
		if len(parts) >= 3 {
			found := false
			for _, v := range d.SLists[name] {
				if v == parts[2] {
					found = true
					break
				}
			}
			if found {
				fmt.Println("TRUE")
			} else {
				fmt.Println("FALSE")
			}
		}
		
	// DLL commands
	case "DLLADDH":
		if len(parts) >= 3 {
			d.DLists[name] = append([]string{parts[2]}, d.DLists[name]...)
			fmt.Println(parts[2])
		}
	case "DLLADDT":
		if len(parts) >= 3 {
			d.DLists[name] = append(d.DLists[name], parts[2])
			fmt.Println(parts[2])
		}
	case "DLLREADF":
		for _, v := range d.DLists[name] {
			fmt.Print(v + " ")
		}
		fmt.Println()
	case "DLLREADB":
		for i := len(d.DLists[name]) - 1; i >= 0; i-- {
			fmt.Print(d.DLists[name][i] + " ")
		}
		fmt.Println()
		
	// BRT commands
	case "BRTINSERT":
		if len(parts) >= 3 {
			val, _ := strconv.Atoi(parts[2])
			// Check if value already exists
			exists := false
			for _, v := range d.Trees[name] {
				if v == val {
					exists = true
					break
				}
			}
			if !exists {
				d.Trees[name] = append(d.Trees[name], val)
				sort.Ints(d.Trees[name])
			}
			fmt.Println(val)
		}
	case "BRTDEL":
		if len(parts) >= 3 {
			val, _ := strconv.Atoi(parts[2])
			for i, v := range d.Trees[name] {
				if v == val {
					d.Trees[name] = append(d.Trees[name][:i], d.Trees[name][i+1:]...)
					break
				}
			}
		}
	case "BRTREAD":
		for _, v := range d.Trees[name] {
			fmt.Print(v, " ")
		}
		fmt.Println()
	}
	
	d.saveToFile()
}

func main() {
	if len(os.Args) < 5 {
		fmt.Println("Usage: go run . --file file.json --query 'COMMAND ...'")
		return
	}
	
	var filename, query string
	for i := 1; i < len(os.Args); i++ {
		if os.Args[i] == "--file" && i+1 < len(os.Args) {
			filename = os.Args[i+1]
			i++
		} else if os.Args[i] == "--query" && i+1 < len(os.Args) {
			query = os.Args[i+1]
			i++
		}
	}
	
	dbms := NewDBMS(filename)
	dbms.executeQuery(query)
}
