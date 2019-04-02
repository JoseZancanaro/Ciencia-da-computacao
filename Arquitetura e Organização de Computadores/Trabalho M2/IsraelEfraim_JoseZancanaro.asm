# Disciplina: 4189 – Arquitetura e Organização de Computadores
# Atividade: Avaliação 03–Programação de procedimentos
# Grupo: - Israel Efraim de Oliveira	
#        - José Carlos Zancanaro

	.data

# TAMANHO MÍNIMO E MÁXIMO
TAMANHO_MINIMO 			: .word 2
TAMANHO_MAXIMO 			: .word 6
TAMANHO_REAL			: .word 0

# OPCAO DE ORDENAÇÃO
OPCAO_ORDENACAO_MINIMA		: .word 1
OPCAO_ORDENACAO_MAXIMA		: .word 3

# TIPO DE ORDENAÇÃO
ORDEM_CRESCENTE			: .word 0
ORDEM_DECRESCENTE		: .word 1

# AVALIAÇÃO
AVALIACAO_MINIMA		: .word 1
AVALIACAO_MAXIMA		: .word 10

# VETORES
VETOR_SERIES_CODIGO		: .word -1, -1, -1, -1, -1, -1
VETOR_SERIES_AS1		: .word -1, -1, -1, -1, -1, -1
VETOR_SERIES_AST		: .word -1, -1, -1, -1, -1, -1
VETOR_SERIES_EST		: .word -1, -1, -1, -1, -1, -1
VETOR_SERIES_CODIGO_AUX		: .word -1, -1, -1, -1, -1, -1
VETOR_SERIES_COPIA_UM		: .word -1, -1, -1, -1, -1, -1
VETOR_SERIES_COPIA_DOIS		: .word -1, -1, -1, -1, -1, -1

# TEXTOS DE IO

TXT_LER_QUANTIDADE_SERIES 	: .asciiz "Insira a quantidade de séries (min. = 2, máx. = 6): "
TXT_LER_TAMANHO_INVALIDO 	: .asciiz "Valor inválido, tente novamente.\n"

TXT_NOME_VETOR_SERIES_CODIGO 	: .asciiz "CS"
TXT_NOME_VETOR_SERIES_AS1 	: .asciiz "AS1"
TXT_NOME_VETOR_SERIES_AST 	: .asciiz "AST"
TXT_NOME_VETOR_SERIES_EST 	: .asciiz "EST"

TXT_VETOR_CS_VALOR_INVALIDO 	: .asciiz "Código já cadastrado ou inválido, tente novamente.\n"
TXT_VETOR_AS1_VALOR_INVALIDO	: .asciiz "Quantidade inválida, tente novamente.\n"
TXT_VETOR_AST_VALOR_INVALIDO	: .asciiz "Valor negativo ou superior à quantidade do vetor anterior, tente novamente.\n"
TXT_VETOR_EST_VALOR_INVALIDO	: .asciiz "Avaliação inválida, tente novamente.\n"

TXT_VETOR_COLCHETE_ABRE 	: .asciiz "["
TXT_VETOR_COLCHETE_FECHA	: .asciiz "] : "

TXT_LER_SERIE_ORDENACAO		: .asciiz "Selecione o indicador a ser utilizado para a classificação das séries:\n"
TXT_LER_SERIE_OPCAO_1		: .asciiz "1. Assistiram apenas um episódio.\n"
TXT_LER_SERIE_OPCAO_2		: .asciiz "2. Assistiram todos os episódios.\n"
TXT_LER_SERIE_OPCAO_3		: .asciiz "3. Número de estrelas.\n"
TXT_LER_SERIE_ORDENACAO_OPCAO	: .asciiz "Digite a opção desejada para ordenação (1..3) : "
TXT_LER_SERIE_VALOR_INVALIDO	: .asciiz "Opção inválida, tente novamente.\n"

TXT_MSG_CLASSIFICACAO		: .asciiz "Classificação das séries após ordenação: "
TXT_MSG_CLASSIFICACAO_AS1	: .asciiz "Assistiram apenas um episódio"
TXT_MSG_CLASSIFICACAO_AST	: .asciiz "Assistiram todos os episódios"
TXT_MSG_CLASSIFICACAO_EST	: .asciiz "Número de estrelas"

TXT_EXIBIR_ORDENADO_INICIO	: .asciiz "o lugar - CS = "
TXT_EXIBIR_ORDENADO_MEIO	: .asciiz ", "
TXT_EXIBIR_ORDENADO_FIM		: .asciiz " = "

TXT_MSG_ORDEM_BUBBLESORT	: .asciiz "Digite 0 para ordenação crescente ou 1 para decrescente: "

TXT_MSG_VETOR_SERIES_CS	 	: .asciiz "Insira o código das séries:  \n"
TXT_MSG_VETOR_SERIES_AS1	: .asciiz "Insira a quantidade de pessoas que assistiram apenas um episódio: \n"
TXT_MSG_VETOR_SERIES_AST 	: .asciiz "Insira a quantidade de pessoas que assistiram todos os episódios: \n"
TXT_MSG_VETOR_SERIES_EST	: .asciiz "Insira a avaliação das séries (min = 1, máx = 10): \n"

TXT_MSG_BUBBLESORT_CRESCENTE	: .asciiz "Ordenando posições de forma crescente.  \n"
TXT_MSG_BUBBLESORT_DECRESCENTE	: .asciiz "Ordenando posições de forma decrescente.\n"

TXT_MSG_NOVA_LINHA		: .asciiz "\n"

	.text

	j	main

# <SOLICITAR_VALOR_EXCLUSIVO>
# solicitar_valor_exclusivo : Função para solicitar ao usuário um valor inteiro com restrição.
# Parâmetros : endereço-base da mensagem ($a0), endereço-base da mensagem de erro ($a1), valor mínimo ($a2), valor máximo ($a3).
# Retorna : inteiro válido preenchido pelo usuário.
solicitar_valor_exclusivo:
	
	# PUSH
	addi	$sp, $sp, -28				# Reservar 7 words na pilha.
	sw	$s6, 24($sp)				# $sp + 24 = $s6
	sw	$s5, 20($sp)				# $sp + 20 = $s5
	sw	$s4, 16($sp)				# $sp + 16 = $s4
	sw	$s3, 12($sp)				# $sp + 12 = $s3
	sw	$s2, 8($sp)				# $sp + 8  = $s2
	sw	$s1, 4($sp)				# $sp + 4  = $s1
	sw	$s0, 0($sp)				# $sp + 0  = $s0

	# Copiar parâmetros
	add	$s0, $zero, $a0				# $s0 = $a0
	add	$s1, $zero, $a1				# $s1 = $a1
	add	$s2, $zero, $a2				# $s2 = $a2
	add	$s3, $zero, $a3				# $s3 = $a3
	
	# Inicializar valor de retorno
	addi	$s4, $zero, 0				# $s4 = 0
	
	# DO WHILE - Repetir enquanto usuário não inserir um valor entre o mínimo e máximo.
	
solicitar_valor_exclusivo_do_while:

	# Solicitar valor
	add	$a0, $s0, $zero				# $a0 = MENSAGEM
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	addi	$v0, $zero, 5				# $v0 = read_int
	syscall						# CHAMADA DE SISTEMA (read_int)
	
	add	$s4, $zero, $v0				# $s4 = $v0
	
	# Conferir se o valor inserido é válido
	slt	$s5, $s4, $s2				# $s5 = $s4 < $s2 ? 1 : 0
	sgt	$s6, $s4, $s3				# $s6 = $s4 > $s3 ? 1 : 0
	or	$s5, $s5, $s6				# $s5 = $s5 or $s6
	
	# Pular para o retorno se o valor é válido
	beq	$s5, $zero, solicitar_valor_exclusivo_retornar
	
	# Senão, informar que o valor é inválido
	add	$a0, $s1, $zero				# $a0 = MENSAGEM_VALOR_INVALIDO
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	j	solicitar_valor_exclusivo_do_while

