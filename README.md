# climate_controller-arduino
Dispositivo protótipo de climatizador concebido enquanto eu estagiava no Hospital Martagão Gesteira, em 2017. 

----

## Iniciando

**W.I.P.**
_work in progress_

```console
git clone
```

Segundo [esse link](https://www.arduino.cc/en/guide/libraries), para tornar tudo mais eficiente, você deve copiar o conteúdo da pasta Libraries para a sua pasta de bibliotecas, na pasta de **Sketchbook** do Arduino IDE:


#### macOS ou GNU/Linux
```bash
cp climate_controller-arduino/libraries/*  ~/Documents/Arduino/libraries/
```
_Acho que "Documents" pode estar diferente no seu caminho... tente "*Documents" !_

#### Windows
```console
cd climate_controller-arduino\libraries\*  %USERDIR%\Documents\Arduino\libraries\
```


-----

### Sobre as bibliotecas


>ArduinoJSON
> - Melhor que a biblioteca que usei anteriormente (esqueci nome)

>IRRemote com armazenamento de dados na PROGMEM
> - Significa: **economizar MUITA SRAM**

> etc e tal...

-----

### Compilando com o AVR-GCC do Arduino IDE

Verificar otimizações...

----


## Contribuindo

### Não autorizo ninguém a utilizar esse código - apenas visualizá-lo.
Por enquanto, como não disponibilizei licença: qualquer utilização, reprodução ou edição desse código, **sem sua devida autorização**, está expressamente *PROIBIDA*.


----

## Agradecimentos

* Obrigado ao @bengtmartensson (que indicou a alteração na lib IRRemote)[https://github.com/z3t0/Arduino-IRremote/issues/238]
* Obrigado Victor Ben-Hur pela oportunidade e pelo desafio de testar meus conhecimentos.
* Obrigado Lucas Borges (@1uuc4asb) pelas novas ideias para otimização.
