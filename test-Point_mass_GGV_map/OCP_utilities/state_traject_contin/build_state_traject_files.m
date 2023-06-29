% ----------------------------------------------------------------------------
%% Build the txt files to impose the continuity of the MPC state trajectories
% ----------------------------------------------------------------------------

% Vector of curvilinear abscissae (initialization)
zeta_vals = 0:100;

% Vector of yaw rate values (initialization)
Omega_vals = zeros(size(zeta_vals));

% Save the state trajectories
fileID = fopen(('Omega_traject_contin.txt'), 'w');    
fprintf(fileID,'zeta\tOmega_cont\n');
for ii=1:length(zeta_vals)
    fprintf(fileID,'%.12e\t%.12e\n',zeta_vals(ii),Omega_vals(ii));
end
fclose(fileID);
