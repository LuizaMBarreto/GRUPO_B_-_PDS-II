# Banco de Questões de Cálculo I

Este documento reúne o banco de questões matemáticas que alimentam as batalhas do jogo contra as Provas de Cálculo I. 
Cada questão segue o **padrão de roteiro do livro de Cálculo (James Stewart)**, explicitando:
1. O diagnóstico da questão (indeterminação / formato).
2. As técnicas matemáticas utilizadas (que se traduzem nas **Habilidades do Jogador** que causam dano preparatório).
3. O teorema/fechamento que dispara a finalização (`tentarFinalizar()`), zerando a vida restante da questão.

---

## Tabela de Dificuldade e Vida Fixa

| Nível | Dificuldade Numérica | Vida de Resolução Fixa | Estrutura Típica de Resolução |
| :---: | :---: | :---: | :--- |
| **Fácil** | `1` | **50 HP** | 1 técnica preliminar (dano parcial) + 1 finalização. |
| **Média** | `2` | **75 HP** | 2 técnicas preliminares (danos parciais) + 1 finalização. |
| **Difícil** | `3` | **100 HP** | Múltiplas manipulações/técnicas encadeadas + 1 finalização. |

---

## Modelo de Preenchimento

Para adicionar novas questões, basta copiar o bloco abaixo e preencher com um exercício do Stewart:

```markdown
### [ID]: [Título da Questão]
* **Prova:** P1 (Limites) | P2 (Derivadas) | P3 (Integrais) | P4 (Geral)
* **Dificuldade:** Fácil (50 HP) | Média (75 HP) | Difícil (100 HP)
* **Enunciado:** [Expressão matemática clara]
* **Dica (`fornecerDica()`):** [Texto da dica]

#### Roteiro de Resolução:
1. **Diagnóstico Inicial:**
   - [Identificação: Ex: Forma indeterminada 0/0, produto de funções, etc.]
2. **Etapa(s) Preliminar(es) — Técnicas Aplicadas:**
   - **Técnica 1:** [Nome da Regra/Método] -> *Habilidade correspondente*. Causa [X] de dano.
   - **Desenvolvimento:** [Cálculo matemático].
3. **Etapa de Conclusão / Fechamento:**
   - **Técnica de Fechamento:** [Substituição Direta / Avaliação de Limites] -> Dispara `tentarFinalizar()`.
   - **Resposta Final:** [Valor ou expressão final].
4. **Contra-ataque da Questão:**
   - **Ataque:** [Nome do golpe] -> Cansaço [+X].
```

---

## Questões Cadastradas

### Prova 1: Limites e Continuidade (P1)

#### `Q_LIM_01`: Limite Polinomial por Diferença de Quadrados
* **Prova:** P1 (Limites)
* **Dificuldade:** Fácil (50 HP)
* **Enunciado:** Calcule o limite:
  $$\lim_{x \to 3} \frac{x^2 - 9}{x - 3}$$
* **Dica (`fornecerDica()`):** *"O numerador é uma diferença de quadrados: $x^2 - 9 = (x - 3)(x + 3)$."*

##### Roteiro de Resolução (Stewart Cap. 2):
1. **Diagnóstico Inicial:** A substituição direta com $x = 3$ resulta na forma indeterminada $\frac{0}{0}$. Não podemos aplicar a lei do quociente diretamente.
2. **Etapa 1 (Técnica: Fatoração de Diferença de Quadrados):**
   - Fatoramos o numerador: $\frac{(x - 3)(x + 3)}{x - 3}$.
   - Para $x \neq 3$, cancelamos o fator comum $(x - 3)$, simplificando para $(x + 3)$.
   - *No Jogo:* Habilidade **"Fatoração Algébrica"** causa **25 de dano** (Vida: $50 \to 25$) e marca a questão como apta para finalização (`_etapaPreviaConcluida = true`).
3. **Etapa de Conclusão (Técnica: Substituição Direta):**
   - Aplicamos a propriedade da substituição direta: $\lim_{x \to 3} (x + 3) = 3 + 3 = 6$.
   - *No Jogo:* Ação `tentarFinalizar()` é bem-sucedida. A vida vai **direto a 0**!
   - **Resposta Final:** $\mathbf{L = 6}$.
4. **Contra-ataque da Questão:**
   - **Ataque:** *"Indeterminação 0/0"* $\rightarrow$ Causa **+15 de Cansaço**

---

