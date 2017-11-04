#ifndef SIMULATION_H
#define SIMULATION_H
#include "network.hpp"

using namespace std;

class Simulation{

	private :

	bool custom; ///< bool indicating if default of custom simulation
//given by main
	double H; ///< amount of time in ms per simulation step
//given by user
	double SimTime; ///< total simulation time in ms
	double Iext; ///< external current
	
	///time boundaries for external current application
	double abound;
	double bbound;
	

	unsigned int StepTime; ///< is counted as increments of the timestep H
	Network* network; ///< Network containing all neurons
	
	
	/**
	* allows to set an external current
	* @param double start time of stimulation
	* @param double end time of stimulation
	* @param double value of stimualtion (mV)
	*/
	void SetCurrent(double a, double b, double I);
	
	public:
	
	/**
	* @brief default constructor
	* Uses default simulation and Network values
	*/
	Simulation();
	
	/**
	* @brief custom Simulation constructor
	* @param simulation time
	*/
	Simulation( double sim_time);
	
	/**
	*@brief destructor
	*/
	~Simulation();
	
	/**
	*runs the simulation by calling Network's update method
	*increments the simulation time with each step
	*/
	void Run();
	
	/**
	*takes time value in steps and converts it to ms
	* @param double (int) time in steps
	* @return double time in ms
	*/
	double RealTime(double time) const;
	
	/**
	* allows to set simulation time in ms
	*/
	void SetSimTime();
	
	/**
	* writes membrane potential of all cells into a file at a given time
	*/
	void StoreState();
	


};

#endif
