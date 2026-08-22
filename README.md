# ravenna-time

Um projeto de estudos em C focado na criação de uma aplicação desktop híbrida, unindo lógica de negócio em C com uma interface em HTML/CSS/JS via webview.

O objetivo deste repositório é servir como um laboratório de aprendizado para aprofundar conhecimentos em C (structs, ponteiros, alocação dinâmica, builds multiplataforma) e explorar a integração entre C e tecnologias web através da biblioteca webview.

## Objetivos

- Implementar lógica de cálculo de diferença entre datas em C.
- Validar toda a lógica via terminal antes de qualquer camada de interface.
- Integrar a lógica em C com uma interface gráfica via webview.
- Gerar executáveis para Windows e Linux.
- Organizar o código em múltiplos arquivos seguindo boas práticas.

## Funcionalidades

### Concluídas

- [x] Cálculo de diferença entre duas datas (dia, mês, ano, hora, minuto, segundo)
- [x] Validação de datas, considerando anos bissextos
- [x] Testes manuais via terminal (diversos cenários, incluindo bordas de mês e ano)
- [x] Build automatizado com Makefile (Windows e Linux)
- [x] Ponte C++ (bridge) compilando com a biblioteca webview (Windows e Linux)
- [x] Janela nativa via webview, com HTML embutido no executável em tempo de build

### Em desenvolvimento

- [ ] Interface em HTML/CSS/JS
- [ ] Geração de executáveis (.exe para Windows, binário para Linux)

## Estrutura

```
ravenna-time/
├── build/
├── include/
│   ├── bridge.h
│   └── date.h
├── src/
│   ├── bridge.cpp
│   ├── date.c
│   ├── main.cpp
│   └── terminal_test.c
├── tools/
│   └── embed_html.py
├── ui/
│   └── index.html
├── vendor/
│   ├── webview/
│   └── webview2-headers/
├── README.md
├── Makefile
└── .gitignore
```

## Configuração para desenvolvimento

Após clonar o repositório, inicialize o submódulo da biblioteca `webview`:

```bash
git submodule update --init --depth 1
```
O processo de build depende de **Python 3**, usado para embutir o HTML da interface diretamente no executável final. Certifique-se de ter o Python 3 instalado e disponível no terminal antes de compilar.

### WINDOWS: obtendo os headers do WebView2

No Windows, a interface gráfica usa o beckend **Microsoft Edge WebView2**. A biblioteca `webview` não inclui o header `WebView2.h` - ele precisa ser **baixado separadamente**, direto do pacote oficial da Microsoft e **copiado manualmente** para `vendor/webview2-headers/`, pois não é versionado no repositório (arquivo grande e específico do Windows).

1. Baixe o pacote (é um `.zip` disfarçado de `.nupkg`).
   No diretório do projeto, na raiz:

```powershell
   Invoke-WebRequest -Uri
"https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2" -OutFile webview2.nupkg
```

> Se usar `curl.exe` em vez do `Invoke-webRequest`, confira o tamanho do arquivo baixado antes de seguir (comando `Get-Item webview2.nupkg`) - o `curl.exe` pode falhar silenciosamente e salvar um arquivo de erro pequeno em vez do pacote real. É esperado um arquivo de aproximadamente 9MB.

2. Extraia o pacote:

```powershell
   mkdir libs\webview2
   tar -xr webview2.nupkg -C libs\webview2
```

3. Copie os dois arquivos necessários para `vendor/webview2-headers/`, o caminho dentro do pacote extraído é sempre este:<br>

   > libs\webview2\build\native\include\WebView2.h <br>
   > libs\webview2\build\native\include\WebView2EnvironmentOptions.h

4. Após copiar, pode apagar a pasta `libs/` inteira e o arquivo `webview2.nupkg` - ambos não são mais necessários.

### LINUX: instalando as dependências do GTK3/WebKitGTK

No Linux, a interface gráfica usa **GTK3** (janela e widgets nativos) com **WebKitGTK** (motor de renderização HTML/CSS/JS, baseado no WebKit). Diferente do Windows, aqui não há headers para copiar manualmente - as bibliotecas de desenvolvimento precisam apenas estar **instaladas no sistema**, e o Makefile descobre automaticamente os caminhos de include e as libs de link via `pkg-config`.

1. Instale as bibliotecas de desenvolvimento:

```bash
sudo apt update
sudo apt install -y libgtk-3-dev libwebkit2gtk-4.1-dev
```

2. Rode o build normalmente:

```bash
make
```

> Essa instalação é feita no sistema, não no repositório - ela não é versionada e precisa ser repetida em cada ambiente novo (uma nova instação da distro, um novo Codespace, etc.).

Validado em ambiente Linux via GitHub Codespaces.

## Interface embutida no executável

A interface (`ui/index.html`) não é lida do disco em tempo de execução - ela é convertida em uma string C durante o build (via `tools/embed_html.py`) e compilada diretamente dentro do binário. O resultado é um executável autossuficiente: nenhum arquivo `.html` precisa acompanhar o `.exe`/binário para a aplicação funcionar.

Esse passo roda automáticamente como parte do `make`, sempre que `ui/index.html` for modificado.

## Futuras funcionalidades

- Interface desktop completa via webview
- Camada de polish visual (HTML/CSS/JS)
- Empacotamento final dos executáveis para Windows e Linux

## Licença

MIT
