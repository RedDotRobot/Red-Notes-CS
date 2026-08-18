package api

import (
	"encoding/json"
	"fmt"
	"net/http"
)

// GetClubList gets the club list of a specific simulation
func GetClubList(serverURL string, session string, simulationID int) ([]Club, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/simulations/%d/clubs", serverURL, simulationID), nil)
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

	var clubs []Club
	if err := json.NewDecoder(resp.Body).Decode(&clubs); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return clubs, nil
}

// GetClubInfo gets detailed information about a specific club
func GetClubInfo(serverURL string, session string, simulationID int, clubID string) (*Club, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/simulations/%d/clubs/%s", serverURL, simulationID, clubID), nil)
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

	var club Club
	if err := json.NewDecoder(resp.Body).Decode(&club); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &club, nil
}

// JoinClub joins a club in a specific simulation
func JoinClub(serverURL string, session string, simulationID int, clubID string) (*Club, error) {
	req, err := http.NewRequest("POST", fmt.Sprintf("%s/simulations/%d/clubs/%s/join", serverURL, simulationID, clubID), nil)
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

	var club Club
	if err := json.NewDecoder(resp.Body).Decode(&club); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &club, nil
}

// LeaveClub leaves a club in a specific simulation
func LeaveClub(serverURL string, session string, simulationID int, clubID string) (*Club, error) {
	req, err := http.NewRequest("POST", fmt.Sprintf("%s/simulations/%d/clubs/%s/leave", serverURL, simulationID, clubID), nil)
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

	var club Club
	if err := json.NewDecoder(resp.Body).Decode(&club); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &club, nil
}

// Club represents a club
type Club struct {
	ClubID          string  `json:"clubId"`
	ClubName        string  `json:"clubName"`
	Status          string  `json:"status"` // INACTIVE or ACTIVE
	JoinEnergyCost  float64 `json:"joinEnergyCost"`
	EnergyCostPerHour float64 `json:"energyCostPerHour"`
	HappinessGainPerHour float64 `json:"happinessGainPerHour"`
	CourseID        string  `json:"courseId"`
	StudyHourGainPerHour float64 `json:"studyHourGainPerHour"`
}