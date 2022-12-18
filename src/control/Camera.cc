// #include "Camera.h"

// glm::mat4 view, proj;
// static glm::vec3 direction, up, right;
// static float pitch, yaw, fov, aspect, znear, zfar;

// void Camera::startup(float fov_) {
//     fov = fov_;
//     aspect = Window::ratio();
//     znear = 0.01f;
//     zfar = 800.0f;
//     yaw = 0.0f;
//     pitch = 0.0f;

//     glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
// }

// const glm::vec3 & Camera::Right() { return right; }
// const glm::vec3 & Camera::Direction() { return direction; }

// void Camera::handle_mouse(float dx, float dy, float delta_time) {

//   dx *= MOUSE_SENSE * delta_time;
//   dy *= MOUSE_SENSE * delta_time;

//   yaw += dx;
//   pitch += dy;
// }

// void Camera::Update(const glm::vec3 & position) {
//     pitch = saturate(pitch, -PI_2+0.1f, PI_2-0.1f);

//     yaw = (yaw < 0 ? TAU : 0.0f) + fmodf(yaw, TAU);

//     direction = {cosf(pitch) * sinf(yaw), sinf(pitch), cosf(pitch) * cosf(yaw) };
//     direction = glm::normalize(direction);

//     right = glm::cross({ 0.0f, 1.0f, 0.0f }, direction);
//     up = glm::cross(direction, right);

//     auto pos = position;
//     //pos.z += 100.0f;
//     //pos.y += 100.0f;

//     view = glm::lookAt(pos, pos + direction, up);
//     proj = glm::perspective(fov, aspect, znear, zfar);


//     Resource::useShader(ShaderEnum::BASIC)
//                 .setUniform("view", view)
//                 .setUniform("projection", proj);
// }

// void Camera::wrap_coords(float ix, float iy, float& ox, float& oy) {
//     static float max_offset_x = BLOCK_WIDTH * GAME_WIDTH - WINDOW_WIDTH / 2;
//     static float max_offset_y = BLOCK_HEIGHT * GAME_HEIGHT - WINDOW_HEIGHT / 2;
//     if (ix < WINDOW_WIDTH / 2) ox = WINDOW_WIDTH / 2;
//     if (iy < WINDOW_HEIGHT / 2) oy = WINDOW_HEIGHT / 2;
//     if (ix > max_offset_x) ox = max_offset_x;
//     if (iy > max_offset_y) oy = max_offset_y;
// }