solicitar_valor_exclusivo_retornar:

	# Mover valor válido para retorno
	add	$v0, $zero, $s4				# $v0 = $s2
	
	# POP
	lw	$s0, 0($sp)				# $s0 = $sp + 0
	lw	$s1, 4($sp)				# $s1 = $sp + 4
	lw	$s2, 8($sp)				# $s2 = $sp + 8
	lw	$s3, 12($sp)				# $s3 = $sp + 12
	lw	$s4, 16($sp)				# $s4 = $sp + 16
	lw	$s5, 20($sp)				# $s5 = $sp + 20
	lw	$s6, 24($sp)				# $s6 = $sp + 24
	addi	$sp, $sp, 28
	
	jr	$ra
# </SOLICITAR_VALOR_EXCLUSIVO>
	
# <EXISTE_EM_VETOR>
# existe_em_vetor : Função para conferir se um valor existe em um vetor.
# Parâmetros : endereço-base do vetor ($a0), tamanho do vetor ($a1), valor para conferir ($a2)
# Retorna : 1 se encontrou, 0 se o valor não está no vetor.
existe_em_vetor:
	
	# PUSH
	addi	$sp, $sp, -32				# Reservar 8 words na pilha.
	sw	$s0, 28($sp)				# $sp + 28 = $s0
	sw	$s1, 24($sp)				# $sp + 24 = $s1
	sw	$s2, 20($sp)				# $sp + 20 = $s2
	sw	$s3, 16($sp)				# $sp + 16 = $s3
	sw	$s4, 12($sp)				# $sp + 12 = $s4
	sw	$s5, 8($sp)				# $sp + 8  = $s5
	sw	$s6, 4($sp)				# $sp + 4  = $s6
	sw	$s7, 0($sp)				# $sp + 0  = $s7

	# Copiar parâmetros
	add	$s0, $zero, $a0				# $s0 = $a0
	add	$s1, $zero, $a1				# $s1 = $a1
	add	$s2, $zero, $a2				# $s2 = $a2
	
	# Iniciar variável para iteração e valor para retorno
	addi	$s3, $zero, 0				# $s3 (i) = 0
	addi	$s7, $zero, 0				# $s7 (true/false) = 0 
	
existe_em_vetor_for_ini:
	beq	$s3, $s1, existe_em_vetor_retornar	# Finaliza o loop se atingiu o tamanho do vetor
	
	# Deslocar i e somar endereço base de memória
	sll	$s4, $s3, 2				# $s4 = $s3 * 4
	add	$s4, $s4, $s0				# $s4 += $s0 (endereço do vetor passado por parâmetro)
	
	# Comparar se um valor é igual ao número passado por parâmetro
	lw	$s5, 0($s4)				# $s5 = *$s4 (vetor[i])
	sub	$s6, $s2, $s5				# $s6 = $s2 - $s5
	
	bne	$s6, $zero, existe_em_vetor_fim_if	# Pula para o fim do if se $s6 for diferente de 0.
	
	addi	$s7, $zero, 1				# $s7 = 1
	j	existe_em_vetor_retornar
	
existe_em_vetor_fim_if:	
	addi	$s3, $s3, 1				# $s3 += 1 (i++)
	j	existe_em_vetor_for_ini
	
existe_em_vetor_retornar:
	add	$v0, $zero, $s7				# $v0 = $s7
	
	# POP
	lw	$s7, 0($sp)				# $s7 = $sp + 0
	lw	$s6, 4($sp)				# $s6 = $sp + 4
	lw	$s5, 8($sp)				# $s5 = $sp + 8
	lw	$s4, 12($sp)				# $s4 = $sp + 12
	lw	$s3, 16($sp)				# $s3 = $sp + 16
	lw	$s2, 20($sp)				# $s2 = $sp + 20
	lw	$s1, 24($sp)				# $s1 = $sp + 24
	lw	$s0, 28($sp)				# $s0 = $sp + 28
	addi	$sp, $sp, 32
	
	jr	$ra
# </EXISTE_EM_VETOR>

# <PREENCHER_CODIGO_SERIES>
# preencher_codigo_series : Solicita e preenche um vetor de código de séries com informações preenchidas pelo usuário.
# Parâmetros : endereço-base do vetor ($a0), tamanho do vetor ($a1).
# Retorna : void. Alterações são feitas no vetor por referência.
preencher_codigo_series:

	# PUSH
	addi	$sp, $sp, -36				# Reservar 9 words na pilha.
	sw	$s7, 32($sp)				# $sp + 32 = $s7
	sw	$s6, 28($sp)				# $sp + 28 = $s6
	sw	$s5, 24($sp)				# $sp + 24 = $s5
	sw	$s4, 20($sp)				# $sp + 20 = $s4
	sw	$s3, 16($sp)				# $sp + 16 = $s3
	sw	$s2, 12($sp)				# $sp + 12 = $s2
	sw	$s1, 8($sp)				# $sp + 8  = $s1
	sw	$s0, 4($sp)				# $sp + 4  = $s0
	sw	$ra, 0($sp)				# $sp + 0  = $ra
	
	# Copiar valores do parâmetro
	add	$s0, $zero, $a0				# $s0 = $a0 (endereço-base do vetor)
	add	$s1, $zero, $a1				# $s1 = $a1 (tamanho do vetor)
	
	la 	$a0, TXT_MSG_VETOR_SERIES_CS		# $a0 = TXT_MSG_VETOR_SERIES_CS
	addi 	$v0, $zero , 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	addi	$s2, $zero, 0				# $s2 (i) = 0

preencher_codigo_series_for_ini:
	
	beq	$s2, $s1, preencher_codigo_series_for_fim
	
	sll	$s3, $s2, 2				# $s3 = $s2 (i) * 4
	add	$s3, $s3, $s0				# $s3 += $s0 (endereço-base)

preencher_codigo_series_do_while_ini:

	# Mostrar entrada de vetor
	la	$a0, TXT_NOME_VETOR_SERIES_CODIGO	# $a0 = TXT_NOME_VETOR_SERIES_CODIGO
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_VETOR_COLCHETE_ABRE		# $a0 = TXT_VETOR_COLCHETE_ABRE
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	add	$a0, $zero, $s2				# $a0 = $s2 (i)
	addi	$v0, $zero, 1				# $v0 = print_int
	syscall						# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_VETOR_COLCHETE_FECHA		# $a0 = TXT_VETOR_COLCHETE_FECHA
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	addi	$v0, $zero, 5				# $v0 = read_int
	syscall
	
	add	$s4, $zero, $v0				# $s4 = $v0 (leitura)
	
	# Chamar função para verificar se valores inseridos são exclusivos
	add	$a0, $zero, $s0				# $a0 = $so (endereço-base do vetor)
	add	$a1, $zero, $s2				# $a1 = $s2 (i)
	add	$a2, $zero, $s4				# $s4 = $v0 (alvo)
	jal	existe_em_vetor				# existe_em_vetor($a0, $a1, $a2)
	
	add	$s5, $zero, $v0				# $s5 = $v0 (resultado de existe_em_vetor)
	slt	$s6, $s4, $zero				# $s6 = $s4 < 0 ? 1 : 0
	
	or	$s7, $s5, $s6				# $s7 = $s5 or $s6
	beq	$s7, $zero, preencher_codigo_series_do_while_fim
	
	la	$a0, TXT_VETOR_CS_VALOR_INVALIDO	# $a0 = TXT_VETOR_CS_VALOR_INVALIDO
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)

	j	preencher_codigo_series_do_while_ini
	
