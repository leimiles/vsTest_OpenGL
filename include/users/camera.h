#pragma once

#include "./glm/glm.hpp"
#include "./glm/gtc/matrix_transform.hpp"

class camera
{
public:
	camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	~camera();

	glm::vec3 position;							// ���λ��
	glm::vec3 forward;							// �����������
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;							// ����ռ�Y��
	//glm::vec3 cameraTrans;
	float pitch;								// ��ֱ��ת
	float yaw;									// ˮƽ��ת
	float senseX = 0.001f;					// ���ˮƽ���ж�
	float senseY = 0.001f;					// ��괹ֱ���ж�
	float maxPitch = glm::radians(89.0f);		// ��ֱ��ת��ֵ
	float minPitch = glm::radians(-89.0f);
	//float cameraRotate = 0;
	float zoom = -3;						// ������
	float speedZ = 0;						// ����������ж�

	glm::mat4 get_ViewMatrix();
	void process_MouseMovement(float deltaX, float deltaY);
	void update_CameraPosition();

private:
	void update_CameraVectors();
};

