# So_long - Projeto 42 Lisboa

Este é o meu projeto So_long, desenvolvido como parte do curso da 42 Lisboa. O objetivo do projeto é criar um jogo 2D simples usando a biblioteca gráfica miniLibX.



![So_long](https://github.com/Yumomonteiro/so_long/blob/main/images/jogo.png?raw=true)


## Introdução

O So_long é um jogo onde o jogador controla um personagem em um mapa e precisa coletar itens enquanto evita obstáculos. O jogo é escrito em C e usa a biblioteca gráfica miniLibX para a representação visual.

## Pré-requisitos

Antes de começar, certifique-se de ter o miniLibX instalado em seu sistema. Consulte a documentação da 42 ou a documentação oficial do miniLibX para obter instruções de instalação.

## Como compilar e executar

1. Clone este repositório:

   ```bash
      https://github.com/Yumomonteiro/so_long.git

2. Navegue até o diretório do projeto:

   ```bash
      cd so_long

3. Compile a biblioteca:

    ```bash
      make 
4. Compile o projeto:

    ```bash
    cc main.c so_long.a minilibx-linux/libmlx.a -lXext -lX11 -g

5. Execute o programa com o mapa desejado:

    ```bash
    ./a.out map.ber
    



  