preencher_codigo_series_do_while_fim:
	
	sw	$s4, 0($s3)				# $s3 (vetor[i]) = $s4
	addi	$s2, $s2, 1				# $s2 += 1 (i++)
	
	j	preencher_codigo_series_for_ini
	
preencher_codigo_series_for_fim:
	
	# POP
	lw	$ra, 0($sp)				# $ra = $sp + 0
	lw	$s0, 4($sp)				# $s0 = $sp + 4
	lw	$s1, 8($sp)				# $s1 = $sp + 8
	lw	$s2, 12($sp)				# $s2 = $sp + 12
	lw	$s3, 16($sp)				# $s3 = $sp + 16
	lw	$s4, 20($sp)				# $s4 = $sp + 20
	lw	$s5, 24($sp)				# $s5 = $sp + 24
	lw	$s6, 28($sp)				# $s6 = $sp + 28
	lw	$s7, 32($sp)				# $s7 = $sp + 32
	add	$sp, $sp, 36				# Desalocar 9 words da pilha.
	
	jr	$ra
# </PREENCHER_CODIGO_SERIES>

# <PREENCHER_ASSISTIRAM_UM>
# preencher_assistiram_um : Solicita e preenche um vetor de quantidades de pessoas que assistiram pelo menos um episódio.
# Parâmetros : endereço-base do vetor ($a0), tamanho do vetor ($a1).
# Retorna : void. Alterações são feitas no vetor por referência.
preencher_assistiram_um:

	# PUSH
	addi	$sp, $sp, -36				# Reservar 9 words na pilha.
	sw	$s7, 32($sp)				# $sp + 32 = $s7
	sw	$s6, 28($sp)				# $sp + 28 = $s6
	sw	$s5, 24($sp)				# $sp + 24 = $s5
	sw	$s4, 20($sp)				# $sp + 20 = $s4
	sw	$s3, 16($sp)				# $sp + 16 = $s3
	sw	$s2, 12($sp)				# $sp + 12 = $s2
	sw	$s1, 8($sp)				# $sp + 8  = $s1
	sw	$s0, 4($sp)				# $sp + 4  = $s0
	sw	$ra, 0($sp)				# $sp + 0  = $ra
	
	# Copiar parâmetros
	add	$s0, $zero, $a0				# $s0 = $a0 (endereço-base do vetor)
	add	$s1, $zero, $a1				# $s1 = $a1 (tamanho do vetor)
	
	la 	$a0, TXT_MSG_VETOR_SERIES_AS1		# $a0 = TXT_MSG_VETOR_SERIES_AS1
	addi 	$v0, $zero , 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	addi	$s2, $zero, 0				# $s2 (i) = 0

preencher_assistiram_um_for_ini:
	
	beq	$s2, $s1, preencher_assistiram_um_for_fim
	
	sll	$s3, $s2, 2				# $s3 = $s2 (i) * 4
	add	$s3, $s3, $s0				# $s3 += $s0 (endereço-base)

preencher_assistiram_um_do_while_ini:

	# Mostrar entrada de vetor
	la	$a0, TXT_NOME_VETOR_SERIES_AS1		# $a0 = TXT_NOME_VETOR_SERIES_AS1
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_VETOR_COLCHETE_ABRE		# $a0 = TXT_VETOR_COLCHETE_ABRE
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	add	$a0, $zero, $s2				# $a0 = $s2 (i)
	addi	$v0, $zero, 1				# $v0 = print_int
	syscall						# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_VETOR_COLCHETE_FECHA		# $a0 = TXT_VETOR_COLCHETE_FECHA
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	addi	$v0, $zero, 5				# $v0 = read_int
	syscall
	
	add	$s4, $zero, $v0				# $s4 = $v0 (leitura)
	
	slt	$s5, $s4, $zero				# $s5 = $s4 < 0 ? 1 : 0
	beq	$s5, $zero, preencher_assistiram_um_do_while_fim
	
	la	$a0, TXT_VETOR_AS1_VALOR_INVALIDO	# $a0 = TXT_VETOR_AS1_VALOR_INVALIDO
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)

	j	preencher_assistiram_um_do_while_ini
	
preencher_assistiram_um_do_while_fim:
	
	sw	$s4, 0($s3)				# $s3 (vetor[i]) = $s4
	addi	$s2, $s2, 1				# $s2 += 1 (i++)
	
	j	preencher_assistiram_um_for_ini
	
preencher_assistiram_um_for_fim:
	
	# POP
	lw	$ra, 0($sp)				# $ra = $sp + 0
	lw	$s0, 4($sp)				# $s0 = $sp + 4
	lw	$s1, 8($sp)				# $s1 = $sp + 8
	lw	$s2, 12($sp)				# $s2 = $sp + 12
	lw	$s3, 16($sp)				# $s3 = $sp + 16
	lw	$s4, 20($sp)				# $s4 = $sp + 20
	lw	$s5, 24($sp)				# $s5 = $sp + 24
	lw	$s6, 28($sp)				# $s6 = $sp + 28
	lw	$s7, 32($sp)				# $s7 = $sp + 32
	add	$sp, $sp, 36				# Desalocar 9 words da pilha.
	
	jr	$ra
# </PREENCHER_ASSISTIRAM_UM>

# <PREENCHER_ASSISTIRAM_TODOS>
# preencher_assistiram_todos : Solicita e preenche um vetor de quantidades de pessoas que assistiram todos os episódios.
# Parâmetros : endereço-base do vetor ($a0), endereço-base do vetor AS1 ($a1), tamanho do vetor ($a2).
# Retorna : void. Alterações são feitas no vetor por referência.
preencher_assistiram_todos:

	# PUSH
	addi	$sp, $sp, -36				# Reservar 9 words na pilha.
	sw	$s7, 32($sp)				# $sp + 32 = $s7
	sw	$s6, 28($sp)				# $sp + 28 = $s6
	sw	$s5, 24($sp)				# $sp + 24 = $s5
	sw	$s4, 20($sp)				# $sp + 20 = $s4
	sw	$s3, 16($sp)				# $sp + 16 = $s3
	sw	$s2, 12($sp)				# $sp + 12 = $s2
	sw	$s1, 8($sp)				# $sp + 8  = $s1
	sw	$s0, 4($sp)				# $sp + 4  = $s0
	sw	$ra, 0($sp)				# $sp + 0  = $ra
	
	# Copiar parâmetros
	add	$s0, $zero, $a0				# $s0 = $a0 (endereço-base do vetor AST)
	add	$s1, $zero, $a1				# $s1 = $a1 (endereço-base do vetor AS1)
	add	$s2, $zero, $a2				# $s2 = $a2 (tamanho do vetor)
	
	la 	$a0, TXT_MSG_VETOR_SERIES_AST		# $a0 = TXT_MSG_VETOR_SERIES_AST
	addi 	$v0, $zero , 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	addi	$s3, $zero, 0				# $s3 (i) = 0

preencher_assistiram_todos_for_ini:
	
	beq	$s3, $s2, preencher_assistiram_todos_for_fim
	
	# Endereçar os vetores de audiência
	sll	$s4, $s3, 2				# $s4 = $s3 (i) * 4
	add	$s5, $s4, $s1				# $s5 = $s4 + $s1 (endereço-base AS1)
	add	$s4, $s4, $s0				# $s4 += $s0 (endereço-base AST)

