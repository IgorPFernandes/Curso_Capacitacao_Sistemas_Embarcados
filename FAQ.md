# FAQ - Problemas comuns na configuração da placa BitDogLab ❓❔

Lista de erros e soluções para a placa de prototipagem Raspberry Pi Pico W.

<!--toc:start-->
- [FAQ - Problemas comuns na configuração da placa BitDogLab](#faq-problemas-comuns-na-configuração-da-placa-bitdoglab)
  - [Não consigo usar o monitor serial](#não-consigo-usar-o-monitor-serial)
  - [Estou com erros de importação](#estou-com-erros-de-importação)
  - [Minha placa não aparece no Zadik](#minha-placa-não-aparece-no-zadik)
  - [A placa não aparece no gerenciador de dispositivos](#a-placa-não-aparece-no-gerenciador-de-dispositivos)
<!--toc:end-->

## Não consigo usar o monitor serial

- Use uma *baud rate* de 115200.
- Habilite a entrada serial usb. Para isso, coloque no seu `CMakeLists.txt` o seguinte:

```cmake
pico_enable_stdio_uart(neopixel_pio 0)
pico_enable_stdio_usb(neopixel_pio 1)
```

- Certifique-se que o driver USB Serial (CDC) está instalado na interface 0.
- Chame a função `stdio_init_all();` logo no inicio da `main`.

## Estou com erros de importação

- Use o botão `Clean CMake` da extensão. Ele irá remover o cache e os arquivos de build, fazendo uma compilação limpa novamente.
- Declare o uso de bibliotecas externas dentro do arquivo `CMakeLists`. Faça isso adicionando ou modificado a seguinte linha:

  ```cmake
  target_link_libraries([executavel] [biblioteca])
  ```

  Exemplo:

  ```cmake
  target_link_libraries(blink pico_cyw43_arch)
  ```

  > Dica: o nome vai ser o que está no include, sem o .h e com '_' no lugar de '/'.
  
## Minha placa não aparece no Zadik

- Confira se a placa está no modo *bootsel* (aparece como um pen drive)
- Vá em `Options -> List All Devices`.

## A placa não aparece no gerenciador de dispositivos

- Se não aparece no modo BOOTSEL: instale o driver WinUSB na interface 1
- Se não aparece no modo normal:  instale o USB Serial (CDC) na interface 0
