The files possess the following functionalities : 

a) Competing neurons to stochastic current 

This decision making simulation paradigm is written for 2 neurons , however it can be easily extended to n - competing neurons . Please note that this is a bi-layered architecture . One layer is the input and the 2nd are the competing choices . The decision making model implemented is taken from " Time Course of Perpetual Choice " , by Usher and Mclelland . The inputs here are stochastic , and the code return the output coltages as well as the spiking rate analysis of the competing neurons . The decision is supposed to be triggered when the spiking rate od a neuron crosses a set threshold . 

b) Decision Making Neurons with constant inputs 

This code handles the decision making problem , not in terms of accummulating voltage but by the post synaptic currents of the competing neurons . We use n integrate and fire neurons as competing choices . All the rest is the same . 

c) Poisson Random Input and Corresponding Output 

This code is an advanced implementation of the Integrate and FIre neuron . Input to the neuron comes in the form of spikes obeying Poission Distribution . The corresponding EPSP's and the final Output voltages are returned by the code . 

d) Simple Usher and Mclelland Implementation 

This code just explaing the implementation of the Usher and Mclelland model . The code returns the generic nature of the model . 

e) Single Neuron and Deviation 

This is an open ended coding snippet , aimed to find the deviations in the Output to a stochastic input current with varying standard deviations .    
 