preencher_assistiram_todos_do_while_ini:

	# Mostrar entrada de vetor
	la	$a0, TXT_NOME_VETOR_SERIES_AST		# $a0 = TXT_NOME_VETOR_SERIES_AST
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_VETOR_COLCHETE_ABRE		# $a0 = TXT_VETOR_COLCHETE_ABRE
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	add	$a0, $zero, $s3				# $a0 = $s3 (i)
	addi	$v0, $zero, 1				# $v0 = print_int
	syscall						# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_VETOR_COLCHETE_FECHA		# $a0 = TXT_VETOR_COLCHETE_FECHA
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	addi	$v0, $zero, 5				# $v0 = read_int
	syscall						# CHAMADA DE SISTEMA (read_int)
	
	# O valor digitado permanecerá em $v0 para economizar registradores
	
	lw	$s6, 0($s5)				# $s6 = $s5 (VETOR_SERIES_AS1[i])
	sgt	$s6, $v0, $s6				# $s6 = $v0 > $s6 ? 1 : 0
	slt	$s7, $v0, $zero				# $s6 = $v0 < 0 ? 1 : 0
	
	or	$s7, $s6, $s7				# $s6 = $s6 or $s7
	beq	$s7, $zero, preencher_assistiram_todos_do_while_fim
	
	la	$a0, TXT_VETOR_AST_VALOR_INVALIDO	# $a0 = TXT_VETOR_AST_VALOR_INVALIDO
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)

	j	preencher_assistiram_todos_do_while_ini
	
preencher_assistiram_todos_do_while_fim:
	
	sw	$v0, 0($s4)				# $s4 (vetor[i]) = $v0
	addi	$s3, $s3, 1				# $s3 += 1 (i++)
	
	j	preencher_assistiram_todos_for_ini
	
preencher_assistiram_todos_for_fim:
	
	# POP
	lw	$ra, 0($sp)				# $ra = $sp + 0
	lw	$s0, 4($sp)				# $s0 = $sp + 4
	lw	$s1, 8($sp)				# $s1 = $sp + 8
	lw	$s2, 12($sp)				# $s2 = $sp + 12
	lw	$s3, 16($sp)				# $s3 = $sp + 16
	lw	$s4, 20($sp)				# $s4 = $sp + 20
	lw	$s5, 24($sp)				# $s5 = $sp + 24
	lw	$s6, 28($sp)				# $s6 = $sp + 28
	lw	$s7, 32($sp)				# $s7 = $sp + 32
	add	$sp, $sp, 36				# Desalocar 9 words da pilha.
	
	jr	$ra
# </PREENCHER_ASSISTIRAM_TODOS>

# <PREENCHER_ESTRELAS>
# preencher_estrelas: Solicita e preenche um vetor com avaliação de séries.
# Parâmetros : endereço-base do vetor ($a0), tamanho do vetor ($a1).
# Retorna : void. Alterações são feitas no vetor por referência.
preencher_estrelas:

	# PUSH
	addi	$sp, $sp, -36				# Reservar 9 words na pilha.
	sw	$s7, 32($sp)				# $sp + 32 = $s7
	sw	$s6, 28($sp)				# $sp + 28 = $s6
	sw	$s5, 24($sp)				# $sp + 24 = $s5
	sw	$s4, 20($sp)				# $sp + 20 = $s4
	sw	$s3, 16($sp)				# $sp + 16 = $s3
	sw	$s2, 12($sp)				# $sp + 12 = $s2
	sw	$s1, 8($sp)				# $sp + 8  = $s1
	sw	$s0, 4($sp)				# $sp + 4  = $s0
	sw	$ra, 0($sp)				# $sp + 0  = $ra
	
	# Copiar parâmetros
	add	$s0, $zero, $a0				# $s0 = $a0 (endereço-base do vetor)
	add	$s1, $zero, $a1				# $s1 = $a1 (tamanho do vetor)
	
	la 	$a0, TXT_MSG_VETOR_SERIES_EST		# $a0 = TXT_MSG_VETOR_SERIES_EST
	addi 	$v0, $zero , 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	addi	$s2, $zero, 0				# $s2 (i) = 0

preencher_estrelas_for_ini:
	
	beq	$s2, $s1, preencher_estrelas_for_fim
	
	sll	$s3, $s2, 2				# $s3 = $s2 (i) * 4
	add	$s3, $s3, $s0				# $s3 += $s0 (endereço-base do vetor)

preencher_estrelas_do_while_ini:

	# Mostrar entrada do vetor
	la	$a0, TXT_NOME_VETOR_SERIES_EST		# $a0 = TXT_NOME_VETOR_SERIES_EST
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_VETOR_COLCHETE_ABRE		# $a0 = TXT_VETOR_COLCHETE_ABRE
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	add	$a0, $zero, $s2				# $a0 = $s2 (i)
	addi	$v0, $zero, 1				# $v0 = print_int
	syscall						# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_VETOR_COLCHETE_FECHA		# $a0 = TXT_VETOR_COLCHETE_FECHA
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	addi	$v0, $zero, 5				# $v0 = read_int
	syscall						# CHAMADA DE SISTEMA (read_int)
	
	add	$s4, $zero, $v0				# $s4 = $v0
	
	slti	$s5, $s4, 1				# $s5 = $s4 < 0 ? 1 : 0
	addi	$s6, $zero, 10				# $s6 = 10 (máximo de estrelas)
	sgt	$s6, $s4, $s6				# $s6 = $s4 > 10 ? 1 : 0
	
	or	$s7, $s5, $s6				# $s7 = $s5 or $s6
	beq	$s7, $zero, preencher_estrelas_do_while_fim
	
	la	$a0, TXT_VETOR_EST_VALOR_INVALIDO	# $a0 = TXT_VETOR_EST_VALOR_INVALIDO
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)

	j	preencher_estrelas_do_while_ini
	
preencher_estrelas_do_while_fim:
	
	sw	$s4, 0($s3)				# $s4 (vetor[i]) = $s3
	addi	$s2, $s2, 1				# $s2 += 1 (i++)
	
	j	preencher_estrelas_for_ini
	
preencher_estrelas_for_fim:
	
	# POP
	lw	$ra, 0($sp)				# $ra = $sp + 0
	lw	$s0, 4($sp)				# $s0 = $sp + 4
	lw	$s1, 8($sp)				# $s1 = $sp + 8
	lw	$s2, 12($sp)				# $s2 = $sp + 12
	lw	$s3, 16($sp)				# $s3 = $sp + 16
	lw	$s4, 20($sp)				# $s4 = $sp + 20
	lw	$s5, 24($sp)				# $s5 = $sp + 24
	lw	$s6, 28($sp)				# $s6 = $sp + 28
	lw	$s7, 32($sp)				# $s7 = $sp + 32
	add	$sp, $sp, 36				# Desalocar 9 words da pilha.
	
	jr	$ra
# </PREENCHER_ESTRELAS>

