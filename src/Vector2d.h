#ifndef Vector2d_H
#define Vector2d_H

#include <stdio.h>
#include <math.h>

class Vector2d{

public:

  Vector2d(float aX, float aY){
    x = aX;
    y = aY;   
  }

  Vector2d(float angle){
    x = cos(angle);
    y = sin(angle);
  }

  ~Vector2d(){};

  float GetNorm(){
    return sqrt(x*x+y*y);
  }

  float GetAngle(){
    return atan2(y,x);
  }
  
  Vector2d * GetPerp(){
    float norm = GetNorm();
    //return new Vector2d(-1.*y / norm, x / norm);
    return new Vector2d(y / norm, -1.*x / norm);
  }

  void Normalize(){
     float norm = GetNorm();
     if(norm != 0.){
       x = x/norm;
       y = y/norm;
     }
  }
  void Print(){
    printf("%f, %f\n", x, y);
  }

  Vector2d* GetCopy(){
    return new Vector2d(x,y);
  }
  
  float GetX(){return x;}
  float GetY(){return y;}
  
  float x;
  float y;

private:

};

Vector2d * AddVectors(Vector2d* a, Vector2d* b){

  float x = a->GetX() + b->x;
  float y = a->y + b->y;
  
  return new Vector2d(x,y);
};

Vector2d * SubtractVectors(Vector2d* a, Vector2d* b){

  float x = a->x - b->x;
  float y = a->y - b->y;
  
  return new Vector2d(x,y);
};

Vector2d * ScalarMultiplyVector(float s, Vector2d* a){
  float x = a->x * s;
  float y = a->y * s;
  
  return new Vector2d(x,y);
};

float DotProduct(Vector2d* a, Vector2d* b){

  float x = a->x * b->x;
  float y = a->y * b->y;
  
  return x+y;
};

Vector2d * ProjectAonB(Vector2d* a, Vector2d*b){

  float mag = DotProduct(a,b);
  Vector2d* projAB = ScalarMultiplyVector(mag,b);
  
  return projAB;
} 

Vector2d * GetAntiParallel(Vector2d* a){
  return ScalarMultiplyVector(-1., a);
}

Vector2d * RotateVector(float ang, Vector2d* a){

  float xPrime = a->x * cos(ang) - a->y * sin(ang);
  float yPrime = a->x * sin(ang) + a->y * cos(ang);

  return new Vector2d(xPrime,yPrime);
};
#endif

