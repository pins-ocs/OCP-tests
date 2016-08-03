gridSize = 0.1;

SingleTrack_Road_data.Road.theta0   = 0;
SingleTrack_Road_data.Road.s0       = 0;
SingleTrack_Road_data.Road.x0       = 0;
SingleTrack_Road_data.Road.y0       = 0;
SingleTrack_Road_data.Road.is_SAE   = false;
% 
SingleTrack_Road_data.Road.segments{1}.leftWidth  = 5/2;
SingleTrack_Road_data.Road.segments{1}.curvature  = 0;
SingleTrack_Road_data.Road.segments{1}.rightWidth = 5/2;
SingleTrack_Road_data.Road.segments{1}.gridSize   = gridSize;
SingleTrack_Road_data.Road.segments{1}.length     = 20;
                                  
SingleTrack_Road_data.Road.segments{2}.leftWidth  = 5/2;
SingleTrack_Road_data.Road.segments{2}.curvature  = 0;
SingleTrack_Road_data.Road.segments{2}.rightWidth = 5/2;
SingleTrack_Road_data.Road.segments{2}.gridSize   = gridSize;
SingleTrack_Road_data.Road.segments{2}.length     = 80;
                                  
SingleTrack_Road_data.Road.segments{3}.initialCurvature = 0.02;
SingleTrack_Road_data.Road.segments{3}.leftWidth        = 5/2;
SingleTrack_Road_data.Road.segments{3}.rightWidth       = 5/2;
SingleTrack_Road_data.Road.segments{3}.finalCurvature   = 0.02;
SingleTrack_Road_data.Road.segments{3}.gridSize         = gridSize;
SingleTrack_Road_data.Road.segments{3}.length           = 157.08;
                                  
SingleTrack_Road_data.Road.segments{4}.curvature        = -1.0/40.0;
SingleTrack_Road_data.Road.segments{4}.leftWidth        = 5/2;
SingleTrack_Road_data.Road.segments{4}.rightWidth       = 5/2;
SingleTrack_Road_data.Road.segments{4}.gridSize         = gridSize,
SingleTrack_Road_data.Road.segments{4}.length           = 40.0*3.1428;
                                                  
SingleTrack_Road_data.Road.segments{5}.leftWidth        =  5/2;
SingleTrack_Road_data.Road.segments{5}.curvature        =  0;
SingleTrack_Road_data.Road.segments{5}.rightWidth       =  5/2;
SingleTrack_Road_data.Road.segments{5}.gridSize         =  gridSize;
SingleTrack_Road_data.Road.segments{5}.length           =  80,
                                                    
SingleTrack_Road_data.Road.segments{6}.leftWidth        =  5/2;
SingleTrack_Road_data.Road.segments{6}.curvature        =  0;
SingleTrack_Road_data.Road.segments{6}.rightWidth       =  5/2;
SingleTrack_Road_data.Road.segments{6}.gridSize         =  gridSize;
SingleTrack_Road_data.Road.segments{6}.length           =  20;