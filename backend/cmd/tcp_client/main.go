package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
)

func main() {
	// Server address and port
	ip := "100.89.98.125"
	port := "80"
	address := ip + ":" + port

	conn, err := net.Dial("tcp", address)
	if err != nil {
		fmt.Println("Error connecting:", err)
		return
	}
	defer conn.Close()

	fmt.Println("Connected to server at", address)

	// Send message to server
	fmt.Print("Enter message: ")
	reader := bufio.NewReader(os.Stdin)
	message, _ := reader.ReadString('\n')
	_, err = conn.Write([]byte(message))
	if err != nil {
		fmt.Println("Error sending message:", err)
		return
	}

	// Receive response from server
	reply := make([]byte, 1024)
	_, err = conn.Read(reply)
	if err != nil {
		fmt.Println("Error receiving reply:", err)
		return
	}

	fmt.Println("Server reply:", string(reply))
}
