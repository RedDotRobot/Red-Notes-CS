package api

// ErrorResponse represents an error response from the API
type ErrorResponse struct {
	Error   string `json:"error"`
	Message string `json:"message"`
}

// UniverseExam represents an exam in the universe data (without progress fields)
type UniverseExam struct {
	ExamID   string `json:"examId"`
	CourseID string `json:"courseId"`
	Name     string `json:"name"`
	RequiredStudyHours int `json:"requiredStudyHours"`
}

// UniverseData represents the universe configuration for creating a simulation
type UniverseData struct {
	Courses        []Course        `json:"courses"`
	Exams          []UniverseExam  `json:"exams"`
	Friends        []Friend        `json:"friends"`
	Internships    []Internship    `json:"internships"`
	Clubs          []Club          `json:"clubs"`
}