# <BUBBLESORT_SERIES>
# bubblesort_series : Ordena séries de forma crescente ou decrescente.
# Parâmetros : endereço-base do vetor CS ($a0), endereço-base do vetor a ser ordenado ($a1), tamanho do vetor ($a2), tipo ordenação ($a3) : 0 (crescente), 1 (decrescente).
# Retorna : void. Alterações são feitas nos vetores por referência.
bubblesort_series:

	# PUSH
	addi	$sp, $sp, -36				# Reservar 9 words na pilha.
	sw	$s7, 32($sp)				# $sp + 32 = $s7
	sw	$s6, 28($sp)				# $sp + 28 = $s6
	sw	$s5, 24($sp)				# $sp + 24 = $s5
	sw	$s4, 20($sp)				# $sp + 20 = $s4
	sw	$s3, 16($sp)				# $sp + 16 = $s3
	sw	$s2, 12($sp)				# $sp + 12 = $s2
	sw	$s1, 8($sp)				# $sp + 8  = $s1
	sw	$s0, 4($sp)				# $sp + 4  = $s0
	sw	$ra, 0($sp)				# $sp + 0  = $ra

	# Copiar parâmetros
	add	$s0, $zero, $a0				# $s0 = $a0 (endereço do vetor CS)
	add	$s1, $zero, $a1				# $s1 = $a1 (endereço do vetor a ser ordenado)
	add	$s2, $zero, $a2				# $s2 = $a2 (tamanho do vetor)
	add	$s3, $zero, $a3				# $s3 = $a3 (ordem)
	
	add	$s4, $zero, $zero			# $s4 (i) = 0

bubblesort_series_for_ext_ini:

	beq	$s4, $s2, bubblesort_series_for_ext_fim
	
	sub	$s5, $s2, $s4				# $s5 = $s2 - $s4 (limite do loop j)
	addi	$s5, $s5, -1				# $s5--
	
	add	$s6, $zero, $zero			# $s5 (j) = 0
	
bubblesort_series_for_int_ini:

	beq	$s6, $s5, bubblesort_series_for_int_fim

	# Endereçando o vetor a ser ordenado em j
	sll	$s7, $s6, 2				# $s7 = $s6 * 4
	add	$t0, $s7, $s1				# $t0 = $s7 + $s1 ($vetor_a_ser_ordenado).
	add	$s7, $s7 $s0				# $s7 += $s0 (&vetor_cs)
	
	# Endereçando o vetor a ser orenado em j+1
	addi	$t1, $s6, 1				# $t1 = $s6 + 1 (j + 1)
	sll	$t1, $t1, 2				# $t1 = $t1 * 4
	add	$t2, $t1, $s1				# $t2 = $t1 + $s1 (&vetor_a_ser_ordenado)
	add	$t1, $t1, $s0				# $t1 += $s0 (&vetor_cs)
	
	lw	$t3, 0 ($t0)				# $t3 = *$t0 (vetor_a_ser_ordenado[j])
	lw	$t4, 0 ($t2)				# $t4 = *$t2 (vetor_a_ser_ordenado[j+1])
	
	# Conferir se a ordenação é crescente e o par precisa ser ordenado
	sgt	$t5, $t3, $t4				# $t5 = $t3 > $t4 ? 1 : 0
	nor	$t6, $s3, $zero				# $t6 = !$s3
	and	$t5, $t6, $t5				# $t5 = $t6 and $t5
	
	# Conferir se a ordenação é decrescente e o par precisa ser ordenado
	slt	$t6, $t3, $t4				# $t6 = $t3 < $t4 ? 1 : 0
	and	$t6, $t6, $s3				# $t6 = $t6 and $s3
	
	or	$t5, $t5, $t6				# $t5 = $t5 or $t6
	
	beq	$t5, $zero, bubblesort_series_n_ordena	# Se 0, então não precisamos ordenar.
	
	# SWAP (vetor a ser ordenado)
	sw	$t3, 0 ($t2)				# *$t2 (vetor_a_ser_ordenado[j+1]) = $t3
	sw	$t4, 0 ($t0)				# *$t0 (vetor_a_ser_ordenado[j] = $t4
	
	# SWAP (Códigos de série a ser ordenado)
	lw	$t3, 0 ($s7)				# $t3 = *$s7 (vetor_cs[j]
	lw	$t4, 0 ($t1)				# $t4 = *$t1 (vetor_cs[j+1])
	sw	$t3, 0 ($t1)				# *$t1 (vetor_cs[j+1] = $t3
	sw	$t4, 0 ($s7)				# *$s7 ((vetor_cs[j] = $t4

bubblesort_series_n_ordena:
		
	addi	$s6, $s6, 1				# $s6++ (j++)
	j	bubblesort_series_for_int_ini
	
bubblesort_series_for_int_fim:

	addi	$s4, $s4, 1				# $s4++ (i++)
	j	bubblesort_series_for_ext_ini
	
bubblesort_series_for_ext_fim:

	# POP
	lw	$ra, 0($sp)				# $ra = $sp + 0
	lw	$s0, 4($sp)				# $s0 = $sp + 4
	lw	$s1, 8($sp)				# $s1 = $sp + 8
	lw	$s2, 12($sp)				# $s2 = $sp + 12
	lw	$s3, 16($sp)				# $s3 = $sp + 16
	lw	$s4, 20($sp)				# $s4 = $sp + 20
	lw	$s5, 24($sp)				# $s5 = $sp + 24
	lw	$s6, 28($sp)				# $s6 = $sp + 28
	lw	$s7, 32($sp)				# $s7 = $sp + 32
	add	$sp, $sp, 36				# Desalocar 9 words da pilha.
	
	jr	$ra
# </BUBBLESORT_SERIES>

# <COPIAR_VETOR>
# copiar_vetor : Copia um vetor base para um vetor destino.
# Parâmetros : endereço-base do vetor para copiar ($a0), endereço-base do vetor destino ($a1), tamanho do vetor ($a2)
# Retorna : void.
copiar_vetor:
	
	# PUSH
	addi	$sp, $sp, -28				# Reservar 7 words na pilha.
	sw	$s6, 24($sp)				# $sp + 24 = $s6
	sw	$s5, 20($sp)				# $sp + 20 = $s5
	sw	$s4, 16($sp)				# $sp + 16 = $s4
	sw	$s3, 12($sp)				# $sp + 12 = $s3
	sw	$s2, 8($sp)				# $sp + 8  = $s2
	sw	$s1, 4($sp)				# $sp + 4  = $s1
	sw	$s0, 0($sp)				# $sp + 0  = $s0

	# Copiar parâmetros
	add	$s0, $a0, $zero				# $s0 = $a0
	add	$s1, $a1, $zero				# $s1 = $a1
	add	$s2, $a2, $zero				# $s2 = $a2
	
	add	$s3, $zero, $zero			# $s3 (i) = 0
		
copiar_vetor_for_ini:

	beq	$s3, $s2, copiar_vetor_for_fim
	
	# Endereçar vetor base e vetor destino
	sll	$s4, $s3, 2				# $s4 = $s3 * 4
	add	$s5, $s4, $s0				# $s5 = $s4 + $s0 (&vetor_base)
	add	$s6, $s4, $s1				# $s6 = $s4 + $s1 (&vetor_destino)
	
	# Copiar 
	lw	$s4, 0($s5)				# $s4 = *$s5
	sw	$s4, 0($s6)				# $s6 (vetor_destino[i]) = $s4
	
	addi	$s3, $s3, 1				# $s3++
	j	copiar_vetor_for_ini			# Retornar ao início do loop.

copiar_vetor_for_fim:

	# POP
	lw	$s0, 0($sp)				# $s0 = $sp + 0
	lw	$s1, 4($sp)				# $s1 = $sp + 4
	lw	$s2, 8($sp)				# $s2 = $sp + 8
	lw	$s3, 12($sp)				# $s3 = $sp + 12
	lw	$s4, 16($sp)				# $s4 = $sp + 16
	lw	$s5, 20($sp)				# $s5 = $sp + 20
	lw	$s6, 24($sp)				# $s6 = $sp + 24
	add	$sp, $sp, 28				# Desalocar 7 words da pilha.
	
	jr	$ra
# </COPIAR_VETOR>

