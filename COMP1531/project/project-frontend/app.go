package main

import (
	"fmt"
	"log"

	"test/man/api"
)

func main() {
	payload := api.RegisterPayload{
		StudentID: "z5763342",
		Password:  "password123",
		NameFirst: "Lucas",
		NameLast:  "Cheung",
	}

	resp, err := api.Register("http://localhost:3200", payload)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("Status: 200 OK") // Assuming success since no error
	fmt.Printf("Response: %+v\n", resp)
}
