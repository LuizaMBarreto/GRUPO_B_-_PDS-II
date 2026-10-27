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
#### `Q_LIM_03`: Limite Trigonométrico Fundamental
* **Prova:** P1 (Limites)
* **Dificuldade:** Difícil (100 HP)
* **Enunciado:** Calcule o limite: $$\lim_{x \to 0} \frac{\tan(5x)}{\sin(2x)}$$
* **Dica (`fornecerDica()`):** "Reescreva $\tan(5x)$ como $\frac{\sin(5x)}{\cos(5x)}$ e utilize o limite trigonométrico fundamental $\lim_{u \to 0} \frac{\sin(u)}{u} = 1$ ajustando as constantes dos argumentos."

#### Roteiro de Resolução (Stewart Cap. 2):
1. **Diagnóstico Inicial:**
   - A substituição direta com $x = 0$ resulta na forma indeterminada $\frac{0}{0}$. Envolve funções trigonométricas e requer reescrita algébrica para aplicação do limite fundamental.
2. **Etapa(s) Preliminar(es) — Técnicas Aplicadas:**
   - **Técnica 1:** Reescrita por Identidades Trigonométricas -> *Identidades Trigonométricas*. Causa 35 de dano (Vida: $100 \to 65$).
     - **Desenvolvimento:** Substituímos $\tan(5x) = \frac{\sin(5x)}{\cos(5x)}$, obtendo: $$\frac{\sin(5x)}{\cos(5x) \cdot \sin(2x)}$$
   - **Técnica 2:** Construção das Formas Fundamentais -> *Ajuste de Constantes de Limite*. Causa 35 de dano (Vida: $65 \to 30$).
     - **Desenvolvimento:** Multiplicamos e dividimos por $5x$ e $2x$: $$\left(\frac{\sin(5x)}{5x}\right) \cdot \left(\frac{2x}{\sin(2x)}\right) \cdot \frac{5x}{2x \cdot \cos(5x)} = \left(\frac{\sin(5x)}{5x}\right) \cdot \left(\frac{2x}{\sin(2x)}\right) \cdot \frac{5}{2\cos(5x)}$$
   - **Técnica 3:** Aplicação dos Limites Notáveis -> *Limite Fundamental Trigonométrico*. Causa 15 de dano (Vida: $30 \to 15$) e libera a finalização.
     - **Desenvolvimento:** Como $\lim_{u \to 0} \frac{\sin(u)}{u} = 1$, temos que $\lim_{x \to 0} \frac{\sin(5x)}{5x} = 1$ e $\lim_{x \to 0} \frac{2x}{\sin(2x)} = 1$.
3. **Etapa de Conclusão / Fechamento:**
   - **Técnica de Fechamento:** Avaliação dos Limites dos Fatores -> Dispara `tentarFinalizar()`.
     - **Desenvolvimento:** $1 \cdot 1 \cdot \frac{5}{2 \cos(0)} = 1 \cdot 1 \cdot \frac{5}{2(1)} = \frac{5}{2}$.
   - **Resposta Final:** $\mathbf{L = \frac{5}{2}}$.
4. **Contra-ataque da Questão:**
   - **Ataque:** "Confundir Coeficiente dos Argumentos" -> Causa +22 de Cansaço.
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

#### `Q_DER_3`: Derivada de Produto com Exponencial e Cosseno
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
---

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
#### `Q_INT_03`: Integral Definida Polinomial
* **Prova:** P3 (Integrais)
* **Dificuldade:** Fácil (50 HP)
* **Enunciado:** Calcule a integral definida: $$\int_{1}^{2} (3x^2 - 2x + 1) \, dx$$
* **Dica (`fornecerDica()`):** "Encontre a primitiva $F(x)$ utilizando a Regra da Potência e avalie $F(2) - F(1)$ conforme o Teorema Fundamental do Cálculo."

#### Roteiro de Resolução (Stewart Cap. 5):
1. **Diagnóstico Inicial:**
   - Integral definida de um polinômio simples. Pode ser calculada diretamente encontrando a antiderivada e aplicando o Teorema Fundamental do Cálculo (TFC II).
2. **Etapa(s) Preliminar(es) — Técnicas Aplicadas:**
   - **Técnica 1:** Antidiferenciação por Regra da Potência -> *Regra da Potência para Integração*. Causa 25 de dano (Vida: $50 \to 25$) e marca a questão como apta para finalização (`_etapaPreviaConcluida = true`).
     - **Desenvolvimento:** Calculamos a primitiva $F(x)$: $$F(x) = 3\left(\frac{x^3}{3}\right) - 2\left(\frac{x^2}{2}\right) + x = x^3 - x^2 + x$$
