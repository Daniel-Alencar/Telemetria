- **Objetivo**: 
  Testar o armazenamento e a telemetria em conjunto.

- **Descrição**: 
  Teremos dois circuitos:
    - circuito ‘foguete’:
      - No ‘foguete’, coletamos os dados: tempo, altitude, temperatura e acelerômetro e os enviamos via telemetria para o 'solo'. Logo após isso, gravamos estes mesmos dados no cartão SD.
    - circuito ‘solo’:
      - No ‘solo’, recebemos os dados e imprimimos na Serial. E após um tempo de 40s em operação, o circuito envia uma mensagem para o ‘foguete’ (simulando a ativação manual do paraquedas). Ao qual, o circuito ‘foguete’ reage acendendo um LED.

  OBS.: Somente o tempo (em segundos) era uma informação real, pois os outros dados tinham valores padrões de retorno.

- **Simulado**: Não

- **Resultado**: Bem sucedido.
