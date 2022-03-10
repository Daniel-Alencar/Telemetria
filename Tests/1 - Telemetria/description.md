- **Objetivo**: 
  Testar o envio e o recebimento de dados.

- **Descrição**: 
  Tínhamos dois circuitos com o NRF24L01+, um circuito que iria enviar de forma alternada os valores ‘0’ e ‘1’, trocando o valor de 2 em 2 segundos. Já o outro circuito teria dois leds. Se o valor recebido fosse ‘0’, o LED 0 seria ligado. Porém, se o valor recebido fosse ‘1’, o LED 1 seria ligado.

- **Simulado**: Não

- **Resultado**: Bem sucedido.

Este teste a princípio deu o erro ‘Transmission failed or timeout’. Procurando possíveis resoluções para o erro, encontramos o seguinte:
- Colocar um capacitor conectado ao VCC e o GND do NRF24L01.
- Programar na configuração do NRF24L01+:
  - radio.setAutoAck(false) logo após o radio.begin()

No fim, a segunda alternativa foi o que resolveu o nosso problema e o circuito passou a funcionar como o esperado.
