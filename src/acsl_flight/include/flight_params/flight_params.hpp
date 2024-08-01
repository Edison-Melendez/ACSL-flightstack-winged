/***********************************************************************************************************************
 * Copyright (c) 2024 Giri M. Kumar, Mattia Gramuglia, Andrea L'Afflitto. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *    disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *    following disclaimer in the documentation and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote
 *    products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * File:        flight_params.hpp
 * Author:      Giri Mugundan Kumar
 * Date:        April 30, 2024
 * For info:    Andrea L'Afflitto 
 *              a.lafflitto@vt.edu
 * 
 * Description: Header file for the main flight parameters that will be
 *              used for the entire controller.
 * 
 * GitHub:    https://github.com/andrealaffly/ACSL_flightstack_X8.git
 **********************************************************************************************************************/

#ifndef FLIGHT_PARAMS_HPP_
#define FLIGHT_PARAMS_HPP_

#include <string>
#include <fstream>
#include "nlohmann/json.hpp"  // For parsing json for the flight parameters

using json = nlohmann::json;

// Struct containing the trajectory info coming from the .json file 
struct PiecewisePolynomialTrajectoryInfo {
    // times at which I want to reach the waypoints
	std::vector<double> waypoint_times_; 

    // matrix containing the piecewise polynomial coefficients
	std::vector<std::vector<double>> piecewise_polynomial_coefficients_; 

    // number of waypoints
    int num_waypts;
};

// If you are adding more parameters to your flight in /src/acsl_flight/params/flight_params.json,
// please include it here and modify as needed in the flight_main.cpp/hpp.
struct flight_params {
    // 1. Flight Arm time
    double arm_time;

    // 2. Minimum thrust to motors after arm
    double min_thrust_after_arm;

    // 3. Flight Start time
    double start_time;

    // 4. Trajectory file name
    std::string user_defined_trajectory_file;

    // 5. hover after trajectory is done in seconds
    double hover_time;

    // 6. Type of State Estimation
    bool mocap;

    // 7. Controller rate - Specified as per loop run value in ms.
    int controller_rate;

    // 8. Piecewise Polynomial Trajectory Info
    PiecewisePolynomialTrajectoryInfo traj_params;

    // 9. Landing Start time
    double landing_start_time;

    // 10. Landing End time
    double landing_end_time;

    // 11. Flight End time
    double end_time;       
};

namespace _flight_params_
{
// Class for handling flight parameters
class FlightConfigReader {
public:
    // Constructor
    FlightConfigReader() {}

    // Method to read flight parameters from a JSON file
    flight_params readFlightConfig(const std::string& jsonFile);

    // Method to read the trajecotry info from a JSON file
    PiecewisePolynomialTrajectoryInfo readTrajectoryConfig(const std::string& fileName);
};

}   // namespace _flight_params_

#endif  // FLIGHT_PARAMS_HPP_