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

## Futuras funcionalidades

- Interface desktop completa via webview
- Camada de polish visual (HTML/CSS/JS)
- Empacotamento final dos executáveis para Windows e Linux

## Licença

MIT