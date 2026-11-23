#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Automatizador do Orquestrador ArtPlus
=====================================
Executa o fluxo de orquestracao do ArtPlus a cada 5 minutos
com uma GUI visual. Para quando o usuario fecha o programa.

Requisitos:
- Python 3.8+
- tkinter (incluso no Python padrao)

Uso:
    python automatizador.py

Notas:
- Este script nao substitui o /auto do OpenCode.
- Para modo autentico do /auto, use: /auto [escopo] --max 1
"""

import os
import sys
import time
import threading
import json
import queue
from datetime import datetime, timedelta
from pathlib import Path

try:
    from tkinter import Tk, Label, Button, Frame, StringVar, ttk, messagebox
except ImportError:
    print("tkinter nao disponível. Instale o Python com suporte a GUI.")
    sys.exit(1)


# Configuracoes
INTERVALO_PADRAO = 300  # 5 minutos em segundos
PROJETO_PATH = Path(__file__).parent.resolve()
LOG_PATH = PROJETO_PATH / "logs_automacao"
CONTROLE_PATH = PROJETO_PATH / ".automacao_ativa"
MANIFESTO_AUTOMACAO = LOG_PATH / "manifesto_automacao.json"


class StatusApp:
    """Aplicacao GUI principal"""

    def __init__(self, root):
        self.root = root
        self.root.title("🚀 Orquestrador ArtPlus - Automatizador")
        self.root.geometry("520x380")
        self.root.resizable(False, False)

        self.running = False
        self.timer_thread = None

        # Variaveis de status
        self.status_var = StringVar(value="Pronto para iniciar")
        self.ultima_exec_var = StringVar(value="Nunca")
        self.contador_var = StringVar(value="0")
        self.next_run_var = StringVar(value="--:--")

        self.setup_ui()
        self.setup_window_protocol()
        self.load_status()

    def setup_ui(self):
        """Configura a interface do usuario"""
        # Header
        header = Frame(self.root, bg="#2c3e50", height=60)
        header.pack(fill='x', side='top')

        title = Label(header, text="🤖 ART PLUS AUTOMATIZADOR",
                     font=('Segoe UI', 14, 'bold'), fg='white', bg="#2c3e50")
        title.pack(pady=20)

        # Corpo
        body = Frame(self.root)
        body.pack(fill='both', expand=True, padx=20, pady=10)

        # Status atual
        status_frame = Frame(body, relief='raised', bd=2)
        status_frame.pack(fill='x', pady=5)

        Label(status_frame, text="Status:", font=('Segoe UI', 10, 'bold')).pack(anchor='w', padx=10)
        Label(status_frame, textvariable=self.status_var, font=('Segoe UI', 10),
              fg='blue', wraplength=460).pack(anchor='w', padx=10, pady=5)

        # Metricas
        metrics = Frame(body)
        metrics.pack(fill='x', pady=10)

        metric_frame = Frame(metrics)
        metric_frame.pack(anchor='w')

        Label(metric_frame, text="Ultima execucao:", font=('Segoe UI', 10)).pack(anchor='w')
        Label(metric_frame, textvariable=self.ultima_exec_var, font=('Segoe UI', 10), fg='gray').pack()

        metric_frame2 = Frame(metrics)
        metric_frame2.pack(anchor='w', pady=(10, 0))

        Label(metric_frame2, text="Proxima execucao:", font=('Segoe UI', 10)).pack(anchor='w')
        Label(metric_frame2, textvariable=self.next_run_var, font=('Segoe UI', 10), fg='gray').pack()

        # Contador
        counter_frame = Frame(body)
        counter_frame.pack(fill='x', pady=10)

        Label(counter_frame, text="Execucoes realizadas:", font=('Segoe UI', 9)).pack()
        Label(counter_frame, textvariable=self.contador_var, font=('Segoe UI', 12, 'bold'),
              fg='green').pack()

        # Botoes
        buttons = Frame(body)
        buttons.pack(fill='x', pady=15)

        self.btn_iniciar = Button(buttons, text="▶ INICIAR", bg="#27ae60", fg='white',
                                  font=('Segoe UI', 11, 'bold'), command=self.iniciar)
        self.btn_iniciar.pack(side='left', padx=5)

        self.btn_parar = Button(buttons, text="⏹ PARAR", bg="#e74c3c", fg='white',
                                font=('Segoe UI', 11, 'bold'), command=self.parar, state='disabled')
        self.btn_parar.pack(side='left', padx=5)

        self.btn_status = Button(buttons, text="📋 STATUS", bg="#3498db", fg='white',
                                 font=('Segoe UI', 10), command=self.mostrar_status)
        self.btn_status.pack(side='left', padx=5)

        # Log de mensagens
        Label(body, text="Log:", font=('Segoe UI', 10, 'bold')).pack(anchor='w', pady=(15, 5))

        self.log_text = ttk.Treeview(body, height=8)
        self.log_text.pack(fill='both', expand=True)
        self.log_text['columns'] = ('tempo', 'mensagem')
        self.log_text.column('#0', width=0, stretch='no')
        self.log_text.column('tempo', width=100)
        self.log_text.column('mensagem', width=380)
        self.log_text.heading('tempo', text='Hora')
        self.log_text.heading('mensagem', text='Mensagem')

        # Scrollbar
        vbar = ttk.Scrollbar(body, orient='vertical', command=self.log_text.yview)
        self.log_text.configure(yscrollcommand=vbar.set)
        vbar.pack(side='right', fill='y')

    def setup_window_protocol(self):
        """Configura o protocolo de fechamento"""
        self.root.protocol("WM_DELETE_WINDOW", self.fechar_aplicacao)

    def iniciar(self):
        """Inicia a automatizacao"""
        if self.running:
            return

        self.running = True
        self.status_var.set("🔄 Executando automatizacao...")
        self.btn_iniciar.config(state='disabled')
        self.btn_parar.config(state='normal')

        # Criar arquivo de controle
        CONTROLE_PATH.touch()

        # Iniciar thread
        self.timer_thread = threading.Thread(target=self.executar_loop, daemon=True)
        self.timer_thread.start()

        self.log_message("🚀 Automatizacao iniciada")
        self.status_var.set("🔄 Executando automatizacao...")
        self.btn_iniciar.config(state='disabled')
        self.btn_parar.config(state='normal')
        self.log_message("✅ Botao INICIAR acionado com sucesso.")

    def parar(self):
        """Para a automatizacao"""
        self.running = False
        self.status_var.set("⏸ Automatizacao parada")
        self.btn_iniciar.config(state='normal')
        self.btn_parar.config(state='disabled')

        if CONTROLE_PATH.exists():
            CONTROLE_PATH.unlink()

        self.log_message("⏹ Automatizacao parada")

    def fechar_aplicacao(self):
        """Fecha a aplicacao"""
        if messagebox.askyesno("Confirmar", "Deseja parar a automatizacao e fechar?"):
            self.parar()
            self.root.destroy()
            sys.exit(0)

    def executar_loop(self):
        """Loop principal de execucao"""
        contador = 0

        while self.running:
            try:
                proxima_execucao = datetime.now() + timedelta(seconds=INTERVALO_PADRAO)
                self.next_run_var.set(proxima_execucao.strftime("%H:%M:%S"))

                self.log_message("⚙️ Executando ciclo de orquestracao...")
                sucesso = self.run_orquestracao()

                if sucesso:
                    contador += 1
                    self.contador_var.set(str(contador))
                    self.ultima_exec_var.set(datetime.now().strftime("%H:%M"))
                    self.status_var.set(f"✅ Ultimo ciclo concluído ({contador} execucoes)")
                    self.log_message(f"✅ Ciclo concluído com sucesso")
                else:
                    self.status_var.set("⚠️ Ciclo com falhas - verifique logs")
                    self.log_message("❌ Ciclo falhou")

                self.salvar_manifesto(contador)

                # Aguardar intervalo (5 minutos)
                for _ in range(INTERVALO_PADRAO):
                    if not self.running:
                        break
                    time.sleep(1)

            except Exception as e:
                self.log_message(f"❌ Erro no loop: {str(e)}")
                time.sleep(10)

    def run_orquestracao(self) -> bool:
        """Executa a orquestracao do ArtPlus"""
        try:
            inventory_path = PROJETO_PATH / "docs" / "reverse-engineering" / "INVENTORY.md"

            if not inventory_path.exists():
                return self.executar_f002()

            return self.executar_f002()

        except Exception as e:
            self.log_message(f"Erro na orquestracao: {e}")
            return False

    def executar_f002(self) -> bool:
        """Executa o ciclo para F-002 (DocumentMarks.dll)"""
        try:
            feature_path = PROJETO_PATH / "docs" / "features" / "F-002.md"

            with open(feature_path, 'r', encoding='utf-8') as f:
                spec_content = f.read()

            if 'status: spec' in spec_content.lower() or 'status:spec' in spec_content.lower():
                self.log_message("📝 Spec F-002 completa - proximo: Arquitetura")
                return self.gerar_arquitetura_f002()
            else:
                self.log_message("📝 Gerando documentacao para F-002...")
                return self.gerar_documentacao_f002()

        except Exception as e:
            self.log_message(f"Erro na execucao F-002: {e}")
            return False

    def gerar_documentacao_f002(self) -> bool:
        """Gera documentacao para F-002"""
        log_dir = LOG_PATH / "F-002" / "documentacao"
        log_dir.mkdir(parents=True, exist_ok=True)

        doc_file = log_dir / f"doc-gerada-{datetime.now().strftime('%Y%m%d-%H%M%S')}.md"

        doc_content = f"""# Documentacao F-002 - DocumentMarks.dll
