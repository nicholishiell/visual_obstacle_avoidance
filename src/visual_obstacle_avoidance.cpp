#include "ros/ros.h"

#include "bupimo_msgs/Blob.h"
#include "bupimo_msgs/BlobArray.h"
#include "bupimo_msgs/VelocityCommand.h"

#include "std_msgs/Float64.h"

#include "Vector2d.h"

#include <stdio.h>
#include <string>

using namespace std;

// Global Variables
float currentHeading = 0.;
float currentLinearVel = 0.;

bool firstBlobs = false;

bool blobBeyondThreshold = false;
float bearingToObstacle = 0.;

float proximityThreshold = 235.;

void BlobBearingsCallback(const bupimo_msgs::BlobArray::ConstPtr& msg){
   
  // Get number of blobs detected
  int nBlobs = msg->blobArray.size();
  
  float minDist = 99999.;

  blobBeyondThreshold = false;
  
  for(int i = 0; i < nBlobs; i++){
    firstBlobs = true;
    
    float blobBearing = msg->blobArray[i].bearing;
    float blobX = msg->blobArray[i].x;
    float blobY = msg->blobArray[i].y;

    float blobDist = sqrt(blobX*blobX + blobY*blobY);
    
    if(blobDist < minDist){
      minDist = blobDist;
      bearingToObstacle = blobBearing;
    }    

  }

  if(minDist < proximityThreshold){
    blobBeyondThreshold = true;
  }

  
}

int main(int argc, char **argv){
  ros::init(argc, argv, "visual_obstacle_avoidance");

  ros::NodeHandle n;
 
  ros::Publisher command_pub = n.advertise<bupimo_msgs::VelocityCommand>("obstacleAvoidanceBehaviour", 1000);

  //ros::Subscriber blob_Sub = n.subscribe("blobsGlobal", 1000, BlobBearingsCallback);
  ros::Subscriber blob_Sub = n.subscribe("blobsLocal", 1000, BlobBearingsCallback);  

  ros::Rate loop_rate(25);
  
  while (ros::ok()){
    float targetHeading = 0.;
    float targetLinearVel = 0.; 
    bupimo_msgs::VelocityCommand msg;
    
    if(!firstBlobs){
      printf("Waiting for first blob...\n");
      ros::spinOnce();
      loop_rate.sleep();
      continue;
    }

    if(blobBeyondThreshold){    
      // Travel tangential to the obstacle
      if(bearingToObstacle < 0.) targetHeading = bearingToObstacle - 100.;
      else targetHeading = bearingToObstacle + 100.;
      targetLinearVel = 1.; 
    }
    else{
      targetHeading = 0.;
      targetLinearVel = 0.;  
    }

    msg.bearing = targetHeading;
    msg.linearSpeed = targetLinearVel;
    
    command_pub.publish(msg);
    
    //printf("%f\t%f\t%f\n", dot, msg.linear.x, msg.angular.z);
    //printf("~~~~~~~~~~~~~~~~~~~~~~~\n");
    //getchar();
    
    ros::spinOnce();

    loop_rate.sleep();
  }
  return 0;
};
