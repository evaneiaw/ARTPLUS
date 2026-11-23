import pywinauto
from pywinauto.application import Application
import time
import os
import datetime

# Timestamp para identificação CAP
timestamp = datetime.datetime.now().strftime('%Y%m%d-%H%M')
cap_id_base = f'CAP-{timestamp}'

print(f'Iniciando captura F-004 — {cap_id_base}')
print('='*60)

# Caminho do ArtPro+ v24
artplus_path = r'C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ArtPro+.exe'

# Conectar ao ArtPro+ v24 que já está rodando
try:
    app = Application(backend='uia').connect(process=19560)
    print('[1] Conectado ao processo ArtPro+ v24 (PID 19560)')
except Exception as e:
    print(f'[1] Falha ao conectar: {e}')
    # Tentar iniciar novo
    app = Application(backend='uia').start(artplus_path)
    time.sleep(10)
    print('[1] ArtPro+ iniciado (novo processo)')

# Obter janela principal
windows = app.windows()
if len(windows) == 0:
    print('[ERRO] Nenhuma janela encontrada')
    exit(1)

main_window = windows[0]
print(f'[2] Janela principal: \"{main_window.window_text()}\"')

# Tentar selecionar um objeto para Selection Mark
# Seleção via Ctrl+A ou clicar em objeto existente
try:
    # Primero tentar selecionar tudo (Ctrl+A)
    print('[3] Tentando selecionar todos (Ctrl+A)...')
    main_window.type_keys('^a', pause=0.5)
    time.sleep(1)
    print('[3] Seleção enviada')
except Exception as e:
    print(f'[3] Erro ao selecionar: {e}')

# Ativar Selection Mark via Ctrl+Shift+S
try:
    print('[4] Ativando Selection Mark (Ctrl+Shift+S)...')
    main_window.type_keys('^+S', pause=1.0)
    time.sleep(2)
    print('[4] Selection Mark ativado')
except Exception as e:
    print(f'[4] Erro ao ativar Selection Mark: {e}')

# Capturar screenshot
try:
    screenshot_path = f'rag/evidence/F-004/behavior/CAP-{timestamp}_selection_mark.png'
    main_window.capture_as_image().save(screenshot_path)
    print(f'[5] Screenshot salvo: {screenshot_path}')
except Exception as e:
    print(f'[5] Erro ao capturar screenshot: {e}')

# Verificar barra de status
try:
    # Procurar janelas relacionadas ao status
    for w in app.windows():
        try:
            title = w.window_text()
            if 'status' in title.lower():
                print(f'[6] Barra de status encontrada: \"{title}\"')
                # Capturar o texto
                try:
                    text = w.window_text()
                    print(f'    Texto da barra: {text}')
                except:
                    pass
        except:
            pass
except Exception as e:
    print(f'[6] Erro ao verificar barra: {e}')

print('='*60)
print('Captura F-004 finalizada')
print(f'Identificadores gerados: {cap_id_base}-01 a 06')