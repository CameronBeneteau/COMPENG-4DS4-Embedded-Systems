#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>
#include <uORB/Publication.hpp>

#include <drivers/drv_hrt.h>
#include <uORB/topics/test_motor.h>

#include <uORB/topics/led_control.h>
#include <uORB/topics/debug_value.h>

#define DC_MOTOR 0
#define SERVO_MOTOR 1

#include <uORB/topics/rc_channels.h>

extern "C" __EXPORT int project2_part2_main(int argc, char *argv[]);

int project2_part2_main(int argc, char *argv[])
{
	test_motor_s test_motor;
	double motor_value = 0; // a number between 0 to 1
	double servo_value = 0; // a number between 0 to 1
	uORB::Publication<test_motor_s> test_motor_pub(ORB_ID(test_motor));

	int rc_channels_handle;

	rc_channels_s sensor_data;
	rc_channels_handle = orb_subscribe(ORB_ID(rc_channels));
	orb_set_interval(rc_channels_handle, 200);

	PX4_INFO("Enter speed value (0 to 1). If you enter a value outside the range, the motor will be stopped and the application will be terminated.");
	scanf("%lf", &motor_value);

	PX4_INFO("Enter angle value (0 to 1). If you enter a value outside the range, the motor will be stopped and the application will be terminated.");
	scanf("%lf", &servo_value);

	while (1)
	{
		orb_copy(ORB_ID(rc_channels), rc_channels_handle, &sensor_data);

		motor_value = ((double)sensor_data.channels[2] + 1.0) / 2.0;
		if (motor_value > 1.0 || motor_value < 0)
			break;

		servo_value = ((double)sensor_data.channels[0] * (-1.0) + 1.0) / 2.0;
		if (servo_value > 1.0 || servo_value < 0)
			break;

		PX4_INFO("Motor speed is %f", motor_value);
		test_motor.timestamp = hrt_absolute_time();
		test_motor.motor_number = DC_MOTOR;
		test_motor.value = (float)motor_value;
		test_motor.action = test_motor_s::ACTION_RUN;
		test_motor.driver_instance = 0;
		test_motor.timeout_ms = 0;
		test_motor_pub.publish(test_motor);

		PX4_INFO("Servo angle is %f", servo_value);
		test_motor.timestamp = hrt_absolute_time();
		test_motor.motor_number = SERVO_MOTOR;
		test_motor.value = (float)servo_value;
		test_motor.action = test_motor_s::ACTION_RUN;
		test_motor.driver_instance = 0;
		test_motor.timeout_ms = 0;
		test_motor_pub.publish(test_motor);
	}

	PX4_INFO("The motor will be stopped");
	test_motor.timestamp = hrt_absolute_time();
	test_motor.motor_number = DC_MOTOR;
	test_motor.value = 0.5;
	test_motor.driver_instance = 0;
	test_motor.timeout_ms = 0;

	test_motor_pub.publish(test_motor);

	PX4_INFO("The servo will be reset");
	test_motor.timestamp = hrt_absolute_time();
	test_motor.motor_number = SERVO_MOTOR;
	test_motor.value = 0.5;
	test_motor.driver_instance = 0;
	test_motor.timeout_ms = 0;

	test_motor_pub.publish(test_motor);

	return 0;
}