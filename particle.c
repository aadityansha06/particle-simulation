#include "raylib.h"
#include <math.h>
#include <time.h>

#define width 1000
#define height 650
#define Particle_NUM 150
#define Gravity 0.2

typedef struct
{
  float x, y;
  float r, vx, vy;

} circle;

circle particles[Particle_NUM];

void initParticle()
{
  SetRandomSeed(time(NULL));

  for (int i = 0; i < Particle_NUM; i++)
  {
    float radius = GetRandomValue(20.00f, 25.00f);
    particles[i].x = GetRandomValue(radius, width);
    particles[i].y = GetRandomValue(radius, height);
    particles[i].r = radius;
    particles[i].vx = GetRandomValue(2, 4);
    particles[i].vy = GetRandomValue(2, 4);
  }
}

void DrawParticles()
{
  for (int i = 0; i < Particle_NUM; i++)
  {
    DrawCircle(particles[i].x, particles[i].y, particles[i].r, WHITE);
  }
}

static void WallDetect()
{
  for (int i = 0; i < Particle_NUM; i++)
  {
    if (particles[i].x >= width || particles[i].x <= 0)
    {
      // changing velocity direction which effectively changes the position
      particles[i].vx = particles[i].vx * -1.0f;
    }
    if (particles[i].y >= height)
    {
      particles[i].y = height - particles[i].r;
      particles[i].vy *= -0.5f;
    }
    if (particles[i].y <= 0)
    {
      // adding constant value i.e. it's radius to move it down with that much value
      particles[i].y = particles[i].r;
      particles[i].vy *= -0.5f;
    }
  }
}

void moveParticles()
{
  for (int i = 0; i < Particle_NUM; i++)
  {
    particles[i].vy += Gravity;

    particles[i].vx *= 0.99f;
    particles[i].vy *= 0.99f;

    particles[i].x += particles[i].vx;
    particles[i].y += particles[i].vy;
    WallDetect();
  }

  // particle collision detection
  for (int i = 0; i < Particle_NUM; i++)
  {
    for (int j = i + 1; j < Particle_NUM - 1; j++)
    {
      // calculating distance between two particles using distance formula
      int x1 = particles[i].x;
      int x2 = particles[j].x;
      int y1 = particles[i].y;
      int y2 = particles[j].y;
      float sum = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
      float distance = sum;
      float dx = particles[j].x - particles[i].x;
      float dy = particles[j].y - particles[i].y;
      // calculating sum of both radii
      float radii_sum = particles[i].r + particles[j].r;
      float distanceSq = (dx * dx) + (dy * dy);

      // detecting collision if distance is <= their radii sum
      if (distance <= radii_sum * radii_sum)
      {
        float tempVx = particles[i].vx;
        float tempVy = particles[i].vy;

        // swapping the momentum
        particles[i].vx = particles[j].vx;
        particles[i].vy = particles[j].vy;

        particles[j].vx = tempVx;
        particles[j].vy = tempVy;

        // collision resolution
        float angle = atan2f(dy, dx);
        float overlap = radii_sum - sqrtf(distanceSq);

        // Move particle j slightly away
        particles[j].x += cosf(angle) * overlap;
        particles[j].y += sinf(angle) * overlap;
        particles[j].vy -= 0.02f;
        WallDetect();
      }
    }
  }

  // Drag mouse effect
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
  {
    Vector2 mouse = GetMousePosition();

    for (int i = 0; i < Particle_NUM; i++)
    {
      float ax = mouse.x - particles[i].x;
      float ay = mouse.y - particles[i].y;
      particles[i].vx += ax * 0.005f;
      particles[i].vy += ay * 0.005f;
    }
    WallDetect();
  }
}

int main(void)
{
  InitWindow(width, height, "raylib [core] example - basic window");

  initParticle();
  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();

    // DrawFPS(0, 30);
    ClearBackground(BLACK);
    DrawParticles();

    moveParticles();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
