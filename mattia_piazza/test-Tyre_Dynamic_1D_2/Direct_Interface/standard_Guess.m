%% DIRECT OCP - STATES & CONTROL GUESS - - - - - - - - - - - - - - -
% Author: Mattia Piazza
function x0 = standard_Guess(self) 
	% bounds()
	% Define guess for all states and controls

	oneN      = ones(1,self.N);
	oneN_1    = ones(1,(self.N-1));
	v__g       = oneN * self.pins_data.parameters.v__ss ;
	omega__g   = oneN * self.pins_data.parameters.omega__ss ;
	lambda__g  = oneN * self.pins_data.parameters.lambda__ss ;
	p__g       = oneN * self.pins_data.parameters.p__ss ;
	b__g       = oneN * self.pins_data.parameters.b__ss ;
	Fz__g      = oneN * self.pins_data.parameters.Fz__ss ;
	p__o__g    = oneN_1 * 0 ;
	b__o__g    = oneN_1 * 0 ;

	x_g = reshape([ v__g; omega__g; lambda__g; p__g; b__g; Fz__g;  ], 1, self.N*self.nx );
	u_g = reshape([ p__o__lb; b__o__lb;  ], 1, (self.N-1)*self.nu );
end 
