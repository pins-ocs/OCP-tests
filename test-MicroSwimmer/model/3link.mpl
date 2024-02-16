A  := Matrix(3,3);
b1 := Matrix(3,1);
b3 := Matrix(3,1);

A[1,1] := - L__2*xi*cos(theta)^2
          - L*xi*cos(beta__1 + theta)^2
          - L*xi*cos(beta__3 + theta)^2
          - L__2*eta*sin(theta)^2
          - L*eta*sin(beta__1 + theta)^2
          - L*eta*sin(beta__3 + theta)^2;

A[2,2] := - L__2*eta*cos(theta)^2
          - L*eta*cos(beta__1 + theta)^2
          - L*eta*cos(beta__3 + theta)^2
          - L__2*xi*sin(theta)^2
          - L*xi*sin(beta__1 + theta)^2
          - L*xi*sin(beta__3 + theta)^2;

A[3,3] := (1/12)* (
           - 8*L^3*eta
           - L__2^3*eta
           - 6*L^2*L__2*eta*cos(beta__1)
           - 3*L*L__2^2*eta*cos(beta__1)^2
           - 6*L^2*L__2*eta*cos(beta__3)
           - 3*L*L__2^2*eta*cos(beta__3)^2
           - 3*L*L__2^2*xi*sin(beta__1)^2
           - 3*L*L__2^2*xi*sin(beta__3)^2
           );

A[1,2] := (eta - xi)*(L__2*cos(theta)*sin(theta) + L*cos(beta__1 - beta__3)*sin(beta__1 + beta__3 + 2*theta));

A[1,3] := (1/2)*L*(
          L__2*xi*cos(beta__1 + theta)*sin(beta__1)
          - L__2*xi*cos(beta__3 + theta)*sin(beta__3)
          - eta*(L + L__2*cos(beta__1))*sin(beta__1 + theta)
          + eta*(L + L__2*cos(beta__3))*sin(beta__3 + theta)
        );

A[2,3] := (1/2)*L*( eta*(L + L__2*cos(beta__1))*cos(beta__1 + theta)
                    - eta*(L + L__2*cos(beta__3))*cos(beta__3 + theta)
                    + L__2*xi*sin(beta__1 - beta__3)*sin(beta__1 + beta__3 +theta)
                  );

b1[1] := -(1/2)*L^2*eta*sin(beta__1 + theta);
b1[2] := (1/2)*L^2*eta*cos(beta__1 + theta);
b1[3] := -(1/12)*L^2*eta*(4*L + 3*L__2*cos(beta__1));

b3[1] := (1/2)*L^2*eta*sin(beta__3 + theta);
b3[2] := -(1/2)*L^2*eta*cos(beta__3 + theta);
b3[3] := -(1/12)*L^2*eta*(4*L + 3*L__2*cos(beta__3));
