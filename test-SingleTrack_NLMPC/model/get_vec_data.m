function [X]=get_vec_data(VD,names,pos)
  
  X = zeros(length(names),1);
  if isfield(VD, 'colheaders')
    VDH = VD.colheaders;
  else
    VDH = VD.headers;
  end
  i = 1;
  for nm = names 
    i_data = find(strcmp(VDH,nm)) ;
    assert( length(i_data) > 0, 'Variable %s not found', nm)
    if iscell(VD.data) 
      tmp = VD.data{i_data};
      X(i) = tmp(pos);
    else
      X(i) = VD.data(pos,i_data);
    end
    i = i+1;
  end
  
end
