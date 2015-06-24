#ifndef PARAMETERS
#define PARAMETERS

#include <vector>
#include <string>

#include "msw-enc600.h"

namespace rcl
{
    namespace Parameters
    {
	namespace Common
	{
	    static const float sampling_time = 0.001;//s
	    static const int dof = 7;
	    static const int dof_lc = dof*(dof-1)/2;//for dynamics coriolis term
	};
	
	namespace CommunicationInterface
	{
	    //device name of analog output card.
	    static const std::string ao_dev = "/dev/ixpio3";
	    static const int num_channel = 8;
	    static const float max_voltage = 10.0;
	    
	    //6-axis encoder card
	    static const int enc_6x = 0;
	    static const std::string enc_6x_dev = "/dev/ixpio1";
	    //3-axis encoder card
	    static const int enc_3x = 2;
	    static const std::string enc_3x_dev = "/dev/ixpio2";
	    
	    //encoder mode
	    static const int mode = ENC_QUADRANT;
	};
	
	namespace MotorJoint
	{
	    //TODO tune the PID parameters
	    //controller PID parameters
	    //static const float position_p[] = {0.00020, 0.00025, 0.00015, 0.00020, 0.00015, 0.00030, 0.00004};
	    static const float position_PID_P[] = {0.06, 0.06, 0.04, 0.05, 0.03, 0.04, 0.02};
	    static const float position_PID_I2P[] = {0.0050, 0.0060, 0.0030, 0.0060, 0.0020, 0.0030, 0.0010};
	    static const float position_PID_D2P[] = {0.100, 0.100, 0.100, 0.100, 0.100, 0.100, 0.100};
	    
	    static const float velocity_PID_P[] = {0.012, 0.012, 0.008, 0.010, 0.004, 0.005, 0.002};
	    static const float velocity_PID_I2P[] = {0.0060, 0.0080, 0.0030, 0.0050, 0.0008, 0.0010, 0.0008};
	    static const float velocity_PID_D2P[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	    
	    //torque constant. in Nm/A
	    static const float torq_const[] = {0.0385, 0.0385, 0.0302, 0.0302, 0.0259, 0.0259, 0.0208};
	    
	    //maximun allowable current for each motor. in A
	    static const float max_current[] = {10.0, 10.0, 6.0, 6.0, 3.5, 3.5, 1.5};
	    
	    //the ratio between acutual torque and AO set value
	    //torque/1V, torque in Nm
	    static const float torque_per_voltage[] = { torq_const[0]*max_current[0]/CommunicationInterface::max_voltage, torq_const[1]*max_current[1]/CommunicationInterface::max_voltage, torq_const[2]*max_current[2]/CommunicationInterface::max_voltage, torq_const[3]*max_current[3]/CommunicationInterface::max_voltage, torq_const[4]*max_current[4]/CommunicationInterface::max_voltage, torq_const[5]*max_current[5]/CommunicationInterface::max_voltage, torq_const[6]*max_current[6]/CommunicationInterface::max_voltage };
	    //voltage/1Nm, voltage in V
	    static const float voltage_per_torque[] = { CommunicationInterface::max_voltage/torq_const[0]/max_current[0], CommunicationInterface::max_voltage/torq_const[1]/max_current[1], CommunicationInterface::max_voltage/torq_const[2]/max_current[2], CommunicationInterface::max_voltage/torq_const[3]/max_current[3], CommunicationInterface::max_voltage/torq_const[4]/max_current[4], CommunicationInterface::max_voltage/torq_const[5]/max_current[5], CommunicationInterface::max_voltage/torq_const[6]/max_current[6] };
	    
	    //PID integrator max
	    static float accu_max[] = { torq_const[0]*max_current[0]/position_PID_P[0]/position_PID_I2P[0], torq_const[1]*max_current[1]/position_PID_P[1]/position_PID_I2P[1], torq_const[2]*max_current[2]/position_PID_P[2]/position_PID_I2P[2], torq_const[3]*max_current[3]/position_PID_P[3]/position_PID_I2P[3], torq_const[4]*max_current[4]/position_PID_P[4]/position_PID_I2P[4], torq_const[5]*max_current[5]/position_PID_P[5]/position_PID_I2P[5], torq_const[6]*max_current[6]/position_PID_P[6]/position_PID_I2P[6] };
	    
	    //motor encoder count per revolution
	    static const int enc_count[] = {2000, 2000, 2000, 2000, 2000, 2000, 2000};
	    static const int gear_ratio[] = {483, 483, 404, 404, 404, 404, 204};
	    static const int reduction[] = {enc_count[0]*gear_ratio[0], enc_count[1]*gear_ratio[1], enc_count[2]*gear_ratio[2], enc_count[3]*gear_ratio[3], enc_count[4]*gear_ratio[4], enc_count[5]*gear_ratio[5], enc_count[6]*gear_ratio[6]};
	    //how many joint deg per 1 encoder count
	    static const float deg_per_count[] = {360.0/reduction[0], 360.0/reduction[1], 360.0/reduction[2], 360.0/reduction[3], 360.0/reduction[4], 360.0/reduction[5], 360.0/reduction[6]};
	    //how many encoder count per 1 joint deg
	    static const float count_per_deg[] = {reduction[0]/360.0, reduction[1]/360.0, reduction[2]/360.0, reduction[3]/360.0, reduction[4]/360.0, reduction[5]/360.0, reduction[6]/360.0};
	    
	    //reference position for each joint. in degree
	    static const float home[] = {0.0, -90.0, 0.0, 180.0, 0.0, 0.0, 0.0};
	    
	    //motor rotation direction, in order to match the DH definition
	    static const float dir[] = {-1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0};
	};
	
	namespace JointMode
	{
	    //ratio between the desired maximun speed and the maximun allowable speed
	    static const float default_speed_ratio = 0.5;
	    //ratio between the via-point speed and the desired maximum speed
	    static const float default_via_speed_ratio = 0.7;
	    static const float joint_limit_upper[] = {};
	    static const float joint_limit_lower[] = {};
	    static const float max_vel[] = {};
	    static const float max_acc[] = {};
	};
    };
};

#endif