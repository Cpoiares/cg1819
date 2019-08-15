function EE = degraus( L, E, P, ND, show  )

EE=[];

if show
    xlabel('x')
    ylabel('z')
    zlabel('y')
    view([45 45])
    hold on
end

for n=0:ND-1
    %-----------------------------
    E1=quadrado(1);
    E1=scale(E1, L, E, 1 );
    E1=translate(E1,0,n*E+E/2,n*P);
    if show
        desenhaQuadrado(E1,'r');
    end
    EE=[EE E1];
    %-----------------------------
    if (n<ND-1)
        P1=quadrado(1);
        P1=rotateX(P1,-90);
        P1=scale(P1, L, 1, P );
        P1=translate(P1,0,n*E+E,n*P+P/2);
        EE=[EE P1];
        if show
            desenhaQuadrado(P1,'b');
        end
    end
    
end

