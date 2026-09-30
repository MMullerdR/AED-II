# exercicio 1

vetor1 = [0] * 11


def h1(x):
    return x % 11

def h2(x):
    return (2 * x + 3) % 11

def h3(x):
    return (7 * x + 1) % 11

def add(id):
    vetor1[h1(id)] = 1
    vetor1[h2(id)] = 1
    vetor1[h3(id)] = 1
    return

def isDangerous(id):
    
    return vetor1[h1(id)] and vetor1[h2(id)] and vetor1[h3(id)]

add(15)
print(vetor1)
add(22)
print(vetor1)
add(45)
print(vetor1)

print("Potencialmente perigoso")
print(isDangerous(10))
print(isDangerous(22))

print(isDangerous(37))
print(f"Indice 1: {h2(37)}")
print(f"Indice 2: {h2(37)}")
print(f"Indice 3: {h3(37)}")

# numeros podem ter o mesmo mod, então o 37 acusa que possivelmente é um ID perigoso pois tem o mesmo mod do 15 anteriormente adicionado
# porem a ideia é garantir saber quando NAO estiver presente na hash, então isso tem um pequeno impacto pois apenas vai dar um "falso positivo"

# exercicio 2

N = 7

def h(x):
    return x % 7

sequencia = [10, 17, 24, 31, 5, 12]

# Parte A: Encadeamento Externo
tabela_externa = [[] for _ in range(N)]

def add_externo(id):
    idx = h(id)
    tabela_externa[idx].append(id)

for id in sequencia:
    add_externo(id)

print("Parte A - Encadeamento Externo")
for i, lista in enumerate(tabela_externa):
    print(f"{i}: {lista}")

# Parte B: Encadeamento Interno - Sondagem Linear
tabela_interna = [None] * N

def add_interno(id):
    idx = h(id)
    tentativa = 0
    while tabela_interna[(idx + tentativa) % N] is not None:
        tentativa += 1
        if tentativa == N:
            return  # tabela cheia
    tabela_interna[(idx + tentativa) % N] = id

for id in sequencia:
    add_interno(id)

print("Parte B - Sondagem Linear")
print(tabela_interna)

# Parte C: Analise Critica
# Em disco, o Encadeamento Externo (Parte A) causaria mais lentidao de I/O,
# pois cada no da lista fica alocado em um endereco de memoria diferente e
# nao continuo, exigindo um acesso a disco separado para cada elemento.
# Ja a Sondagem Linear mantem os dados dentro do mesmo array continuo,
# favorecendo leituras sequenciais e reduzindo o numero de I/Os.


# exercicio 3

TOMBSTONE = "LAPIDE"

def remover(id):
    idx = h(id)
    tentativa = 0
    while tentativa < N:
        pos = (idx + tentativa) % N
        if tabela_interna[pos] == id:
            tabela_interna[pos] = TOMBSTONE
            return True
        if tabela_interna[pos] is None:
            return False
        tentativa += 1
    return False

def buscar(id):
    idx = h(id)
    tentativa = 0
    while tentativa < N:
        pos = (idx + tentativa) % N
        if tabela_interna[pos] == id:
            return True
        if tabela_interna[pos] is None:
            return False
        tentativa += 1
    return False

remover(24)
print("Tabela apos remocao do ID 24")
print(tabela_interna)

print("Busca pelo ID 31 apos remocao")
print(buscar(31))

# a lapide (LAPIDE) nao interrompe a busca porque so um espaco None
# encerra a sondagem; a lapide e tratada como "ocupado mas nao e o alvo",
# entao o codigo continua pulando ate achar o 31