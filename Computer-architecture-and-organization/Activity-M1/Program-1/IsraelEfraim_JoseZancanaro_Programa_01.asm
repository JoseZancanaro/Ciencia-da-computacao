# Disciplina: CC4189 –Arquitetura e Organização de Computadores
# Atividade: Avaliação 01–Programação em Linguagem de Montagem
# Programa 01
# Grupo: - Israel Efraim Oliveira
#        - José Carlos Zancanaro

	.data
	#Textos para impressão
	TXT_SLC_TAMANHO:	.asciiz "Entre com o tamanho do vetor (mín. = 2, máx = 8): "
	TXT_SLC_INVALIDO:	.asciiz "Tamanho inválido\n\n"
	TXT_EXB_VETOR_INICIO:	.asciiz "Vetor["
	TXT_EXB_VETOR_FINAL:	.asciiz "] = "
	TXT_PRC_LEITURA:	.asciiz "Insira os valores para o vetor:\n"
	TXT_PRC_EXIBIR:		.asciiz "Exibindo vetor ordenado...\n"
	TXT_PRC_BUBBLE:		.asciiz "Realizando bubble sort.\n"
	TXT_PRC_BUBBLE_FIM:	.asciiz "Bubblesort concluído.\n"
	TXT_COM_NOVALINHA:	.asciiz "\n"
	
	#Variáveis para interação
	vetor:		.word 0, 0, 0, 0, 0, 0, 0, 0
	tamanhoMin:	.word 2
	tamanhoMax:	.word 8
	tamanhoVet:	.word
	
	.text
main:
	la	$s0, tamanhoMin			# $s0 = &(tamanhoMin)
	lw	$s0, 0($s0)			# $s0 = (tamanhoMin)
	la	$s1, tamanhoMax			# $s1 = &(tamanhoMax)
	lw	$s1, 0($s1)			# $s1 = (tamanhoMax)
	la	$s2, tamanhoVet			# $s2 = &(tamanhoVet)
	
do_while_tamVet_inicio:
	la	$a0, TXT_SLC_TAMANHO		# $a0 = "Entre com o tamanho do vetor (mín. = 2, máx = 8): "
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	addi	$v0, $zero, 5			# $v0 = read_int
	syscall					# CHAMADA DE SISTEMA (read_int)
	
	add	$s3, $zero, $v0			# $s3 (tamanhoMin) = $v0
	slt	$t0, $s3, $s0			# $t0 = $s3 < $s0 ? 1 : 0	
	sgt	$t1, $s3, $s1			# $t1 = $s3 > $s1 ? 1 : 0
	add	$t2, $t0, $t1			# $t2 = $t0 + $t1
	
	beq	$t2, $zero, do_while_tamVet_fim	# Pula pro final se o input for > 1 e < 9.
	
	la	$a0, TXT_SLC_INVALIDO		# $a0 = "Tamanho inválido\n\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	j	do_while_tamVet_inicio
do_while_tamVet_fim:
	
	sw	$s3, 0($s2)			# (tamanhoVet) = $s3
	la	$s4, vetor			# $s4 = &vetor
	
	la	$a0, TXT_COM_NOVALINHA		# $a0 = "\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_PRC_LEITURA		# $a0 = "Insira os valores para o vetor:\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADE DE SISTEMA (print_string)
	
	add	$t0, $zero, $zero		# $t0 (i) = 0
	
for_preencher_inicio:
	beq	$t0, $s3, for_preencher_fim	# Pular se i = tamanhoVet (preenchido pelo usuário)
	
	sll	$t1, $t0, 2			# $t1 = $to (i) * 4
	add	$t1, $t1, $s4			# $t1 = $t1 (i*4) + &vetor
	
	la	$a0, TXT_EXB_VETOR_INICIO	# $a0 = "Vetor["
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	add	$a0, $zero, $t0			# $a0 = $t0 (i)
	addi	$v0, $zero, 1			# $v0 = print_int
	syscall					# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_EXB_VETOR_FINAL	# $a0 = "] = "
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	addi	$v0, $zero, 5			# $v0 = read_int
	syscall					# CHAMADA DE SISTEMA (read_int)
	
	sw	$v0, 0($t1)			# vet[i] = $v0
	
	addi	$t0, $t0, 1
	j	for_preencher_inicio		# Volta ao início do for
