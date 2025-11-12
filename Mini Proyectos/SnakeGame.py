import pygame
import random
import sys
import os
from datetime import datetime

# CONFIGURACIÓN INICIAL
pygame.init()
pygame.mixer.init()

ANCHO, ALTO = 600, 600
TAM_CELDA = 20
FPS_BASE = 12

pantalla = pygame.display.set_mode((ANCHO, ALTO))
pygame.display.set_caption("Snake - Niveles Infinitos")
clock = pygame.time.Clock()

# Fuentes
fuente = pygame.font.SysFont("arialrounded", 22, bold=True)
fuente_titulo = pygame.font.SysFont("arialrounded", 40, bold=True)

# Colores
VERDE1 = (118, 200, 94)
VERDE2 = (141, 214, 110)
AZUL = (70, 130, 250)
AZUL_OSCURO = (50, 100, 200)
ROJO = (230, 60, 60)
ROJO_CLARO = (255, 100, 100)
MORADO = (128, 0, 128)
AMARILLO = (255, 215, 0)
BLANCO = (255, 255, 255)
FONDO = (30, 144, 255)
NEGRO = (0, 0, 0)

# SONIDOS
def cargar_sonido(nombre):
    try:
        return pygame.mixer.Sound(nombre)
    except Exception:
        return None

Comer_sonido = cargar_sonido("Comer.wav")
Trampa_sonido = cargar_sonido("Trampa.wav")
GameOver_sonido = cargar_sonido("GameOver.wav")

# RECORDS
RECORD_FILE = "records.txt"
DEFAULT_PLAYER = "Jugador"

def leer_record():
    if os.path.exists(RECORD_FILE):
        try:
            with open(RECORD_FILE, "r", encoding="utf-8") as f:
                line = f.read().strip()
                if not line:
                    return {"player": DEFAULT_PLAYER, "score": 0, "level": 0, "date": ""}
                parts = line.split("|")
                if len(parts) >= 4:
                    return {"player": parts[0], "score": int(parts[1]), "level": int(parts[2]), "date": parts[3]}
        except Exception:
            pass
    return {"player": DEFAULT_PLAYER, "score": 0, "level": 0, "date": ""}

def guardar_record(player, score, level):
    current = leer_record()
    if score > current.get("score", 0):
        with open(RECORD_FILE, "w", encoding="utf-8") as f:
            f.write(f"{player}|{score}|{level}|{datetime.now().isoformat()}")
        return True
    return False

