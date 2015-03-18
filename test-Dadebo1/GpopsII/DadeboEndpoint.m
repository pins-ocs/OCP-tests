function output=DadeboEndpoint(input)
  Tf = input.phase(1).finaltime ;
  x2f = input.phase(1).finalstate(2);
 
  output.objective = x2f;
end
