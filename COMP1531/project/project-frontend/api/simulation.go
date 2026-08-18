package api

import (
	"bytes"
	"encoding/json"
	"fmt"
	"net/http"
)

// CreateSimulationPayload represents the payload for creating a simulation
type CreateSimulationPayload struct {
	UniverseData UniverseData `json:"universeData"`
}

// SimulationIDResponse represents the response containing a simulation ID
type SimulationIDResponse struct {
	SimulationID int `json:"simulationId"`
}

// CreateSimulation creates a new simulation
func CreateSimulation(serverURL string, session string, payload CreateSimulationPayload) (*SimulationIDResponse, error) {
	jsonData, err := json.Marshal(payload)
	if err != nil {
		return nil, fmt.Errorf("marshal payload: %w", err)
	}

	req, err := http.NewRequest("POST", serverURL+"/simulations", bytes.NewBuffer(jsonData))
	if err != nil {
		return nil, fmt.Errorf("create request: %w", err)
	}
	req.Header.Set("Content-Type", "application/json")
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

	var respData SimulationIDResponse
	if err := json.NewDecoder(resp.Body).Decode(&respData); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &respData, nil
}

// GetSimulation gets the status of a specific simulation
func GetSimulation(serverURL string, session string, simulationID int) (*SimulationStatus, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/simulations/%d", serverURL, simulationID), nil)
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

	var respData SimulationStatus
	if err := json.NewDecoder(resp.Body).Decode(&respData); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &respData, nil
}

// SimulationStatus represents the full status of a simulation
type SimulationStatus struct {
	User           User           `json:"user"`
	AcademicPressure AcademicPressure `json:"academicPressure"`
	Wellbeing      Wellbeing      `json:"wellbeing"`
	SocialOptions  []SocialOption `json:"socialOptions"`
	ExtracurricularOptions []ExtracurricularOption `json:"extracurricularOptions"`
	Risks          []Risk         `json:"risks"`
	Actions        []Action       `json:"actions"`
}

// User represents user information
type User struct {
	StudentID string `json:"studentId"`
	NameFirst string `json:"nameFirst"`
	NameLast  string `json:"nameLast"`
	Energy    int    `json:"energy"`
	Happiness int    `json:"happiness"`
}

// AcademicPressure represents academic pressure data
type AcademicPressure struct {
	PendingExamCount     int    `json:"pendingExamCount"`
	TotalStudyHoursRemaining int    `json:"totalStudyHoursRemaining"`
	Exams                []Exam `json:"exams"`
}

// Exam represents an exam
type Exam struct {
	ExamID           string `json:"examId"`
	CourseID         string `json:"courseId"`
	Name             string `json:"name"`
	StudyHoursCompleted int    `json:"studyHoursCompleted"`
	RequiredStudyHours int    `json:"requiredStudyHours"`
	StudyHoursRemaining int    `json:"studyHoursRemaining"`
}

// Wellbeing represents wellbeing data
type Wellbeing struct {
	Energy        int    `json:"energy"`
	Happiness     int    `json:"happiness"`
	CurrentActivity string `json:"currentActivity"`
}

// SocialOption represents a social option
type SocialOption struct {
	FriendID    int    `json:"friendId"`
	FriendName  string `json:"friendName"`
	FriendScore int    `json:"friendScore"`
	Available   bool   `json:"available"`
}

// ExtracurricularOption represents a club option
type ExtracurricularOption struct {
	ClubID   string `json:"clubId"`
	ClubName string `json:"clubName"`
	Status   string `json:"status"` // INACTIVE or ACTIVE
	Allowed  bool   `json:"allowed"`
	Costs    []string `json:"costs"`
	Benefits []string `json:"benefits"`
}

// Risk represents a risk
type Risk struct {
	Type   string `json:"type"` // ACADEMIC_PRESSURE, LOW_ENERGY, etc.
	Reason string `json:"reason"`
}

