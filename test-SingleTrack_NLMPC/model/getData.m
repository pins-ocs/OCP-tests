function [X]=getData(VD,name)

 i_data = find(strcmp(VD.colheaders,name)) ;
 
 assert( length(i_data) > 0, 'Variable %s not found', name)
 
 i_data = find(strcmp(VD.colheaders,name)) ;
 X  = VD.data(:,i_data);
 
 end
