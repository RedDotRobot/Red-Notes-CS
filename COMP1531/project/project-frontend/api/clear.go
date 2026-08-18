package api

import (
	"encoding/json"
	"fmt"
	"net/http"
)

// Clear clears the application state (resets to start)
// No parameters, no response body
func Clear(serverURL string) error {
	req, err := http.NewRequest("DELETE", serverURL+"/clear", nil)
	if err != nil {
		return fmt.Errorf("create request: %w", err)
	}

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