Gerada em: {datetime.now().isoformat()}

## Evidencias estaticas
Arquivos de analise Ghidra disponíveis.

## Fluxo principal
1. Carregar documento de mark set (?ReadMarkSetFile)
2. Selecionar pagina alvo (?ApplyMarkSetToPage)
3. Aplicar marca set (?ApplyMarksFromSet)
4. Atualizar cache (?PrepareMarksCache)

## Proximos passos
- [ ] Analisar arquitetura C++ Qt
- [ ] Definir classes: MarkSet, MarkDocument, MarksCache
- [ ] Implementar funcoes estaticas
"""

        with open(doc_file, 'w', encoding='utf-8') as f:
            f.write(doc_content)

        self.log_message(f"📄 Documentacao salva em {doc_file}")
        return True

    def gerar_arquitetura_f002(self) -> bool:
        """Gera arquitetura para F-002"""
        log_dir = LOG_PATH / "F-002" / "arquitetura"
        log_dir.mkdir(parents=True, exist_ok=True)

        arch_file = log_dir / f"arquitetura-{datetime.now().strftime('%Y%m%d-%H%M%S')}.md"

        arch_content = f"""# Arquitetura F-002 - DocumentMarks.dll
Gerada em: {datetime.now().isoformat()}

## Classes principais
### MarkSet
- Responsabilidade: Representa um conjunto de marcas
- Metodos: load(), applyToPage(), validate()

