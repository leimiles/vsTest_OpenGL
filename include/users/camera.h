#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class camera
{
public:
	camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	~camera();

	glm::vec3 position;							// 相机位置
	glm::vec3 forward;							// 相机的三个轴
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;							// 世界空间Y轴
	//glm::vec3 cameraTrans;
	float pitch;								// 垂直旋转
	float yaw;									// 水平旋转
	float senseX	= 0.001f;					// 鼠标水平敏感度
	float senseY	= 0.001f;					// 鼠标垂直敏感度
	float maxPitch	= glm::radians(89.0f);		// 垂直旋转阈值
	float minPitch	= glm::radians(-89.0f);
	//float cameraRotate = 0;
	float zoom		= -3;						// 相机深度
	float speedZ	= 0;						// 相机景深敏感度

	glm::mat4 get_ViewMatrix();
	void process_MouseMovement(float deltaX, float deltaY);
	void update_CameraPosition();

private:
	void update_CameraVectors();
};