for_preencher_fim:
	
	la	$a0, TXT_COM_NOVALINHA		# $a0 = "\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_PRC_BUBBLE		# $a0 = "Realizando bubble sort.\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	add	$t0, $zero, $zero		# $t0 (i) = 0
	
for_bubble_extno_inicio:
	beq	$t0, $s3, for_bubble_extno_fim	# Pula pro fim se i = tamanhoVet
	
	add	$t1, $zero, $zero		# $t1 (j) = 0
	sub	$t2, $s3, $t0			# $t2 = $s3 (tamanhoVet) - $t0 (i)
	addi	$t2, $t2, -1			# $t2 -= 1
	
for_bubble_intno_inicio:
	beq	$t1, $t2, for_bubble_intno_fim	# Pula pro fim se j = tamanhoVet - i - 1
	
	sll	$t3, $t1, 2			# $t3 (&vet[j]) = $t1 (j) * 4
	add	$t3, $s4, $t3			# $t3 (&vet[j]) += &vetor
	
	addi	$t4, $t1, 1			# $t4 = j+1;
	sll	$t4, $t4, 2			# $t4 (&vet[j+1]) = $t1 * 4
	add	$t4, $s4, $t4			# $t4 (&vet[j+1]) += &vetor
	
	lw	$t5, 0($t3)			# $t5 = vet[j]
	lw	$t6, 0($t4)			# $t6 = vet[j+1]
	slt	$t7, $t6, $t5			# $t7 = vet[j+1] < vet [j] ? 1 : 0
	
	beq	$t7, $zero, bubble_nao_ordenar	# Não ordena se vet[j+1] > vet[j]
	sw	$t6, 0($t3)			# $t6 (vet[j]) = vet[j+1]
	sw	$t5, 0($t4)			# $t5 (vet[j+1]) = vet[j]
bubble_nao_ordenar:

	addi	$t1, $t1, 1			# [j++] $t1 = $t1 + 1
	j	for_bubble_intno_inicio		# Pula para o inicio do for interno
for_bubble_intno_fim:

	addi	$t0, $t0, 1			# [i++] $t0 = $t0 + 1
	j	for_bubble_extno_inicio		# Pula para o inicio do for externo
for_bubble_extno_fim:

	la	$a0, TXT_PRC_BUBBLE_FIM		# $a0 = "Bubblesort concluído.\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_COM_NOVALINHA		# $a0 = "\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	la	$a0, TXT_PRC_EXIBIR		# $a0 = "Exibindo vetor ordenado...\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	add	$t0, $zero, $zero		# $t0 (i) = 0
	
for_exibir_inicio:
	beq	$t0, $s3, for_exibir_fim	# Pular se i = tamanhoVet (preenchido pelo usuário)
	
	sll	$t1, $t0, 2			# $t1 = $to (i) * 4
	add	$t1, $t1, $s4			# $t1 = $t1 (i*4) + &vetor
	
	la	$a0, TXT_EXB_VETOR_INICIO	# $a0 = "Vetor["
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	add	$a0, $zero, $t0			# $a0 = $t0 (i)
	addi	$v0, $zero, 1			# $v0 = print_int
	syscall					# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_EXB_VETOR_FINAL	# $a0 = "] = "
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	lw	$a0, 0($t1)			# $a0 = vet[i]
	addi	$v0, $zero, 1			# $v0 = print_int
	syscall					# CHAMADA DE SISTEMA (print_int)
	
	la	$a0, TXT_COM_NOVALINHA		# $a0 = "\n"
	addi	$v0, $zero, 4			# $v0 = print_string
	syscall					# CHAMADA DE SISTEMA (print_string)
	
	addi	$t0, $t0, 1
	j	for_exibir_inicio		# Volta ao início do for
for_exibir_fim:

	addi	$v0, $zero, 10			# $v0 = fim_programa
	syscall					# CHAMADA DE SISTEMA (fim_programa)
