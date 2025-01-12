# Tutorial: Instalação do Ambiente de Programação do Pico SDK no VS Code

Este tutorial vai guiar você no processo de instalação do ambiente de programação para o **Raspberry Pi Pico** usando o **Pico SDK** no **VS Code**.
Por enquanto apenas consegui embarcar códigos já prontos de outras pessoas pela internet. OBS: Sistema operacional Windows e estou considerando que você tem o C/C++ instalado.

## Passo 1. Instalar o Visual Studio Code

<details>
  <summary>Detalhes</summary>
  - Baixe o Visual Studio Code no [site oficial](https://code.visualstudio.com/).
  - Siga o assistente de instalação para a sua plataforma (Windows, macOS ou Linux).
  
  img
</details>

## Passo 2. Compilador Arm

<details>
  <summary>Detalhes</summary>
  - Baixe AArch32 bare-metal no formato .exe (executável) Link: https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
  - Cuidado que no final da instalação é importante você marcar a caixinha declarando que você deseja adicionar as variáveis de ambiente (Add Path to enviroment Variable)
  
  img
</details>

## Passo 3. Pico SDK

<details>
  <summary>Detalhes</summary>
  - Acesse o reposítorio: https://github.com/raspberrypi/pico-setup-windows/releases/tag/v1.5.1.
  - Clique em last release na direita inferior.
  - Baixe a última versão standalone no formato .exe
  - Abra o instalador como administrador e anote o local da instalação em algum canto.
  - No final escolha uma pasta de fácil acesso para você colocar os exemplos (blink,pwm,etc...) para que você possa testar ou aprender.
  
  img
</details>

## Passo 4. Variáveis de Ambiente
<details>
  <summary>Detalhes</summary>
  - Segure o botão Windows e aperte R.
  - No campo de texto escreva sysdm.cpl, vá em avançados e variáveis de ambiente.
  - A partir daqui você vai encontrar dois campos um das variáveis do usuario e outro das variáveis do sistema.
  - Em ambos você vai seguir o mesmo processo, primeiro clique em novo, irá aparecer dois campos.
  - Em nome da variável você irá inserir "PIKO_SDK_PATH" (sem aspas) 
  - Em valor da variável você irá inserir o diretório de onde você fez instalação do pico-sdk (Exemplo: C:\Program Files\Raspberry Pi\Pico SDK v1.5.1)
  - Confirme e novamente vamos clicar em novo em nome você irá inserir "PICO_TOOLCHAIN_PATH" (sem aspas)
  - Em valor da variável você irá inserir o diretório do pico-sdk propriamente dito (Exemplo: C:\Program Files\Raspberry Pi\Pico SDK v1.5.1\pico-sdk)
  - Agora que você fez isso em variáveis de usuário, faça o mesmo processo em variáveis do sistema.
  - Só faça esse processo caso as variáveis de ambiente ( "PIKO_SDK_PATH" e "PICO_TOOLCHAIN_PATH") não estiverem listadas.
  
  img
</details>

## Passo 5. Instalação e configuração das Extensões CMake, CMakeTools e Raspberry Pi Pico

<details>
  <summary>Detalhes</summary>
  - Abra o VScode vá no icone de extensões e instale o CMake e CMakeTools:
  
  img
  
  - O CMakeTools precisa ser configurado, clique na engranagem que aparece na tela do plug-in e selecione Settings.
  - Procure pelo nome CMake Path e confirme que está escrito "cmake" (sem aspas)
    
  img
  
  - Logo em baixo está "Cmake: Configure Enviroment" caso não haja nenhuma linha adicionada.
  - Clique em add e adicione em item "PICO_SDK_PATH" (sem aspas) e em value o diretório de instalação (Exemplo:C:\Program Files\Raspberry Pi\Pico SDK v1.5.1)
    
  img
  
  - Agora busque por generator e escreva "NMake Makefiles" (sem aspas)
    
  img
  
  - De volta ao menu de extensões procure por Raspberry Pi Pico e instale.
    
  img
  
</details>

## Passo 6. Testando Exemplos

<details>
  <summary>Detalhes</summary>
  - 
</details>
