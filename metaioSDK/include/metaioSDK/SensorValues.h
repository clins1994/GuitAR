// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef _AS_SENSORVALUES_H_
#define _AS_SENSORVALUES_H_

#include <metaioSDK/MobileStructs.h>
#include <metaioSDK/Rotation.h>
#include <metaioSDK/STLCompatibility.h>

namespace metaio
{

/** Sensor reading with timestamp */
struct SensorReading
{ 
	double timestamp;	///< timestamp in [s]
	int accuracy;		///< accuracy - not yet really used (3 seems "good"...)
	Vector3d values;	///< Three floating point numbers from a sensor.
	                    ///< The interpretation depends on the sensor used.

	/** Default constructor */
	SensorReading(): timestamp(0.0), accuracy(0)
	{
	}
};

/** An encapsulation of all the sensors' readings with corresponding time stamps */
struct SensorValues
{
	LLACoordinate location; ///< Device location. Needed: SENSOR_LOCATION
	Vector3d gravity; ///< Normalized gravity vector. Needed: SENSOR_GRAVITY
	double gravityTimestamp; ///< timestamp [s]

	float heading; ///< Heading in degrees, 0=North, 90=East, 180=South. Needed: SENSOR_HEADING
	double headingTimestamp; ///< timestamp [s]

	metaio::Rotation attitude; ///< device attitude based on running sensors. Needed: SENSOR_ATTITUDE
	double attitudeTimestamp; ///< timestamp [s]

	bool	deviceIsMoving; ///< Indicates if device is moving. Needed: SENSOR_DEVICE_MOVEMENT

	stlcompat::Vector<SensorReading> historicalGyroscopeVector;	///< Historical raw gyroscope values [rad/s] with timestamps in [s] Needed: SENSOR_DEVICE_GYROSCOPE
	stlcompat::Vector<SensorReading> historicalAccelerometerVector; ///< Historical raw accelerometer values [m/s^2] with timestamps in [s] Needed: SENSOR_DEVICE_ACCELEROMETER
	stlcompat::Vector<SensorReading> historicalMagnetometerVector; ///< Historical raw magnetometer values [microTesla] with timestamps [s] Needed: SENSOR_DEVICE_MAGNETOMETER

	/** Default constructor */
	SensorValues(): gravityTimestamp(0.0), heading(-1.0), headingTimestamp(0.0), attitudeTimestamp(0), deviceIsMoving(false)
	{
	}

};
}


#endif // _AS_SENSORVALUES_H_
