# Huffman_Compressor

Instruções rápidas em Português para compilar e executar as ferramentas incluídas neste repositório.

Requisitos
- g++ com suporte a C++17
- make

Compilar
-----------
Para compilar ambos os binários (Frequency Counter e Compressor/Decompressor):

```bash
make
```

Isso gera dois executáveis no diretório do projeto:
- `frequency_counter` — ferramenta que conta tokens/caracteres em arquivos fonte
- `compressor_decompressor` — ferramenta para compressão e descompressão (Huffman)

Você também pode compilar apenas um alvo:

```bash
make frequency_counter
# ou
make compressor_decompressor
```

Limpar build

```bash
make clean
```

Uso: Frequency Counter
------------------------
O `frequency_counter` calcula frequências de símbolos/palavras a partir de um arquivo fonte ou de todos os arquivos `.cpp` dentro de uma pasta (não recursivo).

Sintaxe:
```bash
./frequency_counter <arquivo_ou_pasta>
```

Exemplos:
- Processar um único arquivo:
```bash
./frequency_counter src/exemplo.cpp
```
- Processar todos os arquivos `.cpp` numa pasta (ex.: `Compressor_Decompressor/src`):
```bash
./frequency_counter Compressor_Decompressor/src
```

Arquivo de saída:
- O resultado é escrito em `frequency_sheet/output.txt` (este arquivo é criado/atualizado). O formato é uma lista de linhas com `"token" <espaco> <frequencia>`.

Uso: Compressor / Decompressor
--------------------------------
O binário `compressor_decompressor` tem duas operações:
- Compressão: `--compress` (ou `-c`)
- Descompressão: `--decompress` (ou `-d`)

IMPORTANTE: a implementação atual espera um arquivo de "frequency sheet" (gerado pelo `frequency_counter`) para construir a árvore de Huffman. Tipicamente você usará `frequency_sheet/output.txt`.

Compressão (exemplo):
```bash
./compressor_decompressor --compress frequency_sheet/output.txt path/para/arquivo_a_comprimir.cpp
```
- Saída: cria um ficheiro `path/para/arquivo_a_comprimir.cpp_compressed.bin` (ficheiro binário comprimido).

Descompressão (exemplo):
```bash
./compressor_decompressor --decompress frequency_sheet/output.txt path/para/arquivo_a_comprimir.cpp_compressed.bin
```
- Saída: cria um ficheiro com o nome original acrescido de `_decompressed`, por exemplo `path/para/arquivo_a_comprimir.cpp_decompressed`.