#### `Q_LIM_02`: Limite com Racionalização de Raiz
* **Prova:** P1 (Limites)
* **Dificuldade:** Média (75 HP)
* **Enunciado:** Calcule o limite:
  $$\lim_{t \to 0} \frac{\sqrt{t^2 + 9} - 3}{t^2}$$
* **Dica (`fornecerDica()`):** *"Multiplique numerador e denominador pela expressão conjugada $(\sqrt{t^2 + 9} + 3)$."*

##### Roteiro de Resolução (Stewart Cap. 2):
1. **Diagnóstico Inicial:** A substituição direta com $t = 0$ fornece $\frac{\sqrt{9}-3}{0} = \frac{0}{0}$.
2. **Etapa 1 (Técnica: Multiplicação pelo Conjugado):**
   - Racionalizamos o numerador:
     $$\frac{(\sqrt{t^2+9} - 3)(\sqrt{t^2+9} + 3)}{t^2(\sqrt{t^2+9} + 3)} = \frac{(t^2+9) - 9}{t^2(\sqrt{t^2+9} + 3)} = \frac{t^2}{t^2(\sqrt{t^2+9} + 3)}$$
   - *No Jogo:* Habilidade **"Multiplicar pelo Conjugado"** causa **35 de dano** (Vida: $75 \to 40$).
3. **Etapa 2 (Técnica: Cancelamento Algébrico):**
   - Cancelamos $t^2$ para $t \neq 0$: resta $\frac{1}{\sqrt{t^2 + 9} + 3}$.
   - *No Jogo:* Habilidade **"Simplificação de Termos"** causa **15 de dano** (Vida: $40 \to 25$) e libera a finalização.
4. **Etapa de Conclusão (Técnica: Avaliação do Limite):**
   - Substituímos $t = 0$: $\frac{1}{\sqrt{0 + 9} + 3} = \frac{1}{3 + 3} = \frac{1}{6}$.
   - *No Jogo:* Ação `tentarFinalizar()` zera a vida restante da questão!
   - **Resposta Final:** $\mathbf{L = \frac{1}{6}}$.
5. **Contra-ataque da Questão:**
   - **Ataque:** *"Pegadinha do Conjugado"* $\rightarrow$ Causa **+12 de Cansaço**.

---

### Prova 2: Derivadas e Taxas Relacionadas (P2)

#### `Q_DER_01`: Derivação com Regra da Cadeia
* **Prova:** P2 (Derivadas)
* **Dificuldade:** Média (75 HP)
* **Enunciado:** Encontre a derivada da função:
  $$f(x) = (3x^2 - 5x + 2)^4$$
* **Dica (`fornecerDica()`):** *"Identifique a função externa $u^4$ e a função interna $u = 3x^2 - 5x + 2$. Aplique $\frac{d}{dx}[f(u)] = f'(u) \cdot u'$."*

##### Roteiro de Resolução (Stewart Cap. 3):
1. **Diagnóstico Inicial:** Função composta do tipo $[g(x)]^n$. Requer a Regra da Cadeia combinada com a Regra da Potência.
2. **Etapa 1 (Técnica: Diferenciação da Função Externa):**
   - Derivando a parte externa em relação a $u$: $\frac{d}{du}[u^4] = 4u^3 = 4(3x^2 - 5x + 2)^3$.
   - *No Jogo:* Habilidade **"Regra da Potência Externa"** causa **35 de dano** (Vida: $75 \to 40$).
3. **Etapa 2 (Técnica: Diferenciação da Função Interna):**
   - Derivando o polinômio interno: $\frac{d}{dx}[3x^2 - 5x + 2] = 6x - 5$.
   - *No Jogo:* Habilidade **"Derivação de Polinômio Interno"** causa **20 de dano** (Vida: $40 \to 20$) e libera a finalização.
