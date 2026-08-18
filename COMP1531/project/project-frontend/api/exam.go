package api

import (
	"encoding/json"
	"fmt"
	"net/http"
)

// ListExams lists all exams for a given simulation
func ListExams(serverURL string, session string, simulationID int) ([]Exam, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/simulations/%d/exam", serverURL, simulationID), nil)
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

	var exams []Exam
	if err := json.NewDecoder(resp.Body).Decode(&exams); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return exams, nil
}

// GetExamInfo gets detailed information about a specific exam
func GetExamInfo(serverURL string, session string, simulationID int, examID string) (*Exam, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/simulations/%d/exams/%s", serverURL, simulationID, examID), nil)
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

	var exam Exam
	if err := json.NewDecoder(resp.Body).Decode(&exam); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &exam, nil
}

// AttemptExam attempts an exam in the specified simulation
func AttemptExam(serverURL string, session string, simulationID int, examID string) (*ExamAttempt, error) {
	req, err := http.NewRequest("POST", fmt.Sprintf("%s/simulations/%d/exams/%s/attempt", serverURL, simulationID, examID), nil)
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

	var examAttempt ExamAttempt
	if err := json.NewDecoder(resp.Body).Decode(&examAttempt); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &examAttempt, nil
}

// ExamAttempt represents the result of an exam attempt
type ExamAttempt struct {
	ExamID    string `json:"examId"`
	ExamResult string `json:"examResult"` // PASSED or FAILED
}

// GetExamReadiness explains academic readiness for a specific exam
func GetExamReadiness(serverURL string, session string, simulationID int, examID string) (*ExamReadiness, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/simulations/%d/exams/%s/readiness", serverURL, simulationID, examID), nil)
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

	var examReadiness ExamReadiness
	if err := json.NewDecoder(resp.Body).Decode(&examReadiness); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &examReadiness, nil
}

// ExamReadiness represents the academic readiness for an exam
type ExamReadiness struct {
	ExamID       string `json:"examId"`
	Readiness    string `json:"readiness"` // HIGH, MEDIUM, LOW
	ReadinessScore int    `json:"readinessScore"` // 0-100
	Explanation  string `json:"explanation"`
}