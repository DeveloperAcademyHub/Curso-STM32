/*******************************************************************************************************/
//Script Dead Time STM32 - "Curso STM32 - Além dos Limites do Arduino"
//Prof. Eng. Gabriel Vigiano
//Este script tem por objetivo facilitar a configuração do tempo do dead em conjunto com o STM32CubeIDE.
/*******************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

float freqtimer; //Freq de Config. Do Timer.
float steptimer; //Passo do Timer.
float deadtime; //Dead Timer Desejado.
float x; // Condição Para Cálculo do Dead Time Baseado nas Regiões.
float configfinal; //Configuração no CubeIDE -> Campo "Dead Time".

void main()
{
	
	inicio:
	
	printf("-CURSO DE STM32: Alem dos Limites do Arduino-\r\n-Calculo Dead Time-\r\n\r\n");
	printf("Digite a Frequencia do Timer (MHz): "); //Msg.
    scanf ("%f", &freqtimer); //Lê Freq.
    freqtimer=freqtimer*1e6; //Passa Freqtimer para Mhz.
    
    printf("Digite o Dead Time Desejado em Micro Segundos (us): "); //Msg.
    scanf ("%f", &deadtime); //Dead Time Desejado.
    printf("\r\n"); //Pula linha.
    deadtime=(deadtime/1e6); //Converte Dead Time em Segundos.
    
    printf("Frequencia do Timer -> %1.0f MHz\r\n",(freqtimer/1000000)); //Mostra Freq. em Mhz.
    steptimer=(1/freqtimer); //Cálcula Tempo do Passo.
	
    x=deadtime/steptimer; // Valores Para Determinar as Regiões.
    
    //Região 1:
    if (x<=127)
    {
    	configfinal=x;
    	
    	if (configfinal<=255)
    	{
    		printf("STM32CubeIDE Dead Time: %1.0f",configfinal);
		}
		
		else
		{
			printf("Parametros invalidos... Recalcular");
		}	
		
	}
	
	//Região 2:
	else if (x>=128 && x<=191)
	{	
		configfinal=(x-(64*2))/2;
		configfinal=128+configfinal;
		
		if (configfinal<=255)
		{
			printf("STM32CubeIDE Dead Time: %1.0f",configfinal);
		}
		
		else
		{
			printf("Parametros invalidos... Recalcular");
		}
		
	}
	
	//Região 3:
	else if (x>=192 && x<=223)
	{
		configfinal=(x-(32*8))/8;
		configfinal=192+configfinal;
		
		if (configfinal<=255)
		{
			printf("STM32CubeIDE Dead Time: %1.0f",configfinal);
		}
		
		else
		{
			printf("Parametros invalidos... Recalcular");
		}
		
	}
	
	//Região 4:
	else if (x>=224)
	{
		configfinal=(x-(32*16))/16;
		configfinal=224+configfinal;
		
		if (configfinal<=255)
		{
			printf("STM32CubeIDE Dead Time: %1.0f",configfinal);
		}
		
		else
		{
			printf("Parametros invalidos... Recalcular");
		}
	}
	
	//Situação não prevista...
	else
	{
		printf("erro...");
	}
	
	printf("\r\n------------------------------------------------\r\n\r\n"); //Pula linha 2x.
	
	goto inicio; //Volto no início do programa...
	
}
