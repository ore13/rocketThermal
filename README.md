## ROCKETTHERMAL

Quick rocket thermal analysis program for determining the skin temperature of a rocket subject to aerodynamic heating.

# Building and running
build using `make test`. Once complete, run using `run.sh`.
A python script to visualise results is provided as postprocess.py. This requires matplotlib, pandas and numpy, and the base conda enviroment should be sufficient.

# Input files
Input files are listed under IO. The model requires a model definition file as an input. An example can be found in _modelDefinition.txt_. The model definition file lists the csv file name of flight conditions from openrocket (FLIGHTDATA), and a csv file specifying the rocket nose cone curve (DOMAIN). Examples can be found under the IO directory.
