### Was sind die zwei Schritte der vollständigen Induktion für eine Aussage $A(n)$ ab $n_0 \in \mathbb{Z}$?

1. **Induktionsanfang:** $A(n_0)$ ist wahr ✅  
2. **Induktionsschritt:** Für beliebiges $n \ge n_0$ gilt: Wenn $A(n)$ wahr ist, dann ist auch $A(n+1)$ wahr ✅

Informationen: Beim Induktionsschritt wird oft die **Induktionsvoraussetzung** verwendet, um von $n$ auf $n+1$ zu schließen.

### Gib ein einfaches Beispiel, wie die Induktion von $n$ auf $n+1$ funktioniert.

Summe der ersten $n$ natürlichen Zahlen:  
$$
1 + 2 + \dots + n = \frac{n(n+1)}{2}
$$

Informationen:  
- Induktionsanfang: $n=1 \Rightarrow 1 = \frac{1\cdot2}{2}$ ✅  
- Induktionsschritt: Angenommen, Formel gilt für $n$. Dann für $n+1$:  
$$
1 + 2 + \dots + n + (n+1) = \frac{n(n+1)}{2} + (n+1) = \frac{(n+1)(n+2)}{2} ✅
$$

### Was bedeutet $X := A$?

$X$ ist nach Definition gleich $A$.

Informationen: Das Symbol $:=$ wird oft für **Definitionen oder Zuweisungen** in Mathematik und Informatik verwendet.

### Wann ist eine natürliche Zahl $n > 1$ eine Primzahl?

$n$ ist eine Primzahl, wenn für jede Zerlegung $n = k \cdot l$ gilt:  
$k = 1$ oder $l = 1$

Informationen: Beispiele: $2, 3, 5, 7, 11, \dots$

### Wie ist $n!$ definiert?

$$
n! := \prod_{k=1}^{n} k = 1 \cdot 2 \cdot \dots \cdot n
$$

Informationen: Beispiel: $4! = 1 \cdot 2 \cdot 3 \cdot 4 = 24$

### Wie lautet die geometrische Summenformel für $\sum_{k=0}^n x^k$?

$$
\sum_{k=0}^{n} x^k = \frac{1 - x^{n+1}}{1 - x}, \quad x \neq 1
$$

Informationen: Funktioniert nur für $x \neq 1$
