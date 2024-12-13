#pragma once
#include <string>
#include <vector>
#include <numeric>
#include <iterator>
#include <limits>
#include <rclcpp/rclcpp.hpp>

using namespace std;

/* ------------------ Struct ------------------------*/

// Pitch dimension information
//�洢�����򳡳ߴ���صĸ��ֲ���ֵ
struct FieldDimensions
{
    double length;            // The length of the pitch.
    double width;             // The width of the pitch.
    double penaltyDist;       // The straight-line distance from the penalty spot to the bottom line.
    double goalWidth;         // The width of the goal.
    double circleRadius;      // The radius of the center circle.
    double penaltyAreaLength; // The length of the penalty area.
    double penaltyAreaWidth;  // The width of the penalty area.
    double goalAreaLength;    // The length of the goal area.
    double goalAreaWidth;     // The width of the goal area.
                              // Note: The penalty area is larger than the goal area; the actual lengths and widths of the penalty area and the goal area are smaller. This naming is to be consistent with the competition rules.
};
const FieldDimensions FD_KIDSIZE{9, 6, 1.5, 2.6, 0.75, 2, 5, 1, 3};
const FieldDimensions FD_ADULTSIZE{14, 9, 2.1, 2.6, 1.5, 3, 6, 1, 4};

// Pose2D, used to record a point on a plane and its orientation
//�ڶ�άƽ���ϼ�¼һ�����λ�úͷ���
struct Pose2D
{
    double x = 0;
    double y = 0;
    double theta = 0; // rad, counterclockwise is positive starting from the positive direction of the x-axis.
};

// Point, used to record a three-dimensional point
//��ά�ռ��һ����
struct Point
{
    double x;
    double y;
    double z;
};

// Point2D, used to record a two-dimensional point
struct Point2D
{
    double x;
    double y;
};

// BoundingBox
/*���ڱ�ʾ��ά�ռ��е�һ���߽��
�߽��ͨ�����ڼ�����Ӿ��У�������һ����������
�������ڱ��ͼ���еĶ��󡢲ü��������ж����⡣*/
struct BoundingBox
{
    double xmin;
    double xmax;
    double ymin;
    double ymax;
};

/// GameObject, used to store the information of important entities in the game, such as Ball, Goalpost, etc. Compared with the detection::DetectedObject in the /detect message, it has more abundant information.
/*string label;����ʶ����ʶ��Ϊ����ʵ��ı�ǩ��

BoundingBox boundingBox;��������ж����ʶ��������Ͻ�Ϊԭ�㣬x���������ӣ�y���������ӡ�

Point2D precisePixelPoint;������ľ�ȷ���ص�λ�á�ֻ�е���ر�����������ݡ�

double confidence;��ʶ������Ŷȡ�

Point posToRobot;�������ڻ���������ϵ�е�λ�á����λ���Ƕ�ά�ģ�������zֵ��

string info;�����ڴ洢������Ϣ���ַ��������磬�������������������Դ洢���ĸ���������

Point posToField;�������ڳ�������ϵ�е�λ�á����λ���Ƕ�ά�ģ�������zֵ��x����ǰ��y������

double range;�����󵽻������ڳ���ƽ���ϵ�ͶӰ���ֱ�߾��롣

double pitchToRobot, yawToRobot;����������ڻ�����ǰ���ĸ����Ǻ�ƫ���ǣ���λΪ���ȡ����º�����Ϊ����

rclcpp::Time timePoint;�����󱻼�⵽��ʱ��㡣*/
struct GameObject
{
    // --- Obtained from the /detect message ---
    string label;              // What the object is identified as.
    BoundingBox boundingBox;   // The recognition box of the object in the camera, with the upper left corner as the origin, x increasing to the right and y increasing downward.
    Point2D precisePixelPoint; // The precise pixel point position of the object. Only ground landmark points have this data.
    double confidence;         // The confidence of the identification.
    Point posToRobot;          // The position of the object in the robot's body coordinate system. The position is 2D, ignoring the z value.

    // --- Calculated and obtained in the processDetectedObject function ---
    string info;                     // Used to store additional information. For example, for a goalpost object, it can store which goalpost it is.
    Point posToField;                // The position of the object in the field coordinate system. The position is 2D, ignoring the z value. x is forward and y is leftward.
    double range;                    // The straight-line distance from the object to the projection point of the robot's center on the field plane.
    double pitchToRobot, yawToRobot; // The pitch and yaw of the object relative to the front of the robot, in rad. Downward and leftward are positive.
    rclcpp::Time timePoint;          // The time when the object was detected.
};

// The numbers corresponding to the Joystick buttons
//��Ϸ�ֱ�����ö��
enum JoystickBTN
{
    BTN_X,
    BTN_A,
    BTN_B,
    BTN_Y,
    BTN_LB,
    BTN_RB,
    BTN_LT,
    BTN_RT,
    BTN_BACK,
    BTN_START,
};
//ҡ��ö��
enum JoystickAX
{
    AX_LX,
    AX_LY,
    AX_RX,
    AX_RY,
    AX_DX,
    AX_DY,
};