# Lista 1

### Resposta Dissertativa da Questão 8:
Uma possível configuração nos buffers é utilizando 6 floats para cada vértice, de forma que os 3 primeiros correspondam à localização X, Y e Z, e os últimos 3 correspondam à cor RGB. Para utilizar essas informações, precisamos setar dois attribute pointers: o primeiro para as posições, com 3 floats e stride de 6 floats, começando no índice 0; o segundo para as cores, com 3 floats e stride de 6 floats, começando no índice 1 (floats nas posições 3, 4 e 5 do array); o vertex shader para esse exercício precisa utilizar duas locations para extrair ambas informações do vértice, que podem ser identificadas a partir das informações passadas na função glVertexAttribPointer

### Instruções
- Cada exercício tem uma função que retorna um VAO (nomeada com ex5, ex6, etc) e uma função que faz o desenho do conteúdo *bufferizado* (nomeada com drawEx5, drawEx6, etc., localizadas dentro do loop principal).
- Para executar um exercício, basta "descomentar" as duas funções chamadas, incluindo a(s) linha(s) acima, que contém valores específicos para cada exercício (comentando as que linhas de exercícios não estavam comentados) e executar.
- Para o exercício 8, também é necessário comentar a inicialização dos shaders usuais e "descomentar" o shader específico do exercício 8.