#include "neuron.hpp"
#include "gtest/gtest.h"



TEST (NeuronTest, MembranePotential_1Update) {
   
   Neuron neuron(1);
	double TimeStep (0.1);
	double Iext (1.0);
	neuron.setStim(true);
   
    //Test for a single update
    neuron.UpdateNeuron(TimeStep,Iext);
    EXPECT_EQ(20.0*(1.0-exp(-0.1/20.0)), neuron.getMembPot());
    
}

TEST (NeuronTest, MembranePotential_10000Update) 
{
	Neuron neuron(1);
	double TimeStep (0.1);
	double Iext (1.0);
	neuron.setStim(true);
	
	//Test for many updates : membrane potential should tend to 20 but there should be no spikes
    neuron.RepeatUpdate(10000,TimeStep,Iext);
    
    EXPECT_EQ(0, neuron.getSpikeNumb());
    
      EXPECT_GT(1E-4, fabs(19.9999 - neuron.getMembPot()));
    
}

TEST (NeuronTest, MembranePotential_10000Update_Empty) 
{
	Neuron neuron(1);
	double TimeStep (0.1);
	double Iext (1.0);
	neuron.setStim(true);
	    //Test when external imput stops: potential should tend to 0
    Iext=0;
    neuron.RepeatUpdate(1000,TimeStep,Iext);
    
    EXPECT_NEAR(0, neuron.getMembPot(), 1e-3);
	
}

//Excepted spike times for one isolated neuron under this current 92.4, 186.8, 281.2 and 375.6 (in ms)
TEST (Neurontest, FirstSpike)
{
	Neuron neuron(1);
	double TimeStep (0.1);
	double Iext (1.01);
	neuron.setStim(true);

	//Test if first spike occurs at expected time
	neuron.RepeatUpdate(923,TimeStep,Iext);

	EXPECT_EQ(0, neuron.getSpikeNumb());

	neuron.UpdateNeuron(TimeStep,Iext);

	EXPECT_EQ(1, neuron.getSpikeNumb());

	EXPECT_EQ(0.0, neuron.getMembPot());
}

TEST (Neurontest, SecondSpike)
{
	Neuron neuron(1);
	double TimeStep (0.1);
	double Iext (1.01);
	neuron.setStim(true);
	
	//Test if second spike occurs at expected time
	neuron.RepeatUpdate(1868,TimeStep,Iext);

	EXPECT_EQ(1, neuron.getSpikeNumb());

	neuron.UpdateNeuron(TimeStep,Iext);

	EXPECT_EQ(2, neuron.getSpikeNumb());

	EXPECT_EQ(0.0, neuron.getMembPot());
	
}

TEST (Neurontest, EnoughSpikes)
{
	Neuron neuron(1);
	double TimeStep (0.1);
	double Iext (1.01);
	neuron.setStim(true);
	
	//testing if enough spikes occur
	neuron.RepeatUpdate(4000,TimeStep,Iext);
	
	EXPECT_EQ(4, neuron.getSpikeNumb());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