# <SINCRONIZAR_SERIES>
# sincronizar_series : Sincroniza as séries, de acordo com os movimentos feitos no vetor de código de séries.
# Parâmetros : Vetor de códigos originais ($sp + 16), vetor de códigos após ordenação ($sp + 12),
#		tamanho do vetor ($sp + 8), vetor para ser sincronizado ($sp + 4) vetor para ser sincronizado ($sp + 0)
# Retorna : void.Faz alterações por referência.
sincronizar_series:

	# Copiar parâmetros da pilha para t
	lw	$t0, 16 ($sp)				# $t0 = $sp + 16
	lw	$t1, 12 ($sp)				# $t1 = $sp + 12
	lw	$t2, 8 ($sp)				# $t2 = $sp + 8
	lw	$t3, 4 ($sp)				# $t3 = $sp + 4
	lw	$t4, 0 ($sp)				# $t4 = $sp + 0
	addi	$sp, $sp, 20				# Desalocar 5 words da pilha.
	
	# PUSH
	addi	$sp, $sp, -36				# Reservar 9 words na pilha.
	sw	$s7, 32($sp)				# $sp + 32 = $s7
	sw	$s6, 28($sp)				# $sp + 28 = $s6
	sw	$s5, 24($sp)				# $sp + 24 = $s5
	sw	$s4, 20($sp)				# $sp + 20 = $s4
	sw	$s3, 16($sp)				# $sp + 16 = $s3
	sw	$s2, 12($sp)				# $sp + 12 = $s2
	sw	$s1, 8($sp)				# $sp + 8  = $s1
	sw	$s0, 4($sp)				# $sp + 4  = $s0
	sw	$ra, 0($sp)				# $sp + 0  = $ra
	
	# Copiar parâmetros
	add	$s0, $t0, $zero				# $s0 = $t0 (vetor_cs_original)
	add	$s1, $t1, $zero				# $s1 = $t1 (vetor_cs_modificado)
	add	$s2, $t2, $zero				# $s2 = $t2 (tamanho)
	add	$s3, $t3, $zero				# $s3 = $t3 (vetor_a_sincronizar1)
	add	$s4, $t4, $zero				# $s4 = $t4 (vetor_a_sincronizar2)
	
	# Criar vetores auxiliares para sincronização
	add	$a0, $s3, $zero				# $a0 = $s3
	la	$a1, VETOR_SERIES_COPIA_UM		# $a1 = &VETOR_SERIES_COPIA_UM
	add	$a2, $s2, $zero				# $a2 = $s2 (tamanho)
	jal	copiar_vetor				# copiar_vetor ($a0, $a1, $a2)
	
	add	$a0, $s4, $zero				# $a0 = $s4
	la	$a1, VETOR_SERIES_COPIA_DOIS		# $a1 = &VETOR_SERIES_COPIA_UM
	add	$a2, $s2, $zero				# $a2 = $s2 (tamanho)
	jal	copiar_vetor				# copiar_vetor ($a0, $a1, $a2)
	
	add	$s5, $zero, $zero			# $s5 (i) = 0
	
sincronizar_series_for_ext_ini:
	
	beq	$s5, $s2, sincronizar_series_for_ext_fim
	add	$s6, $zero, $zero			# $s6 (j) = 0
	
	# Criar ponteiro para vetor_CS original em i
	sll	$s7, $s5, 2				# $s7 = $s5 (i) * 4
	add	$t0, $s7, $s0				# $t0 = $s7 + $s0 (&vetor_cs_original)
	
sincronizar_series_for_int_ini:

	beq	$s6, $s2, sincronizar_series_for_int_fim
	
	sub	$t1, $s5, $s6				# $t1 = $s5 - $s6
	beq	$t1, $zero, sincronizar_series_nao_troca
	
	# Criar ponteiro para vetor_CS modificado em j
	sll	$t1, $s6, 2				# $t1 = $s6 * 4
	add	$t2, $t1, $s1				# $t2 = $t1 + $s1 (&vetor_cs_modificado)
	
	# Conferir se os códigos de vetor_CS original em i e vetor_CS modificado em j são iguais
	lw	$t2, 0 ($t2)				# $t2 = *$t2
	lw	$t3, 0 ($t0)				# $t3 = *$t0
	sub	$t2, $t2, $t3				# $t2 = $t2 - $t3
	
	bne	$t2, $zero, sincronizar_series_nao_troca
	
	# Sincronizar primeiro vetor
	la	$t2, VETOR_SERIES_COPIA_UM		# $t2 = &VETOR_SERIES_COPIA_UM
	add	$t2, $t2, $s7				# $t2 = $t2 + $s7
	lw	$t2, 0 ($t2)				# $t2 = *$
	add	$t3, $s3, $t1				# $t3 = $s3 + $t1
	sw	$t2, 0 ($t3)				# *$t3 = $t2
	
	# Sincronizar segundo vetor
	la	$t2, VETOR_SERIES_COPIA_DOIS		# $t2 = &VETOR_SERIES_COPIA_DOIS
	add	$t2, $t2, $s7				# $t2 = $t2 + $t1
	lw	$t2, 0 ($t2)				# $t2 = *$t2
	add	$t3, $s4, $t1				# $t3 = $s3 + $t1
	sw	$t2, 0 ($t3)				# *$t3 = $t2
	
	j	sincronizar_series_for_int_fim		# Break (sair do loop interior)
			
sincronizar_series_nao_troca:

	addi	$s6, $s6, 1				# $s6++
	j	sincronizar_series_for_int_ini
	
sincronizar_series_for_int_fim:

	addi	$s5, $s5, 1				# $s5++
	j	sincronizar_series_for_ext_ini
	
sincronizar_series_for_ext_fim:
	
	# POP
	lw	$ra, 0($sp)				# $ra = $sp + 0
	lw	$s0, 4($sp)				# $s0 = $sp + 4
	lw	$s1, 8($sp)				# $s1 = $sp + 8
	lw	$s2, 12($sp)				# $s2 = $sp + 12
	lw	$s3, 16($sp)				# $s3 = $sp + 16
	lw	$s4, 20($sp)				# $s4 = $sp + 20
	lw	$s5, 24($sp)				# $s5 = $sp + 24
	lw	$s6, 28($sp)				# $s6 = $sp + 28
	lw	$s7, 32($sp)				# $s7 = $sp + 32
	add	$sp, $sp, 36				# Desalocar 9 words da pilha.
	
	jr	$ra
# </SINCRONIZAR_SERIES>

