#include <glad/glad.h>
#include <glm/glm.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
	// Camera attribute
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// Euler Angles
	float Yaw;
	float Pitch;

	// Cam options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	
	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	// Return view matrix calculated using Euler Angles and LookAt matrix
	glm::mat4 GetViewMatrix();

	// Accepts input parameter in the form of camera defined ENUM(to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	// Expects the offset value in both the x and y direction
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

	// Only requires input on the vertical wheel - axis
	void ProcessMouseScroll(float yoffset);

private:
	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors();
};
