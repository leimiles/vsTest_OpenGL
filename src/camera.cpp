#include "camera.h"

camera::camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	position	= position;
	worldUp		= worldup;
	forward		= glm::normalize(target - position);
	right		= glm::normalize(glm::cross(forward, worldUp));
	up			= glm::normalize(glm::cross(forward, right));
}

camera::camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	position	= position;
	worldUp		= worldup;
	pitch		= pitch;
	yaw			= yaw;
	forward.x	= glm::cos(pitch) * glm::sin(yaw);
	forward.y	= glm::sin(pitch);
	forward.z	= glm::cos(pitch) * glm::cos(yaw);
	right		= glm::normalize(glm::cross(forward, worldUp));
	up			= glm::normalize(glm::cross(forward, right));
}

camera::~camera()
{

}
	
glm::mat4 camera::get_ViewMatrix()						// 获得ViewMatrix
{														
	glm::mat4 viewMat;
	//viewMat = glm::translate(viewMat, cameraTrans) * glm::lookAt(Position, Position + Forward, WorldUp);
	viewMat = glm::lookAt(position, position + forward, worldUp);
	return viewMat;
}

void camera::update_CameraVectors()						// 更新相机的朝向
{													
	forward.x	= glm::cos(Pitch) * glm::sin(Yaw);
	forward.y	= glm::sin(Pitch);
	forward.z	= glm::cos(Pitch) * glm::cos(Yaw);
	right		= glm::normalize(glm::cross(forward, WorldUp));
	up			= glm::normalize(glm::cross(forward, right));
	position.x	= forward.x * zoom;
	position.y	= forward.y * zoom;
	position.z	= forward.z * zoom;
}

void camera::process_MouseMovement(float deltaX, float deltaY)
{							// 更新相机视角的旋转
	pitch	-= deltaY * senseY;
	yaw		-= deltaX * senseX;
	if (pitch > maxPitch)
		pitch = maxPitch;
	if (pitch < minPitch)
		pitch = minPitch;
	update_CameraPosition();
}

void camera::update_CameraPosition()					// 更新相机深度
{													
	zoom		+= speedZ * 0.1f;
	position	+= forward * speedZ * 0.1f;
	position	= glm::vec4(position, 1.0);
	speedZ		= 0;
	//glm::mat4 cameraRotMat;
	//cameraRotMat = glm::rotate(cameraRotMat, glm::radians(-cameraRotate), glm::vec3(0, 1.0, 0));
	//Position = cameraRotMat * glm::vec4(Position, 1.0);
}
