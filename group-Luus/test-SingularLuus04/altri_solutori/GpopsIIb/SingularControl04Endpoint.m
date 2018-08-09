function output=SingularControl04EndPoint(input)
  Tf = input.phase(1).finaltime ;
  x4f = input.phase(1).finalstate(4);
 
  output.objective = x4f;
end