3. **Etapa de Conclusão / Fechamento:**
   - **Técnica de Fechamento:** Avaliação pelo Teorema Fundamental do Cálculo (TFC II) -> Dispara `tentarFinalizar()`.
     - **Desenvolvimento:** Calculamos $F(2) - F(1)$: $$F(2) = 2^3 - 2^2 + 2 = 8 - 4 + 2 = 6$$ $$F(1) = 1^3 - 1^2 + 1 = 1$$ $$F(2) - F(1) = 6 - 1 = 5$$
   - **Resposta Final:** $\mathbf{5}$.
4. **Contra-ataque da Questão:**
   - **Ataque:** "Erro de Sinal na Subtração do Limite Inferior" -> Causa +10 de Cansaço.
---

### Prova 4: Prova Final (P4)

#### `Q_P4_01`: Limite Trigonométrico por L'Hôpital Repetido
* **Prova:** P4 (Mista)
* **Dificuldade:** Média (75 HP)
* **Enunciado:** Calcule o limite:
  $$\lim_{x \to 0} \frac{x^2}{1 - \cos x}$$
* **Dica (`fornecerDica()`):** *"Se após derivar uma vez a indeterminação continuar, a Regra de L'Hôpital pode ser aplicada novamente."*

##### Roteiro de Resolução (Stewart Cap. 4):
1. **Diagnóstico Inicial:** A substituição direta com $x = 0$ resulta na forma indeterminada $\frac{0}{0}$ (pois $0^2 = 0$ e $1 - \cos 0 = 0$). Não podemos aplicar a lei do quociente diretamente, mas as condições para a Regra de L'Hôpital estão satisfeitas.
2. **Etapa 1 (Técnica: 1ª Aplicação de L'Hôpital):**
   - Derivamos numerador e denominador separadamente: $\lim_{x \to 0} \frac{x^2}{1 - \cos x} = \lim_{x \to 0} \frac{2x}{\sin x}$.
   - Ao substituir, obtemos novamente $\frac{0}{0}$. A indeterminação persiste.
   - *No Jogo:* Habilidade **"Regra de L'Hôpital"** causa **30 de dano** (Vida: $75 \to 45$).
3. **Etapa 2 (Técnica: 2ª Aplicação de L'Hôpital):**
   - Como a forma $\frac{0}{0}$ continua valendo, aplicamos a regra novamente: $\lim_{x \to 0} \frac{2x}{\sin x} = \lim_{x \to 0} \frac{2}{\cos x}$.
   - *No Jogo:* Habilidade **"Aplicação Repetida"** causa **20 de dano** (Vida: $45 \to 25$) e marca a questão como apta para finalização (`_etapaPreviaConcluida = true`).
4. **Etapa de Conclusão (Técnica: Substituição Direta):**
   - Agora o denominador não se anula e a função é contínua em $x = 0$: $\lim_{x \to 0} \frac{2}{\cos x} = \frac{2}{\cos 0} = \frac{2}{1} = 2$.
   - *No Jogo:* Ação `tentarFinalizar()` é bem-sucedida. A vida vai **direto a 0**!
   - **Resposta Final:** $\mathbf{L = 2}$.
5. **Contra-ataques da Questão:**
   - **Ataque 1:** *"Indeterminação 0/0"* $\rightarrow$ Causa **+15 de Cansaço** (ao iniciar a questão).
   - **Ataque 2:** *"Indeterminação Persistente"* $\rightarrow$ Causa **+20 de Cansaço** (após a Etapa 1, testando se o aluno percebe que ainda é $\frac{0}{0}$).

##### Armadilha e Rota Alternativa:
- **Armadilha:** Se o jogador chamar `tentarFinalizar()` após a Etapa 1, a ação falha enquanto `_etapaPreviaConcluida` for `false`, e ele recebe **+25 de Cansaço**.
- **Rota alternativa (método elementar):** Multiplicando por $\frac{1 + \cos x}{1 + \cos x}$, o denominador vira $\sin^2 x$ e o limite fica $\left(\frac{x}{\sin x}\right)^2 (1 + \cos x) \to 1 \cdot 2 = 2$. Pode ser modelada como habilidade **"Limite Fundamental"**, que também leva à resposta 2.

---

#### `Q_P4_02`: Integração por Decomposição em Frações Parciais
* **Prova:** P4 (Geral)
* **Dificuldade:** Difícil (100 HP)
* **Enunciado:** Calcule a integral indefinida: $$\int \frac{5x - 1}{x^2 - 1} \, dx$$
* **Dica (`fornecerDica()`):** "Fatore o denominador como $(x - 1)(x + 1)$ e decomponha o integrando na soma de frações parciais $\frac{A}{x - 1} + \frac{B}{x + 1}$."

#### Roteiro de Resolução (Stewart Cap. 7):
1. **Diagnóstico Inicial:**
   - Função racional onde o grau do numerador (1) é menor que o do denominador (2), e o denominador possui raízes reais distintas. Requer Decomposição em Frações Parciais.
2. **Etapas Preliminares — Técnicas Aplicadas:**
   - **Técnica 1:** Fatoração e Estruturação das Frações -> *Decomposição em Frações Parciais*. Causa 35 de dano (Vida: $100 \to 65$).
     - **Desenvolvimento:** Fatoramos $x^2 - 1 = (x - 1)(x + 1)$: $$\frac{5x - 1}{(x - 1)(x + 1)} = \frac{A}{x - 1} + \frac{B}{x + 1}$$ $$5x - 1 = A(x + 1) + B(x - 1)$$
   - **Técnica 2:** Determinação das Constantes -> *Resolução de Sistema de Coeficientes*. Causa 30 de dano (Vida: $65 \to 35$).
     - **Desenvolvimento:** 
       - Para $x = 1$: $5(1) - 1 = A(1 + 1) + B(0) \implies 4 = 2A \implies A = 2$.
       - Para $x = -1$: $5(-1) - 1 = A(0) + B(-1 - 1) \implies -6 = -2B \implies B = 3$.
   - **Técnica 3:** Integração dos Termos Simples -> *Integração Logarítmica*. Causa 15 de dano (Vida: $35 \to 20$) e libera a finalização.
     - **Desenvolvimento:** $$\int \left( \frac{2}{x - 1} + \frac{3}{x + 1} \right) dx = 2 \ln|x - 1| + 3 \ln|x + 1|$$
3. **Etapa de Conclusão / Fechamento:**
   - **Técnica de Fechamento:** Adição da Constante de Integração -> Dispara `tentarFinalizar()`.
     - **Desenvolvimento:** Unimos os termos e adicionamos a constante $+ C$: $$2 \ln|x - 1| + 3 \ln|x + 1| + C$$
   - **Resposta Final:** $\mathbf{2 \ln|x - 1| + 3 \ln|x + 1| + C}$.
4. **Contra-ataque da Questão:**
   - **Ataque:** "Erro de Sinal ao Encontrar os Coeficientes" -> Causa +20 de Cansaço.
---
#### `Q_P4_03`: Derivação Logarítmica de Função Exponencial Composta
* **Prova:** P4 (Geral)
* **Dificuldade:** Média (75 HP)
* **Enunciado:** Encontre a derivada da função: $$y = x^x \quad (x > 0)$$
* **Dica (`fornecerDica()`):** "Como a variável $x$ está na base e no expoente, aplique o logaritmo natural em ambos os lados ($\ln y = \ln(x^x)$) antes de derivar implicitamente."

#### Roteiro de Resolução (Stewart Cap. 3):
1. **Diagnóstico Inicial:**
   - Função do tipo $[f(x)]^{g(x)}$ onde a variável aparece na base e no expoente. Não se aplicam diretamente as regras usuais de potência nem de exponencial pura; exige Derivação Logarítmica.
2. **Etapas Preliminares — Técnicas Aplicadas:**
   - **Técnica 1:** Aplicação do Logaritmo e Propriedades -> *Aplicação de Logaritmo Natural*. Causa 35 de dano (Vida: $75 \to 40$).
     - **Desenvolvimento:** Aplicamos $\ln$ em ambos os lados e usamos a propriedade de potência: $$\ln y = \ln(x^x) \implies \ln y = x \ln x$$
   - **Técnica 2:** Derivação Implícita e Regra do Produto -> *Derivação Implícita com Regra do Produto*. Causa 20 de dano (Vida: $40 \to 20$) e libera a finalização.
     - **Desenvolvimento:** Derivando em relação a $x$: $$\frac{1}{y} \cdot y' = \frac{d}{dx}[x] \cdot \ln x + x \cdot \frac{d}{dx}[\ln x]$$ $$\frac{1}{y} \cdot y' = 1 \cdot \ln x + x \cdot \frac{1}{x} = \ln x + 1$$
3. **Etapa de Conclusão / Fechamento:**
   - **Técnica de Fechamento:** Isolamento de $y'$ e Substituição -> Dispara `tentarFinalizar()`.
     - **Desenvolvimento:** Isolamos $y'$ multiplicando por $y = x^x$: $$y' = y(\ln x + 1) = x^x (\ln x + 1)$$
   - **Resposta Final:** $\mathbf{y' = x^x (\ln x + 1)}$.
4. **Contra-ataque da Questão:**
   - **Ataque:** "Tratar como Potência Simples ($x \cdot x^{x-1}$)" -> Causa +18 de Cansaço.

---

#### `Q_P4_04`: Integral Definida por Partes Repetida
* **Prova:** P4 (Geral)
* **Dificuldade:** Difícil (100 HP)
* **Enunciado:** Calcule a integral definida:
  $$\int_1^2 x^4 (\ln x)^2 \, dx$$
* **Dica (`fornecerDica()`):** *"Use integração por partes escolhendo $u = (\ln x)^2$, pois derivar o logaritmo reduz o grau. Como o resultado ainda terá um $\ln x$, será preciso aplicar partes uma segunda vez."*

##### Roteiro de Resolução (Stewart Cap. 7):
1. **Diagnóstico Inicial:** Produto de uma potência por o quadrado de um logaritmo, em uma integral definida. Não é integral imediata nem se resolve por substituição simples. Exige Integração por Partes aplicada mais de uma vez e, no fim, a avaliação pelo Teorema Fundamental do Cálculo.
2. **Etapa 1 (Técnica: Escolha de Partes):**
   - Escolha: $u = (\ln x)^2 \implies du = \frac{2\ln x}{x}\,dx$.
   - Diferencial restante: $dv = x^4\,dx \implies v = \frac{x^5}{5}$.
   - *No Jogo:* Habilidade **"Identificar Partes ($u$ e $dv$)"** causa **30 de dano** (Vida: $100 \to 70$).
3. **Etapa 2 (Técnica: 1ª Aplicação da Fórmula de Partes):**
   - Aplicando $uv - \int v \, du$:
     $$\int x^4 (\ln x)^2\,dx = \frac{x^5}{5}(\ln x)^2 - \frac{2}{5}\int x^4 \ln x\,dx$$
   - *No Jogo:* Habilidade **"Fórmula da Integração por Partes"** causa **25 de dano** (Vida: $70 \to 45$).
4. **Etapa 3 (Técnica: 2ª Aplicação de Partes):**
   - Para $\int x^4 \ln x\,dx$, escolhemos $u = \ln x$ e $dv = x^4\,dx$, o que dá $du = \frac{1}{x}\,dx$ e $v = \frac{x^5}{5}$:
     $$\int x^4 \ln x\,dx = \frac{x^5}{5}\ln x - \frac{x^5}{25}$$
   - Substituindo na expressão anterior, a antiderivada completa é:
     $$F(x) = \frac{x^5}{5}(\ln x)^2 - \frac{2x^5}{25}\ln x + \frac{2x^5}{125}$$
   - *No Jogo:* Habilidade **"Aplicação Repetida"** causa **20 de dano** (Vida: $45 \to 25$) e marca a questão como apta para finalização (`_etapaPreviaConcluida = true`).
5. **Etapa de Conclusão (Técnica: Teorema Fundamental do Cálculo):**
   - Avaliamos $F(2) - F(1)$:
     $$F(2) = \frac{32}{5}(\ln 2)^2 - \frac{64}{25}\ln 2 + \frac{64}{125}, \qquad F(1) = \frac{2}{125}$$
   - Subtraindo: $F(2) - F(1) = \frac{32}{5}(\ln 2)^2 - \frac{64}{25}\ln 2 + \frac{62}{125}$.
   - *No Jogo:* Ação `tentarFinalizar()` é bem-sucedida. A vida vai **direto a 0**!
   - **Resposta Final:** $\mathbf{\frac{32}{5}(\ln 2)^2 - \frac{64}{25}\ln 2 + \frac{62}{125} \approx 1{,}80}$.
6. **Contra-ataques da Questão:**
   - **Ataque 1:** *"Esquecer o Fator 2 do Segundo Termo"* $\rightarrow$ Causa **+20 de Cansaço** (após a Etapa 2, testando se o aluno carrega o coeficiente $\frac{2}{5}$ corretamente).
   - **Ataque 2:** *"Esquecer de Avaliar em $x = 1$"* $\rightarrow$ Causa **+15 de Cansaço** (na Etapa de Conclusão, pois o termo $F(1) = \frac{2}{125}$ não é zero).

##### Armadilha e Rota Alternativa:
- **Armadilha:** Se o jogador chamar `tentarFinalizar()` após a Etapa 2, a ação falha enquanto `_etapaPreviaConcluida` for `false`, e ele recebe **+25 de Cansaço**, pois ainda resta uma integral com $\ln x$ a resolver.
- **Rota alternativa (substituição prévia):** Fazendo $t = \ln x$ (então $x = e^t$ e $dx = e^t\,dt$), a integral vira $\int_0^{\ln 2} t^2 e^{5t}\,dt$, que também exige partes duas vezes e leva ao mesmo resultado. Pode ser modelada como habilidade **"Mudança de Variável"**.