# UTILIDADES
def dibujar_tablero():
    for x in range(0, ANCHO, TAM_CELDA):
        for y in range(0, ALTO, TAM_CELDA):
            color = VERDE1 if (x // TAM_CELDA + y // TAM_CELDA) % 2 == 0 else VERDE2
            pygame.draw.rect(pantalla, color, (x, y, TAM_CELDA, TAM_CELDA))

def dibujar_serpiente(serpiente):
    for i, pos in enumerate(serpiente):
        color = AZUL if i == 0 else AZUL_OSCURO
        pygame.draw.rect(pantalla, color, (*pos, TAM_CELDA, TAM_CELDA), border_radius=5)

def dibujar_manzana(pos):
    pygame.draw.circle(pantalla, ROJO, (pos[0] + TAM_CELDA // 2, pos[1] + TAM_CELDA // 2), TAM_CELDA // 2)
    pygame.draw.circle(pantalla, ROJO_CLARO, (pos[0] + TAM_CELDA // 2, pos[1] + TAM_CELDA // 2), TAM_CELDA // 3)

def mostrar_texto(texto, pos, color=BLANCO, fuente_usar=fuente):
    label = fuente_usar.render(texto, True, color)
    pantalla.blit(label, pos)

# CLASE BOTON
class Boton:
    def __init__(self, texto, y):
        self.texto = texto
        self.rect = pygame.Rect(ANCHO // 2 - 120, y, 240, 50)
        self.base_color = (0, 102, 255)
        self.hover_color = (0, 153, 255)
        self.color = self.base_color

    def dibujar(self, mouse_pos):
        self.color = self.hover_color if self.rect.collidepoint(mouse_pos) else self.base_color
        pygame.draw.rect(pantalla, self.color, self.rect, border_radius=10)
        mostrar_texto(self.texto, (self.rect.x + 50, self.rect.y + 10), BLANCO)

    def presionado(self, pos):
        return self.rect.collidepoint(pos)

# POSICION VALIDA
def posicion_valida(excluir, cantidad=1):
    salida = []
    tries = 0
    while len(salida) < cantidad and tries < 5000:
        x = random.randrange(0, ANCHO, TAM_CELDA)
        y = random.randrange(0, ALTO, TAM_CELDA)
        if [x, y] in excluir or [x, y] in salida:
            tries += 1
            continue
        salida.append([x, y])
    return salida if cantidad > 1 else (salida[0] if salida else None)

# PEDIR NOMBRE
def pedir_nombre():
    nombre = ""
    active = True
    while active:
        pantalla.fill(FONDO)
        mostrar_texto("Snake - Niveles Infinitos", (ANCHO // 2 - 220, 140), AMARILLO, fuente_titulo)
        mostrar_texto("Introduce tu nombre:", (ANCHO // 2 - 120, 250))
        pygame.draw.rect(pantalla, BLANCO, (ANCHO//2 - 120, 290, 240, 40), 2)
        mostrar_texto(nombre, (ANCHO//2 - 115, 295), BLANCO)
        pygame.display.flip()
        clock.tick(30)

        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif evento.type == pygame.KEYDOWN:
                if evento.key == pygame.K_RETURN and nombre.strip() != "":
                    return nombre.strip()
                elif evento.key == pygame.K_BACKSPACE:
                    nombre = nombre[:-1]
                else:
                    if len(nombre) < 15:
                        nombre += evento.unicode

# JUEGO PRINCIPAL
def juego(jugador):
    serpiente = []
    inicio_x = (ANCHO // 2) - (TAM_CELDA * 2)
    inicio_y = (ALTO // 2)
    for i in range(5):
        serpiente.append([inicio_x + i * TAM_CELDA, inicio_y])
    serpiente = serpiente[::-1]

    direccion = "DERECHA"
    cambio = direccion

    nivel = 1
    longitud_objetivo = 10
    puntaje = 0

    manzana = posicion_valida(serpiente)
    
    # TRAMPAS
    trampas = []
    manzanas_comidas = 0
    TRAMPAS_CADA = 3

    while True:
        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif evento.type == pygame.KEYDOWN:
                if (evento.key in [pygame.K_UP, pygame.K_w]) and direccion != "ABAJO":
                    cambio = "ARRIBA"
                elif (evento.key in [pygame.K_DOWN, pygame.K_s]) and direccion != "ARRIBA":
                    cambio = "ABAJO"
                elif (evento.key in [pygame.K_LEFT, pygame.K_a]) and direccion != "DERECHA":
                    cambio = "IZQUIERDA"
                elif (evento.key in [pygame.K_RIGHT, pygame.K_d]) and direccion != "IZQUIERDA":
                    cambio = "DERECHA"

        direccion = cambio
        cabeza = list(serpiente[0])
        if direccion == "ARRIBA":
            cabeza[1] -= TAM_CELDA
        elif direccion == "ABAJO":
            cabeza[1] += TAM_CELDA
        elif direccion == "IZQUIERDA":
            cabeza[0] -= TAM_CELDA
        elif direccion == "DERECHA":
            cabeza[0] += TAM_CELDA

        cabeza[0] %= ANCHO
        cabeza[1] %= ALTO

        if cabeza in serpiente:
            if GameOver_sonido: GameOver_sonido.play()
            return puntaje, nivel, False

        serpiente.insert(0, cabeza)

        # Comer manzana
        if cabeza == manzana:
            puntaje += 1
            manzanas_comidas += 1
            if Comer_sonido: Comer_sonido.play()
            manzana = posicion_valida(serpiente + trampas)

            # Crear trampa cada TRAMPAS_CADA manzanas
            if manzanas_comidas % TRAMPAS_CADA == 0:
                nueva_trampa = posicion_valida(serpiente + trampas + [manzana])
                if nueva_trampa:
                    trampas.append(nueva_trampa)
        else:
            serpiente.pop()

        # Colisión con trampas
        for trampa in trampas[:]:
            if cabeza == trampa:
                trampas.remove(trampa)
                if len(serpiente) > 3:
                    serpiente = serpiente[:-2]  # Reducir 2 segmentos
                else:
                    serpiente = serpiente[:3]  # Mantener mínimo 3 segmentos
                if Trampa_sonido:
                    Trampa_sonido.play()
                break

        # Subir nivel
        if len(serpiente) >= longitud_objetivo:
            nivel += 1
            longitud_objetivo += 10

            # Reiniciar serpiente a longitud 5 en cada nuevo nivel
            inicio_x = (ANCHO // 2) - (TAM_CELDA * 2)
            inicio_y = (ALTO // 2)
            serpiente = [[inicio_x + i * TAM_CELDA, inicio_y] for i in range(5)]
            serpiente = serpiente[::-1]
            direccion = "DERECHA"
            cambio = direccion

            # Reiniciar trampas y manzana
            trampas.clear()
            manzana = posicion_valida(serpiente)
            manzanas_comidas = 0

        # Dibujar todo
        pantalla.fill(NEGRO)
        dibujar_tablero()
        dibujar_serpiente(serpiente)
        dibujar_manzana(manzana)
        for trampa in trampas:
            pygame.draw.rect(pantalla, MORADO, (*trampa, TAM_CELDA, TAM_CELDA))
            pygame.draw.rect(pantalla, AMARILLO, (*trampa, TAM_CELDA, TAM_CELDA), 2)

        mostrar_texto(f"{puntaje}", (10, 8))
        mostrar_texto(f"Nivel: {nivel}", (110, 8), AMARILLO)
        record = leer_record()
        mostrar_texto(f"Record: {record['score']} ({record['player']})", (220, 8), MORADO)

        pygame.display.flip()
        velocidad = FPS_BASE * (1.1 ** (nivel - 1)) + (puntaje // 2)
        clock.tick(max(6, int(velocidad)))

# MENÚ 
def menu():
    boton_play = Boton("Play", 250)
    boton_exit = Boton("Exit", 320)

    while True:
        pantalla.fill(FONDO)
        mostrar_texto("Snake - Niveles Infinitos", (ANCHO // 2 - 220, 140), AMARILLO, fuente_titulo)

        mouse_pos = pygame.mouse.get_pos()
        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif evento.type == pygame.MOUSEBUTTONDOWN:
                if boton_play.presionado(evento.pos):
                    jugador = pedir_nombre()
                    puntaje, nivel, gano = juego(jugador)
                    game_over(puntaje, nivel, jugador, gano)
                elif boton_exit.presionado(evento.pos):
                    pygame.quit()
                    sys.exit()

        boton_play.dibujar(mouse_pos)
        boton_exit.dibujar(mouse_pos)
        pygame.display.flip()
        clock.tick(30)

# GAME OVER
def game_over(puntaje, nivel, jugador, gano):
    record = leer_record()
    nuevo = False
    if guardar_record(jugador, puntaje, nivel):
        nuevo = True
    if GameOver_sonido and not nuevo:
        GameOver_sonido.play()

    while True:
        pantalla.fill((70, 130, 250))

        # GAME OVER o RETO COMPLETADO centrado
        texto_principal = "¡Reto completado!" if gano else "Game Over"
        label = fuente_titulo.render(texto_principal, True, AMARILLO if gano else BLANCO)
        pantalla.blit(label, ((ANCHO - label.get_width()) // 2, 150))

        # PUNTAJE
        label = fuente.render(f"Puntaje: {puntaje}", True, BLANCO)
        pantalla.blit(label, ((ANCHO - label.get_width()) // 2, 250))

        # NIVEL
        label = fuente.render(f"Nivel alcanzado: {nivel}", True, BLANCO)
        pantalla.blit(label, ((ANCHO - label.get_width()) // 2, 290))

        # RECORD
        rec = leer_record()
        label = fuente.render(f"Record: {rec['score']} ({rec['player']})", True, AMARILLO)
        pantalla.blit(label, ((ANCHO - label.get_width()) // 2, 330))

        # NUEVO RECORD
        if nuevo:
            label = fuente.render("¡Nuevo récord guardado!", True, AMARILLO)
            pantalla.blit(label, ((ANCHO - label.get_width()) // 2, 370))

        # INSTRUCCIÓN ENTER
        label = fuente.render("ENTER para volver al menú", True, BLANCO)
        pantalla.blit(label, ((ANCHO - label.get_width()) // 2, 420))

        pygame.display.flip()

        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif evento.type == pygame.KEYDOWN and evento.key == pygame.K_RETURN:
                return

# EJECUCIÓN PRINCIPAL
if __name__ == "__main__":
    menu()