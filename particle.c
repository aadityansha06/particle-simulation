#include "raylib.h"
#include <math.h>
#include <time.h>

#define width 1000
#define height 650
#define Particle_NUM 50
#define Gravity 0.2

typedef struct{
    int x,y;
    float r,vx,vy;
    

}circle;

circle particles[Particle_NUM];

void Drawparticles(){

  for (int i =0 ; i<Particle_NUM; i++) {
   DrawCircle(particles[i].x,particles[i].y,particles[i].r,WHITE);

  }

     
}

static void Walldetact(){
   for (int i=0; i<Particle_NUM; i++) {
   
    
   if (particles[i].x>=width|| particles[i].x<=0){
        particles[i].vx = particles[i].vx *  -1.0f;    
    }
   if( particles[i].y>=height){
      particles[i].y = height - particles[i].r; // Snap it to the floor
    particles[i].vy *= -0.5f;

    }if( particles[i].y<=0){
                particles[i].vy *= -0.5f;
    }
   }
}

void moveParticles(){
       
   for (int i =0 ; i<Particle_NUM; i++) {
        particles[i].vy +=Gravity;

        particles[i].vx *= 0.99f;
      particles[i].vy *= 0.99f;

       particles[i].x += particles[i].vx;  
      particles[i].y += particles[i].vy;  
         Walldetact();                              


   }

   // particle collison detection 
   
   for (int i =0 ;i<Particle_NUM; i++){
       for (int j=i+1; j<Particle_NUM-1;j++) {
             //  calcucalting distance between two particles using distance formula 
           int x1 = particles[i].x;
           int x2 = particles[j].x;
           int y1 = particles[i].y;
           int y2 = particles[j].y;
           float sum = (x2-x1)*(x2-x1) + (y2-y1) * (y2-y1);
           float distance = sqrtf(sum);
           float dx = particles[j].x - particles[i].x;
            float dy = particles[j].y - particles[i].y; 
           //calculating sum of both radii 
            float radii_sum = particles[i].r + particles[j].r;
            float distanceSq = (dx*dx) + (dy*dy); // No Sqrt needed! Faster.

            float radiiSum = particles[i].r + particles[j].r;
            
        // detecting collison if distance is <= theri radii sum
        if (distance<=radii_sum){
      float tempVx = particles[i].vx;
                float tempVy = particles[i].vy;

                particles[i].vx = particles[j].vx;
                particles[i].vy = particles[j].vy;

                particles[j].vx = tempVx;
                particles[j].vy = tempVy;
                float angle = atan2f(dy, dx);
                float overlap = radiiSum - sqrtf(distanceSq);
                
                // Move particle j slightly away
                particles[j].x += cosf(angle) * overlap;
                particles[j].y += sinf(angle) * overlap;
              Walldetact();   
          // particles[j].vy -= 0.02f;   

         }
            }
   
   }

   // Drag mouse effect
   if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
       Vector2 mouse = GetMousePosition();

    for (int i=0; i<Particle_NUM; i++) {
        float ax = mouse.x - particles[i].x;
       float ay = mouse.y - particles[i].y; 
        particles[i].vx += ax * 0.005f;
        particles[i].vy += ay * 0.005f;
    }
          Walldetact();   
    }

   // adding air resistence
 /*   for (int i=0; i<Particle_NUM; i++) {
        //float ax = mouse.x - particles[i].x;
      // float ay = mouse.y - particles[i].y; 
        particles[i].vx += 0.1f;
        particles[i].vy += 0.1f;
    }
*/
   // adding gravity

}

void initparticle(){

SetRandomSeed(time(NULL));

float radius = GetRandomValue(10.00f, 15.00f);
 for (int i=0; i<Particle_NUM; i++) {
    
   particles[i].x = GetRandomValue(radius,width);
    particles[i].y = GetRandomValue(radius, height);
    particles[i].r  = radius;
  particles[i].vx = GetRandomValue(2, 4);
   particles[i].vy = GetRandomValue(2, 4);

 }

}

int main(void)
{
    InitWindow(width, height, "raylib [core] example - basic window");

  // circle c;
  initparticle();
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
    
     //  DrawFPS(0, 30);
       ClearBackground(BLACK);
       Drawparticles();

        moveParticles();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
