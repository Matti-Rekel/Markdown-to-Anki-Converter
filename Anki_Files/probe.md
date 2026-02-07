# Integration und Differentiation

### Wie lautet der Hauptsatz (Fundermentalsatz) der Differential und Integralrechnung (HDI)?

$f:[a,b] \rightarrow \mathbb{R}$ stetig, $F: [a,b] \rightarrow \mathbb{R}$ eine Stammfunktion von $f$, dann $$\int_a^b f(x) dx = [F(x)]_a^b = F(b) - F(a)$$

Quelle: 2026.01.27_Übung, 2026.01.28_Vorlesung

### Was ist die Bedingung für den HDI?

$f$ muss stetig sein.

Quelle: 2026.01.28_Vorlesung

### Wie lautet die Formel für partielle Integration?

$$\int_a^b f'(x)g(x) dx = [fg]_a^b - \int_a^b f(x)g'(x) dx$$

Informationen: Bedingung: Seien $f,g: [a,b] \rightarrow \mathbb{R}$ stetig differenzierbar.

Quelle: 2026.01.27_Übung

### Wie lauteten die Bedingungen für partielle Integration?

- Seien $f,g: [a,b] \rightarrow \mathbb{R}$ stetig differenzierbar. 
- Lol
    - Hurensohn
- Pimmel

usw.

Informationen: Formel: $$\int_a^b f'(x)g(x) dx = [fg]_a^b - \int_a^b f(x)g'(x) dx$$

Quelle: 2026.01.27_Übung

### Seien $F,G$ Stammfunktionen von $f$ was gilt für $F-G$?

$F-G$ ist konstant.

Quelle: 2026.01.28_Vorlesung

### Was sind die Bedingungen für die Substitutionsregel?

Sei $f: I \rightarrow \mathbb{R}$ stetig, $\varphi: [a,b] \rightarrow \mathbb{R}$ stetig differenzierbar mit $\varphi([a,b]) \subset I$.

Informationen: $$\int_a^b f(\varphi(t)) \varphi'(t) dt = \int_{\varphi(a)}^{\varphi(b)} f(x) dx$$

Quelle: 2026.01.28_Vorlesung

### Wie lautet die Formel für die Substitutionsregel?

$$\int_a^b f(\varphi(t)) \varphi'(t) dt = \int_{\varphi(a)}^{\varphi(b)} f(x) dx$$

Informationen: Sei $f: I \rightarrow \mathbb{R}$ stetig, $\varphi: [a,b] \rightarrow \mathbb{R}$ stetig differenzierbar mit $\varphi([a,b]) \subset I$.

Quelle: 2026.01.28_Vorlesung

### Wende die Substitutions Regel an: $\int_a^b f(t+c) dt$.

$$\int_{a+c}^{b+c}f(x) dx$$

Informationen: $$\int_a^b f(\varphi(t)) \varphi'(t) dt = \int_{\varphi(a)}^{\varphi(b)} f(x) dx$$

Quelle: 2026.01.28_Vorlesung

### Wende die partielle Integrationsregel an: $\int_a^b \log(x) dx$

$$= [x\log(x)]_a^b - \int_a^b x \frac{1}{x} dx$$

Informationen: Formel: $$\int_a^b f'(x)g(x) dx = [fg]_a^b - \int_a^b f(x)g'(x) dx$$

Quelle: 2026.01.28_Vorlesung

### Wie lautet das Wallische Produkt?

$$\frac{\pi}{2} = \prod_{k=1}^\infty \frac{4k^2}{4k^2-1}$$

Quelle: 2026.01.30_Vorlesung

### Wie lautet die Trapez-Regel?

Sei $f:[0,1] \rightarrow \mathbb{R}$ zweimal stetig differenzierbar. Dann ist $$\int_0^1 f(x) dx = \frac{1}{2} (f(0)+f(1)) -R$$, wobei für das Restglied gilt: $$R = \frac{1}{2} \int_0^1 x (1-x) f''(x) dx = \frac{1}{12} f''(\xi )$$ für ein $\xi  \in [0,1]$

Quelle: 2026.01.30_Vorlesung