# Problem Statement

You are planning to visit the Kingdom of BnL (Blockchain and Logistics). The kingdom consists of $ n $ cities connected by $ m $ bidirectional roads. Each road has a checkpoint that requires you to **hold** a certain amount of cryptocurrency to pass through — specifically, for the $ i $-th road connecting cities $ u_i $ and $ v_i $, you must hold **at least** $ a_i $ units of BTC **and** at least $ b_i $ units of ETH simultaneously. Note that you do **not** spend the cryptocurrencies; you only need to possess them.

The current market prices are:
- $ S $ dollars per BTC
- $ T $ dollars per ETH

Your goal is to ensure that you can travel between **any pair of cities** (i.e., the entire road network is connected) while minimizing your total expenditure on purchasing the required cryptocurrencies.

Formally, if you choose a set of roads that makes the graph connected, let:
- $ A = \max\{a_i \mid \text{road } i \text{ is used}\} $
- $ B = \max\{b_i \mid \text{road } i \text{ is used}\} $

Then your total cost is $ A \cdot S + B \cdot T $ dollars.

Find the **minimum possible cost** to achieve full connectivity. If it is impossible to connect all cities, output $-1$.

## Input

The first line contains four integers:
- $ n $: number of cities ($ 1 \leq n \leq 2000 $)
- $ m $: number of roads ($ 1 \leq m \leq 2000 $)
- $ S $: price of BTC in dollars ($ 1 \leq S \leq 10^9 $)
- $ T $: price of ETH in dollars ($ 1 \leq T \leq 10^9 $)

Each of the next $ m $ lines describes a road with four integers:
- $ u_i, v_i $: the cities connected by the road ($ 1 \leq u_i, v_i \leq n $, $ u_i \ne v_i $)
- $ a_i $: minimum BTC required ($ 1 \leq a_i \leq 10^9 $)
- $ b_i $: minimum ETH required ($ 1 \leq b_i \leq 10^9 $)

There is at most one road between any pair of cities.

## Output

Print a single integer — the minimum total cost in dollars to ensure full connectivity. If it is impossible, print `-1`.

## Examples

### Example 1

**Input**:
```
4 5 1 1
1 2 19 1
2 3 8 12
2 4 12 15
1 3 17 8
3 4 1 17
```

**Output**:
```
32
```

**Explanation**:  
One optimal solution uses roads $(1,3)$, $(2,3)$, and $(2,4)$.  
- Maximum $ a_i = \max(17, 8, 12) = 17 $  
- Maximum $ b_i = \max(8, 12, 15) = 15 $  
- Cost = $ 17 \cdot 1 + 15 \cdot 1 = 32 $

### Example 2

**Input**:
```
3 1 998244353 1000000007
1 2 1 1
```

**Output**:
```
-1
```

**Explanation**:  
With only one road, city 3 is isolated → impossible to connect all cities.

---

> **Note**: This problem requires minimizing the cost defined by the **maximum** BTC and ETH requirements across selected edges, not the sum. Standard MST (e.g., Kruskal with edge weight = $ a_i S + b_i T $) does **not** apply directly.

--- 
