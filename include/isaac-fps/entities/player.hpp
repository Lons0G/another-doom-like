#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

class Player {
public:
  Player(Vector3 start_pos);
  ~Player();

  void Update();
  Camera GetCamera() const;

private:
  void HandleMovement();
  void HandleLook();

  Camera _camera;
  Vector3 _position;
  float _movespeed;

  float _yaw;
  float _pitch;
  float _mouse_sensitivity;
};

#endif // !PLAYER_HPP
