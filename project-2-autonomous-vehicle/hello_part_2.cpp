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
	px4_sleep(2);
	debug_value_s debug_data;
	int debug_handle = orb_subscribe(ORB_ID(debug_value));
	orb_set_interval(debug_handle, 500);

	test_motor_s test_motor;
	test_motor_s test_servo;

	uORB::Publication<test_motor_s> test_motor_pub(ORB_ID(test_motor));
	uORB::Publication<test_motor_s> test_servo_pub(ORB_ID(test_motor));
	uORB::Publication<debug_value_s> debug_value_pub(ORB_ID(debug_value));

	test_motor.timestamp = hrt_absolute_time();
	test_motor.motor_number = DC_MOTOR;
	test_motor.value = 0.5;
	test_motor.action = test_motor_s::ACTION_RUN;
	test_motor.driver_instance = 0;
	test_motor.timeout_ms = 0;

	test_servo.timestamp = hrt_absolute_time();
	test_servo.motor_number = SERVO_MOTOR;
	test_servo.value = 0.5;
	test_servo.action = test_motor_s::ACTION_RUN;
	test_servo.driver_instance = 0;
	test_servo.timeout_ms = 0;

	test_motor_pub.publish(test_motor);
	test_servo_pub.publish(test_servo);

	px4_sleep(2);

	while (1)
	{
		orb_copy(ORB_ID(debug_value), debug_handle, &debug_data);

		int direction = debug_data.ind;
		int speed = debug_data.value;

		debug_value_pub.publish(debug_data);

		// Set motors
		test_motor.timestamp = hrt_absolute_time();
		test_motor.motor_number = DC_MOTOR;
		test_motor.action = test_motor_s::ACTION_RUN;
		test_motor.driver_instance = 0;
		test_motor.timeout_ms = 0;

		test_servo.timestamp = hrt_absolute_time();
		test_servo.motor_number = SERVO_MOTOR;
		test_servo.action = test_motor_s::ACTION_RUN;
		test_servo.driver_instance = 0;
		test_servo.timeout_ms = 0;

		// Set speed based on pi distance
		if (speed == 1)
		{
			test_motor.value = 0.6;
		}
		else if (speed == 2)
		{
			test_motor.value = 0.9;
		}
		else
		{ // speed = 0
			test_motor.value = 0.5;
		}

		// Set direction based on pi camera
		if (direction == 0)
		{
			test_servo.value = 0.1;
		}
		else if (direction == 2)
		{
			test_servo.value = 0.9;
		}
		else
		{ // direction = 1
			test_servo.value = 0.5;
		}

		debug_data.timestamp = hrt_absolute_time();
		debug_value_pub.publish(debug_data);

		test_motor_pub.publish(test_motor);
		test_servo_pub.publish(test_servo);
		px4_usleep(50000);
	}
	return 0;
}