// Action represents a possible action
type Action struct {
	Activity   string   `json:"activity"` // STUDYING, SLEEPING, EATING, EXERCISING, HANGOUT
	TargetID   string   `json:"targetId,omitempty"` // Optional, e.g., exam ID for STUDYING
	Allowed    bool     `json:"allowed"`
	Impacts    []string `json:"impacts"`
	Reason     string   `json:"reason"`
}

// ListSimulations lists all simulations for a user
func ListSimulations(serverURL string, session string) (*SimulationListResponse, error) {
	req, err := http.NewRequest("GET", serverURL+"/simulations/list", nil)
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

	var respData SimulationListResponse
	if err := json.NewDecoder(resp.Body).Decode(&respData); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &respData, nil
}

// SimulationListResponse represents the response containing a list of simulations
type SimulationListResponse struct {
	Simulations []SimulationSummary `json:"simulations"`
}

// SimulationSummary represents a summary of a simulation
type SimulationSummary struct {
	SimulationID int    `json:"simulationId"`
	Activity     string `json:"activity"` // DOOM_SCROLLING, STUDYING, etc.
	Energy       int    `json:"energy"`
	Happiness    int    `json:"happiness"`
}

// GetSimulationPlan gets the balanced short-term plan for a simulation
func GetSimulationPlan(serverURL string, session string, simulationID int) (*Plan, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/simulations/%d/plan", serverURL, simulationID), nil)
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

	var respData Plan
	if err := json.NewDecoder(resp.Body).Decode(&respData); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &respData, nil
}

// Plan represents a balanced short-term plan
type Plan struct {
	AcademicPressure AcademicPressure `json:"academicPressure"`
	Wellbeing        Wellbeing        `json:"wellbeing"`
	SocialOptions    []SocialOption   `json:"socialOptions"`
	ExtracurricularOptions []ExtracurricularOption `json:"extracurricularOptions"`
	Risks            []Risk           `json:"risks"`
	Actions          []Action         `json:"actions"`
}

// GetSimulationRecommendation gets a wellbeing recommendation for a simulation
func GetSimulationRecommendation(serverURL string, session string, simulationID int) (*Recommendation, error) {
	req, err := http.NewRequest("GET", fmt.Sprintf("%s/simulations/%d/recommendation", serverURL, simulationID), nil)
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

	var respData Recommendation
	if err := json.NewDecoder(resp.Body).Decode(&respData); err != nil {
		return nil, fmt.Errorf("decode response: %w", err)
	}
	return &respData, nil
}

// Recommendation represents a wellbeing recommendation
type Recommendation struct {
	Action   string `json:"activity"` // DOOM_SCROLLING, STUDYING, etc.
	ExamID   string `json:"examId,omitempty"` // Optional, required when action is STUDYING
	Reason   string `json:"reason"`
	Alternative struct {
		Action string `json:"action"`
		Reason string `json:"reason"`
	} `json:"alternative"`
}

// PerformAction performs an action in a simulation
func PerformAction(serverURL string, session string, simulationID int, payload ActionPayload) error {
	jsonData, err := json.Marshal(payload)
	if err != nil {
		return fmt.Errorf("marshal payload: %w", err)
	}

	req, err := http.NewRequest("POST", fmt.Sprintf("%s/simulations/%d/action", serverURL, simulationID), bytes.NewBuffer(jsonData))
	if err != nil {
		return fmt.Errorf("create request: %w", err)
	}
	req.Header.Set("Content-Type", "application/json")
	req.Header.Set("Session", session)

	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		return fmt.Errorf("send request: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode >= 400 {
		var errorResp ErrorResponse
		if err := json.NewDecoder(resp.Body).Decode(&errorResp); err != nil {
			return fmt.Errorf("request failed with status %d: unable to parse error response", resp.StatusCode)
		}
		return fmt.Errorf("request failed with status %d: %s", resp.StatusCode, errorResp.Message)
	}

	return nil
}

// ActionPayload represents the payload for performing an action
type ActionPayload struct {
	Activity  string `json:"activity"` // STUDYING, SLEEPING, EATING, EXERCISING, HANGOUT
	Duration  int    `json:"duration"` // in minutes
	TargetID  string `json:"targetId,omitempty"` // Required when activity is STUDYING, specifying which exam to study for
}