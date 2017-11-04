#ifndef NETWORK_H
#define NETWORK_H
#include "neuron.hpp"
#include <fstream>

using namespace std; 

class Network {

private:

	const int N; ///< number of wanted cells in simulation
	 const int Ne; ///< number of wanted exitatory cells
	 const int Ni; ///< number of wanted inhibitory cells
	 const int Ce; ///< number of excitatory connections on a cell
	 const int Ci; ///< number of inhibitory connections on a cell
	 const int Cext; ///< number of external connections on a cell
	const double Je; ///< excitatory coefficient
	const double Ji; ///< inhibitory coefficient
	const double H; ///< timeStep given by simulation


	vector<Neuron*> Cells; ///< table with references to all neurons
	vector<vector<int>> Connections; ///< stores connections in network as ints
	vector<int> SpikeTimes; ///< vector storing time value of spiking neuron (in steps)
	vector<double> indexes; ///vector storing index of spiking neuron
	
		
	/**
	 * Creates N Neurons, stores their ref in Cells
	 */
	void CreateNeurons(); 
	
	/**
	 * Creates links between Neurons and stores them in Connections
	 */
	void LinkNetwork();
	
	///time boudaries for data acquisition
	double Start;
	double Stop;


public:

	/**
	 * @brief default Constructor
	 * @param int number of desires Neurons
	 * @param double h simulation time step
	 */
	Network();
	
	/**
	 * @brief constructor for default simulation
	 * Used for custom simulation
	 * @param int number of desires Neurons
	 * @param int number of excitatory neurons
	 * @param int Ni number of wanted inhibitory neurons
	 * @param int Ce number of excitatory connections
	 * @param int Ci number of inhibitory connections
	 * @param int Cext number of external connections 
	 * @param double Je excitatory coefficient
	 * @param double Ji inhibitory coefficient
	 */
	Network(int n,int ne, int ni, int ce, int ci, int cext, double je, double ji);
	
	/**
	 * Network copy has been blocked
	 */
	Network(Network& other)=delete;
	~Network();

	/**
	 * Calls update method of all Neurons and handles potential transmission
	 */
	void UpdateNetwork(double Iext_, unsigned int time);
	
	/**
	 * stores the membrane potential of all Neurons contained in Network in a vector
	 * @return returns vector of potentials (double)
	 */
	vector<double> StoreState() const;
	
	/**
	 *stores spike time in a document associated with Neuron Id can be done at any time
	 */
	 
	 void StoreSpike(unsigned int time, unsigned int i);
	
	/**
	*writes paires values of SpikeTimes and indexes in a document at the end of simulation
	*/
	 void writeSpikes() const;
	 
	/**
	* allows to choose time boundaries between which spikes are recorded
	*/
	void setDataAcquisition();
	
};

#endif
