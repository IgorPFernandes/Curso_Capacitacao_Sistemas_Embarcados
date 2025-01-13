# Tutorial: Instalação do Ambiente de Programação do Pico SDK no VS Code

Este tutorial vai guiar você no processo de instalação do ambiente de programação para o **Raspberry Pi Pico** usando o **Pico SDK** no **VS Code**.<br>
Por enquanto, apenas consegui embarcar códigos já prontos de outras pessoas pela internet. **OBS**: Sistema operacional Windows e estou considerando que você tem o **C/C++** instalado.<br>

## Passo 1. Instalar o Visual Studio Code

<details>
  <summary>Detalhes</summary>
  
  <br>
  
  - Baixe o Visual Studio Code no [site oficial](https://code.visualstudio.com/).<br>
  - Siga o assistente de instalação para a sua plataforma (Windows, macOS ou Linux).<br>
</details>

## Passo 2. Compilador Arm

<details>
  <summary>Detalhes</summary>
  
  <br>
  
  - Baixe AArch32 bare-metal no formato .exe (executável). Link: https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads<br>
  - Cuidado que no final da instalação é importante você marcar a caixinha declarando que você deseja adicionar as variáveis de ambiente (Add Path to Environment Variable).<br>
  <br>
  
  ![gnu arm](img/aarch32bare-metal.png)<br>
  
</details>

## Passo 3. Pico SDK

<details>
  <summary>Detalhes</summary>
  
  <br>
  
  - Acesse o repositório: https://github.com/raspberrypi/pico-setup-windows/releases/tag/v1.5.1.<br>
  - Clique em last release na direita inferior.<br>
  - Baixe a última versão standalone no formato .exe<br>
  - Abra o instalador como administrador e anote o local da instalação em algum canto.<br>
  - No final, escolha uma pasta de fácil acesso para você colocar os exemplos (blink, pwm, etc...) para que você possa testar ou aprender.<br>
  <br>
  
  ![pico](img/pico-sdk.png)<br>
  
</details>

## Passo 4. Variáveis de Ambiente

<details>
  <summary>Detalhes</summary>
  
  <br>
  
  - Segure o botão Windows e aperte R.<br>
  - No campo de texto escreva **sysdm.cpl**, vá em **Avançados** e **Variáveis de Ambiente**.<br>
  - A partir daqui, você vai encontrar dois campos: um das variáveis do usuário e outro das variáveis do sistema.<br>
  - Em ambos você vai seguir o mesmo processo: primeiro clique em **Novo**.<br>
  - Irá aparecer dois campos:<br>
    - Em **Nome da variável** você irá inserir "PICO_SDK_PATH" (sem aspas).<br>
    - Em **Valor da variável** você irá inserir o diretório de onde você fez a instalação do pico-sdk (Exemplo: **C:\Program Files\Raspberry Pi\Pico SDK v1.5.1**).<br>
  - Confirme e, novamente, vamos clicar em **Novo**.<br>
  - Em **Nome da variável** você irá inserir "PICO_TOOLCHAIN_PATH" (sem aspas).<br>
  - Em **Valor da variável** você irá inserir o diretório do pico-sdk propriamente dito (Exemplo: **C:\Program Files\Raspberry Pi\Pico SDK v1.5.1\pico-sdk**).<br>
  - Agora que você fez isso em variáveis de usuário, faça o mesmo processo em variáveis do sistema.<br>
  - Só faça esse processo caso as variáveis de ambiente ("PIKO_SDK_PATH" e "PICO_TOOLCHAIN_PATH") não estiverem listadas.<br>
  <br>
  
  ![Variáveis de Ambiente](img/varamb.png)<br>
  
</details>

## Passo 5. Instalação e configuração das Extensões CMake, CMakeTools e Raspberry Pi Pico

<details>
  <summary>Detalhes</summary>
  
  <br>
  
  - Abra o VSCode, vá no ícone de extensões e instale o **CMake** e **CMakeTools**:<br>
  <br>
  
  ![cmake e cmaketools](img/cmake_cmaketools.png)<br>
  
  - O **CMakeTools** precisa ser configurado. Clique na engrenagem que aparece na tela do plug-in e selecione **Settings**.<br>
  - Procure pelo nome **CMake Path** e confirme que está escrito "cmake" (sem aspas).<br>
  <br>
  
  ![cmake path](img/cmakepath.png)<br>
  
  - Logo em baixo está "CMake: Configure Environment". Caso não haja nenhuma linha adicionada, clique em **Add** e adicione o item "PICO_SDK_PATH" (sem aspas) e, em **Value**, o diretório de instalação (Exemplo: **C:\Program Files\Raspberry Pi\Pico SDK v1.5.1**).<br>
  <br>
  
  ![configuração de ambiente](img/configenv.png)<br>
  
  - Agora busque por **generator** e escreva "NMake Makefiles" (sem aspas).<br>
  <br>
  
  ![generator](img/generator.png)<br>
  
  - De volta ao menu de extensões, procure por **Raspberry Pi Pico** e instale.<br>
  <br>
  
  ![raspberry pi pico extensão](img/raspb.png)<br>
  
</details>

## Passo 6. Instalador Zadig, Driver RP2040 para embarcar diretamente pelo VScode

<details>
  <summary>Detalhes</summary>
  <br>
  
  - Atavés do link: https://zadig.akeo.ie/. Baixe a última versão. <br>
  - Quando finalizado inicialize o executável como administrador e verifique se o driver em questão está como "RP2 Boot (Interface 1)"
  - Confirme a instalação.
</details>

## Passo 7. Testando Exemplos

<details>
  <summary>Detalhes</summary>
  <br>
  
  - Abra o VScode, selecione o icone da extensão Raspberry Pi Pico que aparece a sua esquerda e clique em "New Project From Examples". <br>
  - A partir daqui iremos clicar na seta da primeira caixa de seleção e selecionar o arquivo blink. <br>
  - Selecione também o boardtype como Pico W e em baixo escolha o diretorio que deseja armazenar o exemplo. <br>
  
  ![create](img/create.png)<br>
  
  - Após isso clique em create, irá sugir uma nova aba do VScode onde iremos ter o código em um arquivo chamado blink.c <br>
  - Quando selecionar o código veja que na parte inferior da tela tem um botão chamado "compile". <br>
  - Agora que o código foi processado pelo compilador é gerado um arquivo .uf dentro da sua pasta. <br>
  - Você poderá embarcar o código, mas antes vamos aprender a deixar o nosso pi pico W no modo bootsel. <br>
</details>

## Passo 8. Modo Bootsel

<details>
  <summary>Detalhes</summary>
  
  <br>
  
  - Conecte o dispositivo via USB, caso apareça um novo particionamento (Ex: Como um prendive sendo colocado) é porque já está em modo bootsel e não precisa prosseguir.
  - Para colocar no modo bootsel, mantenha pressionado o botão branco bootsel da imagem por 3 segundos. <br>

  ![bootsel](img/botboot.jpg)<br>

  - Em seguida pressione o botão reset da imagem e solte ambos botões. <br>

  ![reset](img/botreset.jpg)<br>

  - Quando aparecer um novo compartimento no seu computador (Ex: Como um pendrive conectando) é porque foi um sucesso. <br>
  - Sempre que precisar embarcar um novo código é necessário entrar no modo bootsel. <br>
  - Agora volte ao VScode (Na folder blink), clique no icone da extensão pi pico projects e selecione Run Project (USB) <br>

  ![run](img/run.png)<br>

  - Parabéns!!! Você embarcou seu primeiro projeto no BitDogLab!! <br>

  ![blink1](img/blink2.gif)
  
</details>
