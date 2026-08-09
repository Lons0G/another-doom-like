#include "isaac-fps/entities/player.hpp"
#include <cmath>
#include <raylib.h>
#include <raymath.h>

namespace {
constexpr float EYE_HEIGHT = 1.7f;
constexpr float PITCH_LIMIT = 89.0f * DEG2RAD;
} // namespace

Player::Player(Vector3 start_pos)
    : _position(start_pos), _movespeed(4.0f), _yaw(0.0f), _pitch(0.0f),
      _mouse_sensitivity(0.0003f) {
  _camera.position = Vector3Add(_position, {0.0f, EYE_HEIGHT, 0.0f});
  _camera.target = Vector3Add(_camera.position, {0.0f, 0.0f, -1.0f});
  _camera.up = {0.0f, 1.0f, 0.0f};
  _camera.fovy = 45.0f;
  _camera.projection = CAMERA_PERSPECTIVE;
}

Player::~Player() {}

Camera Player::GetCamera() const { return _camera; }

void Player::HandleLook() {
  Vector2 mouseDelta = GetMouseDelta();

  _yaw -= mouseDelta.x * _mouse_sensitivity;
  _pitch -= mouseDelta.y * _mouse_sensitivity;

  if (_pitch > PITCH_LIMIT) {
    _pitch = PITCH_LIMIT;
  }
  if (_pitch < -PITCH_LIMIT) {
    _pitch = -PITCH_LIMIT;
  }
}

void Player::HandleMovement() {
  char forward = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
  char sideway = IsKeyDown(KEY_A) - IsKeyDown(KEY_D);

  Vector3 forward_dir = {sinf(_yaw), 0.0f, cosf(_yaw)};
  Vector3 sideway_dir = {cosf(_yaw), 0.0f, -sinf(_yaw)};

  Vector3 moveDir = Vector3Add(Vector3Scale(forward_dir, (float)forward),
                               Vector3Scale(sideway_dir, (float)sideway));
  if (Vector3Length(moveDir) > 0.0f) {
    moveDir = Vector3Normalize(moveDir);
  }

  float delta = GetFrameTime();
  _position = Vector3Add(_position, Vector3Scale(moveDir, _movespeed * delta));
}

void Player::Update() {
  HandleLook();
  HandleMovement();

  _camera.position = Vector3Add(_position, {0.0f, EYE_HEIGHT, 0.0f});

  Vector3 lookDirection = {cosf(_pitch) * sinf(_yaw), sinf(_pitch),
                           cosf(_pitch) * cosf(_yaw)};

  _camera.target = Vector3Add(_camera.position, lookDirection);
}
