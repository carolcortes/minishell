# minishell
# 🐚 minishell

> Projeto desenvolvido na 42 como parte do currículo do common core.
> O objetivo é criar um shell minimalista que interpreta e executa comandos no estilo do bash.

---

## 🚧 Em construção

Este repositório está **em desenvolvimento ativo** por [Carol Cortes](https://github.com/carolcortes) e [Cassiano Gross](https://github.com/Zorug).
Acompanhe nosso progresso pelas [issues](https://github.com/carolcortes/minishell/issues) e [pull requests](https://github.com/carolcortes/minishell/pulls)!

---

## ✨ Objetivos do projeto

- Criar um prompt interativo que aceita comandos do usuário
- Implementar comandos embutidos como `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`
- Suportar execução de comandos com argumentos e variáveis de ambiente
- Lidar com redirecionamentos (`>`, `<`, `>>`) e pipes (`|`)
- Tratar sinais como `CTRL+C` e `CTRL+\`
- Reproduzir o comportamento do bash em vários cenários

---

## 📁 Estrutura atual

```bash
.
├── src/           # Código-fonte da minishell
├── include/       # Headers do projeto
├── lib/           # Libft (ou outras libs usadas)
├── Makefile       # Script de compilação
└── README.md      # Este arquivo
