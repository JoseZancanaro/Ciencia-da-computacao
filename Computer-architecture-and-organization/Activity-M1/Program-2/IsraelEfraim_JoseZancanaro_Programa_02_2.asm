# Disciplina: CC4189 –Arquitetura e Organização de Computadores
# Atividade: Avaliação 01–Programação em Linguagem de Montagem
# Programa 02
# Grupo: - Israel Efraim Oliveira
#        - José Carlos Zancanaro

	.data
	#Textos para impressão
	TXT_SLC_TAMANHO:	.asciiz "Entre com o tamanho do vetor (mín. = 2, máx. = 8): "
	TXT_SLC_INVALIDO:	.asciiz "Valor inválido!\n\n"
	TXT_VET_ENT_INICIO:	.asciiz "Vetor_Entrada["
	TXT_VET_PAR_INICIO:	.asciiz "Vetor_Pares["
	TXT_VET_IMP_INICIO:	.asciiz "Vetor_Impares["
	TXT_VET_FINAL:		.asciiz "]: "
	TXT_PRC_LEITURA:	.asciiz "Insira os valores para o vetor de entrada:\n"
	TXT_PRC_EXIBIR:		.asciiz "Exibindo vetores...\n"
	TXT_PRC_EXIBIR_NPAR:	.asciiz	"Não há números pares!\n"
	TXT_PRC_EXIBIR_NIMP:	.asciiz	"Não há números ímpares!\n"
	TXT_PRC_EXIBIR_PAR:	.asciiz "Vetor de números pares:\n"
	TXT_PRC_EXIBIR_IMP:	.asciiz "Vetor de números ímpares:\n"
	TXT_PRC_SEPARAR:	.asciiz "Separando valores numéricos.\n"
	TXT_PRC_SEPARAR_FIM:	.asciiz "Separação concluída.\n"
	TXT_COM_NOVALINHA:	.asciiz "\n"
	
	#Variáveis para interação
	tamanhoMin:		.word 2
	tamanhoMax:		.word 8
	
	Vetor_Entrada:		.word 0, 0, 0, 0, 0, 0, 0, 0
	tamanhoEntrada:		.word 0
	
	Vetor_Pares:		.word -1, -1, -1, -1, -1, -1, -1, -1
	tamanhoPares:		.word 0
	
	Vetor_Impares:		.word -1, -1, -1, -1, -1, -1, -1, -1
	tamanhoImpares:		.word 0
		
	.text
main:
	la	$s0, tamanhoMin			# $s0 = &(tamanhoMin)
	lw	$s0, 0($s0)			# $s0 = (tamanhoMin)
	la	$s1, tamanhoMax			# $s1 = &(tamanhomax)
	lw	$s1, 0($s1)			# $s1 = (tamanhoMax)
	la	$s2, tamanhoEntrada		# $s2 = &(tamanhoEntrada)
	
do_while_tamVet_inicio:
	la	$a0, TXT_SLC_TAMANHO		# $a0 = "Entre com o número de itens do vetor(mín. = 2, máx. = 8): "
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	addi	$v0, $zero, 5			# $v0 = read_int
	syscall					# CHAMADA DE SISTEMA (read_int)
	
	add	$s3, $zero, $v0			# $s3 (tamanhoEntrada) = $v0
	slt	$t0, $s3, $s0			# $t0 = $s3 < $s0 ? 1 : 0	
	sgt	$t1, $s3, $s1			# $t1 = $s3 > $s1 ? 1 : 0
	add	$t2, $t0, $t1			# $t2 = $t0 + $t1
	
	beq	$t2, $zero, do_while_tamVet_fim	# Pula pro final se o input for > 1 e < 9.
	
	la	$a0, TXT_SLC_INVALIDO		# $a0 = "Tamanho inválido.\n\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	j	do_while_tamVet_inicio
do_while_tamVet_fim:
	
	add	$s1, $zero, $s3			# mover tamanhoEntrada para o $s1
	sw	$s1, 0($s2)			# (tamanhoEntrada) = $s1
	la	$s0, Vetor_Entrada		# $s0 = &(Vetor_Entrada)
	
	la	$a0, TXT_COM_NOVALINHA		# $a0 = "\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_PRC_LEITURA		# $a0 = "Insira os valores para o vetor de entrada:\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	add	$t0, $zero, $zero		# $t0 (i) = 0
	
for_preencher_ent_inicio:
	beq	$t0, $s1, for_preencher_ent_fim	# Pula para o fim se i = tamanhoEntrada
	sll	$t1, $t0, 2			# $t1 = $t0 (i) * 4
	add	$t1, $s0, $t1			# $t1 += &Vetor_Entrada
	
	la	$a0, TXT_VET_ENT_INICIO		# $a0 = "Vetor_Entrada["
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	add	$a0, $zero, $t0			# $a0 = $t0 (i)
	addi	$v0, $zero, 1			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_VET_FINAL		# $a0 = "]: "
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	addi	$v0, $zero, 5			# $v0 = read_int
	syscall					# CHAMADA DE SISTEMA (read_int)
	
	sw	$v0, 0($t1)			# Vetor_Entrada[i] = $v0
	
	addi	$t0, $t0, 1			# [i++] $t0 += 1
	j	for_preencher_ent_inicio	# Pula para o início do for.