# <SOLICITAR_ORDENACAO>
# solicitar_ordenacao : Retorna a opção desejada de ordenação (1 - AS1, 2 - AST, 3 - EST).
# Parâmetros : void.
# Retorna : inteiro (opção de 1 à 3).
solicitar_ordenacao:

	# PUSH
	addi	$sp, $sp, -20				# Reservar 5 words na pilha.
	sw	$s3, 16 ($sp)				# $sp + 16 = $s3
	sw	$s2, 12 ($sp)				# $sp + 12 = $s2
	sw	$s1, 8 ($sp)				# $sp + 8  = $s1
	sw	$s0, 4 ($sp)				# $sp + 4  = $s0
	sw	$ra, 0 ($sp)				# $sp + 0  = $ra
	
	# Imprimir opções
	la	$a0, TXT_LER_SERIE_ORDENACAO		# $a0 = TXT_LER_SERIE_ORDENACAO
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_LER_SERIE_OPCAO_1		# $a0 = TXT_LER_SERIE_OPCAO_1
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_LER_SERIE_OPCAO_2		# $a0 = TXT_LER_SERIE_OPCAO_2
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_LER_SERIE_OPCAO_3		# $a0 = TXT_LER_SERIE_OPCAO_1
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	# Solicitar valor entre 1 e 3
	la	$a0, TXT_LER_SERIE_ORDENACAO_OPCAO	# $a0 = TXT_LER_SERIE_ORDENACAO_OPCAO
	la	$a1, TXT_LER_SERIE_VALOR_INVALIDO	# $a1 = TXT_LER_SERIE_VALOR_INVALIDO
	la	$a2, OPCAO_ORDENACAO_MINIMA		# $a2 = &OPCAO_ORDENACAO_MINIMA
	lw	$a2, 0 ($a2)				# $a2 = *OPCAO_ORDENACAO_MINIMA
	la	$a3, OPCAO_ORDENACAO_MAXIMA		# $a3 = &OPCAO_ORDENACAO_MAXIMA
	lw	$a3, 0 ($a3)				# $a3 = *OPCAO_ORDENACAO_MAXIMA
	jal	solicitar_valor_exclusivo		# solicitar_valor_exclusivo ($a0, $a1, $a2, $a3)
	
	# POP
	lw	$ra, 0 ($sp)				# $ra = $sp + 0
	lw	$s0, 4 ($sp)				# $s0 = $sp + 4
	lw	$s1, 8 ($sp)				# $s1 = $sp + 8
	lw	$s2, 12 ($sp)				# $s2 = $sp + 12
	lw	$s3, 16 ($sp)				# $s3 = $sp + 16
	addi	$sp, $sp, 20				# Desalocar 5 words da pilha.
		
	jr	$ra
# </SOLICITAR_ORDENACAO>

# <MOSTRAR_VETOR_ORDENADO>
# mostrar_vetor_ordenado : Exibe resultado de ordenação de acordo com os parâmetros.
# Parâmetros : endereço-base do vetor de códigos ($a0), endereço-base do vetor ordenado ($a1), tamanho do vetor ($a2), texto da categoria de ordenação ($a3)
# Retorna : void. Não há alteração, único efeito colateral é a exibição dos textos.
mostrar_vetor_ordenado:

	# PUSH
	addi	$sp, $sp, -28				# Reservar 7 words na pilha.
	sw	$s6, 24 ($sp)				# $sp + 24 = $s6
	sw	$s5, 20 ($sp)				# $sp + 20 = $s5
	sw	$s4, 16 ($sp)				# $sp + 16 = $s4
	sw	$s3, 12 ($sp)				# $sp + 12 = $s3
	sw	$s2, 8 ($sp)				# $sp + 8  = $s2
	sw	$s1, 4 ($sp)				# $sp + 4  = $s1
	sw	$s0, 0 ($sp)				# $sp + 0  = $s0

	# Copiar parâmetros
	add	$s0, $a0, $zero				# $s0 = $a0
	add	$s1, $a1, $zero				# $s1 = $a1
	add	$s2, $a2, $zero				# $s2 = $a2
	add	$s3, $a3, $zero				# $s3 = $a3
	
	# Mostrar o tipo de classificação da ordenação
	
	la	$a0, TXT_MSG_CLASSIFICACAO		# $a0 = TXT_MSG_CLASSIFICACAO
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	add	$a0, $s3, $zero				# $a0 = texto_categoria_ordenacao
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_MSG_NOVA_LINHA			# $a0 = TXT_EXIBIR_NOVA_LINHA
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	add	$s4, $zero, $zero			# $s4 (i) = 0
	
mostrar_vetor_ordenado_for_ini:

	beq	$s4, $s2, mostrar_vetor_ordenado_for_fim
	
	# Mostrar classificação
	
	addi	$a0, $s4, 1				# $s5 = $s4 + 1
	addi	$v0, $zero, 1				# $v0 = print_int
	syscall						# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_EXIBIR_ORDENADO_INICIO		# $a0 = TXT_EXIBIR_ORDENADO_INICIO
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	sll	$s5, $s4, 2				# $s5 = $s4 (i) * 4
	
	add	$s6, $s5, $s0				# $s6 = $s5 + $s0 (&vetor_cs)
	lw	$a0, 0 ($s6)				# $a0 = *$s6
	addi	$v0, $zero, 1				# $v0 = print_int
	syscall						# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_EXIBIR_ORDENADO_MEIO		# $a0 = TXT_EXIBIR_ORDENADO_MEIO
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	add	$a0, $s3, $zero				# $a0 = $s3
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_EXIBIR_ORDENADO_FIM		# $a0 = TXT_EXIBIR_ORDENADO_FIM
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	# Exibir valor em i 
	add	$s6, $s5, $s1				# $s6 = $s5 + $s1 (&vetor_ordenado)
	lw	$a0, 0 ($s6)				# $a0 = *$s6
	addi	$v0, $zero, 1				# $v0 = print_int
	syscall						# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_MSG_NOVA_LINHA			# $a0 = TXT_EXIBIR_NOVA_LINHA
	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)	

	addi	$s4, $s4, 1				# $s4++ (i++)
	j	mostrar_vetor_ordenado_for_ini
	
mostrar_vetor_ordenado_for_fim:

	# POP
	lw	$s0, 0 ($sp)				# $sp + 0  = $s0
	lw	$s1, 4 ($sp)				# $sp + 4  = $s1
	lw	$s2, 8 ($sp)				# $sp + 8  = $s2
	lw	$s3, 12 ($sp)				# $sp + 12 = $s3
	lw	$s4, 16 ($sp)				# $sp + 16  = $s4
	lw	$s5, 20 ($sp)				# $sp + 20  = $s5
	lw	$s6, 24 ($sp)				# $sp + 24  = $s6
	addi	$sp, $sp, 28				# Desalocar 7 words na pilha.

	jr	$ra
# </MOSTRAR_VETOR_ORDENADO>


