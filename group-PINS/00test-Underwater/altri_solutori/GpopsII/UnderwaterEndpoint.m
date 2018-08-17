function output=UnderwaterEndpoint(input)
  %Tf = input.phase(1).finaltime ;
  Tf = input.phase(1).finalstate(7);
 
  output.objective = Tf;
end
