function EE = patamar( L, A, show )


if show
    xlabel('x')
    ylabel('z')
    zlabel('y')
    view([45 45])
    hold on
end

A1=quadrado(1);
A1=rotateX(A1,-90);
A1=scale(A1, L, 1, A );
A1=translate(A1,0,0,A/2);
if show
    desenhaQuadrado(A1,'g');
end
EE=A1;
