package api

import (
	"encoding/json"
	"fmt"
	"net/http"
)

// ListInternships lists all internships for a given simulation
func ListInternships(serverURL string, session string, simulationID int) ([]Internship, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/simulations/%d/internships", serverURL, simulationID), nil)
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

	var internships []Internship
	if err := json.NewDecoder(resp.Body).Decode(&internships); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return internships, nil
}

// GetInternshipInfo gets detailed information about a specific internship
func GetInternshipInfo(serverURL string, session string, simulationID int, internshipID string) (*Internship, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/simulations/%d/internships/%s", serverURL, simulationID, internshipID), nil)
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

	var internship Internship
	if err := json.NewDecoder(resp.Body).Decode(&internship); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &internship, nil
}

// ApplyInternship applies for an internship in a specific simulation
func ApplyInternship(serverURL string, session string, simulationID int, internshipID string) (*Internship, error) {
	req, err := http.NewRequest("PUT", fmt.Sprintf("%s/simulations/%d/internships/%s/apply", serverURL, simulationID, internshipID), nil)
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

	var internship Internship
	if err := json.NewDecoder(resp.Body).Decode(&internship); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &internship, nil
}

// Internship represents an internship
type Internship struct {
	InternshipID   string   `json:"internshipId"`
	CompanyName    string   `json:"companyName"`
	RequiredCourses []string `json:"requiredCourses"`
	TotalTime      int      `json:"totalTime"`
	InternshipStatus string `json:"internshipStatus"` // e.g., "AVAILABLE", "APPLIED"
}