for_preencher_ent_fim:
	
	la	$a0, TXT_COM_NOVALINHA		# $a0 = "\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_PRC_SEPARAR		# $a0 = "Separando valores numéricos.\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	la	$s2, Vetor_Pares		# $s2 = &(Vetor_Pares)
	la	$s3, tamanhoPares		# $s3 = &(tamanhoPares)
	lw	$s4, 0($s3)			# $s4 = (tamanhoPares)
	
	la	$s5, Vetor_Impares		# $s5 = &(Vetor_Impares)
	la	$s6, tamanhoImpares		# $s6 = &(tamanhoImpares)
	lw	$s7, 0($s6)			# $s7 = (tamanhoImpares)
	
	add	$t0, $zero, $zero		# $t0 (i) = 0

for_separar_inicio:
	beq	$t0, $s1, for_separar_fim	# Pular para o final se i = tamanhoEntrada
	
	sll	$t1, $t0, 2			# $t1 = $t0 (i) * 4
	add	$t1, $s0, $t1			# $t1 += &(Vetor_Entrada)
	lw	$t1, 0($t1)			# $t1 = Vetor_Entrada[i]
	
	andi	$t2, $t1, 1			# $t2 = $t1 & 0x00000001
	bne	$t2, $zero, if_valor_impar	# Desvia se é impar
	
	sll	$t2, $s4, 2			# $t2 = (tamanhoPares) * 4
	add	$t2, $s2, $t2			# $t2 += &(Vetor_Pares)
	sw	$t1, 0($t2)			# Vetor_Pares[tamanhoPares] = $t1 (Vetor_Entrada[i])
	addi	$s4, $s4, 1			# $s4 (tamanhoPares) += 1
	j	if_valor_impar_fim
	
if_valor_impar:
	sll	$t2, $s7, 2			# $t2 = (tamanhoImpares) * 4
	add	$t2, $s5, $t2			# $t2 += &(Vetor_Impares)
	sw	$t1, 0($t2)			# Vetor_Impares[tamanhoImpares] = $t1 (Vetor_Entrada[i])
	addi	$s7, $s7, 1			# $s7 (tamanhoImpares) += 1
if_valor_impar_fim:

	addi	$t0, $t0, 1			# [i++] $t0 += 1
	j	for_separar_inicio		# Pula para o início do for
for_separar_fim:
	
	sw	$s4, 0($s3)			# (tamanhoPares) = $s4
	sw	$s7, 0($s6)			# (tamanhoImpares) = $s7
	
	la	$a0, TXT_PRC_SEPARAR_FIM	# $a0 = "Separação concluída.\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_COM_NOVALINHA		# $a0 = "\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_PRC_EXIBIR		# $a0 = "Exibindo vetores...\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_COM_NOVALINHA		# $a0 = "\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	bne	$s4, $zero, exibir_par_inicio	# Pula para exibição se há valores em vetor PAR.
	la	$a0, TXT_PRC_EXIBIR_NPAR	# $a0 = "Não há números pares!\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	j	exibir_par_fim
	
exibir_par_inicio:
	la	$a0, TXT_PRC_EXIBIR_PAR		# $a0 = "Vetor de números pares:\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)

	add	$t0, $zero, $zero		# $t0 (i) = 0
	
for_exibir_pares_inicio:
	beq	$t0, $s4, for_exibir_pares_fim	# Pular se i = tamanhoPares
	
	sll	$t1, $t0, 2			# $t1 = $to (i) * 4
	add	$t1, $t1, $s2			# $t1 = $t1 (i*4) + &(Vetor_Pares)
	
	la	$a0, TXT_VET_PAR_INICIO		# $a0 = "Vetor_Pares["
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	add	$a0, $zero, $t0			# $a0 = $t0 (i)
	addi	$v0, $zero, 1			# $v0 = print_int
	syscall					# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_VET_FINAL		# $a0 = "]: "
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	lw	$a0, 0($t1)			# $a0 = vet[i]
	addi	$v0, $zero, 1			# $v0 = print_int
	syscall					# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_COM_NOVALINHA		# $a0 = "\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	addi	$t0, $t0, 1
	j	for_exibir_pares_inicio		# Volta ao início do for
for_exibir_pares_fim:
exibir_par_fim:

	la	$a0, TXT_COM_NOVALINHA		# $a0 = "\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	bne	$s7, $zero, exibir_impar_inicio	# Pula para exibição se ímpares tiver elementos
	la	$a0, TXT_PRC_EXIBIR_NIMP	# $a0 = "Não há valores ímpares!\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	j	exibir_impar_fim		# não exibe vetor
	
exibir_impar_inicio:
	la	$a0, TXT_PRC_EXIBIR_IMP		# $a0 = "Vetor de números ímpares:\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)

	add	$t0, $zero, $zero		# $t0 (i) = 0
	
for_exibir_impares_inicio:
	beq	$t0, $s7, for_exibir_impares_fim# Pular se i = tamanhoImpares
	
	sll	$t1, $t0, 2			# $t1 = $to (i) * 4
	add	$t1, $t1, $s5			# $t1 = $t1 (i*4) + &(Vetor_Impares)
	
	la	$a0, TXT_VET_IMP_INICIO		# $a0 = "Vetor_Impares["
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	add	$a0, $zero, $t0			# $a0 = $t0 (i)
	addi	$v0, $zero, 1			# $v0 = print_int
	syscall					# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_VET_FINAL		# $a0 = "]: "
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	lw	$a0, 0($t1)			# $a0 = vet[i]
	addi	$v0, $zero, 1			# $v0 = print_int
	syscall					# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_COM_NOVALINHA		# $a0 = "\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	addi	$t0, $t0, 1
	j	for_exibir_impares_inicio	# Volta ao início do for
for_exibir_impares_fim:
exibir_impar_fim:
	
	addi	$v0, $zero, 10			# $v0 = fim_programa
	syscall
