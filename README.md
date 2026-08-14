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

### Em desenvolvimento

- [ ] Integração com webview (ponte C ↔ JS)
- [ ] Interface em HTML/CSS/JS
- [ ] Geração de executáveis (.exe para Windows, binário para Linux)

## Estrutura

```
ravenna-time/
├── build/
├── include/
│   └── date.h
├── src/
│   ├── date.c
│   └── main.c
├── README.md
├── Makefile
└── .gitignore
```

## Configuração para desenvolvimento

Após clonar o repositório, inicialize o submódulo da biblioteca `webview`:

```bash 
git submodule update --init --depth 1
```

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

## Futuras funcionalidades

- Interface desktop completa via webview
- Camada de polish visual (HTML/CSS/JS)
- Empacotamento final dos executáveis para Windows e Linux

## Licença

MIT