main:

	# Solicitar tamanho real dos vetores (de 2 à 6)

	la	$s0, TAMANHO_REAL			# $s0 = &(TAMANHO_REAL)
	
	la	$a0, TXT_LER_QUANTIDADE_SERIES		# $a0 = TXT_LER_QUANTIDADE_SERIES
	la	$a1, TXT_LER_TAMANHO_INVALIDO		# $a1 = TXT_LER_TAMANHO_INVALIDO
	la	$a2, TAMANHO_MINIMO			# $a2 = &(TAMANHO_MINIMO)
	lw	$a2, 0($a2)				# $a2 = TAMANHO_MINIMO
	la	$a3, TAMANHO_MAXIMO			# $a3 = &(TAMANHO_MAXIMO)
	lw	$a3, 0($a3)				# $a3 = TAMANHO_MAXIMO
	jal	solicitar_valor_exclusivo		# solicitar_valor_exclusivo ($a0, $a1, $a2, $a3)
	
	# Salvar tamanho real dos vetores em $s0
	
	sw	$v0, 0($s0)				# *$s0 = $v0
	add	$s0, $zero, $v0				# $s0 = $v0
	
	# Ler vetor de códigos de séries
	
	la	$a0, VETOR_SERIES_CODIGO		# $a0 = &(VETOR_SERIES_CODIGO)
	add	$a1, $zero, $s0				# $a1 = $s0 (tamanho do vetor)
	jal	preencher_codigo_series			# preencher_codigo_series ($a0, $a1)
	
	# Copiar vetor de códigos para um vetor auxiliar para assistir na sincronização em seguida.
	
	la	$a0, VETOR_SERIES_CODIGO		# $a0 = &VETOR_SERIES_CODIGO
	la	$a1, VETOR_SERIES_CODIGO_AUX		# $a1 = &VETOR_SERIES_CODIGO_AUX
	add	$a2, $s0, $zero				# $a2 = $s0 (TAMANHO_REAL)
	jal	copiar_vetor				# copiar_vetor($a0, $a1, $a2)
	
	# Solicitar quantidade de pessoas que assistiram um episódio apenas
	
	la	$a0, VETOR_SERIES_AS1			# $a0 = &(VETOR_SERIES_AS1)
	add	$a1, $zero, $s0				# $a1 = $s0 (tamanho do vetor)
	jal	preencher_assistiram_um			# preencher_assistiram_um ($a0, $a1)
	
	# Solicitar quantidade de pessoas que assistiram todos
	
	la	$a0, VETOR_SERIES_AST			# $a0 = &(VETOR_SERIES_AST)
	la	$a1, VETOR_SERIES_AS1			# $a1 = &(VETOR_SERIES_AS1)
	add	$a2, $zero, $s0				# $a2 = $s0 (tamanho do vetor)
	jal	preencher_assistiram_todos		# preencher_assistiram_todos ($a0, $a1, $a2)
	
	# Solicitar avaliação das séries
	
	la	$a0, VETOR_SERIES_EST			# $a0 = &(VETOR_SERIES_EST)
	add	$a1, $zero, $s0				# $a1 = $s0 (tamanho do vetor)
	jal	preencher_estrelas			# preencher_estrelas ($a0, $a1)
	
	# Solicitar qual vetor será ordenado (AS1 / AST / EST)
	
	jal	solicitar_ordenacao			# solicitar_ordenacao()
	add	$s1, $v0, $zero				# $s1 = $v0
	
	# Solicitar tipo de ordenação (Crescente / Decrescente)
	
	la	$a0, TXT_MSG_ORDEM_BUBBLESORT		# $a0 = TXT_MSG_ORDEM_BUBBLESORT
	la	$a1, TXT_LER_TAMANHO_INVALIDO		# $a1 = TXT_LER_TAMANHO_INVALIDO
	la	$a2, ORDEM_CRESCENTE			# $a2 = &ORDEM_CRESCENTE
	lw	$a2, 0 ($a2)				# $a2 = *ORDEM_CRESCENTE
	la	$a3, ORDEM_DECRESCENTE			# $a3 = &ORDEM_CRESCENTE
	lw	$a3, 0 ($a3)				# $a3 = *ORDEM_CRESCENTE
	jal	solicitar_valor_exclusivo		# solicitar_valor_exclusivo ($a0, $a1, $a2, $a3)
	
	add	$s2, $v0, $zero				# $s2 = $v0
	
	# Informar o tipo de ordenação escolhido.
	
	bne	$s2, $zero, main_mostrar_aviso_decrescente
	la	$a0, TXT_MSG_BUBBLESORT_CRESCENTE	# $a0 = TXT_MSG_BUBBLESORT_CRESCENTE
	j	main_mostrar_aviso_fim
	
main_mostrar_aviso_decrescente:
	la	$a0, TXT_MSG_BUBBLESORT_DECRESCENTE	# $a0 = TXT_MSG_BUBBLESORT_DECRESCENTE
	
main_mostrar_aviso_fim:

	addi	$v0, $zero, 4				# $v0 = print_string
	syscall						# CHAMADA DE SISTEMA (print_string)
	
	la	$s4, VETOR_SERIES_CODIGO
	
	# SWITCH CASE
	
	# Configurar qual vetor será ordenado e quais serão apenas sincronizados.
	
	# $s0 = tamanho
	# $s1 = escolha para o switch
	# $s2 = tipo de ordenação
	# $s3 = nome do indicador de classificação
	# $s4 = vetor_cs
	# $s5 = vetor_para_ordenar
	# $s6 = vetor_para_sincronizar
	# $s7 = vetor_para_sincronizar
	
main_escolha_caso_1:
	addi	$s3, $s1, -1				# Case 1: Devemos ordenar o vetor AS1 e sincronizar AST e EST.
	bne	$s3, $zero, main_escolha_caso_2

	la	$s3, TXT_MSG_CLASSIFICACAO_AS1		# $s3 = TXT_MSG_CLASSIFICACAO_AS1
	la	$s5, VETOR_SERIES_AS1			# $s5 = &VETOR_SERIES_AS1
	la	$s6, VETOR_SERIES_AST			# $s6 = &VETOR_SERIES_AST
	la	$s7, VETOR_SERIES_EST			# $s7 = &VETOR_SERIES_EST
	
	j	main_escolha_sair			# break
	
main_escolha_caso_2:
	addi	$s3, $s1, -2				# Case 2: Devemos ordenar o vetor AST e sincronizar o AS1 e EST.
	bne	$s3, $zero, main_escolha_caso_3
	
	la	$s3, TXT_MSG_CLASSIFICACAO_AST		# $s3 = TXT_MSG_CLASSIFICACAO_AST
	la	$s5, VETOR_SERIES_AST			# $s5 = &VETOR_SERIES_AST
	la	$s6, VETOR_SERIES_AS1			# $s6 = &VETOR_SERIES_AS1
	la	$s7, VETOR_SERIES_EST			# $s7 = &VETOR_SERIES_EST
	
	j	main_escolha_sair			# break
	
main_escolha_caso_3:
	addi	$s3, $s1, -3				# Case 3: Devemos ordenar o vetor EST e ordenar o AS1 e AST.
	bne	$s3, $zero, main_escolha_sair
	
	la	$s3, TXT_MSG_CLASSIFICACAO_EST		# $s3 = TXT_MSG_CLASSIFICACAO_EST
	la	$s5, VETOR_SERIES_EST			# $s5 = &VETOR_SERIES_EST
	la	$s6, VETOR_SERIES_AS1			# $s6 = &VETOR_SERIES_AS1
	la	$s7, VETOR_SERIES_AST			# $s7 = &VETOR_SERIES_AST
	
main_escolha_sair:

	# Chamar bubblesort
	add	$a0, $s4, $zero				# $a0 = $s4 (vetor de códigos)
	add	$a1, $s5, $zero				# $a1 = $s5 (vetor para ser ordenado)
	add	$a2, $s0, $zero				# $a2 = $s0 (tamanho real do vetor)
	add	$a3, $s2, $zero				# $a3 = $s2 (tipo de ordenação)
	jal	bubblesort_series			# bubblesort_series ($a0, $a1, $a2, $a3)
	
	# Chamar sincronizador
	la	$s1, VETOR_SERIES_CODIGO_AUX		# $s1 = &VETOR_SERIES_CODIGO_AUX
	addi	$sp, $sp, -20				# Reservar 5 words na pilha
	sw	$s1, 16 ($sp)				# $sp + 16 = VETOR_SERIES_CODIGO_AUX
	sw	$s4, 12 ($sp)				# $sp + 12 = VETOR_SERIES_CODIGO (após ser ordenado)
	sw	$s0, 8 ($sp)				# $sp + 8  = tamanho
	sw	$s6, 4 ($sp)				# $sp + 4  = vetor_para_sincronizar1
	sw	$s7, 0 ($sp)				# $sp + 0  = vetor_para_sincronizar2
	jal	sincronizar_series			# sincronizar_series ($sp + 16, $sp + 12, $sp + 8, $sp + 4, $sp + 0)
	
	# Mostrar resultados
	add	$a0, $s4, $zero				# $a0 = $s4
	add	$a1, $s5, $zero				# $a1 = $s5
	add	$a2, $s0, $zero				# $a2 = $s0
	add	$a3, $s3, $zero				# $a3 = $s3
	jal	mostrar_vetor_ordenado			# mostrar_vetor_ordenado ($a0, $a1, $a2, $a3)

	addi	$v0, $zero, 10				# $v0 = exit(0)
	syscall						# CHAMADA DE SISTEMA (exit(0))