### MarkDocument
- Responsabilidade: Documento contendo marcas
- Metodos: getPageCount(), getPage(), copyMark()

### MarksCache
- Responsabilidade: Cache de marcas para performance
- Metodos: prepare(), invalidate()

## Dependencias
- Document.dll (core do documento)
- Qt6Core.dll, Qt6Widgets.dll
"""

        with open(arch_file, 'w', encoding='utf-8') as f:
            f.write(arch_content)

        self.log_message(f"🔧 Arquitetura salva em {arch_file}")
        return True

    def salvar_manifesto(self, contador: int):
        """Salva manifesto de automatizacao"""
        LOG_PATH.mkdir(parents=True, exist_ok=True)

        manifesto = {
            "automacao_ativa": self.running,
            "contador_execucoes": contador,
            "intervalo_segundos": INTERVALO_PADRAO,
            "ultima_atualizacao": datetime.now().isoformat(),
            "status_atual": self.status_var.get()
        }

        with open(MANIFESTO_AUTOMACAO, 'w', encoding='utf-8') as f:
            json.dump(manifesto, f, indent=2)

    def load_status(self):
        """Carrega status salvo"""
        if MANIFESTO_AUTOMACAO.exists():
            try:
                with open(MANIFESTO_AUTOMACAO, 'r', encoding='utf-8') as f:
                    data = json.load(f)
                    self.contador_var.set(str(data.get('contador_execucoes', 0)))
            except:
                pass

    def log_message(self, mensagem: str):
        """Adiciona mensagem ao log"""
        hora = datetime.now().strftime("%H:%M:%S")
        self.log_text.insert('', 'end', values=(hora, mensagem))
        self.log_text.see('end')

    def mostrar_status(self):
        """Mostra status detalhado"""
        status = f"""Status atual: {self.status_var.get()}
Execucoes: {self.contador_var.get()}
Ultima: {self.ultima_exec_var.get()}
Proxima: {self.next_run_var.get()}
Pasta: {PROJETO_PATH}
"""
        messagebox.showinfo("Status da Automatizacao", status)


def main():
    root = Tk()
    app = StatusApp(root)
    root.mainloop()


if __name__ == "__main__":
    main()