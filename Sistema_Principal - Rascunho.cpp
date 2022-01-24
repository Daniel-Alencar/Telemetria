// Programa principal : Atmega328p + Telemetria + Cartão SD + Experimento


//Declarar bibliotecas,caso necessário
//Declarar frequência do atmega como 16 MHz


//Declarar variáveis
    //Sugestão : Uma variável do tipo BYTE(Caso possível), em que cada bit indicará se um componente está funcionando.
                //Isso evitará tentativas desnecessárias de usar um componente que não está sendo detectado por qualquer que seja o motivo
                    //Exemplo : 8 bits(1 Byte = 8 bits) 0000 0000 ; O primeiro(começando pela direita) representa se o módulo SD está funcionando ou não. 1 se sim, 0 se não.
                        //Portanto, toda vez que for executar algo do SD verifica nessa variável se o cartão SD está funcionando(ao verificar APENAS primeiro bit da direita)
                        //Setar um desses bits para representar a comunicação serial com o outro atmega328p. Se estiver funcionando, set como 1, se não set como 0.
                    //Seria interessante também se podessemos detectar a ativação do sistema de ignição(quando ativar o circuito, enviar um sinal pro atmega via telemetria. 
                        // Exemplo: Poderiamos utilizar um dos bits para registrar no sistema que a foi enviado o sinal para acionar a ignição(independente se realmente ignitou ou não)
                        //Também permitirá registrar em um dos bits que o foguete saiu da base, basta verificar a aceleração(Se ela for maior que um certo valor, pra evitar erro)
                            //Isso permmitiria saber se um foguete está subindo,descendo ou parado. útil tanto pra análise a posteriori, quanto para a interface do computador no solo.


void setup()
{
    //Configurar : Telemetria, Cartão SD e experimento.
    // Lembrando que cada um desses não são funções essenciais, portanto é necessário colocar uma espécie de "time-out" para a inicialização de cada.
        //Se houver um timeout, escrever no respectivo bit da variável do tipo BYTE.

}


void loop main()
{
/*Importante : A função do sistema principal é :
                1-> Registrar as informações recebida via SERIAL do sistema de recuperação no cartão SD, tal como Resultado do filtro de kalman, resultado do BMP e do MPU.
                        Registrar o tempo também baseado no PRÓPRIO tempo do sistema principal.
                2-> Utilizar as MESMAS informações que foram escritas no cartão SD e enviar na telemetria para a base principal.
                3-> Essa escrita(item 1) e envio(item 2) APENAS ocorrem quando recebem informação via serial.
*/

//Inicialmente, executar o que for necessário e INDEPENDENTE(exemplo : experimento) de receber dados da serial tais como:
    //  Verificar o funcionamento da telemetria para atualizar seu bit correspondente a cada iteração?
    //  Realização do experimento,caso utilize recursos computacionais.
    //  Atualizar variáveis locais, caso necessário

//Em seguida, verificar se foi recebido informações via serial do outro atmega328p(sistema de recuperação)
    //Caso sim, atualizar as variáveis correspondentes com os valores recebidos.
            //Registrar no SD, caso o bit correspondente esteja indicando seu funcionamento
            //Enviar via telemetria, caso o bit correspondente indique seu funcionamento. Sugestão: Enviar na telemetria também a variável do tipo BYTE que diz se um componente está funcionando ou não. Ocupa 1 Byte.
    //Caso não seja recebido nada, não fazer nada(nem telemetria, nem registro no SD.)

}