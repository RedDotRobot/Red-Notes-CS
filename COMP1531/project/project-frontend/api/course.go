package api

import (
	"encoding/json"
	"fmt"
	"net/http"
)

// ListCourses lists all courses for a given simulation
func ListCourses(serverURL string, session string, simulationID int) ([]Course, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/courses/%d", serverURL, simulationID), nil)
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

	var courses []Course
	if err := json.NewDecoder(resp.Body).Decode(&courses); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return courses, nil
}

// GetCourseInfo gets detailed information about a specific course
func GetCourseInfo(serverURL string, session string, simulationID int, courseID string) (*Course, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/courses/%d/%s", serverURL, simulationID, courseID), nil)
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

	var course Course
	if err := json.NewDecoder(resp.Body).Decode(&course); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &course, nil
}

// Course represents a course
type Course struct {
	CourseID string `json:"courseId"`
	Name     string `json:"name"`
}