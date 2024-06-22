[![✗](https://img.shields.io/badge/Release-v1.0.0-ffb600.svg?style=for-the-badge)](https://github.com/agustin-golmar/Flex-Bison-Compiler/releases)

[![✗](https://github.com/agustin-golmar/Flex-Bison-Compiler/actions/workflows/pipeline.yaml/badge.svg?branch=production)](https://github.com/agustin-golmar/Flex-Bison-Compiler/actions/workflows/pipeline.yaml)

# Flex-Bison-Compiler

A base compiler example, developed with Flex and Bison.

* [Environment](#environment)
* [CI/CD](#cicd)
* [Recommended Extensions](#recommended-extensions)
* Installation
  * [Docker](doc/readme/Docker.md)
  * [Microsoft Windows](doc/readme/Windows.md)
  * [Ubuntu](doc/readme/Ubuntu.md)

## Environment

Set the following environment variables to control and configure the behaviour of the application:

|Name|Default|Description|
|-|:-:|-|
|`LOG_IGNORED_LEXEMES`|`true`|When `true`, logs all of the ignored lexemes found with Flex at DEBUGGING level. To remove those logs from the console output set it to `false`.|
|`LOGGING_LEVEL`|`INFORMATION`|The minimum level to log in the console output. From lower to higher, the available levels are: `ALL`, `DEBUGGING`, `INFORMATION`, `WARNING`, `ERROR` and `CRITICAL`.|

## CI/CD

To trigger an automatic integration on every push or PR (_Pull Request_), you must activate _GitHub Actions_ in the _Settings_ tab. Use the following configuration:

|Key|Value|
|-|-|
|Actions permissions|Allow all actions and reusable workflows|
|Artifact and log retention|`30 days`|
|Fork pull request workflows from outside collaborators|Require approval for all outside collaborators|
|Workflow permissions|Read repository contents and packages permissions|
|Allow GitHub Actions to create and approve pull requests|`false`|

After integration is done, change the badges of this `README.md` to point to the new repository.

## Recommended Extensions

* [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
* [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
* [Yash](https://marketplace.visualstudio.com/items?itemName=daohong-emilio.yash)


<h1>=== 𝑀𝒶𝓇𝒾𝓂𝒷𝒶 # ===</h1>

#Bienvenidos al Proyecto Especial de la materia 𝒜𝓊𝓉ó𝓂𝒶𝓉𝒶𝓈, 𝒯𝑒𝑜𝓇í𝒶 𝒹𝑒 𝐿𝑒𝓃𝑔𝓊𝒶𝒿𝑒𝓈 𝓎 𝒞𝑜𝓂𝓅𝒾𝓁𝒶𝒹𝑜𝓇𝑒𝓈

#El objetivo de este trabajo es desarrollar un lenguaje para generar partituras musicales 
    de una forma más simple que las disponibles en el mercado.


<h2>============ 𝐼𝒩𝒮𝒯𝑅𝒰𝒞𝒞𝐼𝒪𝒩𝐸𝒮 𝒟𝐸 𝒰𝒮𝒪 =============</h2>

    
    #Clonar repositorio Marimba#.
    #Correr este comando para generar arcvhivos ejecutables (se asume entorno de linux):

        >>>  <project_root>/script/ubuntu/build.sh

        #<project_root> es el path hasta el directorio root del proyecto.
    
    #Correr este comando para parsear un archivo .msh (unicado en root del proyecto):

        >>>  ./script/ubuntu/generate.sh <path_to_file>

        #<path_to_file> es el path al archivo .msh que queremos parsear.

        #El resultado son dos archivos, un midi y un .pdf

    #OBSERVACIONES:
        #Es necesario contar con la version 18 de Java, así como tener Maven y musescore instalados

