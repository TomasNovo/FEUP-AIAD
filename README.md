# FEUP-AIAD
Programming in Java with Jade for AIAD 2019/2020 at FEUP.

## 1. Project 1 - Clients and CPUs

As 1st project of AIAD, we created a multiple agent system with two agents:  


• *Client* - this agent wants to compile a project and has a deadline. 


• *CPU* - this agent receives some files of the project of the Client and if the compilation of the files can be done in the respective deadline, the CPU will compile the files that he received and will send them to Client. If not, CPU will preview a new deadline and will negotiate with the Client. 

According to Client's tolerance, he will accept or reject the negotiation and will communicate his decision to the CPU.

The objective of this project was to decrease the total compilation of the files of the Client's project. This objective was successfully accomplished. 


More info of this project can found 
[here](../blob/master/docs/Relatorio-Proj1.pdf)


## 2. Project 2 - Rapidminer

As 2nd project of AIAD, we had to create and solve a classification and a linear regression problem using data from the 1st part of the project. 

The *classification* problem was the decision of the Client. We gave to Rapidminer info about previous compilations and it had to preview the responses according to its analysis.

In the *linear regression* problem we used the time difference between the predicted compilation time given by the CPU and the deadline of the project.

More info of this project can found [here](../blob/master/docs/Relatorio-Proj2.pdf).
