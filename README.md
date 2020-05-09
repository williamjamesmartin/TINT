# TINT
 
 Dependencies: bash, g++ (any compiler post-version 11 should be fine), python3, numpy, pandas, keras, conda

Steps to use TINT:
1. Compile map.cpp with g++, i.e. "g++ map.cpp"
2. If you would not like to compile as a.out, you need to change the code in the shell script to be the desired name of your compiled program
3. "chmod +x compile_data.sh"
4. "./compile_data.sh" to run the simulation 1000 times as default, may take a while, again you can edit the sh to change these parameters
5. Utilize the SpeciesNeural IPython file to run our neural network to predict which traits are more valuable based on your simulations; edit however you please!
