package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
	"strings"
)

func main() {
	// Connect to the server
	conn, err := net.Dial("tcp", "0.0.0.0:8080")
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error connecting to server: %v\n", err)
		return
	}
	defer func() {
		fmt.Println("Closing connection...")
		conn.Close()
	}()

	fmt.Println("Connected to the server. Type your message and press Enter. Type 'exit' to disconnect:")

	// Channel to handle server messages
	go func() {
		serverReader := bufio.NewReader(conn)
		for {
			serverMessage, err := serverReader.ReadString('\n')
			if err != nil {
				fmt.Println("\nDisconnected from server.")
				os.Exit(0) // Exit the program if the server disconnects
			}
			fmt.Print("Server: " + serverMessage)
		}
	}()

	// Main loop to send messages to the server
	reader := bufio.NewReader(os.Stdin)
	for {
		fmt.Print("You: ")
		clientMessage, err := reader.ReadString('\n')
		if err != nil {
			fmt.Fprintf(os.Stderr, "Error reading input: %v\n", err)
			continue
		}

		// Trim message to remove extra whitespace
		clientMessage = strings.TrimSpace(clientMessage)

		// Exit if user types "exit"
		if clientMessage == "exit" {
			fmt.Println("Disconnecting...")
			break
		}

		// Send message to the server
		_, err = conn.Write([]byte(clientMessage + "\n"))
		if err != nil {
			fmt.Fprintf(os.Stderr, "Error sending message: %v\n", err)
			break
		}
	}
}
