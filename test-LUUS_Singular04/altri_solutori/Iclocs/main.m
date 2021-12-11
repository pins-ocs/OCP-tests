% MAIN - Main script to solve the Optimal Control Problem
%
% Copyright (C) 2010 Paola Falugi, Eric Kerrigan and Eugene van Wyk. All Rights Reserved.
% This code is published under the BSD License.
% Department of Electrical and Electronic Engineering,
% Imperial College London London  England, UK 
% ICLOCS (Imperial College London Optimal Control) 5 May 2010
% iclocs@imperial.ac.uk

%--------------------------------------------------------

clear all;format compact;


[problem,guess]=Singular04;       % Fetch the problem definition
options= settings;                      % Get options and solver settings         

[infoNLP,data]=transcribeOCP(problem,guess,options); % Format for NLP solver

[solution,status] = solveNLP(infoNLP,data);      % Solve the NLP

output(solution,options,data);         % Output solutions

