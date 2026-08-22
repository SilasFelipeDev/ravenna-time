# Este arquivo existe para permitir que o executável ravenna seja
# autossuficiente (um unico binário, sem arquivos externos).
#
# Ele lê o conteudo de um arquivo .html e gera um arquivo .h com esse
# conteudo lido, transformado em um String C. Esse .h é incluido pelo main.cpp
# e compilado junto com o resto do programa, então o HTML fica "soldado" 
# dentro do executável, sem precisar ser lido do disco em tempo de execução.

import sys # da acesso a sys.argv, a lista de argumentos passados na linha de comando

def embed(html_path, css_path, output_path, var_name):
    # abre o arquivo .html de entrada em modo leitura (texto, UTF-8)
    # o "with" garante que o arquivo seja fechado sozinho ao final do bloco
    with open(html_path, 'r', encoding='utf-8') as html:
        content = html.read() # lê todo o conteudo do arquivo para uma unica string

    # abre o arquivo .css de entrada em modo de leitura (texto, UTF-8)
    with open(css_path, 'r', encoding='utf-8') as css:
        css_content = css.read()

    style_block = f"<style>\n{css_content}\n</style>"
    content = content.replace("<!-- CSS_HERE -->", style_block)

    # Prepara o conteudo para virar uma String C valida (escaping):
    # 1) toda barra invertida vira barra dupla, senão o C interpreta errado
    # 2) toda aspas dupla vira aspas escapadas, senão o C acha que a string terminou ali
    # 3) toda quebra de linha fecha a string atual e abre outra na linha seguinte
    #    (strings C adjacentes são concatenadas automaticamente pelo compilador)
    escaped = content.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n"\n"')

    # abre o arquivo .h de saida em modo escrita
    with open(output_path, 'w', encoding='utf-8') as f:
        # escreve a declaração C final:
        # #pragma once evita que o header seja incluido duas vezes
        # a variavel recebe o nome passado em var_name (ex: INDEX_HTML) 
        f.write(f'#pragma once\nstatic const char* {var_name} = \n"{escaped}";\n')

# só executa embed(...) se o script for rodado diretamente por esse arquivo
# (não executa se este arquivo for importado por outro script python)
if __name__ == "__main__":
    # Pega os 4 argumentos da linha de comando:
    # sys.argv[1] = caminho do .html de entrada
    # sys.argv[2] = caminho do .css de entrada
    # sys.argv[3] = caminho do .h de saida
    # sys.argv[4] = nome da variavel C a ser gerada
    embed(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])