package api

import (
	"encoding/json"
	"fmt"
	"net/http"
)

// ListFriends lists all possible friends for a given simulation
func ListFriends(serverURL string, session string, simulationID int) ([]Friend, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/simulations/%d/friends", serverURL, simulationID), nil)
	if err != nil {
		return nil, fmt.Errorf("create request: %w", err)
	}
	req.Header.Set("Session", session)

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

	var friends []Friend
	if err := json.NewDecoder(resp.Body).Decode(&friends); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return friends, nil
}

// GetFriendInfo gets detailed information about a specific friend
func GetFriendInfo(serverURL string, session string, simulationID int, friendID int) (*Friend, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/simulations/%d/friends/%d", serverURL, simulationID, friendID), nil)
	if err != nil {
		return nil, fmt.Errorf("create request: %w", err)
	}
	req.Header.Set("Session", session)

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

	var friend Friend
	if err := json.NewDecoder(resp.Body).Decode(&friend); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &friend, nil
}

// AddFriend adds a friend to the student's social network
func AddFriend(serverURL string, session string, simulationID int, friendID int) (*Friend, error) {
	req, err := http.NewRequest("PUT", fmt.Sprintf("%s/simulations/%d/friends/%d", serverURL, simulationID, friendID), nil)
	if err != nil {
		return nil, fmt.Errorf("create request: %w", err)
	}
	req.Header.Set("Session", session)

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

	var friend Friend
	if err := json.NewDecoder(resp.Body).Decode(&friend); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &friend, nil
}

// RemoveFriend removes a friend from the student's social network
func RemoveFriend(serverURL string, session string, simulationID int, friendID int) (*Friend, error) {
	req, err := http.NewRequest("DELETE", fmt.Sprintf("%s/simulations/%d/friends/%d", serverURL, simulationID, friendID), nil)
	if err != nil {
		return nil, fmt.Errorf("create request: %w", err)
	}
	req.Header.Set("Session", session)

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

	var friend Friend
	if err := json.NewDecoder(resp.Body).Decode(&friend); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &friend, nil
}

// Friend represents a friend
type Friend struct {
	FriendID     int    `json:"friendId"`
	FriendName   string `json:"friendName"`
	FriendScore  int    `json:"friendScore"`
	FriendHappinessBonus int    `json:"friendHappinessBonus"`
	FriendIntelligenceBonus int    `json:"friendIntelligenceBonus"`
	FriendEnergyDrain  int    `json:"friendEnergyDrain"`
}