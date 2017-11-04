#ifndef NEURON_H
#define NEURON_H
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <random>
#include <cassert>

using namespace std;


class Neuron{
	
	private:

		double MembPot; ///< Neuron's membrane potential
		double SpikeNumb; ///< Number of recorded spikes
		vector<double> SpikeHistory; ///< time values of recorded spikes
		vector<double> Buffer; ///< buffer of size delay+1
		unsigned int CellTime; ///< internal cell clock counted as increments of H
		
		double Cap; ///<capacity
		double Res; ///<resistance
		double Tau; ///<I'm not sure
		bool Stim; ///<Indicates if neuron recieves programmed external current
		
		const double TauRef; ///< refractory period
		const double Vres; ///< membrane potential after spike
		const double SpikeThreshold; ///< potential to trigger neuron spike
		const unsigned int Delay; ///< delay in steps for current to arrive
		const bool Excitatory; ///< indicates nature of neuron (excitatory or inhibitory)
		
	//private methods
		
	/**
	 * convert time value into a buffer index
	 * @param int time value
	 * @return int buffer index
	 */
		unsigned int Index(unsigned int time);

	public:

	/**
	 * Neuron constructor 
	 *@param bool indicating neuron type true: excitatory false: inhibitory
	 */
		Neuron(bool ex);
	/**
	 * Neuron copy is blocked
	 */
		Neuron(const Neuron& other) = delete;

	//getters 
	/**
	 * takes no arguments
	 * @return current Membrane Potential
	 */
	  
		double getMembPot() const;
	/**
	 * takes no arguments
	 * @return number of recorded spikes
	 */
		double getSpikeNumb() const ;
		
	/**
	 * takes no arguments
	 * @return time (in real time: ms) of last recorded spike
	 */
		double getLastSpike() const;

	//setters
	/**
	 * set a cells membrane potential to given value
	 * @param double wanted potential
	 */
		void setMembPot(double value);
	
	/**
	 * set a cells stimulation state
	 * is 0 by default (cells don't receive programmed external current)
	 * @param bool stimulation
	 */
		void setStim(bool stim);

	//cell dev methods
	/**
	 * stores cellTime converted into RealTime (ms) into SpikeHistory
	 * @param double H: simulation time step
	 */
		void storeSpikeTime(double H);
		
	/**
	 *changes value of membrane potential according to time laps, external current or spikes
	 * @param double H: simulation time step
	 * @param double external current if there is one
	 * @return true if cells fires during current step
	 */
		bool UpdateNeuron(double H, double Iext);
		
	/**
	 * allows to cycle through given number of updates for tests
	 * @param int number of cycles
	 */
	 void RepeatUpdate(int i, double H, double Iext);
		

	/**
	 * resets membrane potential to rest value
	 * no arguments or return value
	 */
		void Reset();
		
	/**
	 * adds a spike to SpikeHistory and calls the Neuron's reset method
	 * @param double: the time step to convert time value to RealTime (ms)
	 */
		void Fire(double H);
		
	/**
	 * takes in voltage and stores it in Neuron's buffer index [(time+D)%(D+1)] according to general time
	 * @param double: voltage
	 * @param int for simulation's time
	 */
		void Receive(double charge, unsigned int time);
		
	/**
	 * indicates if the neuron is excitatory
	 * @return bool true if the neuron is excitatorz, false if inhibitory
	 */
	 
	 bool isEx() const;


};

#endif
