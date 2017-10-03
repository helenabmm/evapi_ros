#ifndef INCLUDE_EVAROBOT_CONTROLLER_H_
#define INCLUDE_EVAROBOT_CONTROLLER_H_



#include <diagnostic_updater/diagnostic_updater.h>
#include <diagnostic_updater/publisher.h>

#include <stdio.h>
#include <stdlib.h>

#include <ros/console.h>
#include <realtime_tools/realtime_publisher.h>

#include <string>
#include <sstream>

#include "ros/ros.h"


#include "geometry_msgs/PointStamped.h"
#include "geometry_msgs/Twist.h"

#include "std_srvs/Empty.h"
#include "im_msgs/WheelVel.h"

#include "nav_msgs/Odometry.h"

#include <ErrorCodes.h>


float g_f_left_desired = 0.0;
float g_f_right_desired = 0.0;

float g_f_linear_desired = 0.0;
float g_f_angular_desired = 0.0;

float g_f_left_measured = 0.0;
float g_f_right_measured = 0.0;

float g_f_linear_measured = 0.0;
float g_f_angular_measured = 0.0;

double g_d_wheel_separation;
bool b_is_received_params = false;

bool b_reset_controller = false;

using namespace std;

double g_d_p_1;
double g_d_i_1;
double g_d_d_1;
double g_d_w_1;

double g_d_p_2;
double g_d_i_2;
double g_d_d_2;
double g_d_w_2;

double g_d_dt = 0.0;

int g_i_controller_type;

class PIDController {
 public:
  PIDController();
  PIDController(double d_proportional_constant,
                double d_integral_constant,
                double d_derivative_constant,
		double d_windup_constant,
                double _d_max_vel,
                string _str_name);
  void UpdateParams(double d_proportional_constant,
                    double d_integral_constant,
                    double d_derivative_constant,
		    double d_windup_constant);
  void ProduceDiagnostics(
      diagnostic_updater::DiagnosticStatusWrapper &stat);

  ~PIDController();

  float RunController(float f_desired, float f_measured);
  void Reset();

 private:
  double d_integral_error;
  double d_derivative_error;
  double d_proportional_error;
  double d_windup_error;
  double d_pre_error;

  double d_integral_constant;
  double d_derivative_constant;
  double d_proportional_constant;
  double d_windup_constant;

  float f_filtered_data_pre;
  string str_name;

  double d_max_vel;

  ros::Time read_time;
  ros::Duration dur_time;
};

#endif  // INCLUDE_EVAROBOT_CONTROLLER_H_