4. **Etapa de Conclusão (Técnica: Multiplicação pela Regra da Cadeia):**
   - Produto final: $f'(x) = 4(3x^2 - 5x + 2)^3 \cdot (6x - 5)$.
   - *No Jogo:* Ação `tentarFinalizar()` zera a vida da questão!
   - **Resposta Final:** $\mathbf{f'(x) = 4(6x - 5)(3x^2 - 5x + 2)^3}$.
5. **Contra-ataque da Questão:**
   - **Ataque:** *"Esquecer a Derivada Interna"* $\rightarrow$ Causa **+18 de Cansaço**.

---

#### `Q_DER_02`: Derivação com Regra do Quociente
* **Prova:** P2 (Derivadas)
* **Dificuldade:** Fácil (50 HP)
* **Enunciado:** Derive a função:
  $$g(x) = \frac{3x - 1}{2x + 1}$$
* **Dica (`fornecerDica()`):** *"É um quociente de duas funções. Use a Regra do Quociente: $\left(\frac{f}{g}\right)' = \frac{g f' - f g'}{g^2}$."*

##### Roteiro de Resolução (Stewart Cap. 3):
1. **Diagnóstico Inicial:** Quociente de duas funções lineares. Não existe simplificação algébrica prévia que elimine a fração, então é preciso usar a regra do quociente. 
2. **Etapa 1 (Técnica: Aplicação da Regra do Quociente):**
   - Identificamos o numerador $f(x) = 3x - 1$, com $f'(x) = 3$, e denominador $h(x) = 2x + 1$, com $h'(x) = 2$.
   - Aplicando a regra $(f/h)' = \frac{h f' - f h'}{h^2}$:
     $$g'(x) = \frac{(2x + 1) \cdot 3 - (3x - 1) \cdot 2}{(2x + 1)^2}$$
   - *No Jogo:* Habilidade **"Regra do Quociente"** causa **25 de dano** (Vida: $50 \to 25$) e marca a questão como apta para finalização (`_etapaPreviaConcluida = true`).
3. **Etapa de Conclusão (Técnica: Simplificação do Numerador):**
   - Expandindo o numerador: $(6x + 3) - (6x - 2) = 6x + 3 - 6x + 2 = 5$. Os termos em $x$ se cancelam.
   - Resultado final: $g'(x) = \frac{5}{(2x + 1)^2}$.
   - *No Jogo:* Ação `tentarFinalizar()` zera a vida restante da questão!
   - **Resposta Final:** $\mathbf{g'(x) = \frac{5}{(2x + 1)^2}}$.
4. **Contra-ataque da Questão:**
   - **Ataque:** *"Derivar Numerador e Denominador Separadamente"* $\rightarrow$ Causa **+10 de Cansaço**

---

### Q_DER_3: Derivada de Produto com Exponencial e Cosseno
* **Prova:** P2 (Derivadas)
* **Dificuldade:** Difícil (100 HP)
* **Enunciado:** Derive a função: $y = e^{-2t} \cos 4t$
* **Dica (`fornecerDica()`):** "É um produto, então use $(fg)' = f'g + fg'$. Cuidado: as duas derivadas internas pedem Cadeia — o expoente $-2t$ e o argumento $4t$."

#### Roteiro de Resolução (Stewart Cap. 3, Seções 3.2 e 3.4):
1. **Diagnóstico Inicial:** Produto de uma exponencial composta por um cosseno composto. Exige Regra do Produto por fora e Regra da Cadeia nos dois fatores.
2. **Etapa 1 (Técnica: Regra do Produto):**
   - $y' = (e^{-2t})' \cdot \cos 4t + e^{-2t} \cdot (\cos 4t)'$
   - *No Jogo:* Habilidade **"Regra do Produto"** causa **40 de dano** (Vida: $100 \to 60$).
3. **Etapa 2 (Técnica: Regra da Cadeia na Exponencial):**
   - $(e^{-2t})' = -2e^{-2t}$
   - *No Jogo:* Habilidade **"Regra da Cadeia"** causa **25 de dano** (Vida: $60 \to 35$).
4. **Etapa 3 (Técnica: Regra da Cadeia no Cosseno):**
   - $(\cos 4t)' = -4\mathrm{sen} 4t$
     $$y' = -2e^{-2t}\cos 4t - 4e^{-2t}\mathrm{sen} 4t$$
   - *No Jogo:* Habilidade **"Simplificação de Termos"** causa **20 de dano** (Vida: $35 \to 15$) e libera a finalização.
5. **Etapa de Conclusão (Técnica: Fatoração do Termo Comum):**
   - Colocando $-2e^{-2t}$ em evidência.
   - *No Jogo:* Ação `tentarFinalizar()` zera a vida restante da questão!
   - **Resposta Final:** $\mathbf{y' = -2e^{-2t}(\cos 4t + 2\mathrm{sen} 4t)}$
6. **Contra-ataque da Questão:**
   - **Ataque:** *"Esquecer o Fator Interno"* $\rightarrow$ Causa **+20 de Cansaço**.

### Prova 3: Integrais e Técnicas de Integração (P3)

#### `Q_INT_01`: Integração por Partes Clássica
* **Prova:** P3 (Integrais)
* **Dificuldade:** Difícil (100 HP)
* **Enunciado:** Calcule a integral indefinida:
  $$\int x \sin(x) \, dx$$
* **Dica (`fornecerDica()`):** *"Use a regra de partes $\int u \, dv = uv - \int v \, du$, escolhendo $u = x$."*

##### Roteiro de Resolução (Stewart Cap. 7):
1. **Diagnóstico Inicial:** Produto de uma função polinomial por uma função trigonométrica periódica. Não pode ser resolvida por substituição simples $u$.
2. **Etapa 1 (Técnica: Escolha de Partes LIATE e Diferenciação):**
   - Escolha: $u = x \implies du = dx$.
   - Diferencial restante: $dv = \sin(x)dx \implies v = \int \sin(x)dx = -\cos(x)$.
   - *No Jogo:* Habilidade **"Identificar Partes ($u$ e $dv$)"** causa **35 de dano** (Vida: $100 \to 65$).
3. **Etapa 2 (Técnica: Aplicação da Fórmula de Partes):**
   - Aplicando $uv - \int v \, du$:
     $$-x\cos(x) - \int (-\cos(x)) \, dx = -x\cos(x) + \int \cos(x) \, dx$$
   - *No Jogo:* Habilidade **"Fórmula da Integração por Partes"** causa **35 de dano** (Vida: $65 \to 30$) e libera a finalização.
4. **Etapa de Conclusão (Técnica: Integração Imediata):**
   - A integral imediata de $\cos(x)$ é $\sin(x)$.
   - Somamos a constante de integração $+ C$.
   - *No Jogo:* Ação `tentarFinalizar()` conclui a questão e zera a vida!
   - **Resposta Final:** $\mathbf{-x \cos(x) + \sin(x) + C}$.
5. **Contra-ataque da Questão:**
   - **Ataque:** *"Troca de Sinal no Cosseno"* $\rightarrow$ Causa **+20 de Cansaço**.

---

#### `Q_INT_02`: Integral por Substituição Simples
* **Prova:** P3 (Integrais)
* **Dificuldade:** Média (75 HP)
* **Enunciado:** Calcule a integral indefinida:
  $$\int e^x \sqrt{1 + e^x} \, dx$$
* **Dica (`fornecerDica()`):** *"Use a regra da substituição $\int f(g(x)) \, g'(x) \, dx = \int f(u) \, du$, escolhendo $u = 1 + e^x$."*

##### Roteiro de Resolução (Stewart Cap. 5):
1. 1. **Diagnóstico Inicial:** Produto de uma função exponencial pela raiz quadrada de 1 + e^x . Não é integral imediata nem se resolve por manipulação algébrica; a substituição só é viável porque e^x dx é exatamente a derivada do radicando.
2. **Etapa 1 (Técnica: Escolha da Substituição):**
   - Tomamos $u = 1 + e^x$, a expressão que está dentro da raiz.
   - Sua diferencial é $du = e^x \, dx$ — exatamente o fator que aparece multiplicando do lado de fora.
   - Reescrevendo: $\int \sqrt{1 + e^x} \cdot e^x \, dx = \int \sqrt{u} \, du$.
   - *No Jogo:* Habilidade **"Escolha da Substituição"** causa **30 de dano** (Vida: $75 \to 45$).
3. **Etapa 2 (Técnica: Regra da Potência para Integração):**
   - A raiz vira potência fracionária: $\sqrt{u} = u^{1/2}$.
   - Aplicando $\int u^n du = \frac{u^{n+1}}{n+1}$ com $n = \frac{1}{2}$: $\int u^{1/2} du = \frac{u^{3/2}}{3/2} = \frac{2}{3}u^{3/2}$.
   - *No Jogo:* Habilidade **"Regra da Potência na Integração"** causa **20 de dano** (Vida: $45 \to 25$) e libera a finalização.
4. **Etapa de Conclusão (Técnica: Retorno à Variável Original):**
   - Trocamos $u$ de volta por $1 + e^x$: $\frac{2}{3}(1 + e^x)^{3/2}$.
   - Somando a constante de integração: $\frac{2}{3}(1 + e^x)^{3/2} + C$.
   - *No Jogo:* Ação `tentarFinalizar()` zera a vida restante da questão!
   - **Resposta Final:** $\mathbf{\frac{2}{3}(1 + e^x)^{3/2} + C}$.
5. **Contra-ataque da Questão:**
   - **Ataque:** *"Esquecer de Voltar para x"* $\rightarrow$ Causa **+15 de Cansaço**

---

### Prova 4: Prova Final (P4)
*(Espaço reservado para as questões mistas +difíceis)*

