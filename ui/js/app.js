// ================================================================
// PASSO 0: Pegar referências dos elementos do DOM 
// ================================================================
// document.getElementById busca um elemento pelo atributo id="..."
// guardamos cada um numa constante para não precisar buscar de novo
// toda vez que precisarmos dele.
const form         = document.getElementById("form");
const date1Input   = document.getElementById("date1");
const horary1Input = document.getElementById("horary1");
const date2Input   = document.getElementById("date2");
const horary2Input = document.getElementById("horary2");

// querySelector busca por um seletor CSS qualquer (aqui, a classe .output)
const outputDiv    = document.querySelector(".output");

// O botão está dentro do form, sem ID. document.querySelector("button"),
// busca a primeira tag <button> encontrada no documento.
const submitButton = document.querySelector("button");

// ================================================================
// FUNÇÃO 1: buildDateJson(dateValue, timeValue)
// ================================================================
// Recebe duas strings vindas dos inputs: 
//   dateValue = "yyyy-mm-dd" (padrão do <input type="date">)
//   timeValue = "hh:mm:ss"   (padrão do <input type="time">)
// Devolve uma string JSON pronta, no formato que o parseDateJson (C++) espera.

function buildDateObject(dateValue, timeValue){
    // .split("-") quebra a string em pedaços, usando "-" como separador, 
    // e devolve um array. Ex: "2005-02-04".split("-") vira ["2005", "02", "04"]
    const dateParts = dateValue.split("-");
    
    // Mesma lógica pro horário, separador ":"
    const timeParts = timeValue.split(":");

    // Retornamos um OBJETO JS. O Webview.h serializa objetos passados 
    // como argumento diretamente como JSON de verdade - sem aspas extras
    // nem escaping. Se retornássemos uma string, o webview.h trataria o 
    // texto como um VALOR string e escaparia as aspas internas (\"year\" em vez de 
    // "year"), quebrando a busca por "},{" que o bridge.cpp faz para separar
    // as duas datas.
    //
    // Number(...) converte cada pedaço (que vem como string, ex: "02")
    // para números de verdade
    return {
        year  : Number(dateParts[0]),
        month : Number(dateParts[1]),
        day   : Number(dateParts[2]),
        hour  : Number(timeParts[0]),
        minute: Number(timeParts[1]),
        second: Number(timeParts[2]),
    }
}

// ================================================================
// FUNÇÃO 2: displayResult(responseJson)
// ================================================================
// Recebe o objeto que voltou do calculateDiff (C++) e escreve
// o resultado (ou erro) dentro da .output

function displayResult(response){
    // webview.h já entraga o retorno do C++ como objeto JS (parse automático),
    // então "response" já é um objeto - não precisa de JSON.parse aqui
    const result = response;

    // "in" checa se aquela chave existe dentro do objeto
    if ("error" in result){
        outputDiv.textContent = "Erro: " + result.error;
        return; // Encerra a função aqui, não executa o resto
    }

    // Se não é erro, result tem years/months/days/hours/minutes/seconds
    outputDiv.textContent =
        "A Distância Entre as Datas é de: " +
        result.years   + " ano(s), "     +
        result.months  + " mes(es), "    +
        result.days    + " dia(s), "     +
        result.hours   + " hora(s), "    +
        result.minutes + " minuto(s) e " +
        result.seconds + " segundo(s)";
}

// ================================================================
// FUNÇÃO 4: clearForm()
// ================================================================
// Zera os 4 campos e o output

function clearForm(){
    date1Input.value      = "";
    horary1Input.value    = "";
    date2Input.value      = "";
    horary2Input.value    = "";
    outputDiv.textContent = "";
}

// ================================================================
// FUNÇÃO 4: setButtonMode(mode)
// ================================================================
// Centraliza a troca de estado do botão num único lugar.
// mode é a string "calculate" ou "clear"

function setButtonMode(mode){
    submitButton.dataset.mode = mode;

    if (mode === "calculate"){
        submitButton.textContent = "CALCULAR";
    } else {
        submitButton.textContent = "LIMPAR";
    }
}

// ================================================================
// FUNÇÃO 5: handleSubmit(event)
// ================================================================
// Decide o que fazer quando o form é enviado dependendo do modo atual
// do botão.

// "async" antes de function permite usar "await" dentro da função.
// "await" pausa a execução até uma Promise ser resolvida - 
// necessário porque calculateDiff (bindado no webview) retorna uma 
// Promise, não o valor direto.

async function handleSubmit(event){
    // Impede o comportamento padrão do form, que seria recarregar a página
    event.preventDefault();

    if (submitButton.dataset.mode === "clear"){
        // Estamos em modo "LIMPAR": só limpa e volta pro modo calcular 
        clearForm();
        setButtonMode("calculate");
        return; // não executa o resto da função 
    }

    // Estamos em modo "CALCULAR": monta os dois Objetos de data
    const startObj = buildDateObject(date1Input.value, horary1Input.value);
    const endObj   = buildDateObject(date2Input.value, horary2Input.value);

    // Chama a função bindada pelo C++ (main.cpp: w.bind("calculateDiff", ...))
    // o await espera a Promise resolver e entregar o valor final direto
    const responseObj = await calculateDiff(startObj, endObj);

    displayResult(responseObj);
    setButtonMode("clear");
}

// ================================================================
// PASSO FINAL: registrar o listener
// ================================================================
// Toda vez que o form for submetido (Enter ou clique no botão),
// handleSubmite é chamada automáticamente, recebendo o evento.

form.addEventListener("submit", handleSubmit);

// Garante o estado inicial correto do botão ao carregar a página
setButtonMode("calculate");