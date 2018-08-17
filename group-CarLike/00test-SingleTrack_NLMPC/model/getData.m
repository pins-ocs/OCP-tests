function [X]=getData(VD,name)
  
if isfield(VD, 'colheaders')
   VDH = VD.colheaders;
 else
   VDH = VD.headers;
 end
 i_data = find(strcmp(VDH,name)) ;
 assert( length(i_data) > 0, 'Variable %s not found', name)
 
 i_data = find(strcmp(VDH,name)) ;
 X  = VD.data(:,i_data);
 if iscell(X) 
   X = cell2mat(X);
 end
 
 end
