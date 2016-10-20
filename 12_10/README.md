##Caminho mais curto (caixeiro viajante)

Uma agência de viagens, está a organizar uma volta ao mundo e para tal o roteiro deve passar por vários pontos turísticos. No entanto, de forma a rentabilizar esta viagem, o trajeto deve ser o mais curto possível, regressando ainda assim ao ponto de partida. Os pontos são descritos por coordenadas geográficas em graus. O cálculo das distâncias entre as localidades é feito pela fórmula de 'haversine' e deverá imprimir as localidades pela ordem correta.

####Primeira solução
O primeiro algoritmo pensado por mim foi o mais simples de todos (mas de maneira nenhuma o mais eficiente), o algoritmo do vizinho mais próximo.
######Descrição do algoritmo:
  - 1º Escolher os dois pontos mais próximos, estes dois pontos serão o nosso ponto de partida;
  - 2º Ver qual o ponto mais próximo de um dos pontos no extremo do nosso caminho e adiciona-lo à solução;
  - 3º Enquanto houver pontos sem ligação repetir o passo 2º;
  
A solução obtida com este algoritmo pode estar distante da solução real em cerca de 20%, ou seja, é uma má solução, mas é o mais simples de fazer, e para caminhos pequenos pode ser uma solução aceitável.

##Shortest path (traveling salesman)

A travel agency, is organizing a world trip and for that the script should go to diferent places. But we want to do that in the eficient way, to monetize our trip, the path should be the shortest possible, coming back to the first point. The points in the input file are described in geographic coordinates in degrees. To calculate the distance you shoud use the 'haversine' formula ant should print the spots in the correct order.

####First solution
The first algorithm thought by me was the simplest (but in no way the most efficient), the algorithm of the closest neighbor.
######Description of the algorithm
    -1º Choose the two closest points, this two points will be our starter point 
    -2º See witch point is the closest to either points on the extreme of our path and add it ti our solution
    -3º While there are points without connection repeat the step 2º

The solution obtained with this algorithm is deslocated from the real solution in 20%, so it's a bad solution but its the simpliest solution to make and for short travels gives a acceptable solution 
