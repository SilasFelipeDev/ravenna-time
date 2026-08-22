/*
    main.cpp 
    Ponto de entrada do ravenna-time: abre a janela webview,
    expoe calculateDiff pro JS, e carrega a UI embutida.
*/

#include "webview/webview.h" // API C++ da lib webview
#include "ui_html.h"         // gerado pelo tools/embed_html.py, contem INDEX_HTML
#include "bridge.h"          // declaracao de calculateDiff

int main(){
    webview::webview w(true, nullptr);

    w.set_title("Ravenna Time");
    w.set_size(800, 600, WEBVIEW_HINT_NONE);

    // expoe calculateDiff (definida em bridge.cpp) pro JS
    w.bind("calculateDiff", calculateDiff);

    // carrega o HTML embutido em build-time
    w.set_html(INDEX_HTML);

    w.run();

    return 0;
}