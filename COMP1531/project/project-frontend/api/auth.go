package api

import (
	"bytes"
	"encoding/json"
	"fmt"
	"net/http"
)

// RegisterPayload represents the payload for user registration
type RegisterPayload struct {
	StudentID string `json:"studentId"`
	Password  string `json:"password"`
	NameFirst string `json:"nameFirst"`
	NameLast  string `json:"nameLast"`
}

// RegisterResponse represents the response from user registration
type RegisterResponse struct {
	Session string `json:"session"`
}

// Register registers a new user
func Register(serverURL string, payload RegisterPayload) (*RegisterResponse, error) {
	jsonData, err := json.Marshal(payload)
	if err != nil {
		return nil, fmt.Errorf("marshal payload: %w", err)
	}

	req, err := http.NewRequest("POST", serverURL+"/auth/register", bytes.NewBuffer(jsonData))
	if err != nil {
		return nil, fmt.Errorf("create request: %w", err)
	}
	req.Header.Set("Content-Type", "application/json")

	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		return nil, fmt.Errorf("send request: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode >= 400 {
		var errorResp ErrorResponse
		if err := json.NewDecoder(resp.Body).Decode(&errorResp); err != nil {
			return nil, fmt.Errorf("request failed with status %d: unable to parse error response", resp.StatusCode)
		}
		return nil, fmt.Errorf("request failed with status %d: %s", resp.StatusCode, errorResp.Message)
	}

	var respData RegisterResponse
	if err := json.NewDecoder(resp.Body).Decode(&respData); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &respData, nil
}

// LoginPayload represents the payload for user login
type LoginPayload struct {
	StudentID string `json:"studentId"`
	Password  string `json:"password"`
}

// LoginResponse represents the response from user login
type LoginResponse struct {
	Session string `json:"session"`
}

// Login logs in a user
func Login(serverURL string, payload LoginPayload) (*LoginResponse, error) {
	jsonData, err := json.Marshal(payload)
	if err != nil {
		return nil, fmt.Errorf("marshal payload: %w", err)
	}

	req, err := http.NewRequest("POST", serverURL+"/auth/login", bytes.NewBuffer(jsonData))
	if err != nil {
		return nil, fmt.Errorf("create request: %w", err)
	}
	req.Header.Set("Content-Type", "application/json")

	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		return nil, fmt.Errorf("send request: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode >= 400 {
		var errorResp ErrorResponse
		if err := json.NewDecoder(resp.Body).Decode(&errorResp); err != nil {
			return nil, fmt.Errorf("request failed with status %d: unable to parse error response", resp.StatusCode)
		}
		return nil, fmt.Errorf("request failed with status %d: %s", resp.StatusCode, errorResp.Message)
	}

	var respData LoginResponse
	if err := json.NewDecoder(resp.Body).Decode(&respData); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &respData, nil
}